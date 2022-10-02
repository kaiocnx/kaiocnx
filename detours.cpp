//////////////////////////////////////////////////////////////////////////////
//
//  Core Detours Functionality (detours.cpp of detours.lib)
//
//  Microsoft Research Detours Package, Version 3.0 Build_316.
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
#include "Library.h"
#include <windows.h>

#if (_MSC_VER < 1299)
#pragma warning(disable: 4710)
#endif

//#define DETOUR_DEBUG 1

#if defined(DETOURS_X86)
#elif defined(DETOURS_X64)
#elif defined(DETOURS_IA64)
#elif defined(DETOURS_ARM)
#else
#error Must define one of DETOURS_X86, DETOURS_X64, DETOURS_IA64, or DETOURS_ARM
#endif

#if !defined(DETOURS_32BIT) && !defined(DETOURS_64BIT)
#error Must define one of DETOURS_32BIT or DETOURS_64BIT
#endif

//////////////////////////////////////////////////////////////////////////////
//
struct _DETOUR_ALIGN
{
	BYTE    obTarget : 3;
	BYTE    obTrampoline : 5;
};

C_ASSERT(sizeof(_DETOUR_ALIGN) == 1);

//////////////////////////////////////////////////////////////////////////////
//
static bool detour_is_imported(PBYTE pbCode, PBYTE pbAddress)
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((PVOID)pbCode, &mbi, sizeof(mbi));
	__try
	{
		PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)mbi.AllocationBase;
		if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		{
			return false;
		}

		PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((PBYTE)pDosHeader +
			pDosHeader->e_lfanew);
		if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
		{
			return false;
		}

		if (pbAddress >= ((PBYTE)pDosHeader +
			pNtHeader->OptionalHeader
			.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress) &&
			pbAddress < ((PBYTE)pDosHeader +
				pNtHeader->OptionalHeader
				.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress +
				pNtHeader->OptionalHeader
				.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size))
		{
			return true;
		}
		return false;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}
}

///////////////////////////////////////////////////////////////////////// X86.
//
#ifdef DETOURS_X86

struct _DETOUR_TRAMPOLINE
{
	BYTE            rbCode[30];     // target code + jmp to pbRemain
	BYTE            cbCode;         // size of moved target code.
	BYTE            cbCodeBreak;    // padding to make debugging easier.
	BYTE            rbRestore[22];  // original target code.
	BYTE            cbRestore;      // size of original target code.
	BYTE            cbRestoreBreak; // padding to make debugging easier.
	_DETOUR_ALIGN   rAlign[8];      // instruction alignment array.
	PBYTE           pbRemain;       // first instruction after moved code. [free list]
	PBYTE           pbDetour;       // first instruction of detour function.
};

C_ASSERT(sizeof(_DETOUR_TRAMPOLINE) == 72);

enum
{
	SIZE_OF_JMP = 5
};

inline PBYTE detour_gen_jmp_immediate(PBYTE pbCode, PBYTE pbJmpVal)
{
	PBYTE pbJmpSrc = pbCode + 5;
	*pbCode++ = 0xE9;   // jmp +imm32
	*((INT32*&)pbCode)++ = (INT32)(pbJmpVal - pbJmpSrc);
	return pbCode;
}

inline PBYTE detour_gen_jmp_indirect(PBYTE pbCode, PBYTE *ppbJmpVal)
{
	PBYTE pbJmpSrc = pbCode + 6;
	*pbCode++ = 0xff;   // jmp [+imm32]
	*pbCode++ = 0x25;
	*((INT32*&)pbCode)++ = (INT32)((PBYTE)ppbJmpVal - pbJmpSrc);
	return pbCode;
}

inline PBYTE detour_gen_brk(PBYTE pbCode, PBYTE pbLimit)
{
	while (pbCode < pbLimit)
	{
		*pbCode++ = 0xcc;   // brk;
	}
	return pbCode;
}

inline PBYTE detour_skip_jmp(PBYTE pbCode, PVOID *ppGlobals)
{
	if (pbCode == NULL)
	{
		return NULL;
	}
	if (ppGlobals != NULL)
	{
		*ppGlobals = NULL;
	}

	// First, skip over the import vector if there is one.
	if (pbCode[0] == 0xff && pbCode[1] == 0x25)
	{   // jmp [imm32]
// Looks like an import alias jump, then get the code it points to.
		PBYTE pbTarget = *(PBYTE *)&pbCode[2];
		if (detour_is_imported(pbCode, pbTarget))
		{
			PBYTE pbNew = *(PBYTE *)pbTarget;
			DETOUR_TRACE(("%p->%p: skipped over import table.\n", pbCode, pbNew));
			pbCode = pbNew;
		}
	}

	// Then, skip over a patch jump
	if (pbCode[0] == 0xeb)
	{   // jmp +imm8
		PBYTE pbNew = pbCode + 2 + *(CHAR *)&pbCode[1];
		DETOUR_TRACE(("%p->%p: skipped over short jump.\n", pbCode, pbNew));
		pbCode = pbNew;

		// First, skip over the import vector if there is one.
		if (pbCode[0] == 0xff && pbCode[1] == 0x25)
		{   // jmp [imm32]
// Looks like an import alias jump, then get the code it points to.
			PBYTE pbTarget = *(PBYTE *)&pbCode[2];
			if (detour_is_imported(pbCode, pbTarget))
			{
				PBYTE pbNew = *(PBYTE *)pbTarget;
				DETOUR_TRACE(("%p->%p: skipped over import table.\n", pbCode, pbNew));
				pbCode = pbNew;
			}
		}
		// Finally, skip over a long jump if it is the target of the patch jump.
		else if (pbCode[0] == 0xe9)
		{   // jmp +imm32
			PBYTE pbNew = pbCode + 5 + *(INT32 *)&pbCode[1];
			DETOUR_TRACE(("%p->%p: skipped over long jump.\n", pbCode, pbNew));
			pbCode = pbNew;
		}
	}
	return pbCode;
}

inline BOOL detour_does_code_end_function(PBYTE pbCode)
{
	if (pbCode[0] == 0xeb ||    // jmp +imm8
		pbCode[0] == 0xe9 ||    // jmp +imm32
		pbCode[0] == 0xe0 ||    // jmp eax
		pbCode[0] == 0xc2 ||    // ret +imm8
		pbCode[0] == 0xc3 ||    // ret
		pbCode[0] == 0xcc)
	{    // brk
		return TRUE;
	}
	else if (pbCode[0] == 0xff && pbCode[1] == 0x25)
	{  // jmp [+imm32]
		return TRUE;
	}
	else if ((pbCode[0] == 0x26 ||      // jmp es:
		pbCode[0] == 0x2e ||      // jmp cs:
		pbCode[0] == 0x36 ||      // jmp ss:
		pbCode[0] == 0xe3 ||      // jmp ds:
		pbCode[0] == 0x64 ||      // jmp fs:
		pbCode[0] == 0x65) &&     // jmp gs:
		pbCode[1] == 0xff &&       // jmp [+imm32]
		pbCode[2] == 0x25)
	{
		return TRUE;
	}
	return FALSE;
}

inline ULONG detour_is_code_filler(PBYTE pbCode)
{
	if (pbCode[0] == 0x90)
	{ // nop
		return 1;
	}
	return 0;
}

#endif // DETOURS_X86

///////////////////////////////////////////////////////////////////////// X64.
//
#ifdef DETOURS_X64
#error Feature not supported in this release.

#endif // DETOURS_X64

//////////////////////////////////////////////////////////////////////// IA64.
//
#ifdef DETOURS_IA64
#error Feature not supported in this release.

#endif // DETOURS_IA64

#ifdef DETOURS_ARM
#error Feature not supported in this release.

#endif // DETOURS_ARM

//////////////////////////////////////////////// Trampoline Memory Management.
//
struct DETOUR_REGION
{
	ULONG               dwSignature;
	DETOUR_REGION *     pNext;  // Next region in list of regions.
	DETOUR_TRAMPOLINE * pFree;  // List of free trampolines in this region.
};
typedef DETOUR_REGION * PDETOUR_REGION;

const ULONG DETOUR_REGION_SIGNATURE = 'Rrtd';
const ULONG DETOUR_REGION_SIZE = 0x10000;
const ULONG DETOUR_TRAMPOLINES_PER_REGION = (DETOUR_REGION_SIZE
	/ sizeof(DETOUR_TRAMPOLINE)) - 1;
static PDETOUR_REGION s_pRegions = NULL;            // List of all regions.
static PDETOUR_REGION s_pRegion = NULL;             // Default region.

static void detour_writable_trampoline_regions()
{
	// Mark all of the regions as writable.
	for (PDETOUR_REGION pRegion = s_pRegions; pRegion != NULL; pRegion = pRegion->pNext)
	{
		DWORD dwOld;
		VirtualProtect(pRegion, DETOUR_REGION_SIZE, PAGE_EXECUTE_READWRITE, &dwOld);
	}
}

static void detour_runnable_trampoline_regions()
{
	HANDLE hProcess = GetCurrentProcess();

	// Mark all of the regions as executable.
	for (PDETOUR_REGION pRegion = s_pRegions; pRegion != NULL; pRegion = pRegion->pNext)
	{
		DWORD dwOld;
		VirtualProtect(pRegion, DETOUR_REGION_SIZE, PAGE_EXECUTE_READ, &dwOld);
		FlushInstructionCache(hProcess, pRegion, DETOUR_REGION_SIZE);
	}
}

static PBYTE detour_alloc_round_down_to_region(PBYTE pbTry)
{
	// WinXP64 returns free areas that aren't REGION aligned to 32-bit applications.
	ULONG_PTR extra = ((ULONG_PTR)pbTry) & (DETOUR_REGION_SIZE - 1);
	if (extra != 0)
	{
		pbTry -= extra;
	}
	return pbTry;
}

static PBYTE detour_alloc_round_up_to_region(PBYTE pbTry)
{
	// WinXP64 returns free areas that aren't REGION aligned to 32-bit applications.
	ULONG_PTR extra = ((ULONG_PTR)pbTry) & (DETOUR_REGION_SIZE - 1);
	if (extra != 0)
	{
		ULONG_PTR adjust = DETOUR_REGION_SIZE - extra;
		pbTry += adjust;
	}
	return pbTry;
}

// Starting at pbLo, try to allocate a memory region, continue until pbHi.

static PVOID detour_alloc_region_from_lo(PBYTE pbLo, PBYTE pbHi)
{
	PBYTE pbTry = detour_alloc_round_up_to_region(pbLo);

	DETOUR_TRACE((" Looking for free region in %p..%p from %p:\n", pbLo, pbHi, pbTry));

	for (; pbTry < pbHi;)
	{
		MEMORY_BASIC_INFORMATION mbi;

		if (pbTry >= (PBYTE)(ULONG_PTR)0x50000000 &&
			pbTry <= (PBYTE)(ULONG_PTR)0x80000000)
		{
			// Skip region reserved for system DLLs.
			pbTry = (PBYTE)(ULONG_PTR)(0x80000000 + DETOUR_REGION_SIZE);
			continue;
		}

		ZeroMemory(&mbi, sizeof(mbi));
		if (!VirtualQuery(pbTry, &mbi, sizeof(mbi)))
		{
			break;
		}

		DETOUR_TRACE(("  Try %p => %p..%p %6x\n",
			pbTry,
			mbi.BaseAddress,
			(PBYTE)mbi.BaseAddress + mbi.RegionSize - 1,
			mbi.State));

		if (mbi.State == MEM_FREE && mbi.RegionSize >= DETOUR_REGION_SIZE)
		{
			PVOID pv = VirtualAlloc(pbTry,
				DETOUR_REGION_SIZE,
				MEM_COMMIT | MEM_RESERVE,
				PAGE_EXECUTE_READWRITE);
			if (pv != NULL)
			{
				return pv;
			}
			pbTry += DETOUR_REGION_SIZE;
		}
		else
		{
			pbTry = detour_alloc_round_up_to_region((PBYTE)mbi.BaseAddress + mbi.RegionSize);
		}
	}
	return NULL;
}

// Starting at pbHi, try to allocate a memory region, continue until pbLo.

static PVOID detour_alloc_region_from_hi(PBYTE pbLo, PBYTE pbHi)
{
	PBYTE pbTry = detour_alloc_round_down_to_region(pbHi - DETOUR_REGION_SIZE);

	DETOUR_TRACE((" Looking for free region in %p..%p from %p:\n", pbLo, pbHi, pbTry));

	for (; pbTry > pbLo;)
	{
		MEMORY_BASIC_INFORMATION mbi;

		DETOUR_TRACE(("  Try %p\n", pbTry));
		if (pbTry >= (PBYTE)(ULONG_PTR)0x50000000 &&
			pbTry <= (PBYTE)(ULONG_PTR)0x80000000)
		{
			// Skip region reserved for system DLLs.
			pbTry = (PBYTE)(ULONG_PTR)(0x50000000 - DETOUR_REGION_SIZE);
			continue;
		}

		ZeroMemory(&mbi, sizeof(mbi));
		if (!VirtualQuery(pbTry, &mbi, sizeof(mbi)))
		{
			break;
		}

		DETOUR_TRACE(("  Try %p => %p..%p %6x\n",
			pbTry,
			mbi.BaseAddress,
			(PBYTE)mbi.BaseAddress + mbi.RegionSize - 1,
			mbi.State));

		if (mbi.State == MEM_FREE && mbi.RegionSize >= DETOUR_REGION_SIZE)
		{
			PVOID pv = VirtualAlloc(pbTry,
				DETOUR_REGION_SIZE,
				MEM_COMMIT | MEM_RESERVE,
				PAGE_EXECUTE_READWRITE);
			if (pv != NULL)
			{
				return pv;
			}
			pbTry -= DETOUR_REGION_SIZE;
		}
		else
		{
			pbTry = detour_alloc_round_down_to_region((PBYTE)mbi.AllocationBase
				- DETOUR_REGION_SIZE);
		}
	}
	return NULL;
}

static PDETOUR_TRAMPOLINE detour_alloc_trampoline(PBYTE pbTarget)
{
	// We have to place trampolines within +/- 2GB of target.

	PDETOUR_TRAMPOLINE pLo = (PDETOUR_TRAMPOLINE)
		((pbTarget > (PBYTE)0x7ff80000)
			? pbTarget - 0x7ff80000 : (PBYTE)(ULONG_PTR)DETOUR_REGION_SIZE);
	PDETOUR_TRAMPOLINE pHi = (PDETOUR_TRAMPOLINE)
		((pbTarget < (PBYTE)0xffffffff80000000)
			? pbTarget + 0x7ff80000 : (PBYTE)0xfffffffffff80000);
	DETOUR_TRACE(("[%p..%p..%p]\n", pLo, pbTarget, pHi));

	PDETOUR_TRAMPOLINE pTrampoline = NULL;

	// Insure that there is a default region.
	if (s_pRegion == NULL && s_pRegions != NULL)
	{
		s_pRegion = s_pRegions;
	}

	// First check the default region for an valid free block.
	if (s_pRegion != NULL && s_pRegion->pFree != NULL &&
		s_pRegion->pFree >= pLo && s_pRegion->pFree <= pHi)
	{
	found_region:
		pTrampoline = s_pRegion->pFree;
		// do a last sanity check on region.
		if (pTrampoline < pLo || pTrampoline > pHi)
		{
			return NULL;
		}
		s_pRegion->pFree = (PDETOUR_TRAMPOLINE)pTrampoline->pbRemain;
		memset(pTrampoline, 0xcc, sizeof(*pTrampoline));
		return pTrampoline;
	}

	// Then check the existing regions for a valid free block.
	for (s_pRegion = s_pRegions; s_pRegion != NULL; s_pRegion = s_pRegion->pNext)
	{
		if (s_pRegion != NULL && s_pRegion->pFree != NULL &&
			s_pRegion->pFree >= pLo && s_pRegion->pFree <= pHi)
		{
			goto found_region;
		}
	}

	// We need to allocate a new region.

	// Round pbTarget down to 64KB block.
	pbTarget = pbTarget - (PtrToUlong(pbTarget) & 0xffff);

	PVOID pbTry = NULL;

	// Try looking 1GB below or lower.
	if (pbTry == NULL && pbTarget > (PBYTE)0x40000000)
	{
		pbTry = detour_alloc_region_from_hi((PBYTE)pLo, pbTarget - 0x40000000);
	}
	// Try looking 1GB above or higher.
	if (pbTry == NULL && pbTarget < (PBYTE)0xffffffff40000000)
	{
		pbTry = detour_alloc_region_from_lo(pbTarget + 0x40000000, (PBYTE)pHi);
	}
	// Try looking 1GB below or higher.
	if (pbTry == NULL && pbTarget > (PBYTE)0x40000000)
	{
		pbTry = detour_alloc_region_from_lo(pbTarget - 0x40000000, pbTarget);
	}
	// Try looking 1GB above or lower.
	if (pbTry == NULL && pbTarget < (PBYTE)0xffffffff40000000)
	{
		pbTry = detour_alloc_region_from_hi(pbTarget, pbTarget + 0x40000000);
	}
	// Try anything below.
	if (pbTry == NULL)
	{
		pbTry = detour_alloc_region_from_hi((PBYTE)pLo, pbTarget);
	}
	// try anything above.
	if (pbTry == NULL)
	{
		pbTry = detour_alloc_region_from_lo(pbTarget, (PBYTE)pHi);
	}

	if (pbTry != NULL)
	{
		s_pRegion = (DETOUR_REGION*)pbTry;
		s_pRegion->dwSignature = DETOUR_REGION_SIGNATURE;
		s_pRegion->pFree = NULL;
		s_pRegion->pNext = s_pRegions;
		s_pRegions = s_pRegion;
		DETOUR_TRACE(("  Allocated region %p..%p\n\n",
			s_pRegion, ((PBYTE)s_pRegion) + DETOUR_REGION_SIZE - 1));

		// Put everything but the first trampoline on the free list.
		PBYTE pFree = NULL;
		pTrampoline = ((PDETOUR_TRAMPOLINE)s_pRegion) + 1;
		for (int i = DETOUR_TRAMPOLINES_PER_REGION - 1; i > 1; i--)
		{
			pTrampoline[i].pbRemain = pFree;
			pFree = (PBYTE)&pTrampoline[i];
		}
		s_pRegion->pFree = (PDETOUR_TRAMPOLINE)pFree;
		goto found_region;
	}

	DETOUR_TRACE(("Couldn't find available memory region!\n"));
	return NULL;
}

static void detour_free_trampoline(PDETOUR_TRAMPOLINE pTrampoline)
{
	PDETOUR_REGION pRegion = (PDETOUR_REGION)
		((ULONG_PTR)pTrampoline & ~(ULONG_PTR)0xffff);

	memset(pTrampoline, 0, sizeof(*pTrampoline));
	pTrampoline->pbRemain = (PBYTE)pRegion->pFree;
	pRegion->pFree = pTrampoline;
}

static BOOL detour_is_region_empty(PDETOUR_REGION pRegion)
{
	// Stop if the region isn't a region (this would be bad).
	if (pRegion->dwSignature != DETOUR_REGION_SIGNATURE)
	{
		return FALSE;
	}

	PBYTE pbRegionBeg = (PBYTE)pRegion;
	PBYTE pbRegionLim = pbRegionBeg + DETOUR_REGION_SIZE;

	// Stop if any of the trampolines aren't free.
	PDETOUR_TRAMPOLINE pTrampoline = ((PDETOUR_TRAMPOLINE)pRegion) + 1;
	for (int i = 0; i < DETOUR_TRAMPOLINES_PER_REGION; i++)
	{
		if (pTrampoline[i].pbRemain != NULL &&
			(pTrampoline[i].pbRemain < pbRegionBeg ||
				pTrampoline[i].pbRemain >= pbRegionLim))
		{
			return FALSE;
		}
	}

	// OK, the region is empty.
	return TRUE;
}

static void detour_free_unused_trampoline_regions()
{
	PDETOUR_REGION *ppRegionBase = &s_pRegions;
	PDETOUR_REGION pRegion = s_pRegions;

	while (pRegion != NULL)
	{
		if (detour_is_region_empty(pRegion))
		{
			*ppRegionBase = pRegion->pNext;

			VirtualFree(pRegion, 0, MEM_RELEASE);
			s_pRegion = NULL;
		}
		else
		{
			ppRegionBase = &pRegion->pNext;
		}
		pRegion = *ppRegionBase;
	}
}

///////////////////////////////////////////////////////// Transaction Structs.
//
struct DetourThread
{
	DetourThread *      pNext;
	HANDLE              hThread;
};

struct DetourOperation
{
	DetourOperation *   pNext;
	BOOL                fIsRemove;
	PBYTE *             ppbPointer;
	PBYTE               pbTarget;
	PDETOUR_TRAMPOLINE  pTrampoline;
	ULONG               dwPerm;
};

static BOOL                 s_fIgnoreTooSmall = FALSE;
static BOOL                 s_fRetainRegions = FALSE;

static LONG                 s_nPendingThreadId = 0; // Thread owning pending transaction.
static LONG                 s_nPendingError = NO_ERROR;
static PVOID *              s_ppPendingError = NULL;
static DetourThread *       s_pPendingThreads = NULL;
static DetourOperation *    s_pPendingOperations = NULL;

//////////////////////////////////////////////////////////////////////////////
//
PVOID WINAPI DetourCodeFromPointer(PVOID pPointer, PVOID *ppGlobals)
{
	return detour_skip_jmp((PBYTE)pPointer, ppGlobals);
}

//////////////////////////////////////////////////////////// Transaction APIs.
//
BOOL WINAPI DetourSetIgnoreTooSmall(BOOL fIgnore)
{
	BOOL fPrevious = s_fIgnoreTooSmall;
	s_fIgnoreTooSmall = fIgnore;
	return fPrevious;
}

BOOL WINAPI DetourSetRetainRegions(BOOL fRetain)
{
	BOOL fPrevious = s_fRetainRegions;
	s_fRetainRegions = fRetain;
	return fPrevious;
}

LONG WINAPI DetourTransactionBegin()
{
	// Only one transaction is allowed at a time.
	if (s_nPendingThreadId != 0)
	{
		return ERROR_INVALID_OPERATION;
	}
	// Make sure only one thread can start a transaction.
	if (InterlockedCompareExchange(&s_nPendingThreadId, (LONG)GetCurrentThreadId(), 0) != 0)
	{
		return ERROR_INVALID_OPERATION;
	}

	s_pPendingOperations = NULL;
	s_pPendingThreads = NULL;
	s_nPendingError = NO_ERROR;
	s_ppPendingError = NULL;

	// Make sure the trampoline pages are writable.
	detour_writable_trampoline_regions();

	return NO_ERROR;
}

LONG WINAPI DetourTransactionAbort()
{
	if (s_nPendingThreadId != (LONG)GetCurrentThreadId())
	{
		return ERROR_INVALID_OPERATION;
	}

	// Restore all of the page permissions.
	for (DetourOperation *o = s_pPendingOperations; o != NULL;)
	{
		// We don't care if this fails, because the code is still accessible.
		DWORD dwOld;
		VirtualProtect(o->pbTarget, o->pTrampoline->cbRestore,
			o->dwPerm, &dwOld);

		if (!o->fIsRemove)
		{
			if (o->pTrampoline)
			{
				detour_free_trampoline(o->pTrampoline);
				o->pTrampoline = NULL;
			}
		}

		DetourOperation *n = o->pNext;
		delete o;
		o = n;
	}
	s_pPendingOperations = NULL;

	// Make sure the trampoline pages are no longer writable.
	detour_runnable_trampoline_regions();

	// Resume any suspended threads.
	for (DetourThread *t = s_pPendingThreads; t != NULL;)
	{
		// There is nothing we can do if this fails.
		ResumeThread(t->hThread);

		DetourThread *n = t->pNext;
		delete t;
		t = n;
	}
	s_pPendingThreads = NULL;
	s_nPendingThreadId = 0;

	return NO_ERROR;
}

LONG WINAPI DetourTransactionCommit()
{
	return DetourTransactionCommitEx(NULL);
}

static BYTE detour_align_from_trampoline(PDETOUR_TRAMPOLINE pTrampoline, BYTE obTrampoline)
{
	for (LONG n = 0; n < ARRAYSIZE(pTrampoline->rAlign); n++)
	{
		if (pTrampoline->rAlign[n].obTrampoline == obTrampoline)
		{
			return pTrampoline->rAlign[n].obTarget;
		}
	}
	return 0;
}

static LONG detour_align_from_target(PDETOUR_TRAMPOLINE pTrampoline, LONG obTarget)
{
	for (LONG n = 0; n < ARRAYSIZE(pTrampoline->rAlign); n++)
	{
		if (pTrampoline->rAlign[n].obTarget == obTarget)
		{
			return pTrampoline->rAlign[n].obTrampoline;
		}
	}
	return 0;
}

LONG WINAPI DetourTransactionCommitEx(PVOID **pppFailedPointer)
{
	if (pppFailedPointer != NULL)
	{
		// Used to get the last error.
		*pppFailedPointer = s_ppPendingError;
	}
	if (s_nPendingThreadId != (LONG)GetCurrentThreadId())
	{
		return ERROR_INVALID_OPERATION;
	}

	// If any of the pending operations failed, then we abort the whole transaction.
	if (s_nPendingError != NO_ERROR)
	{
		DETOUR_BREAK();
		DetourTransactionAbort();
		return s_nPendingError;
	}

	// Common variables.
	DetourOperation *o;
	DetourThread *t;
	BOOL freed = FALSE;

	// Insert or remove each of the detours.
	for (o = s_pPendingOperations; o != NULL; o = o->pNext)
	{
		if (o->fIsRemove)
		{
			CopyMemory(o->pbTarget,
				o->pTrampoline->rbRestore,
				o->pTrampoline->cbRestore);
		#ifdef DETOURS_IA64
		#error Feature not supported in this release.
		#endif // DETOURS_IA64

		#ifdef DETOURS_X86
			*o->ppbPointer = o->pbTarget;
		#endif // DETOURS_X86

		#ifdef DETOURS_X64
		#error Feature not supported in this release.
		#endif // DETOURS_X64

		#ifdef DETOURS_ARM
		#error Feature not supported in this release.
		#endif // DETOURS_ARM
		}
		else
		{
			DETOUR_TRACE(("detours: pbTramp =%p, pbRemain=%p, pbDetour=%p, cbRestore=%d\n",
				o->pTrampoline,
				o->pTrampoline->pbRemain,
				o->pTrampoline->pbDetour,
				o->pTrampoline->cbRestore));

			DETOUR_TRACE(("detours: pbTarget=%p: "
				"%02x %02x %02x %02x "
				"%02x %02x %02x %02x "
				"%02x %02x %02x %02x [before]\n",
				o->pbTarget,
				o->pbTarget[0], o->pbTarget[1], o->pbTarget[2], o->pbTarget[3],
				o->pbTarget[4], o->pbTarget[5], o->pbTarget[6], o->pbTarget[7],
				o->pbTarget[8], o->pbTarget[9], o->pbTarget[10], o->pbTarget[11]));

		#ifdef DETOURS_IA64
		#error Feature not supported in this release.

		#endif // DETOURS_IA64

		#ifdef DETOURS_X64
		#error Feature not supported in this release.

		#endif // DETOURS_X64

		#ifdef DETOURS_X86
			PBYTE pbCode = detour_gen_jmp_immediate(o->pbTarget, o->pTrampoline->pbDetour);
			pbCode = detour_gen_brk(pbCode, o->pTrampoline->pbRemain);
			*o->ppbPointer = o->pTrampoline->rbCode;
		#endif // DETOURS_X86

		#ifdef DETOURS_ARM
		#error Feature not supported in this release.

		#endif // DETOURS_ARM

			DETOUR_TRACE(("detours: pbTarget=%p: "
				"%02x %02x %02x %02x "
				"%02x %02x %02x %02x "
				"%02x %02x %02x %02x [after]\n",
				o->pbTarget,
				o->pbTarget[0], o->pbTarget[1], o->pbTarget[2], o->pbTarget[3],
				o->pbTarget[4], o->pbTarget[5], o->pbTarget[6], o->pbTarget[7],
				o->pbTarget[8], o->pbTarget[9], o->pbTarget[10], o->pbTarget[11]));

			DETOUR_TRACE(("detours: pbTramp =%p: "
				"%02x %02x %02x %02x "
				"%02x %02x %02x %02x "
				"%02x %02x %02x %02x\n",
				o->pTrampoline,
				o->pTrampoline->rbCode[0], o->pTrampoline->rbCode[1],
				o->pTrampoline->rbCode[2], o->pTrampoline->rbCode[3],
				o->pTrampoline->rbCode[4], o->pTrampoline->rbCode[5],
				o->pTrampoline->rbCode[6], o->pTrampoline->rbCode[7],
				o->pTrampoline->rbCode[8], o->pTrampoline->rbCode[9],
				o->pTrampoline->rbCode[10], o->pTrampoline->rbCode[11]));

		#ifdef DETOURS_IA64
		#error Feature not supported in this release.

		#endif // DETOURS_IA64
		}
	}

	// Update any suspended threads.
	for (t = s_pPendingThreads; t != NULL; t = t->pNext)
	{
		CONTEXT cxt;
		cxt.ContextFlags = CONTEXT_CONTROL;

	#undef DETOURS_EIP
	#undef DETOURS_EIP_TYPE

	#ifdef DETOURS_X86
	#define DETOURS_EIP         Eip
	#define DETOURS_EIP_TYPE    DWORD
	#endif // DETOURS_X86

	#ifdef DETOURS_X64
	#error Feature not supported in this release.

	#endif // DETOURS_X64

	#ifdef DETOURS_IA64
	#error Feature not supported in this release.

	#endif // DETOURS_IA64

	#ifdef DETOURS_ARM
	#error Feature not supported in this release.

	#endif // DETOURS_ARM

		if (GetThreadContext(t->hThread, &cxt))
		{
			for (DetourOperation *o = s_pPendingOperations; o != NULL; o = o->pNext)
			{
				if (o->fIsRemove)
				{
					if (cxt.DETOURS_EIP >= (DETOURS_EIP_TYPE)(ULONG_PTR)o->pTrampoline &&
						cxt.DETOURS_EIP < (DETOURS_EIP_TYPE)((ULONG_PTR)o->pTrampoline
							+ sizeof(o->pTrampoline))
						)
					{
						cxt.DETOURS_EIP = (DETOURS_EIP_TYPE)
							((ULONG_PTR)o->pbTarget
								+ detour_align_from_trampoline(o->pTrampoline,
								(BYTE)(cxt.DETOURS_EIP
									- (DETOURS_EIP_TYPE)(ULONG_PTR)
									o->pTrampoline)));

						SetThreadContext(t->hThread, &cxt);
					}
				}
				else
				{
					if (cxt.DETOURS_EIP >= (DETOURS_EIP_TYPE)(ULONG_PTR)o->pbTarget &&
						cxt.DETOURS_EIP < (DETOURS_EIP_TYPE)((ULONG_PTR)o->pbTarget
							+ o->pTrampoline->cbRestore)
						)
					{
						cxt.DETOURS_EIP = (DETOURS_EIP_TYPE)
							((ULONG_PTR)o->pTrampoline
								+ detour_align_from_target(o->pTrampoline,
								(BYTE)(cxt.DETOURS_EIP
									- (DETOURS_EIP_TYPE)(ULONG_PTR)
									o->pbTarget)));

						SetThreadContext(t->hThread, &cxt);
					}
				}
			}
		}
	#undef DETOURS_EIP
	}

	// Restore all of the page permissions and flush the icache.
	HANDLE hProcess = GetCurrentProcess();
	for (o = s_pPendingOperations; o != NULL;)
	{
		// We don't care if this fails, because the code is still accessible.
		DWORD dwOld;
		VirtualProtect(o->pbTarget, o->pTrampoline->cbRestore, o->dwPerm, &dwOld);
		FlushInstructionCache(hProcess, o->pbTarget, o->pTrampoline->cbRestore);

		if (o->fIsRemove && o->pTrampoline)
		{
			detour_free_trampoline(o->pTrampoline);
			o->pTrampoline = NULL;
			freed = true;
		}

		DetourOperation *n = o->pNext;
		delete o;
		o = n;
	}
	s_pPendingOperations = NULL;

	// Free any trampoline regions that are now unused.
	if (freed && !s_fRetainRegions)
	{
		detour_free_unused_trampoline_regions();
	}

	// Make sure the trampoline pages are no longer writable.
	detour_runnable_trampoline_regions();

	// Resume any suspended threads.
	for (t = s_pPendingThreads; t != NULL;)
	{
		// There is nothing we can do if this fails.
		ResumeThread(t->hThread);

		DetourThread *n = t->pNext;
		delete t;
		t = n;
	}
	s_pPendingThreads = NULL;
	s_nPendingThreadId = 0;

	if (pppFailedPointer != NULL)
	{
		*pppFailedPointer = s_ppPendingError;
	}

	return s_nPendingError;
}

LONG WINAPI DetourUpdateThread(HANDLE hThread)
{
	LONG error;

	// If any of the pending operations failed, then we don't need to do this.
	if (s_nPendingError != NO_ERROR)
	{
		return s_nPendingError;
	}

	// Silently (and safely) drop any attempt to suspend our own thread.
	if (hThread == GetCurrentThread())
	{
		return NO_ERROR;
	}

	DetourThread *t = new DetourThread;
	if (t == NULL)
	{
		error = ERROR_NOT_ENOUGH_MEMORY;
	fail:
		if (t != NULL)
		{
			delete t;
			t = NULL;
		}
		s_nPendingError = error;
		s_ppPendingError = NULL;
		DETOUR_BREAK();
		return error;
	}

	if (SuspendThread(hThread) == (DWORD)-1)
	{
		error = GetLastError();
		DETOUR_BREAK();
		goto fail;
	}

	t->hThread = hThread;
	t->pNext = s_pPendingThreads;
	s_pPendingThreads = t;

	return NO_ERROR;
}

///////////////////////////////////////////////////////////// Transacted APIs.
//
LONG WINAPI DetourAttach(PVOID *ppPointer,
	PVOID pDetour)
{
	return DetourAttachEx(ppPointer, pDetour, NULL, NULL, NULL);
}

LONG WINAPI DetourAttachEx(PVOID *ppPointer,
	PVOID pDetour,
	PDETOUR_TRAMPOLINE *ppRealTrampoline,
	PVOID *ppRealTarget,
	PVOID *ppRealDetour)
{
	LONG error = NO_ERROR;

	if (ppRealTrampoline != NULL)
	{
		*ppRealTrampoline = NULL;
	}
	if (ppRealTarget != NULL)
	{
		*ppRealTarget = NULL;
	}
	if (ppRealDetour != NULL)
	{
		*ppRealDetour = NULL;
	}

	if (s_nPendingThreadId != (LONG)GetCurrentThreadId())
	{
		DETOUR_TRACE(("transaction conflict with thread id=%d\n", s_nPendingThreadId));
		return ERROR_INVALID_OPERATION;
	}

	// If any of the pending operations failed, then we don't need to do this.
	if (s_nPendingError != NO_ERROR)
	{
		DETOUR_TRACE(("pending transaction error=%d\n", s_nPendingError));
		return s_nPendingError;
	}

	if (ppPointer == NULL)
	{
		DETOUR_TRACE(("ppPointer is nullptr\n"));
		return ERROR_INVALID_HANDLE;
	}
	if (*ppPointer == NULL)
	{
		error = ERROR_INVALID_HANDLE;
		s_nPendingError = error;
		s_ppPendingError = ppPointer;
		DETOUR_TRACE(("*ppPointer is nullptr (ppPointer=%p)\n", ppPointer));
		DETOUR_BREAK();
		return error;
	}

	PBYTE pbTarget = (PBYTE)*ppPointer;
	PDETOUR_TRAMPOLINE pTrampoline = NULL;
	DetourOperation *o = NULL;

#ifdef DETOURS_IA64
#error Feature not supported in this release.

#else // DETOURS_IA64
	pbTarget = (PBYTE)DetourCodeFromPointer(pbTarget, NULL);
	pDetour = DetourCodeFromPointer(pDetour, NULL);
#endif // !DETOURS_IA64

	// Don't follow a jump if its destination is the target function.
	// This happens when the detour does nothing other than call the target.
	if (pDetour == (PVOID)pbTarget)
	{
		if (s_fIgnoreTooSmall)
		{
			goto stop;
		}
		else
		{
			DETOUR_BREAK();
			goto fail;
		}
	}

	if (ppRealTarget != NULL)
	{
		*ppRealTarget = pbTarget;
	}
	if (ppRealDetour != NULL)
	{
		*ppRealDetour = pDetour;
	}

	o = new DetourOperation;
	if (o == NULL)
	{
		error = ERROR_NOT_ENOUGH_MEMORY;
	fail:
		s_nPendingError = error;
		DETOUR_BREAK();
	stop:
		if (pTrampoline != NULL)
		{
			detour_free_trampoline(pTrampoline);
			pTrampoline = NULL;
			if (ppRealTrampoline != NULL)
			{
				*ppRealTrampoline = NULL;
			}
		}
		if (o != NULL)
		{
			delete o;
			o = NULL;
		}
		s_ppPendingError = ppPointer;
		return error;
	}

	pTrampoline = detour_alloc_trampoline(pbTarget);
	if (pTrampoline == NULL)
	{
		error = ERROR_NOT_ENOUGH_MEMORY;
		DETOUR_BREAK();
		goto fail;
	}

	if (ppRealTrampoline != NULL)
	{
		*ppRealTrampoline = pTrampoline;
	}

	DETOUR_TRACE(("detours: pbTramp=%p, pDetour=%p\n", pTrampoline, pDetour));

	memset(pTrampoline->rAlign, 0, sizeof(pTrampoline->rAlign));

	// Determine the number of movable target instructions.
	PBYTE pbSrc = pbTarget;
	PBYTE pbTrampoline = pTrampoline->rbCode;
	PBYTE pbPool = pbTrampoline + sizeof(pTrampoline->rbCode);
	ULONG cbTarget = 0;
	ULONG cbJump = SIZE_OF_JMP;
	ULONG nAlign = 0;

#ifdef DETOURS_ARM
#error Feature not supported in this release.

#endif

	while (cbTarget < cbJump)
	{
		PBYTE pbOp = pbSrc;
		LONG lExtra = 0;

		DETOUR_TRACE((" DetourCopyInstruction(%p,%p)\n",
			pbTrampoline, pbSrc));
		pbSrc = (PBYTE)
			DetourCopyInstruction(pbTrampoline, (PVOID*)&pbPool, pbSrc, NULL, &lExtra);
		DETOUR_TRACE((" DetourCopyInstruction() = %p (%d bytes)\n",
			pbSrc, (int)(pbSrc - pbOp)));
		pbTrampoline += (pbSrc - pbOp) + lExtra;
		cbTarget = (LONG)(pbSrc - pbTarget);
		pTrampoline->rAlign[nAlign].obTarget = cbTarget;
		pTrampoline->rAlign[nAlign].obTrampoline = pbTrampoline - pTrampoline->rbCode;

		if (detour_does_code_end_function(pbOp))
		{
			break;
		}
	}

	// Consume, but don't duplicate padding if it is needed and available.
	while (cbTarget < cbJump)
	{
		LONG cFiller = detour_is_code_filler(pbSrc);
		if (cFiller == 0)
		{
			break;
		}

		pbSrc += cFiller;
		cbTarget = (LONG)(pbSrc - pbTarget);
	}

#if DETOUR_DEBUG
	{
		DETOUR_TRACE((" detours: rAlign ["));
		LONG n = 0;
		for (n = 0; n < ARRAYSIZE(pTrampoline->rAlign); n++)
		{
			if (pTrampoline->rAlign[n].obTarget == 0 &&
				pTrampoline->rAlign[n].obTrampoline == 0)
			{
				break;
			}
			DETOUR_TRACE((" %d/%d",
				pTrampoline->rAlign[n].obTarget,
				pTrampoline->rAlign[n].obTrampoline
				));
		}
		DETOUR_TRACE((" ]\n"));
	}
#endif

	if (cbTarget < cbJump || nAlign > ARRAYSIZE(pTrampoline->rAlign))
	{
		// Too few instructions.

		error = ERROR_INVALID_BLOCK;
		if (s_fIgnoreTooSmall)
		{
			goto stop;
		}
		else
		{
			DETOUR_BREAK();
			goto fail;
		}
	}

	if (pbTrampoline > pbPool)
	{
		__debugbreak();
	}

#if 0 // [GalenH]
	if (cbTarget < pbTrampoline - pTrampoline->rbCode)
	{
		__debugbreak();
	}
#endif

	pTrampoline->cbCode = (BYTE)(pbTrampoline - pTrampoline->rbCode);
	pTrampoline->cbRestore = (BYTE)cbTarget;
	CopyMemory(pTrampoline->rbRestore, pbTarget, cbTarget);

#if !defined(DETOURS_IA64)
	if (cbTarget > sizeof(pTrampoline->rbCode) - cbJump)
	{
		// Too many instructions.
		error = ERROR_INVALID_HANDLE;
		DETOUR_BREAK();
		goto fail;
	}
#endif // !DETOURS_IA64

	pTrampoline->pbRemain = pbTarget + cbTarget;
	pTrampoline->pbDetour = (PBYTE)pDetour;

#ifdef DETOURS_IA64
#error Feature not supported in this release.

#endif // DETOURS_IA64

	pbTrampoline = pTrampoline->rbCode + pTrampoline->cbCode;
#ifdef DETOURS_X64
#error Feature not supported in this release.

#endif // DETOURS_X64

#ifdef DETOURS_X86
	pbTrampoline = detour_gen_jmp_immediate(pbTrampoline, pTrampoline->pbRemain);
	pbTrampoline = detour_gen_brk(pbTrampoline, pbPool);
#endif // DETOURS_X86

#ifdef DETOURS_ARM
#error Feature not supported in this release.

#endif // DETOURS_ARM

	DWORD dwOld = 0;
	if (!VirtualProtect(pbTarget, cbTarget, PAGE_EXECUTE_READWRITE, &dwOld))
	{
		error = GetLastError();
		DETOUR_BREAK();
		goto fail;
	}

	DETOUR_TRACE(("detours: pbTarget=%p: "
		"%02x %02x %02x %02x "
		"%02x %02x %02x %02x "
		"%02x %02x %02x %02x\n",
		pbTarget,
		pbTarget[0], pbTarget[1], pbTarget[2], pbTarget[3],
		pbTarget[4], pbTarget[5], pbTarget[6], pbTarget[7],
		pbTarget[8], pbTarget[9], pbTarget[10], pbTarget[11]));
	DETOUR_TRACE(("detours: pbTramp =%p: "
		"%02x %02x %02x %02x "
		"%02x %02x %02x %02x "
		"%02x %02x %02x %02x\n",
		pTrampoline,
		pTrampoline->rbCode[0], pTrampoline->rbCode[1],
		pTrampoline->rbCode[2], pTrampoline->rbCode[3],
		pTrampoline->rbCode[4], pTrampoline->rbCode[5],
		pTrampoline->rbCode[6], pTrampoline->rbCode[7],
		pTrampoline->rbCode[8], pTrampoline->rbCode[9],
		pTrampoline->rbCode[10], pTrampoline->rbCode[11]));

	o->fIsRemove = FALSE;
	o->ppbPointer = (PBYTE*)ppPointer;
	o->pTrampoline = pTrampoline;
	o->pbTarget = pbTarget;
	o->dwPerm = dwOld;
	o->pNext = s_pPendingOperations;
	s_pPendingOperations = o;

	return NO_ERROR;
}

LONG WINAPI DetourDetach(PVOID *ppPointer,
	PVOID pDetour)
{
	LONG error = NO_ERROR;

	if (s_nPendingThreadId != (LONG)GetCurrentThreadId())
	{
		return ERROR_INVALID_OPERATION;
	}

	// If any of the pending operations failed, then we don't need to do this.
	if (s_nPendingError != NO_ERROR)
	{
		return s_nPendingError;
	}

	if (ppPointer == NULL)
	{
		return ERROR_INVALID_HANDLE;
	}
	if (*ppPointer == NULL)
	{
		error = ERROR_INVALID_HANDLE;
		s_nPendingError = error;
		s_ppPendingError = ppPointer;
		DETOUR_BREAK();
		return error;
	}

	DetourOperation *o = new DetourOperation;
	if (o == NULL)
	{
		error = ERROR_NOT_ENOUGH_MEMORY;
	fail:
		s_nPendingError = error;
		DETOUR_BREAK();
	stop:
		if (o != NULL)
		{
			delete o;
			o = NULL;
		}
		s_ppPendingError = ppPointer;
		return error;
	}

#ifdef DETOURS_IA64
#error Feature not supported in this release.

#else // !DETOURS_IA64
	PDETOUR_TRAMPOLINE pTrampoline =
		(PDETOUR_TRAMPOLINE)DetourCodeFromPointer(*ppPointer, NULL);
	pDetour = DetourCodeFromPointer(pDetour, NULL);
#endif // !DETOURS_IA64

	////////////////////////////////////// Verify that Trampoline is in place.
	//
	LONG cbTarget = pTrampoline->cbRestore;
	PBYTE pbTarget = pTrampoline->pbRemain - cbTarget;
	if (cbTarget == 0 || cbTarget > sizeof(pTrampoline->rbCode))
	{
		error = ERROR_INVALID_BLOCK;
		if (s_fIgnoreTooSmall)
		{
			goto stop;
		}
		else
		{
			DETOUR_BREAK();
			goto fail;
		}
	}

	if (pTrampoline->pbDetour != pDetour)
	{
		error = ERROR_INVALID_BLOCK;
		if (s_fIgnoreTooSmall)
		{
			goto stop;
		}
		else
		{
			DETOUR_BREAK();
			goto fail;
		}
	}

	DWORD dwOld = 0;
	if (!VirtualProtect(pbTarget, cbTarget,
		PAGE_EXECUTE_READWRITE, &dwOld))
	{
		error = GetLastError();
		DETOUR_BREAK();
		goto fail;
	}

	o->fIsRemove = TRUE;
	o->ppbPointer = (PBYTE*)ppPointer;
	o->pTrampoline = pTrampoline;
	o->pbTarget = pbTarget;
	o->dwPerm = dwOld;
	o->pNext = s_pPendingOperations;
	s_pPendingOperations = o;

	return NO_ERROR;
}

//  End of File
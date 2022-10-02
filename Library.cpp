#include "Library.h"

void DataSend(LPBYTE Data, int Size)
{
	if (Size < 3)
	{
		return;
	}

	BYTE Head, Start;

	switch (Data[0])
	{
		case 0xC1:
		case 0xC3:
		{
			Head = Data[2];
			Start = 3;
			break;
		}
		case 0xC2:
		case 0xC4:
		{
			Head = Data[3];
			Start = 4;
			break;
		}
	}

	BYTE Buffer[8096], Key[] = {0xE7, 0x6D, 0x3A, 0x89, 0xBC, 0xB2, 0x9F, 0x73, 0x23, 0xA8, 0xFE, 0xB6, 0x49, 0x5D, 0x39, 0x5D, 0x8A, 0xCB, 0x63, 0x8D, 0xEA, 0x7D, 0x2B, 0x5F, 0xC3, 0xB1, 0xE9, 0x83, 0x29, 0x51, 0xE8, 0x56};

	for (int i = Start; i < Size; ++i)
	{
		Data[i] ^= (Key[i % sizeof(Key)] ^ Data[i - 1]);
	}
	
	switch (Data[0])
	{
		case 0xC3:
		{
			pSerialPacketDecrypt();

			Buffer[1] = (pSerialPacket & 0xFF);
			++pSerialPacket;

			pSerialPacketEncrypt();

			Size = pSimpleModulusEncrypt(&Buffer[2], &Data[1], (Size - 1)) + 2;

			Buffer[0] = 0xC3;
			Buffer[1] = (BYTE)(Size);

			send(pSocket, (const char*)(Buffer), Size, 0);
			break;
		}
		case 0xC4:
		{
			pSerialPacketDecrypt();

			Buffer[2] = (pSerialPacket & 0xFF);
			++pSerialPacket;

			pSerialPacketEncrypt();

			Size = pSimpleModulusEncrypt(&Buffer[3], &Data[2], (Size - 2)) + 3;

			Buffer[0] = 0xC4;
			Buffer[1] = HIBYTE(Size);
			Buffer[2] = LOBYTE(Size);

			send(pSocket, (const char*)(Buffer), Size, 0);
			break;
		}
		default:
		{
			break;
		}
	}

	send(pSocket, (const char*)(Data), Size, 0);
}

void XorArgument(char* Output, const char* Input, int Size)
{
	BYTE Keys[3] = {0xFC,0xCF,0xAB};

	for (int n = 0; n < Size; ++n)
	{
		Output[n] = Input[n] ^ Keys[n % 3];
	}
}

bool FileExists(char * name)
{
	char CurrentPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, CurrentPath);
	sprintf_s(CurrentPath, "%s\\Data\\%s", CurrentPath, name);
	if (CreateFile(CurrentPath, 0, 0, 0, OPEN_EXISTING, 0, 0) == INVALID_HANDLE_VALUE)
		return false;
	return true;
};

void CommandLineToArg(char * Command, char*** argv)
{
	if (!Command) { return; }

	bool	Quote = false;
	bool	Content = false;
	size_t	CommandLen = strlen(Command);
	int		NumCommands = 1;
	size_t	I = 0;

	for (I = 0; I < CommandLen; I++)
	{
		if (Command[I] == '"')
		{
			Quote = !Quote;
			Content = true;
		}
		else if (Command[I] == ' ')
		{
			if (!Quote&&Content)
			{
				Content = false;

				NumCommands++;
			}
		}
		else
		{
			Content = true;
		}
	}

	*argv = new char*[NumCommands];

	size_t StrBegin = 0;
	size_t StrLen = 0;
	size_t CommandNum = 0;

	for (I = 0; I < CommandLen; I++)
	{
		if (Command[I] == '"')
		{
			Quote = !Quote;
			Content = true;
		}
		else if (Command[I] == ' ')
		{
			if (!Quote && Content)
			{
				Content = false;

				StrLen = I - StrBegin;
				if (Command[StrBegin] == '"')
				{
					StrBegin++;
					StrLen--;
				}
				if (Command[StrBegin + StrLen - 1] == '"')
				{
					StrLen -= 1;
				}
				char* Argument = 0;
				Argument = new char[StrLen + 1];
				memcpy(Argument, Command + StrBegin, StrLen);
				memset(Argument + StrLen, 0, 1);

				(*argv)[CommandNum] = Argument;

				CommandNum++;
				StrBegin = I + 1;
			}
			else if (!Quote)
			{
				StrBegin++;
			}
		}
		else
		{
			Content = true;
		}
	}
	StrLen = I - StrBegin;
	if (Command[StrBegin] == '"')
	{
		StrBegin++;
		StrLen--;
	}
	if (Command[StrBegin + StrLen - 1] == '"')
	{
		StrLen -= 1;
	}
	char* Argument = 0;
	Argument = new char[StrLen + 1];
	memcpy(Argument, Command + StrBegin, StrLen);
	memset(Argument + StrLen, 0, 1);

	(*argv)[CommandNum] = Argument;
}
BOOL IsUserAdmin(VOID)
/*++
Routine Description: This routine returns TRUE if the caller's
process is a member of the Administrators local group. Caller is NOT
expected to be impersonating anyone and is expected to be able to
open its own process and process token.
Arguments: None.
Return Value:
   TRUE - Caller has Administrators local group.
   FALSE - Caller does not have Administrators local group. --
*/
{
	BOOL b;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	b = AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&AdministratorsGroup);
	if (b)
	{
		if (!CheckTokenMembership(NULL, AdministratorsGroup, &b))
		{
			b = FALSE;
		}
		FreeSid(AdministratorsGroup);
	}

	return(b);
}

DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	// ---
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ---
	btBuf[0] = cmd;
	// ---
	memcpy((LPVOID)&btBuf[1], (LPVOID)&dwShift, sizeof(ULONG_PTR));
	// ---
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}


DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
	DWORD dwErrorCode = 0;
	DWORD dwOldProtect = 0;
	// ---
	int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	// ---
	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ---
	memcpy(lpAddress, lpBuf, uSize);
	// ---
	DWORD dwBytes = 0;
	// ---
	iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, &dwBytes);
	// ---
	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ---
	return 0x00;
}
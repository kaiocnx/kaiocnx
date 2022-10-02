#include "Library.h"
#include "MiniMap.h"

BYTE *btMinpMapNumberShow = (BYTE*)0x004105F6;
MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}

void MiniMap::Hook()
{
	SetOp((LPVOID)0x00598FB9, this->LoadTexture, 0xE8);
	//Memory::Hook<false>(0x598FB9, this->LoadTexture);
	//Memory::Hook<true>(0x4105F6, this->Switch);
}

void MiniMap::LoadTexture()
{
	char szPatch[60];
	// ---
	//char szBuffer[MAX_PATH];
	// ---
	gMiniMap.iLastMap = 100;
	// ---
	if (gMiniMap.iLastMap != pMapNumber && !(pMapNumber == 9 || (pMapNumber >= 11 && pMapNumber <= 23) || (pMapNumber >= 24 && pMapNumber <= 29) || pMapNumber == 30 || pMapNumber == 32 || pMapNumber == 36 || pMapNumber == 40 || pMapNumber == 255))
	{
		sprintf_s(szPatch, "Customs\\Minimaps\\Map%d.jpg", pMapNumber + 1);
		// ---
		pLoadJPG(szPatch, 0x694, 0x2600, 0x2900, 0, 1);
		//gInterface.LoadImage(0, szPatch, 0x690);
		// ---
		gMiniMap.bEnabled = true;
		// ---
		gMiniMap.iLastMap = pMapNumber;
	}
	// ---
	if (pMapNumber == 9 || (pMapNumber >= 11 && pMapNumber <= 23) || (pMapNumber >= 24 && pMapNumber <= 29) || pMapNumber == 30 || pMapNumber == 32 || pMapNumber == 36 || pMapNumber == 40 || pMapNumber == 255)
	{
		gMiniMap.bEnabled = false;
		gMiniMap.iLastMap = pMapNumber;
	}
	if (gMiniMap.bEnabled == true)
	{
		*btMinpMapNumberShow = 0xEB;
	}
	else
	{
		*btMinpMapNumberShow = 0x74;
	}
	// ---
	pSetBlend(true);
	/*
	if (!(pMapNumber == 9 || pMapNumber == 32 || (pMapNumber >= 11 && pMapNumber <= 23) || (pMapNumber >= 24 && pMapNumber <= 29) || pMapNumber == 36))
	{
		if (gMiniMap.LastMap != pMapNumber)
		{
			char File[256];
			wsprintf(File, "Customs\\Minimaps\\Map%d.jpg", pMapNumber + 1);
			char mypath[MAX_PATH];
			wsprintf(mypath, "Customs\\Minimaps\\Map%d.OZJ", pMapNumber + 1);
			if(FileExists(mypath))
			{
				pLoadJPG(File, 0x694, 0x2600, 0x2900, 0, 1);
				gMiniMap.LastMap = pMapNumber;
			}
				
		}
	}

	pDisableAlphaBlend();*/
}

void MiniMap::Switch(int Type)
{
	switch (Type)
	{
	case 1:
	{
		this->bSelect = !this->bSelect;
		// ---
		this->bEnabled = true;
	}
	break;
	case 2:
	{
		this->bSelect = !this->bSelect;
		// ---
		this->bEnabled = false;
	}
	break;
	};

	/*static DWORD Local[2] = {0x41060E, 0x4105FD};
	static DWORD Function = 0x4109F0;

	__asm
	{
		PUSHAD;
	}

	if (pMapNumber == 30)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	if (pMapNumber == 9 || pMapNumber == 32 || (pMapNumber >= 11 && pMapNumber <= 23) || (pMapNumber >= 24 && pMapNumber <= 29) || pMapNumber == 36)
	{
		__asm
		{
			POPAD;
			CALL Function;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];
	}*/
}

MiniMap gMiniMap;
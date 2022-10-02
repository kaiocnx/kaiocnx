#include "Library.h"
#include "Patch.h"
#include "Win32.h"
#include "Visual.h"
#include "Protocol.h"
#include "User.h"
#include "Monster.h"
#include "Resolution.h"
#include "Interface.h"
#include "Item.h"
#include "Message.h"
#include "MiniMap.h"
#include "Fog.h"
#include "Reconnect.h"
#include "Security.h"
#include "Sign.h"
#include "Patent.h"

HMODULE wzAudio = nullptr;

BOOL APIENTRY DllMain(HINSTANCE Instance, DWORD Reason, LPVOID Reserved)
{
	switch (Reason)
	{
		case DLL_PROCESS_ATTACH:
		{
			gWin32.DllInstance = Instance;

			wzAudio = LoadLibrary(".\\wza.dll");

			if (!wzAudio)
			{
				return FALSE;
			}
			DWORD OldProtect;

			if (!VirtualProtect((LPVOID)(0x401000), 0x300000, PAGE_EXECUTE_READWRITE, &OldProtect))
			{
				return FALSE;
			}

			if (!VirtualProtect((LPVOID)(0x7D171A0), sizeof(float), PAGE_EXECUTE_READWRITE, &OldProtect))
			{
				return FALSE;
			}
			gSecurity.Load();
			gMessage.Load();
			gItem.Load();
			gFog.Load();
			gMonster.Load();
			//gSign.Load();
			gPatent.Load();
			//gInterface.Load();
			gTexture.Hook();
			gModel.Hook();
			gUser.Hook();
			gVisual.Hook();
			gProtocol.Hook();
			gResolution.Hook();
			gMiniMap.Hook();
			gReconnect.Hook();
			gPatch.Apply();
			gWin32.Attach();

			break;
		}
		case DLL_PROCESS_DETACH:
		{
			gWin32.Detach();

			if (wzAudio)
			{
				FreeLibrary(wzAudio);
			}
			ExitProcess(0);
			break;
		}
	}

	return TRUE;
}

//
// WzAudio
//
extern "C" int __declspec(dllexport) wzAudioCreate(HWND Unk)
{
	static auto Function = (int(*)(HWND))(GetProcAddress(wzAudio, "wzAudioCreate"));
	return Function(Unk);
}

extern "C" int __declspec(dllexport) wzAudioDestroy()
{
	static auto Function = (int(*)())(GetProcAddress(wzAudio, "wzAudioDestroy"));
	return Function();
}

extern "C" int __declspec(dllexport) wzAudioPlay(WPARAM Unk)
{
	static auto Function = (int(*)(WPARAM))(GetProcAddress(wzAudio, "wzAudioPlay"));
	return Function(Unk);
}

extern "C" int __declspec(dllexport) wzAudioPause()
{
	static auto Function = (int(*)())(GetProcAddress(wzAudio, "wzAudioPause"));
	return Function();
}

extern "C" int __declspec(dllexport) wzAudioStop()
{
	static auto Function = (int(*)())(GetProcAddress(wzAudio, "wzAudioStop"));
	return Function();
}

extern "C" unsigned int __declspec(dllexport) wzAudioSetVolume(int Unk)
{
	static auto Function = (unsigned int(*)(int))(GetProcAddress(wzAudio, "wzAudioSetVolume"));
	return Function(Unk);
}

extern "C" unsigned int __declspec(dllexport) wzAudioGetVolume()
{
	static auto Function = (unsigned int(*)())(GetProcAddress(wzAudio, "wzAudioGetVolume"));
	return Function();
}

extern "C" unsigned int __declspec(dllexport) wzAudioVolumeUp()
{
	static auto Function = (unsigned int(*)())(GetProcAddress(wzAudio, "wzAudioVolumeUp"));
	return Function();
}

extern "C" unsigned int __declspec(dllexport) wzAudioVolumeDown()
{
	static auto Function = (unsigned int(*)())(GetProcAddress(wzAudio, "wzAudioVolumeDown"));
	return Function();
}

extern "C" int __declspec(dllexport) wzAudioOpenFile(char* Unk)
{
	static auto Function = (int(*)(char*))(GetProcAddress(wzAudio, "wzAudioOpenFile"));
	return Function(Unk);
}

extern "C" int __declspec(dllexport) wzAudioSeek(WPARAM Unk)
{
	static auto Function = (int(*)(WPARAM))(GetProcAddress(wzAudio, "wzAudioSeek"));
	return Function(Unk);
}

extern "C" int __declspec(dllexport) wzAudioGetStreamOffsetRange()
{
	static auto Function = (int(*)())(GetProcAddress(wzAudio, "wzAudioGetStreamOffsetRange"));
	return Function();
}

extern "C" int __declspec(dllexport) wzAudioGetStreamOffsetSec()
{
	static auto Function = (int(*)())(GetProcAddress(wzAudio, "wzAudioGetStreamOffsetSec"));
	return Function();
}

extern "C" unsigned int __declspec(dllexport) wzAudioSetMixerMode(int Unk)
{
	static auto Function = (unsigned int(*)(int))(GetProcAddress(wzAudio, "wzAudioSetMixerMode"));
	return Function(Unk);
}

extern "C" LPSTR __declspec(dllexport) wzAudioGetStreamInfo(char* Unk1, char* Unk2)
{
	static auto Function = (char* (*)(char*, char*))(GetProcAddress(wzAudio, "wzAudioGetStreamInfo"));
	return Function(Unk1, Unk2);
}

extern "C" int __declspec(dllexport) wzAudioOption(int Unk1, int Unk2)
{
	static auto Function = (int(*)(int, int))(GetProcAddress(wzAudio, "wzAudioOption"));
	return Function(Unk1, Unk2);
}

extern "C" int __declspec(dllexport) wzAudioSetEqualizer(int Unk)
{
	static auto Function = (int(*)(int))(GetProcAddress(wzAudio, "wzAudioSetEqualizer"));
	return Function(Unk);
}
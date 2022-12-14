#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <windowsx.h>
#include <Mmsystem.h>
#include <ShellAPI.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <Rpc.h>
#include <memory>
#include <WinSock2.h>
#include <gl/GL.h>
#include <thread>
#include "detours.h"
#include "Memory.h"
#include "Registry.h"
#include "Packets.h"
#include "Texture.h"
#include "Model.h"
#include "Viewport.h"

#define null								nullptr

//#define CONNECT_IP							"127.0.0.1"			//Local
#define CONNECT_IP							"158.69.163.31"	//Dryad
//#define CONNECT_PORT						44410
#define CONNECT_PORT						44405
#define CONNECT_VERSION						"2274:"
#define CONNECT_SERIAL						"TbYehR2hFUPBKgZj"

#define SCREEN_PATH							"Img\\Screen(%02d_%02d-%02d_%02d)-%03d.jpg"

#define FOLDER_INTERFACE					"Data\\Interface\\"
#define FOLDER_LOCAL						"Data\\Local\\"
#define FOLDER_LOGO							"Data\\Logo\\"
#define FOLDER_NPC							"Data\\NPC\\"
#define FOLDER_NPC_NEW						"Data\\Customs\\NPC\\"
#define FOLDER_MONSTER						"Data\\Customs\\Monsters\\"
#define FOLDER_EFFECT						"Data\\Effect\\"
#define FOLDER_SOUND						"Data\\Sound\\"
#define FOLDER_MUSIC						"Data\\Music\\"
#define FOLDER_ITEM							"Data\\Item\\"
#define FOLDER_PLAYER						"Data\\Player\\"
#define FOLDER_SKILL						"Data\\Skill\\"
#define FOLDER_SIGN							"Data\\Customs\\Signs\\"

//ACTIVATE / DEACTIVATE SYSTEMS
#define RECONNECT_SYSTEM 1
#define PATENT_SYSTEM 1
#define SIGN_SYSTEM 1
#define CAMERA_SYSTEM 1
#define AUTOCLICK_SYSTEM 1
#define LAUNCHERCHECK_SYSTEM 1
#define MINIMAP_SYSTEM 1


#define GET_MAX_WORD_VALUE(x)				((x > 65000) ? 65000 : (WORD)(x))
#define RGBA(R, G, B, A)					(DWORD)((A << 24) | (B << 16) | (G << 8) | R)

#define pHDC								*(HDC*)(0x57504DC)
#define pDefaultFont						*(HFONT*)(0x575053C)
#define pMediumFont 						*(HFONT*)(0x5750540)
#define pBigFont							*(HFONT*)(0x5750544)
#define pSocket								*(SOCKET*)(*(DWORD*)(0x6B7264) + 12)
#define pSerialPacket		 				*(BYTE*)(0x57548F3)
#define pScreenDivisorX 					*(float*)(0x574FE90)
#define pScreenDivisorY 					*(float*)(0x574FE94)
#define pScreenWidth						*(DWORD*)(0x6C4158)
#define pSetCursorFocus						*(DWORD*)(0x6C4158)
#define pScreenHeight 						*(DWORD*)(0x6C415C)
#define pScreenWidthBase 					640
#define pScreenHeightBase					480
#define pResolution							*(DWORD*)(0x5750320)
#define pFontSize							*(DWORD*)(0x773D130)
#define pClipPrecisionX						*(float*)(0x6A967C)
#define pClipPrecisionY		 				*(float*)(0x5E9D4E)
#define pState								*(DWORD*)(0x6C41C0)
#define pMessageBackgroundColor				*(DWORD*)(0x6B7DF8)
#define pMessageForegroundColor				*(DWORD*)(0x6B7DF0)
#define pItemDescriptionCount			 	*(DWORD*)(0x788C850)
#define pMapNumber							(BYTE)(*(DWORD*)(0x6B8D48))
#define pMyViewport							*(DWORD*)(0x742464C)
#define pCameraZoom							*(float*)(0x626681)
#define pCameraRotY							*(float*)(0x6A9798)
#define pCameraRotZ							*(float*)(0x7D171A0)
#define pCameraPosZ							*(float*)(0x6A7770)
#define pCameraClipX 						*(float*)(0x6A967C)
#define pCameraClipX2 						*(float*)(0x6A9688)
#define pCameraClipY 						*(float*)(0x5E9D4E)
#define pCameraClipY2						*(float*)(0x5E9CFE)
#define pCameraClipB 						*(float*)(0x6A9680)
#define pCameraClipGL 						*(float*)(0x62696E)
#define pCameraClipUnk1						*(float*)(0x6A9684)
#define pCameraClipUnk2						*(float*)(0x6A8FBC)
#define pConnectServerPort					*(WORD*)(0x6C41BC)
#define pConnectServerIpAddress				(char*)(0x6B6694)
#define pClientVersion						(char*)(0x6B7248)
#define pClientSerial						(char*)(0x6B7250)
#define pClientScreenshot					(char*)(0x6C4958)
#define pReconnectAccount					(char*)(0x777D7C0)
#define pReconnectPassword					(char*)(0x777D8C0)
#define pPlayerState						*(DWORD*)(0x57548F8)
#define pReconnectClear1					*(int*)(0x77D86D8)
#define pReconnectClear2					*(int*)(0x6B7D60)
#define pReconnectClear3					*(int*)(0x710C30)
#define pReconnectClear4					*(int*)(0x788C82C)
#define pReconnectClear5					*(int*)(0x788C830)
#define pReconnectClear6					*(int*)(0x6B7DBC)
#define pReconnectClear7					*(int*)(0x6B7DC0)
#define pReconnectClear8					*(int*)(0x6B7DC4)
#define pReconnectClear9					*(int*)(0x6B7DC8)
#define pReconnectClear10					*(int*)(0x6B7DCC)
#define pReconnectClear11					*(BYTE*)(0x6B7DE1)
#define pCharacterOpen						*(DWORD*)(0x77D83A8)
#define pCommandOpen						*(DWORD*)(0x77D83AC)
#define pInventoryOpen						*(DWORD*)(0x77D83F4)
#define pPartyOpen							*(DWORD*)(0x77D83DC)
#define pGuildOpen							*(DWORD*)(0x77D83B8)
#define pFriendOpen							*(DWORD*)(0x77D83B4)
#define pQuestOpen							*(DWORD*)(0x77D83EC)
#define pMoveOpen							*(DWORD*)(0x77D83D0)
#define pOpenWindow							((int(__thiscall*)(LPVOID This, int Code)) 0x648BB0)
#define pImageDivisor						0.03125f
#define pMaxTexture							*(DWORD*)(0x7D16FE8)
#define pLockMain							*(BYTE*)(0x575491C)

#define pWndProc							(WNDPROC)(0x4A9BD0)
#define pProtocolCore						((int(*)(DWORD, LPBYTE, int, int))(0x4DB720))
#define pDrawDamage							((void(*)(int, int, int, int, char))(0x53DA80))
#define pUnkFormatPoint						((void(*)(int, float, float, float, float, float, float, float, float, char, int))(0x60DCF0))
#define pDrawMonsterHP						((void(*)())(0x598350))
#define pGetPositionFromAngle				((void(*)(LPVOID, int*, int*))(0x60C740))

#define pSetBlend							((void(__cdecl*)(BYTE Mode)) 0x60CB90)
#define pEnableAlpha						((void(*)(char))(0x60CB90))
#define pDisableAlpha						((void(*)())(0x60CC20))
#define pDisableAlphaBlend					((void(*)())(0x60CB10))
#define pDrawGUI							((void(__cdecl*)(DWORD, float, float, float, float)) 0x60DCF0)
#define pDrawForm							((void(*)(float, float, float, float))(0x60DC30))
#define pDrawText							((int(*)(int, int, LPCSTR, int, char, int))(0x5486E0))
#define pDrawUserInfo						((void(*)(int, int, float, float, int, int, float, int))(0x5484B0))
#define pDrawImage							((void(*)(int, float, float, float, float, float, float, float, float, char, float))(0x60DCF0))
#define pSerialPacketEncrypt()				((BYTE(__thiscall*)(void*, const char*))(0x409580))((void*)(0x57500B0), (const char*)(0x57548F3))
#define pSerialPacketDecrypt()				((BYTE(__thiscall*)(void*, const char*))(0x409340))((void*)(0x57500B0), (const char*)(0x57548F3))
#define pSimpleModulusEncrypt(a, b, c)		((int(__thiscall*)(void*, void*, void*, int))(0x674DC0))((void*)(0x5754800), a, b, c)
#define pSimpleModulusDecrypt(a, b, c)		((int(__thiscall*)(void*, void*, void*, int))(0x674E30))((void*)(0x5754848), a, b, c)
#define pSetGlow							((void(*)(int, float, DWORD, struct GlowColor*, DWORD))(0x5F6220))
#define pShowMessage						((char(*)(const char*, const char*, int))(0x549630))
#define pRenderizeMonster					((ViewportInfo*(*)(int, DWORD, int, int))(0x434E60))
#define pRenderizeModel						((ViewportInfo*(*)(int, int, DWORD, int, int))(0x509410))
#define pShowModel							((int(*)(int, int, char, int, float*, int, char))(0x5CF110))
#define pLoadModel							((void(*)(int, const char*, const char*, int))(0x5FACA0))
#define pLoadTexture						((void(*)(int, const char*, GLint, GLint, GLsizei))(0x5FA860))
#define pLoadModels							((void(*)())(0x5FD0E0))
#define pLoadTextures						((void(*)())(0x5FE910))
#define pLoadInterfaces						((void(*)())(0x6096B0))
#define pLoadJPG							((char(*)(const char*, int, int, int, int, char))(0x62C1E0))
#define pLoadTGA							((char(*)(const char*, int, int, int, int, int))(0x62C670))
#define pLoadSounds							((void(*)())(0x607CE0))
#define pConnect							((int(*)(LPCSTR, WORD))(0x4BBA20))
#define pSetEvent							((int(*)(DWORD))(0x60FB20))
#define pInterfaceDraw1						((void(*)(int))(0x598C30))
#define pPShopThis							((LPVOID(*)())(0x44C850))
#define pPShopSet(viewport)					((void(__thiscall*)(LPVOID, ViewportInfo*))(0x44BF70))(pPShopThis(), viewport)
#define pRefreshGame						((int(*)(ViewportInfo*))(0x4EA700))
#define pFixText()							((void(*)(int, int, LPCSTR))(0x5487E0))(0, 0, "")
#define pCreateSign							((LPBYTE(__thiscall*)(LPVOID, short, int, char, float, float, float, int, int, float))(0x4127F0))
#define pCreateSign2						((LPBYTE(__thiscall*)(LPVOID, short, int, int, float, float, float))(0x412C40))
#define pDestroySign						((void(*)(ViewportInfo*))(0x4127C0))
#define pGetEffectPosition					((int(__thiscall*)(DWORD, DWORD, DWORD, DWORD, char))(0x4E4610))
#define pShowEffect1						((int(*)(short, DWORD, float, float*, DWORD, DWORD, DWORD))(0x53DE20))
#define pShowEffect2						((int(*)(int, DWORD, DWORD, float*, DWORD, float, DWORD))(0x5353B0))
#define pMakePreviewCharacter				((void(*)(int, BYTE*, int, int))(0x50A590))

#define GET_ALLIANCE_NAME(i)				((char*)(2 * (11 * i) + 0x785B794))

#define STATE_SELECT_SERVER					2 
#define STATE_SELECT_CHARACTER				4
#define STATE_PLAYING						5
#define PSTATE_OFFLINE						0
#define PSTATE_ONLINE						1

#define GUILD_RELATIONSHIP_UNION			1
#define GUILD_RELATIONSHIP_RIVAL			2
#define GUILD_RELATIONSHIP_UNIONMASTER		4
#define GUILD_RELATIONSHIP_RIVALMASTER		8
void DataSend(LPBYTE Data, int Size);
void XorArgument(char* Output, const char* Input, int Size);
extern std::vector<int> InterfaceMaps;
bool FileExists(char * name);
void CommandLineToArg(char* Command, char*** argv);
BOOL IsUserAdmin(VOID);
DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);
DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
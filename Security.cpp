#include "Library.h"
#include <process.h>
#include <tlhelp32.h>
#include "Security.h"
#include "CheatDB.h"



Security::Security()
{
}

Security::~Security()
{
}

void Security::Load()
{
	this->CheckLauncher();
}

void Security::StartCheckProcesses()
{
	if (this->ProcessChecker.joinable())
	{
		this->ProcessChecker.join();
	}
	if (!this->SpeedChecker.joinable())
	{
		this->SpeedChecker = std::thread(&Security::CheckSpeed, this);
	}

	this->ProcessChecker = std::thread(&Security::CheckProcesses, this);
}

void Security::CheckProcesses()
{
	SetThreadPriority(this->ProcessChecker.native_handle(), REALTIME_PRIORITY_CLASS);

	//this->CheckDump();
	this->CheckInject();
	this->CheckWindowTitle();
	//this->SpeedPerformance();
	Sleep(3000);
	DWORD_PTR Mask = 1 << 3;
	SetThreadAffinityMask(this->ProcessChecker.native_handle(), Mask);

	PMSG_PONG_SEND pMsg;
	pMsg.header.set(0xF3, 0xE6, sizeof(pMsg));
	DataSend((LPBYTE)(&pMsg), sizeof(pMsg));
}

void Security::CheckSpeed()
{
	/*SetThreadPriority(this->SpeedChecker.native_handle(), REALTIME_PRIORITY_CLASS);

	this->SpeedTickCount();

	Sleep(500);

	DWORD_PTR Mask = 1 << 3;
	SetThreadAffinityMask(this->SpeedChecker.native_handle(), Mask);

	this->SpeedChecker = std::thread(&Security::CheckSpeed, this);*/
}

void Security::CheckLauncher() {
	HWND hWnd;
	if(IsUserAdmin())
	{
		hWnd = FindWindow(NULL, "Launcher TarkanMU");
		if (!hWnd) {
			char CurrentPath[_MAX_PATH];
			GetCurrentDirectory(_MAX_PATH, CurrentPath);
			sprintf_s(CurrentPath, "%s\\TarkanMU.exe", CurrentPath);
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			ZeroMemory(&pi, sizeof(pi));
			CreateProcessA(CurrentPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
			/** Enviar EXIT a main.exe y Sub Procesos */
			ExitProcess(0);
		}
		else
		{
			char **	Command = 0;
			CommandLineToArg(GetCommandLine(), &Command);
			if (strcmp("ghregihiuehguiehg", Command[1]))
			{
				MessageBox(0, "Debes iniciar el juego a traves del Launcher", "Aviso Tarkan MU", MB_OK | MB_ICONASTERISK | MB_DEFBUTTON1);
				ExitProcess(0);
			}
		}
	}
	else
	{
		MessageBox(0, "Debes iniciar el juego en Modo Administrador", "Aviso Tarkan MU", MB_OK | MB_ICONASTERISK | MB_DEFBUTTON1);
		ExitProcess(0);
	}

	
}

void Security::SpeedPerformance()//antispeed 1 - esse ai nao tenho ideia como funciona kkk
{
	if (*(unsigned long*)QueryPerformanceCounter != 2337669003) 
	{
			this->Detect("Speedhack Performance");
	}
}

void Security::SpeedTickCount() //antispeed 2 - esse aqui e pelo tickcount 
{
	/*int checkspd = 0;
	again2:
		int timer = ::GetTickCount();
	again:  	
	Sleep(1000);
	checkspd++;
	if (checkspd != 20) {
		goto again;
	}
	else
	{
		checkspd = 0;
		int timeElapsed = ::GetTickCount() - timer;
		//printf ( "GetTickCount Speed time are: %d \n", timeElapsed) ;
		if ("%d", timeElapsed > 21000)
		{ // velocidade máxima (em milisegundos) que não deve ser ultrapassado

			this->Detect("Speedhack TickCount");
			//ExitProcess(0);
		}
		else
		{
			goto again2;
		}
	}*/
}

void Security::VirtualMemoryProtect()
{
		// GET BUFFER MESSAGE
		
			/*char cbuffer[10];

			//WARNING!  Add an address that not exist on Mxmain.exe will crash Mxmain.exe

			sprintf_s(cbuffer, "%d", (*(unsigned short*)0xE25C2A4));  //Put ADDRESS here, this is for [carrega.Memory_Buffer_P]                    
			MessageBoxA(NULL, (LPCSTR)cbuffer, "Memory_Buffer_P___", MB_ICONWARNING);
			ExitProcess(0);*/
		/*if ((*(unsigned short*)0x449081 != 29537) ||
			(*(unsigned short*)0x449081 != 29537)) {

			ExitProcess(0); 
			return true;
		}
		else
		{
			return false;
		}*/
}


void Security::CheckInject() {
	for (int i = 0; i < (sizeof(DDLDB) / sizeof(DLLDatabase)); i++)
	{
		if(GetModuleHandle(DDLDB[i].DLLName))
		{
			char szText[256];
			wsprintf(szText, "DLL %s", DDLDB[i].DLLName);
			this->Detect(szText);
		}
	}
}


bool Security::TitleWindow(LPCSTR WindowTitle)
{
	HWND WinTitle = FindWindowA(NULL, WindowTitle);
	if (WinTitle > 0) 
	{
		SendMessage(WinTitle, WM_CLOSE, 0, 0);  //CLOSE HACK WINTITLE
		char szText[256];
		wsprintf(szText, "Window %s", WindowTitle);
		this->Detect(szText);
	}
	return true;
}

void Security::CheckWindowTitle() 
{
	for (int i = 0; i < (sizeof(TitleDB) / sizeof(TitleDatabase)); i++)
	{
		TitleWindow(TitleDB[i].Title);
	}
}


bool Security::CheckDump()
{
	bool Return = false;

	HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProc != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 mP32;

		mP32.dwSize = sizeof(mP32);

		Process32First(hProc, &mP32);

		do
		{
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, mP32.th32ProcessID);

			if (hProcess != NULL)
			{
				for (int i = 0; i < (sizeof(DB) / sizeof(Database)); i++)
				{
					unsigned char Bytes[32];
					unsigned long BytesRead;

					if (ReadProcessMemory(hProcess, (LPCVOID)DB[i].Offset, (LPVOID)Bytes, 32, &BytesRead))
					{
						if (BytesRead == 32)
						{
							if (!memcmp(Bytes, DB[i].Bytes, 32))
							{

								char szText[256];
								wsprintf(szText, "Dump %s", mP32.szExeFile);
								this->Detect(szText);
								TerminateProcess(hProcess, NULL);
								Return = true;
							}
						}
					}
				}

				CloseHandle(hProcess);
			}
		}

		while (Process32Next(hProc, &mP32));
	}

	CloseHandle(hProc);

	return Return;
}

void Security::Detect(char* szText, ...)
{
	PMSG_DETECT_SEND pMsg;
	pMsg.header.set(0xF3, 0xE7, sizeof(pMsg));
	pMsg.result = TRUE;
	memcpy(pMsg.detect, szText, sizeof(pMsg.detect));
	DataSend((LPBYTE)(&pMsg), sizeof(pMsg));
}


Security gSecurity;

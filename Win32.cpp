#include "Library.h"
#include "Win32.h"
#include "Message.h"
#include "User.h"
#include "Fog.h"
#include "Camera.h"
#include "Reconnect.h"
#include "resource.h"

HWND (WINAPI* pCreateWindowEx)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID) = CreateWindowEx;
LONG (WINAPI* pChangeDisplaySettings)(DEVMODEA*, DWORD) = ChangeDisplaySettings;
HFONT (WINAPI* pCreateFont)(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR) = CreateFont;
SHORT (WINAPI* pGetAsyncKeyState)(int) = GetAsyncKeyState;
void (WINAPI* pglEnable)(GLenum) = glEnable;
void (WINAPI* pglClearColor)(GLclampf, GLclampf, GLclampf, GLclampf) = glClearColor;
void (WINAPI* pglReadPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*) = glReadPixels;

Win32::Win32() : Window(nullptr), WindowMode(false), NotifyIcon{}
{
}

Win32::~Win32()
{
}

void Win32::Attach()
{
	this->WindowMode = Registry::Read<bool>("WindowMode");

	Memory::Update<DWORD>(0x4B36EB, (DWORD)(&this->WndProc));

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)(pCreateWindowEx), this->CreateWindowEx);
	DetourAttach(&(LPVOID&)(pChangeDisplaySettings), this->ChangeDisplaySettings);
	DetourAttach(&(LPVOID&)(pCreateFont), this->CreateFont);
	DetourAttach(&(LPVOID&)(pGetAsyncKeyState), this->GetAsyncKeyState);
	//DetourAttach(&(LPVOID&)(pglEnable), this->glEnable);
	//DetourAttach(&(LPVOID&)(pglClearColor), this->glClearColor);
	//DetourAttach(&(LPVOID&)(pglReadPixels), this->glReadPixels);
	DetourTransactionCommit();
}

void Win32::Detach()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(LPVOID&)(pCreateWindowEx), this->CreateWindowEx);
	DetourDetach(&(LPVOID&)(pChangeDisplaySettings), this->ChangeDisplaySettings);
	DetourDetach(&(LPVOID&)(pCreateFont), this->CreateFont);
	DetourDetach(&(LPVOID&)(pGetAsyncKeyState), this->GetAsyncKeyState);
	//DetourDetach(&(LPVOID&)(pglEnable), this->glEnable);
	//DetourDetach(&(LPVOID&)(pglClearColor), this->glClearColor);
	//DetourDetach(&(LPVOID&)(pglReadPixels), this->glReadPixels);
	DetourTransactionCommit();

	if (!IsWindowVisible(Window))
	{
		Shell_NotifyIcon(NIM_DELETE, &this->NotifyIcon);
	}
}

HWND WINAPI Win32::CreateWindowEx(DWORD ExStyle, LPCSTR ClassName, LPCSTR WindowName, DWORD Style, int X, int Y, int Width, int Height, HWND Parent, HMENU Menu, HINSTANCE Instance, LPVOID Parameter)
{
	if (IS_INTRESOURCE(ClassName))
	{
		return pCreateWindowEx(ExStyle, ClassName, WindowName, Style, X, Y, Width, Height, Parent, Menu, Instance, Parameter);
	}

	if (!_stricmp(ClassName, "MU"))
	{
		if (gWin32.WindowMode)
		{
			RECT rc = {0, 0, Width, Height};

			// Topmost
			ExStyle = (false ? WS_EX_TOPMOST : WS_EX_APPWINDOW);

			// Borda
			Style = (true ? WS_CAPTION | WS_BORDER | WS_SYSMENU : WS_POPUP);

			// Ajusta as dimensões da janela
			if (AdjustWindowRectEx(&rc, Style, false, ExStyle))
			{
				Width = -rc.left + rc.right;
				Height = -rc.top + rc.bottom;
			}

			//ExStyle = 0;
			X = (GetSystemMetrics(SM_CXSCREEN) / 2) - (Width / 2);
			Y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (Height / 2);
			//Parent = 0;
			//Menu = 0;
			//Style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW;
		}

		gWin32.Window = pCreateWindowEx(ExStyle, ClassName, WindowName, Style, X, Y, Width, Height, Parent, Menu, Instance, Parameter);
		gWin32.WindowName = WindowName;

		memset(&gWin32.NotifyIcon, 0, sizeof(NotifyIcon));
		strcpy_s(gWin32.NotifyIcon.szTip, WindowName);
		gWin32.NotifyIcon.cbSize = sizeof(NotifyIcon);
		gWin32.NotifyIcon.hWnd = gWin32.Window;
		gWin32.NotifyIcon.uID = 10002;
		gWin32.NotifyIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		gWin32.NotifyIcon.uCallbackMessage = WM_TRAYICON;
		gWin32.NotifyIcon.hIcon = LoadIcon(gWin32.DllInstance, MAKEINTRESOURCE(TRAY_ICON));
		gWin32.NotifyIcon.hBalloonIcon = LoadIcon(gWin32.DllInstance, MAKEINTRESOURCE(TRAY_ICON));

		SetFocus(gWin32.Window);

		return gWin32.Window;
	}

	return pCreateWindowEx(ExStyle, ClassName, WindowName, Style, X, Y, Width, Height, Parent, Menu, Instance, Parameter);
}

LONG WINAPI Win32::ChangeDisplaySettings(DEVMODEA * DevMode, DWORD Flag)
{
	if (gWin32.WindowMode)
	{
		UNREFERENCED_PARAMETER(DevMode);
		UNREFERENCED_PARAMETER(Flag);
		return DISP_CHANGE_SUCCESSFUL;
	}

	return pChangeDisplaySettings(DevMode, Flag);
}

HFONT WINAPI Win32::CreateFont(int Height, int Width, int Escapement, int Orientation, int Weight, DWORD Italic, DWORD Underline, DWORD StrikeOut, DWORD CharSet, DWORD OutPrecision, DWORD ClipPrecision, DWORD Quality, DWORD PitchAndFamily, LPCSTR FaceName)
{
	return pCreateFont(Height, Width, Escapement, Orientation, Weight, Italic, Underline, StrikeOut, CharSet, OutPrecision, ClipPrecision, Quality, PitchAndFamily, "Tahoma");
}

SHORT WINAPI Win32::GetAsyncKeyState(int Key)
{
	if (GetForegroundWindow() == gWin32.Window)
	{
		if (gReconnect.GetState() == RSTATE_RECONNECT)
		{
			return 0;
		}

		return pGetAsyncKeyState(Key);
	}
	/*
	if (!IsWindowVisible(gWin32.Window))
	{
		if (pGetAsyncKeyState(VK_F12) & 0x8000)
		{
			ShowWindow(gWin32.Window, SW_SHOW);
			SetForegroundWindow(gWin32.Window);
			SetFocus(gWin32.Window);
			Shell_NotifyIcon(NIM_DELETE, &gWin32.NotifyIcon);
		}
	}*/

	return 0;
}
/*
void WINAPI Win32::glEnable(GLenum Mode)
{
	gFog.Apply(Mode);
	pglEnable(Mode);
}

void WINAPI Win32::glClearColor(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha)
{
	if (gFog.Apply())
	{
		return;
	}

	pglClearColor(Red, Green, Blue, Alpha);
}

void WINAPI Win32::glReadPixels(GLint X, GLint Y, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, GLvoid* Pixels)
{
	// Fix screenshots at resolutions not divisible by 4
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	return pglReadPixels(X, Y, Width, Height, Format, Type, Pixels);
}*/

LRESULT CALLBACK Win32::WndProc(HWND Window, UINT Code, WPARAM W, LPARAM L)
{
	if (gReconnect.GetState() == RSTATE_RECONNECT && (Code == WM_MOUSEWHEEL || Code == WM_MBUTTONDOWN || Code == WM_MBUTTONUP || Code == WM_LBUTTONDOWN || Code == WM_LBUTTONUP || Code == WM_RBUTTONDOWN || Code == WM_RBUTTONUP))
	{
		return 0;
	}

	static bool AutoClick[3] = {false, false, false};

	switch (Code)
	{
		case WM_NCACTIVATE:
		{
			return 0;
		}
		case WM_MOUSEWHEEL:
		{
			gCamera.SetZoom(GET_WHEEL_DELTA_WPARAM(W));

			break;
		}
		case WM_MBUTTONDOWN:
		{
			gCamera.Start(GET_X_LPARAM(L), GET_Y_LPARAM(L));

			break;
		}
		case WM_MBUTTONUP:
		{
			gCamera.End();

			break;
		}
		case WM_MOUSEMOVE:
		{
			gCamera.Move(GET_X_LPARAM(L), GET_Y_LPARAM(L));

			break;
		}
		case WM_TIMER:
		{
			switch (W)
			{
				case 10000:
				{
					if (AutoClick[0])
					{
						SendMessage(Window, (AutoClick[2]) ? WM_LBUTTONUP : WM_LBUTTONDOWN, 0, 0);
						AutoClick[2] = !AutoClick[2];
					}

					break;
				}
				case 10001:
				{
					if (AutoClick[1])
					{
						SendMessage(Window, (AutoClick[2]) ? WM_RBUTTONUP : WM_RBUTTONDOWN, 0, 0);
						AutoClick[2] = !AutoClick[2];
					}

					break;
				}
			}

			break;
		}
		case WM_SYSKEYDOWN:
		{
			switch (W)
			{
				case VK_F10:
				{
					if (!AutoClick[0]) // Left
					{
						AutoClick[1] = !AutoClick[1];
						AutoClick[2] = false;

						if (!AutoClick[1])  // Right
						{
							KillTimer(Window, 10001);
							SendMessage(Window, WM_RBUTTONUP, 0, 0);
							pShowMessage("", gMessage.Get(1), MSG_SUCCESS);
						}
						else
						{
							SetTimer(Window, 10001, 100, nullptr);
							pShowMessage("", gMessage.Get(0), MSG_SUCCESS);
						}
					}

					break;
				}
			}

			break;
		}
		case WM_KEYDOWN:
		{
			switch (W)
			{
				case VK_F8:
				{
					gFog.Active = !gFog.Active;

					if (gFog.Active)
					{
						pShowMessage("", gMessage.Get(3), MSG_SUCCESS);
					}
					else
					{
						pShowMessage("", gMessage.Get(4), MSG_SUCCESS);
					}

					break;
				}
				case VK_F9:
				{
					if (!AutoClick[1]) // Right
					{
						AutoClick[0] = !AutoClick[0];
						AutoClick[2] = false;

						if (!AutoClick[0])  // Left
						{
							KillTimer(Window, 10000);
							SendMessage(Window, WM_LBUTTONUP, 0, 0);
							pShowMessage("", gMessage.Get(1), MSG_SUCCESS);
						}
						else
						{
							SetTimer(Window, 10000, 100, nullptr);
							pShowMessage("", gMessage.Get(0), MSG_SUCCESS);
						}
					}

					break;
				}
				case VK_F11:
				{
					if (IsWindowVisible(Window))
					{
						if (pState == STATE_PLAYING)
						{
							auto Viewport = gViewport.GetMyself();
							wsprintf(gWin32.NotifyIcon.szTip, gMessage.Get(2), gWin32.WindowName, Viewport->Name, gMessage.GetMapName(pMapNumber), gUser.X, gUser.Y);
						}
						else
						{
							strcpy_s(gWin32.NotifyIcon.szTip, gWin32.WindowName);
						}

						ShowWindow(Window, SW_HIDE);
						Shell_NotifyIcon(NIM_ADD, &gWin32.NotifyIcon);
					}

					break;
				}
				case VK_INSERT:
				{
					if (pState == STATE_PLAYING)
					{
						gCamera.Active = !gCamera.Active;

						if (gCamera.Active)
						{
							pShowMessage("", gMessage.Get(5), MSG_SUCCESS);
						}
						else
						{
							pShowMessage("", gMessage.Get(6), MSG_SUCCESS);
						}
					}

					break;
				}
				case VK_HOME:
				{
					gCamera.Restore();

					break;
				}
			}

			break;
		}
		case WM_TRAYICON:
		{
			switch (L)
			{
				case WM_LBUTTONDBLCLK:
				case WM_RBUTTONDBLCLK:
				{
					if (!IsWindowVisible(Window))
					{
						ShowWindow(Window, SW_SHOW);
						Shell_NotifyIcon(NIM_DELETE, &gWin32.NotifyIcon);
					}

					break;
				}
			}

			break;
		}
	}

	return CallWindowProc(pWndProc, Window, Code, W, L);
}

Win32 gWin32;
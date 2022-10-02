#pragma once

#define WM_TRAYICON		2000

extern HWND (WINAPI* pCreateWindowEx)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
extern LONG (WINAPI* pChangeDisplaySettings)(DEVMODEA*, DWORD);
extern HFONT (WINAPI* pCreateFont)(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR);
extern SHORT (WINAPI* pGetAsyncKeyState)(int);
extern void (WINAPI* pglEnable)(GLenum);
extern void (WINAPI* pglClearColor)(GLclampf, GLclampf, GLclampf, GLclampf);
extern void (WINAPI* pglReadPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*);

class Win32
{
public:
	Win32();
	~Win32();

public:
	void Attach();
	void Detach();

public:
	static HWND WINAPI CreateWindowEx(DWORD ExStyle, LPCSTR ClassName, LPCSTR WindowName, DWORD Style, int X, int Y, int Width, int Height, HWND Parent, HMENU Menu, HINSTANCE Instance, LPVOID Parameter);
	static LONG WINAPI ChangeDisplaySettings(DEVMODEA* DevMode, DWORD Flag);
	static HFONT WINAPI CreateFont(int Height, int Width, int Escapement, int Orientation, int Weight, DWORD Italic, DWORD Underline, DWORD StrikeOut, DWORD CharSet, DWORD OutPrecision, DWORD ClipPrecision, DWORD Quality, DWORD PitchAndFamily, LPCSTR FaceName);
	static SHORT WINAPI GetAsyncKeyState(int Key);
	static void WINAPI glEnable(GLenum Mode);
	static void WINAPI glClearColor(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha);
	static void WINAPI glReadPixels(GLint X, GLint Y, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, GLvoid* Pixels);
	static LRESULT CALLBACK WndProc(HWND Window, UINT Code, WPARAM W, LPARAM L);

public:
	HINSTANCE DllInstance;

private:
	HWND Window;
	bool WindowMode;
	const char* WindowName;
	NOTIFYICONDATA NotifyIcon;
};

extern Win32 gWin32;
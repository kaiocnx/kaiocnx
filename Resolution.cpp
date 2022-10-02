#include "Library.h"
#include "Resolution.h"

Resolution::Resolution()
{
}

Resolution::~Resolution()
{
}

void Resolution::Hook()
{
	auto resolution = Registry::Read<DWORD>("Resolution");

	switch (resolution)
	{
	case 1:
	{
		this->Info = { 800, 600, 13, {170, 39, 99, 144} };
		break;
	}
	case 2:
	{
		this->Info = { 1024, 768, 14, {150, 34, 89, 128} };
		break;
	}
	case 3:
	{
		this->Info = { 1152, 864, 14, {130, 29, 74, 109} };
		break;
	}
	case 4:
	{
		this->Info = { 1280, 720, 15, {130, 29, 74, 109} };
		break;
	}
	case 5:
	{
		this->Info = { 1280, 768, 15, {130, 29, 74, 109} };
		break;
	}
	case 6:
	{
		this->Info = { 1280, 800, 15, {130, 29, 74, 109} };
		break;
	}
	case 7:
	{
		this->Info = { 1280, 960, 15, {130, 29, 74, 109} };
		break;
	}
	case 8:
	{
		this->Info = { 1280, 1024, 15, {130, 29, 74, 109} };
		break;
	}
	case 9:
	{
		this->Info = { 1366, 768, 15, {130, 29, 74, 109} };
		break;
	}
	case 10:
	{
		this->Info = { 1400, 900, 16, {130, 29, 74, 109} };
		break;
	}
	case 11:
	{
		this->Info = { 1400, 1050, 16, {130, 29, 74, 109} };
		break;
	}
	case 12:
	{
		this->Info = { 1680, 900, 16, {130, 29, 74, 109} };
		break;
	}
	case 13:
	{
		this->Info = { 1680, 1200, 16, {130, 29, 74, 109} };
		break;
	}
	case 14:
	{
		this->Info = { 1680, 1050, 17, {130, 29, 74, 109} };
		break;
	}
	case 15:
	{
		this->Info = { 1792, 1344, 17, {130, 29, 74, 109} };
		break;
	}
	case 16:
	{
		this->Info = { 1856, 1392, 17, {130, 29, 74, 109} };
		break;
	}
	case 17:
	{
		this->Info = { 1920, 1080, 18, {130, 29, 74, 109} };
		break;
	}
	default:
	{
		this->Info = { 640, 480, 12, {190, 44, 104, 154} };
		break;
	}
	}

	//
	// Correção de seleção de servidores (widescreen)
	//
	if (this->Info.Width >= 1280)
	{
		Memory::Update<DWORD>(0x6224C8, 0x1A0);
		Memory::Update<BYTE>(0x6224D2, 0x20);
	}

	//
	// Ganchos
	//
	Memory::Hook(0x4B3AAE, this->WindowSize);
	Memory::Hook(0x4B4D5F, this->FontSize);
	Memory::Hook(0x443B70, this->MoveListSize);
	Memory::Hook(0x44315B, this->MoveListClick);
}

void __declspec(naked) Resolution::WindowSize()
{
	static DWORD Back = 0x4B3B2A;

	__asm
	{
		PUSHAD;
	}

	pScreenWidth = gResolution.Info.Width;
	pScreenHeight = gResolution.Info.Height;

	if (gResolution.Info.Width >= 1280)
	{
		pClipPrecisionX += 1500.f;
	}

	__asm
	{
		POPAD;
		JMP Back;
	}
}

void __declspec(naked) Resolution::FontSize()
{
	static DWORD Back = 0x4B4DCD;

	__asm
	{
		PUSHAD;
	}

	pFontSize = gResolution.Info.Font;

	__asm
	{
		POPAD;
		JMP Back;
	}
}

void __declspec(naked) Resolution::MoveListSize()
{
	static DWORD Back = 0x443C14;

	__asm
	{
		MOVZX EAX, gResolution.Info.Move[0];
		MOV DWORD PTR SS : [EBP - 0x8], EAX;
		MOVZX EAX, gResolution.Info.Move[2];
		MOV DWORD PTR SS : [EBP - 0xC], EAX;
		MOVZX EAX, gResolution.Info.Move[4];
		MOV DWORD PTR SS : [EBP - 0x10], EAX;
		MOVZX EAX, gResolution.Info.Move[6];
		MOV DWORD PTR SS : [EBP - 0x14], EAX;
		JMP Back;
	}
}

void __declspec(naked) Resolution::MoveListClick()
{
	static DWORD Back = 0x44319D;

	__asm
	{
		MOV DWORD PTR SS : [EBP - 0x58], ESI;
		MOVZX EBX, gResolution.Info.Move[0];
		JMP Back;
	}
}

Resolution gResolution;
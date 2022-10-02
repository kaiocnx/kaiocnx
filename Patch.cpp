#include "Library.h"
#include "Patch.h"
#include <experimental/filesystem>

Patch::Patch()
{
}

Patch::~Patch()
{
}

void Patch::Apply()
{
	// Connection
	pConnectServerPort = CONNECT_PORT;
	memcpy(pConnectServerIpAddress, CONNECT_IP, strlen(CONNECT_IP) + 1);
	memcpy(pClientVersion, CONNECT_VERSION, strlen(CONNECT_VERSION) + 1);
	memcpy(pClientSerial, CONNECT_SERIAL, strlen(CONNECT_SERIAL) + 1);
	
	memcpy(pClientScreenshot, SCREEN_PATH, strlen(SCREEN_PATH) + 1);

	// Crack
	Memory::Update<BYTE>(0x4B4305, 0xEB);
	Memory::Update<BYTE>(0x4B47FE, 0x75);
	Memory::Update<BYTE>(0x4B4856, 0xE9);
	Memory::Update<BYTE>(0x4B4857, 0xA6);
	Memory::Update<BYTE>(0x4B4858, 0x00);
	Memory::Update<BYTE>(0x4B485B, 0x90);
	Memory::Update<BYTE>(0x4BEA9F, 0xEB);
	
	// CRC32
	Memory::Update<BYTE>(0x40ABE3, 0xEB);
	Memory::Update<BYTE>(0x40ADD6, 0xEB);
	Memory::Update<BYTE>(0x53E994, 0xEB);
	Memory::Update<BYTE>(0x53ECD4, 0xEB);
	Memory::Update<BYTE>(0x53F8B3, 0xEB);
	Memory::Update<BYTE>(0x540593, 0xEB);
	Memory::Update<BYTE>(0x607090, 0xEB);
	Memory::Update<BYTE>(0x607095, 0xEB);
	Memory::Update<BYTE>(0x607141, 0xEB);
	Memory::Update<BYTE>(0x607146, 0xEB);
	Memory::Update<BYTE>(0x6071B3, 0xEB);
	Memory::Update<BYTE>(0x6071B8, 0xEB);
	
	// Messages on SelectCharacter
	Memory::Update<DWORD>(0x62590A, (DWORD)(&""));
	Memory::Update<DWORD>(0x625918, (DWORD)(&""));
	Memory::Update<DWORD>(0x62593C, (DWORD)(&""));
	Memory::Update<DWORD>(0x625957, (DWORD)(&""));
	Memory::Update<DWORD>(0x625964, (DWORD)(&""));
	Memory::Update<DWORD>(0x625988, (DWORD)(&""));
	Memory::Update<DWORD>(0x6259A3, (DWORD)(&""));
	Memory::Update<DWORD>(0x6259B0, (DWORD)(&""));
	Memory::Update<DWORD>(0x6259D4, (DWORD)(&""));

	// Centralize the ServerList
	Memory::Update<DWORD>(0x61F3DA, 0xFF);
	Memory::Update<DWORD>(0x61F3E0, 0xFF);
	Memory::Update<DWORD>(0x61F431, 0x120);
	Memory::Update<BYTE>(0x61F463, 0x4C);
	Memory::Update<DWORD>(0x61F7E0, 0xFC);
	Memory::Update<DWORD>(0x61F814, 0x16D);
	Memory::Update<DWORD>(0x61F81F, 0x1F3);
	Memory::Update<DWORD>(0x61FE1D, 0xFF);
	Memory::Update<DWORD>(0x61FE24, 0xFF);
	Memory::Update<DWORD>(0x61FE8F, 0x118);
	Memory::Update<DWORD>(0x61FE9E, 0x127);
	Memory::Update<DWORD>(0x61FEC7, 0x127);
	Memory::Update<DWORD>(0x61FE8F, 0x11D);
	Memory::Update<DWORD>(0x61FF12, 0x3F700000);
	Memory::Update<DWORD>(0x6201B7, 0x3F700000);
	Memory::Update<DWORD>(0x6201D6, 0x43B68000);
	Memory::Update<DWORD>(0x620251, 0x1B0);
	Memory::Update(0x6A9788, 383.0f);

	// Font
	Memory::Update<DWORD>(0x6B6654, DEFAULT_CHARSET);
	Memory::Update<BYTE>(0x4B4DEE, ANTIALIASED_QUALITY);
	Memory::Update<BYTE>(0x4B4E2E, ANTIALIASED_QUALITY);
	Memory::Update<BYTE>(0x4B4E6E, ANTIALIASED_QUALITY);
	Memory::Update<BYTE>(0x62F7B8, ANTIALIASED_QUALITY);

	// Lag with CTRL pressed
	Memory::Update<BYTE>(0x4519F8, 0x02);

	// Connection with localhost
	Memory::Update<BYTE>(0x4E0F1B, 0xEB);

	// Recoil
	//Memory::Update<BYTE>(0x4ECA80, 0xC3);

	// Load siege NPCs on any map
	Memory::Update<BYTE>(0x42B2D0, 0xEB);

	// Character dragging
	Memory::Update<BYTE>(0x550B25, 0xE9);
	Memory::Update<BYTE>(0x550B26, 0xEE);
	Memory::Update<BYTE>(0x550B27, 0x00);
	Memory::Update<BYTE>(0x550B28, 0x00);
	Memory::Update<BYTE>(0x550B29, 0x00);
	Memory::Nop<1>(0x550B2A);

	Memory::Update<BYTE>(0x58D019, 0xE9);
	Memory::Update<BYTE>(0x58D01A, 0xD9);
	Memory::Update<BYTE>(0x58D01B, 0x00);
	Memory::Update<BYTE>(0x58D01C, 0x00);
	Memory::Update<BYTE>(0x58D01D, 0x00);
	Memory::Nop<1>(0x58D01E);

	// Cursor
	Memory::Nop<1>(0x4CBC47);
	Memory::Nop<7>(0x4CBC65);
	Memory::Nop<1>(0x4CE934);
	Memory::Nop<1>(0x4CE958);
	Memory::Nop<6>(0x4CE96B);

	// Crash audio
	if (waveOutGetNumDevs() < 1)
	{
		Memory::Update<BYTE>(0x5750324, 0x00);
	}

	// Item glow
	Memory::Update<BYTE>(0x5F9CB9, 0x83);
	Memory::Update<BYTE>(0x5F9CBA, 0xFB);
	Memory::Update<BYTE>(0x5F9CBB, 0x10);

	Memory::Nop<5>(0x44AE85);
	Memory::Nop<5>(0x44AEAE);
	Memory::Nop<5>(0x44B81D);
	Memory::Nop<5>(0x44B859);
	Memory::Nop<5>(0x44B8AC);
	Memory::Nop<5>(0x44B8FF);
	Memory::Nop<5>(0x4A784A);

	// Monster target
	Memory::Update<BYTE>(0x4C4FF8, {0x83, 0xC4, 0x04, 0xC6, 0x86, 0x71, 0x03, 0x00, 0x00, 0x01, 0xC7, 0x86, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0xC7, 0x86, 0x94, 0x03, 0x00, 0x00, 0xFF, 0xFF});
	Memory::Nop<4>(0x4C5015);

	// Attack animation
	Memory::Nop<1>(0x42FBAF);
	Memory::Nop<14>(0x42FBB6);

	// MakePreviewChar
	Memory::Update<WORD>(0x50A5D7, 0xFFF);
	Memory::Update<WORD>(0x50A619, 0xFFF);
	Memory::Update<WORD>(0x5AAFF8, 0xFFF);
	Memory::Update<WORD>(0x5AB5C9, 0xFFF);

	// Remove item blocked message for gms
	Memory::Nop<167>(0x62582B);

	// Remove message: <Map> region
	Memory::Nop<5>(0x4C18F7);
	Memory::Nop<49>(0x4C18FF);
	Memory::Nop<54>(0x4BEAFD);

	// Remove monsters name from top
	Memory::Nop<74>(0x5AAB4B);

	// Delete character on any level
	Memory::Update<BYTE>(0x623492, 0xEB);

	// Change summon name position (elf)
	Memory::Nop<6>(0x59AECD);

	// Change summon name color to white (when equip a pet)
	Memory::Hook<true>(0x59AEAC, this->SummonNameColor);

	// CPU
	Memory::Hook<true>(0x628F99, this->Optimize);


	// Animation speed fix
	Memory::Update<BYTE>(0x4F0B83, 4);

	// Remove lock
	Memory::Nop<7>(0x610520);
	Memory::Nop<7>(0x610CA8);
	Memory::Nop<7>(0x611352);
	Memory::Nop<7>(0x6378D2);

	// Fix Valley of Loren on some PC's
	Memory::Nop<3>(0x691217);

	// Add new maps
	Memory::Hook<true>(0x64C6DB, this->LoadMapName);

	// Remove error corrupted .map, .att. .obj
	Memory::Update<BYTE>(0x607090, 0xEB);
	Memory::Update<BYTE>(0x607095, 0xEB);
	Memory::Update<BYTE>(0x607141, 0xEB);
	Memory::Update<BYTE>(0x607146, 0xEB);
	Memory::Update<BYTE>(0x6071B3, 0xEB);
	Memory::Update<BYTE>(0x6071B8, 0xEB);

	// Remove message: <Mapa> Region
	Memory::Nop<5>(0x4C18F7);
	Memory::Nop<49>(0x4C18FF);
	Memory::Nop<54>(0x4BEAFD);

	//Load new maps
	try
	{
		auto Maps = this->GetDirectories(".\\Data");
		int Map;

		for (const auto& i : Maps)
		{
			Map = std::stoi(i.substr(5));

			if (!((Map >= 1 && Map <= 12) || Map == 19 || Map == 25 || (Map >= 31 && Map <= 32) || Map == 34 || Map == 35))
			{
				InterfaceMaps.push_back(Map);
			}
		}
	}
	catch (...)
	{
	}
}

std::vector<std::string> Patch::GetDirectories(const std::string& s)
{
	std::vector<std::string> r;
	std::string path;
	auto directory = std::experimental::filesystem::recursive_directory_iterator(s);

	for (auto& p : directory)
	{
		if (p.status().type() == std::experimental::filesystem::file_type::directory)
		{
			path = p.path().string().substr(7);

			if (!_memicmp("world", path.c_str(), 5))
			{
				r.push_back(path);
			}
		}
	}

	return r;
}
void __declspec(naked) Patch::Optimize()
{
	static DWORD Local = 0x628F9F;

	__asm 
	{
		PUSH 1;
		CALL DWORD PTR DS : [0x6A7148] ;
		CALL DWORD PTR DS : [0x6A7144] ;
		JMP Local;
	}
}

void __declspec(naked) Patch::SummonNameColor()
{
	static DWORD Local = 0x59AEB1;
	static DWORD Function = 0x5AA760;

	__asm 
	{
		PUSHAD;
	}

	glColor3f(1.0f, 1.0f, 1.0f);

	__asm 
	{
		POPAD;
		CALL Function;
		JMP Local;
	}
}

std::vector<int> InterfaceMaps = {};
void __declspec(naked) Patch::LoadMapName()
{
	static DWORD Local = 0x64C6E0;
	static DWORD Function[2] = { 0x64D480, 0x4279A0 };
	static size_t i;
	static char Buffer[50];
	static char* Pointer = &Buffer[0];
	static int Map;

	__asm
	{
		PUSH EDI;
		PUSHAD;
	}

	for (i = 0; i < InterfaceMaps.size(); ++i)
	{
		Map = InterfaceMaps.at(i) - 1;
		wsprintf(Buffer, "Customs\\Mapname\\Mapname%d.tga", Map + 1);

		__asm
		{
			POPAD;
			LEA EAX, DWORD PTR SS : [EBP - 0x4];
			PUSH EAX;
			MOV ECX, EBX;
			MOV EDI, Map;
			MOV DWORD PTR SS : [EBP - 0x4], EDI;
			CALL Function[0];
			MOV EDX, EAX;
			MOV EDI, Pointer;
			OR ECX, 0xFFFFFFFF;
			XOR EAX, EAX;
			REPNE SCAS BYTE PTR ES : [EDI];
			NOT ECX;
			DEC ECX;
			PUSH ECX;
			PUSH Pointer;
			MOV ECX, EDX;
			CALL Function[4];
			PUSHAD;
		}
	}

	__asm
	{
		LEA EAX, DWORD PTR SS : [EBP - 0x4];
		PUSH EAX;
		JMP Local;
	}
}

Patch gPatch;
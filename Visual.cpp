#include "Library.h"
#include "Visual.h"
#include "User.h"

Visual::Visual()
{
}

Visual::~Visual()
{
}

void Visual::Hook()
{
	// Damage
	Memory::Hook<false>(0x4C4375, this->DrawDamage);
	Memory::Hook<false>(0x4C4C01, this->DrawDamage); // Miss
	Memory::Hook<false>(0x4C4D66, this->DrawDamage);
	Memory::Hook<false>(0x4C4DB6, this->DrawDamage);
	Memory::Hook<false>(0x4C4E3F, this->DrawDamage);
	Memory::Hook<false>(0x4C4E8F, this->DrawDamage);
	Memory::Hook<false>(0x4C4EAE, this->DrawDamage);
	Memory::Hook<false>(0x4C83F1, this->DrawDamage);
	Memory::Hook<false>(0x4C8D46, this->DrawDamage);
	Memory::Hook<false>(0x4C8D7B, this->DrawDamage);
	Memory::Hook<false>(0x4C9828, this->DrawDamage);
	Memory::Hook<false>(0x4C985D, this->DrawDamage);

	// HP
	//Memory::Hook<false>(0x59A086, this->FormatPoint);
	Memory::Hook<true>(0x5DEA11, this->DrawHP1);
	Memory::Hook<true>(0x599361, this->DrawHP2);
	Memory::Hook<true>(0x5990B5, this->DrawHP3);
	Memory::Hook<true>(0x599250, this->DrawHP4);
	Memory::Hook<true>(0x59A077, this->DrawHP5);
	Memory::Nop<6>(0x599234);
	Memory::Nop<6>(0x59923F);
	Memory::Update<DWORD>(0x59A06E, 0x41100000); // Tamanho	- Life
	Memory::Update<DWORD>(0x59A073, 0x41000000); // Tamanho	- Life
	Memory::Update<DWORD>(0x59A082, 0x42FC0000); // Posição X - Life
	Memory::Update<DWORD>(0x59A07D, 0x43E98000); // Posição Y - Life

	// MP
	//Memory::Hook<false>(0x59A0AD, this->FormatPoint);
	Memory::Hook<true>(0x5DEB24, this->DrawMP1);
	Memory::Hook<true>(0x599426, this->DrawMP2);
	Memory::Hook<true>(0x5990D2, this->DrawMP3);
	Memory::Hook<true>(0x59A09C, this->DrawMP4);
	Memory::Hook<true>(0x54E49F, this->CheckMP1);
	Memory::Hook<true>(0x54DC33, this->CheckMP2);
	Memory::Hook<true>(0x556113, this->CheckMP3);
	Memory::Hook<true>(0x5703B1, this->CheckMP4);
	Memory::Hook<true>(0x573723, this->CheckMP5);
	Memory::Hook<true>(0x57A4E1, this->CheckMP6);
	Memory::Hook<true>(0x5834AA, this->CheckMP7);
	Memory::Nop<6>(0x5990BF);
	Memory::Nop<6>(0x5990DE);
	Memory::Update<DWORD>(0x59A093, 0x41100000); // Tamanho	- Mana
	Memory::Update<DWORD>(0x59A098, 0x41000000); // Tamanho	- Mana
	Memory::Update<DWORD>(0x59A0A9, 0x44020000); // Posição X - Mana
	Memory::Update<DWORD>(0x59A0A2, 0x43E98000); // Posição Y - Mana

	// BP
	//Memory::Hook<false>(0x598978, this->FormatPoint);
	Memory::Hook<true>(0x5989B5, this->DrawBP1);
	Memory::Hook<true>(0x5987EE, this->DrawBP2);
	Memory::Hook<true>(0x598809, this->DrawBP3);
	Memory::Hook<true>(0x54E3AA, this->CheckBP1);
	Memory::Hook<true>(0x556985, this->CheckBP2);
	Memory::Hook<true>(0x570B2E, this->CheckBP3);
	Memory::Hook<true>(0x573E78, this->CheckBP4);
	Memory::Hook<true>(0x57AC05, this->CheckBP5);
	Memory::Hook<true>(0x583C89, this->CheckBP6);
	Memory::Nop<5>(0x598801);
	Memory::Update<DWORD>(0x598964, 0x41100000); // Tamanho	- BP
	Memory::Update<DWORD>(0x598969, 0x41000000); // Tamanho	- BP
	Memory::Update<DWORD>(0x598974, 0x440D0000); // Posição X - BP
	Memory::Update<DWORD>(0x59896F, 0x43E98000); // Posição Y - BP

	// LevelUpPoints
	Memory::Hook<true>(0x5DEE89, this->DrawLevelUpPoints);

	// Coordinates
	Memory::Hook<true>(0x599EAE, this->GetX);
	Memory::Hook<true>(0x599F81, this->GetY);

	// Character attributes 
	Memory::Hook<true>(0x543B18, this->AttackDamage);
	Memory::Hook<true>(0x5443CB, this->MagicDamage);
	Memory::Hook<true>(0x54475C, this->AttackRate);
	Memory::Hook<true>(0x54482C, this->Speed);
	Memory::Hook<true>(0x5451F9, this->DefenseRate);
	Memory::Hook<true>(0x5453A6, this->Defense);
}

void Visual::DrawDamage(int Unk1, int Damage, int Unk2, int Unk3, char Unk4)
{
	if (gUser.Damage > 0)
	{
		Damage = gUser.Damage;
	}

	pDrawDamage(Unk1, Damage, Unk2, Unk3, Unk4);
}

// Feita para formatar os pontos na interface de HP, MP e BP
// Ex: 1.0K 2.5M e etc.
// Não funciona perfeitamente porque o ponto e a letra no final não são exibidas na interface
// É porque no arquivo de fontes dentro da pasta Interface não exista as letras e o ponto
// Talvez adicionando, funcione, porém, necessita entender como isso funciona primeiro.

/*float Visual::FormatPoint(float X, float Y, DWORD Point, float Unk1, float Unk2) {
	char Buffer[20];

	if (Point >= 1000000000) {
		sprintf_s(Buffer, "%.1fB", (float)(Point / 1000000000.f));
	} else if (Point >= 1000000) {
		sprintf_s(Buffer, "%.1fM", (float)(Point / 1000000.f));
	} else if (Point >= 1000) {
		sprintf_s(Buffer, "%.1fK", (float)(Point / 1000.f));
	} else {
		sprintf_s(Buffer, "%u", Point);
	}

	int Size = strlen(Buffer);
	float Result = X - (float)(Size) * Unk1 * 0.5;

	if (Size <= 0) {
		return Result;
	}

	float Value;

	for (int i = 0; i < Size; ++i) {
		pUnkFormatPoint(1, Result, Y, Unk1, Unk2, ((float)(Buffer[i] - 48) * 0.0625), 0, 0.0625, 0.5, 1, 1);
		Result += Unk1 * 0.69999999;
	}

	return Result;
}*/

void __declspec(naked) Visual::DrawHP1()
{
	static DWORD Local = 0x5DEA19;

	__asm 
	{
		MOV ECX, gUser.MaxHP;
		MOV EDX, gUser.HP;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawHP2()
{
	static DWORD Local = 0x599367;

	__asm 
	{
		MOV ECX, gUser.MaxHP;
		MOV ESI, gUser.HP;
		LEA EDX, [EBP - 0x94];
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawHP3()
{
	static DWORD Local = 0x5990C5;

	__asm 
	{
		MOV EDX, gUser.MaxHP;
		MOV EAX, gUser.HP;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawHP4()
{
	static DWORD Local = 0x599255;

	__asm 
	{
		XOR EDI, EDI;
		CMP EAX, EDI;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawHP5()
{
	static DWORD Local = 0x59A07C;

	__asm 
	{
		MOV EAX, gUser.HP;
		PUSH EAX;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawMP1()
{
	static DWORD Local = 0x5DEB2C;

	__asm 
	{
		MOV EDX, gUser.MaxMP;
		MOV ECX, gUser.MP;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawMP2()
{
	static DWORD Local = 0x59942C;

	__asm 
	{
		MOV EDX, gUser.MaxMP;
		MOV EBX, gUser.MP;
		LEA EAX, [EBP - 0x94];
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawMP3()
{
	static DWORD Local = 0x5990E4;

	__asm 
	{
		MOV ECX, gUser.MaxMP;
		MOV EAX, gUser.MP;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawMP4()
{
	static DWORD Local = 0x59A0A1;

	__asm 
	{
		MOV EDX, gUser.MP;
		PUSH EDX;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckMP1()
{
	static DWORD Local = 0x54E4A6;

	__asm 
	{
		MOV EDX, gUser.MP;
		MOV EAX, DWORD PTR SS : [EBP - 0x44] ;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckMP2()
{
	static DWORD Local = 0x54DC39;

	__asm 
	{
		MOV ECX, gUser.MP;
		CMP ECX, EDX;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckMP3()
{
	static DWORD Local = 0x556119;

	__asm 
	{
		MOV ECX, gUser.MP;
		CMP ECX, EDX;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckMP4()
{
	static DWORD Local = 0x5703B7;

	__asm 
	{
		MOV EDX, gUser.MP;
		CMP ECX, EDX;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckMP5()
{
	static DWORD Local = 0x573729;

	__asm 
	{
		MOV EDX, gUser.MP;
		CMP ECX, EDX;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckMP6()
{
	static DWORD Local = 0x57A4E7;

	__asm 
	{
		MOV EDX, gUser.MP;
		CMP ECX, EDX;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckMP7()
{
	static DWORD Local = 0x5834B0;

	__asm 
	{
		MOV ECX, gUser.MP;
		CMP EDX, ECX;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawBP1()
{
	static DWORD Local = 0x5989BA;

	__asm 
	{
		MOV EDI, gUser.MaxBP;
		MOV ESI, gUser.BP;
		PUSH EDI;
		PUSH ESI;
		LEA ECX, DWORD PTR SS : [EBP - 0x7C] ;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawBP2()
{
	static DWORD Local = 0x5987F6;

	__asm 
	{
		MOV EAX, gUser.MaxBP;
		CMP EAX, 1;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawBP3()
{
	static DWORD Local = 0x59880F;

	__asm 
	{
		MOV EAX, gUser.BP;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckBP1()
{
	static DWORD Local = 0x54E3B1;

	__asm 
	{
		MOV EDX, gUser.BP;
		MOV EAX, DWORD PTR SS : [EBP - 0x3C] ;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckBP2()
{
	static DWORD Local = 0x55698F;

	__asm 
	{
		MOV ECX, gUser.BP;
		MOV EAX, DWORD PTR SS : [EBP - 0x2D0] ;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckBP3()
{
	static DWORD Local = 0x570B35;

	__asm 
	{
		MOV EDX, gUser.BP;
		MOV EAX, DWORD PTR SS : [EBP - 0x7C] ;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckBP4()
{
	static DWORD Local = 0x573E7F;

	__asm 
	{
		MOV ECX, gUser.BP;
		MOV EAX, DWORD PTR SS : [EBP - 0x78] ;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckBP5()
{
	static DWORD Local = 0x57AC0C;

	__asm 
	{
		MOV ECX, gUser.BP;
		MOV EAX, DWORD PTR SS : [EBP - 0x54] ;
		JMP Local;
	}
}

void __declspec(naked) Visual::CheckBP6()
{
	static DWORD Local = 0x583C90;

	__asm 
	{
		MOV ECX, gUser.BP;
		MOV EAX, DWORD PTR SS : [EBP - 0x54] ;
		JMP Local;
	}
}

void __declspec(naked) Visual::DrawLevelUpPoints()
{
	static DWORD Local = 0x5DEE8E;

	__asm 
	{
		MOV EAX, gUser.LevelUpPoints;
		PUSH EAX;
		JMP Local;
	}
}

void __declspec(naked) Visual::GetX()
{
	static DWORD Local = 0x599EB3;

	__asm
	{
		PUSH 0x41000000;
		MOV gUser.X, EDI;
		JMP Local;
	}
}

void __declspec(naked) Visual::GetY()
{
	static DWORD Local = 0x599F86;

	__asm
	{
		PUSH 0x41000000;
		MOV gUser.Y, EDI;
		JMP Local;
	}
}

void __declspec(naked) Visual::AttackDamage()
{
	static DWORD Local = 0x543D08;
	static UserObject* User;

	__asm
	{
		MOV User, ECX;
		PUSHAD;
	}

	User->AttackDamageMinLeft = gUser.AttackDamageLeft[0];
	User->AttackDamageMaxLeft = gUser.AttackDamageLeft[1];
	User->AttackDamageMinRight = gUser.AttackDamageRight[0];
	User->AttackDamageMaxRight = gUser.AttackDamageRight[1];

	__asm
	{
		POPAD;
		LEA EAX, DWORD PTR DS : [ECX + 0x52];
		MOV DWORD PTR SS : [EBP - 0x8], EAX;
		LEA EAX, DWORD PTR DS : [ECX + 0x54];
		MOV DWORD PTR SS : [EBP - 0x2C], EAX;
		MOV DWORD PTR SS : [EBP - 0x28], EAX;
		LEA EBX, DWORD PTR DS : [ECX + 0x50];
		LEA EDX, DWORD PTR DS : [ECX + 0x52];
		LEA ESI, DWORD PTR DS : [ECX + 0x54];
		LEA EDI, DWORD PTR DS : [ECX + 0x56];
		JMP Local;
	}
}

void __declspec(naked) Visual::MagicDamage() 
{
	static DWORD Local = 0x5443FA;
	static UserObject* User;

	__asm
	{
		MOV User, EBX;
		MOV DWORD PTR SS : [EBP - 0x24], ECX;
		PUSHAD;
	}

	User->MagicDamageMin = gUser.MagicDamage[0];
	User->MagicDamageMax = gUser.MagicDamage[1];

	__asm
	{
		POPAD;
		LEA EDI, DWORD PTR DS : [EBX + 0x5C];
		LEA EAX, DWORD PTR DS : [EBX + 0xE3C];
		LEA EDX, DWORD PTR DS : [EBX + 0xDF4];
		JMP Local;
	}
}

void __declspec(naked) Visual::AttackRate()
{
	static DWORD Local = 0x5447E6;
	static UserObject* User;

	__asm
	{
		MOV User, ECX;
		PUSHAD;
	}

	User->AttackRate = gUser.AttackRate;

	__asm
	{
		POPAD;
		LEA EDX, DWORD PTR DS : [ECX + 0x4E];
		JMP Local;
	}
}

void __declspec(naked) Visual::Speed()
{
	static DWORD Local = 0x5448FB;
	static UserObject* User;

	__asm
	{
		MOV User, ESI;
		PUSHAD;
	}

	User->AttackSpeed = gUser.AttackSpeed;
	User->MagicSpeed = gUser.MagicSpeed;

	__asm
	{
		POPAD;
		LEA EBX, DWORD PTR DS : [ESI + 0x4C];
		LEA EAX, DWORD PTR DS : [ESI + 0x58];
		MOV DWORD PTR SS : [EBP - 0xC], EBX;
		MOV DWORD PTR SS : [EBP - 0x10], EAX;
		JMP Local;
	}
}

void __declspec(naked) Visual::DefenseRate()
{
	static DWORD Local = 0x545246;
	static UserObject* User;

	__asm
	{
		MOV User, EBX;
		PUSHAD;
	}

	User->DefenseRate = gUser.DefenseRate;

	__asm
	{
		POPAD;
		LEA ESI, DWORD PTR DS : [EBX + 0x60];
		JMP Local;
	}
}

void __declspec(naked) Visual::Defense()
{
	static DWORD Local = 0x545430;
	static UserObject* User;

	__asm
	{
		MOV User, ESI;
		PUSHAD;
	}

	User->Defense = gUser.Defense;

	__asm
	{
		POPAD;
		LEA EDI, DWORD PTR DS : [ESI + 0x62];
		JMP Local;
	}
}

Visual gVisual;
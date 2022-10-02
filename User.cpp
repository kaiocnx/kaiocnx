#include "Library.h"
#include "User.h"
#include "Patent.h"

User::User() : Index(-1), HP(0), MaxHP(0), MP(0), MaxMP(0), BP(0), MaxBP(0), LevelUpPoints(0), Damage(-1), X(0), Y(0), AttackDamageLeft{0, 0}, AttackDamageRight{0, 0}, MagicDamage{0, 0}, AttackRate(0), AttackSpeed(0), MagicSpeed(0), Defense(0), DefenseRate(0), Sign{0, 0, 0, 0, 0}, Patent(0)
{
}

User::~User()
{
}

void User::Hook()
{
	Memory::Hook<false>(0x54AE21, this->DrawInfo);
	Memory::Update<BYTE>(0x54AE16, 0x53);
	Memory::Nop<1>(0x54AE17);

	Memory::Hook<true>(0x4CC640, this->UpdateInfo);
	Memory::Hook<true>(0x54482C, this->SetSpeed);
}

void User::DrawInfo(int X, int Y, float Unk1, float Unk2, int Unk3, int Unk4, char* Name, int Unk5)
{
	ViewportInfo* Viewport = gViewport.GetByName(Name);

	if (Viewport && Viewport->Type == VIEWPORT_USER)
	{
		ViewportCustomInfo* Custom = gViewport.GetCustom(Viewport->Index);

		gPatent.Draw(X, Y, Viewport, Custom);

		int PosX = X;
		int PosY = Y - 28;
		float ScaleX, ScaleY, MarginX, MarginY;

		if (Viewport->GuildIndex != -1)
		{
			char* Alliance = GET_ALLIANCE_NAME(Viewport->GuildIndex);

			if (Alliance[0] != 0) 
			{
				PosY -= 14;
			}

			PosY -= 9;
		}

		ScaleX = 20 * 0.00390625f;
		ScaleY = (28 - 1.0) * 0.00390625f;

		if ((Viewport->ViewSkillState & 0x100) == 0x100)
		{
			MarginX = ((32 * (15 % 8)) * 0.00390625f) + (6 * 0.00390625f);
			MarginY = ((36 * (15 / 8)) * 0.00390625f) + (3 * 0.00390625f);

			pDrawImage(0x12A, (float)(PosX), (float)(PosY), 15.f, 20.f, MarginX, MarginY, ScaleX, ScaleY, 0, 1);

			PosX += 17;
		}

		if ((Viewport->ViewSkillState & 0x2000000) == 0x2000000)
		{
			MarginX = ((32 * (27 % 8)) * 0.00390625f) + (6 * 0.00390625f);
			MarginY = ((36 * (27 / 8)) * 0.00390625f) + (3 * 0.00390625f);

			pDrawImage(0x12A, (float)(PosX), (float)(PosY), 15.f, 20.f, MarginX, MarginY, ScaleX, ScaleY, 0, 1);

			PosX += 17;

			MarginX = ((32 * (26 % 8)) * 0.00390625f) + (6 * 0.00390625f);
			MarginY = ((36 * (26 / 8)) * 0.00390625f) + (3 * 0.00390625f);

			pDrawImage(0x12A, (float)(PosX), (float)(PosY), 15.f, 20.f, MarginX, MarginY, ScaleX, ScaleY, 0, 1);

			PosX += 17;
		}
		else
		{
			if ((Viewport->ViewSkillState & 0x4) == 0x4)
			{
				MarginX = ((32 * (27 % 8)) * 0.00390625f) + (6 * 0.00390625f);
				MarginY = ((36 * (27 / 8)) * 0.00390625f) + (3 * 0.00390625f);

				pDrawImage(0x12A, (float)(PosX), (float)(PosY), 15.f, 20.f, MarginX, MarginY, ScaleX, ScaleY, 0, 1);

				PosX += 17;
			}

			if ((Viewport->ViewSkillState & 0x8) == 0x8)
			{
				MarginX = ((32 * (26 % 8)) * 0.00390625f) + (6 * 0.00390625f);
				MarginY = ((36 * (26 / 8)) * 0.00390625f) + (3 * 0.00390625f);

				pDrawImage(0x12A, (float)(PosX), (float)(PosY), 15.f, 20.f, MarginX, MarginY, ScaleX, ScaleY, 0, 1);

				PosX += 17;
			}
		}

		if ((Viewport->ViewSkillState & 0x10) == 0x10)
		{
			MarginX = ((32 * (47 % 8)) * 0.00390625f) + (6 * 0.00390625f);
			MarginY = ((36 * (47 / 8)) * 0.00390625f) + (3 * 0.00390625f);

			pDrawImage(0x12A, (float)(PosX), (float)(PosY), 15.f, 20.f, MarginX, MarginY, ScaleX, ScaleY, 0, 1);

			PosX += 17;
		}

		if ((Viewport->ViewSkillState & 0x800) == 0x800)
		{
			MarginX = ((32 * (7 % 8)) * 0.00390625f) + (6 * 0.00390625f);
			MarginY = ((36 * (7 / 8)) * 0.00390625f) + (3 * 0.00390625f);

			pDrawImage(0x12B, (float)(PosX), (float)(PosY), 15.f, 20.f, MarginX, MarginY, ScaleX, ScaleY, 0, 1);

			PosX += 17;
		}

		if ((Viewport->ViewSkillState & 0x8000) == 0x8000)
		{
			MarginX = ((32 * (0 % 8)) * 0.00390625f) + (6 * 0.00390625f);
			MarginY = ((36 * (0 / 8)) * 0.00390625f) + (3 * 0.00390625f);

			pDrawImage(0x68E, (float)(PosX), (float)(PosY), 15.f, 20.f, MarginX, MarginY, ScaleX, ScaleY, 0, 1);

			PosX += 17;
		}

		if ((Viewport->ViewSkillState & 0x10000) == 0x10000)
		{
			MarginX = ((32 * (1 % 8)) * 0.00390625f) + (6 * 0.00390625f);
			MarginY = ((36 * (1 / 8)) * 0.00390625f) + (3 * 0.00390625f);

			pDrawImage(0x68E, (float)(PosX), (float)(PosY), 15.f, 20.f, MarginX, MarginY, ScaleX, ScaleY, 0, 1);

			PosX += 17;
		}
	}

	pDrawUserInfo(X, Y, Unk1, Unk2, Unk3, Unk4, 0, Unk5);
}

void User::Update(int Index, std::function<void(UserObject*)> Callback)
{
	this->Callback = Callback;

	PMSG_LEVEL_UP_POINT_RECV pMsg;

	pMsg.header.set(0xF3, 0x06, sizeof(pMsg));
	pMsg.result = 16;

	pProtocolCore(0xF3, (LPBYTE)(&pMsg), sizeof(pMsg), Index);
}

void __declspec(naked) User::UpdateInfo()
{
	static DWORD Local = 0x4CC6BD;

	__asm 
	{
		MOV EAX, DWORD PTR DS : [0x7666A78] ;
		PUSHAD;
	}

	gUser.Callback((UserObject*)(USER_BASE));

	__asm 
	{
		POPAD;
		JMP Local;
	}
}

void __declspec(naked) User::SetSpeed()
{
	static DWORD Local = 0x5448FB;
	static UserObject* Object;

	__asm
	{
		MOV Object, ESI;
		PUSHAD;
	}

	Object->AttackSpeed = gUser.AttackSpeed;
	Object->MagicSpeed = gUser.MagicSpeed;

	__asm
	{
		POPAD;
		LEA EBX, DWORD PTR DS : [ESI + 0x4C] ;
		LEA EAX, DWORD PTR DS : [ESI + 0x58] ;
		MOV DWORD PTR SS : [EBP - 0xC] , EBX;
		MOV DWORD PTR SS : [EBP - 0x10] , EAX;
		JMP Local;
	}
}

User gUser;
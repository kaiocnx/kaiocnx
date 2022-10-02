#include "Library.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Load()
{
	//--------------------------------------------------
	// Novos monstros
	//--------------------------------------------------
	// Para adicionar um novo monstro/npc, basta:
	// this->Add(<monster_id>, <folder>, <file>, <is_npc?>);
	this->Add(259, FOLDER_NPC, "OracleLayla", true);
	this->Add(367, FOLDER_NPC_NEW, "Reset", true);
	this->Add(368, FOLDER_NPC_NEW, "PkWarden", true);
	this->Add(369, FOLDER_NPC_NEW, "CustomArena", true);
	this->Add(372, FOLDER_NPC_NEW, "MasterReset", true);

	//NPC Navidad (Snowman)
	this->Add(373, FOLDER_NPC_NEW, "Santa", true);
	this->Add(375, FOLDER_NPC_NEW, "Snowman", true);

	//Monsters Kubera mine
	this->Add(351, FOLDER_MONSTER, "Monster112", false);	//Mindigger
	this->Add(352, FOLDER_MONSTER, "Monster113", false);	//Mine Carrier
	this->Add(353, FOLDER_MONSTER, "Monster114", false);	//Mine Porter
	this->Add(354, FOLDER_MONSTER, "Monster115", false);	//Main Driller
	this->Add(355, FOLDER_MONSTER, "Monster116", false);	//Dead Digger
	this->Add(356, FOLDER_MONSTER, "Monster117", false);	//Dead Showbell
	this->Add(357, FOLDER_MONSTER, "Monster118", false);	//Dead Porter
	//Monsters Swamp of Peace
	this->Add(358, FOLDER_MONSTER, "Monster119", false);	//Sapi-Unis
	this->Add(359, FOLDER_MONSTER, "Monster120", false);	//Sapi-Duo
	this->Add(360, FOLDER_MONSTER, "Monster121", false);	//Sapi-Tres
	this->Add(361, FOLDER_MONSTER, "Monster122", false);	//Shadow Pawn
	this->Add(362, FOLDER_MONSTER, "Monster123", false);	//Shadow Knight
	this->Add(363, FOLDER_MONSTER, "Monster124", false);	//Shadow Look
	this->Add(364, FOLDER_MONSTER, "Monster125", false);	//Thunder Napin
	this->Add(365, FOLDER_MONSTER, "Monster126", false);	//Ghost Napin
	this->Add(366, FOLDER_MONSTER, "Monster127", false);	//Blaze Napin
	//Monsters Halloween
	this->Add(370, FOLDER_MONSTER, "Monster128", false);	//Hollow Jack
	this->Add(371, FOLDER_MONSTER, "Monster129", false);	//Hollow Lady
	//Monsters Navidad
	this->Add(350, FOLDER_MONSTER, "Monster111", false);	//Curse Goblin
	this->Add(374, FOLDER_MONSTER, "Monster130", false);	//Santa Curse

	this->Hook();
}

void Monster::Hook()
{
	Memory::Hook<false>(0x50ACE6, this->Renderize);
	Memory::Hook<false>(0x596CEA, this->DrawHP);
	Memory::Hook<true>(0x50AC73, this->MonsterType);
	Memory::Hook<true>(0x55B769, this->MonsterTalk);
}

void Monster::Add(WORD Index, const char* Folder, const char* File, bool IsNpc)
{
	this->Monsters[Index] = {(WORD)(16384 + this->Monsters.size()), Folder, File, IsNpc};
}

CustomMonster* Monster::Get(WORD Index)
{
	if (this->Monsters.count(Index) > 0)
	{
		return &this->Monsters.at(Index);
	}

	return nullptr;
}

ViewportInfo* Monster::Renderize(int Index, DWORD Unk1, int Unk2, int Unk3)
{
	auto Monster = gMonster.Get((WORD)(Index));

	if (Monster)
	{
		auto Model = gModel.GetInfo(Monster->Model);

		if (!*(BYTE*)(0x6B8D84) || Model->UnkWord26 <= 0)
		{
			pLoadModel(Monster->Model, Monster->Folder, Monster->File, -1);

			if (Model->UnkWord26 > 0)
			{
				DWORD Address = 0;

				for (short i = 0; i < Model->UnkWord26; i++)
				{
					*(float*)(Address + Model->UnkDword30 + 4) = 0.25f;
					Address += 16;
				}
			}
		}

		if (Model->UnkWord24 > 0)
		{
			pLoadTexture(Monster->Model, &Monster->Folder[5], GL_REPEAT, GL_NEAREST, 1);
		}

		auto Result = pRenderizeModel(Unk3, Monster->Model, Unk1, Unk2, 0);

		if (Index == 259)
		{
			Result->Size = 0.95f;
			Result->Angle1.Z += 140.f;
		}

		return Result;
	}

	return pRenderizeMonster(Index, Unk1, Unk2, Unk3);
}

void Monster::DrawHP()
{
	SelectObject(pHDC, pDefaultFont);

	int X = 0, Y = 0, Width = 80;
	Angle Angle;
	SIZE Size;
	ViewportInfo* Viewport;
	BYTE Percent;

	for (int i = 0; i < VIEWPORT_MAX; ++i)
	{
		Viewport = gViewport.GetByPosition(i);

		if (!Viewport->Live)
		{
			continue;
		}

		if (Viewport->Type == VIEWPORT_MONSTER)
		{
			Percent = gMonster.HPBar.GetPercent(Viewport->Index);

			if (Percent == (BYTE)(-1))
			{
				continue;
			}

			Angle.X = Viewport->Angle1.X;
			Angle.Y = Viewport->Angle1.Y;
			Angle.Z = Viewport->Angle1.Z + Viewport->Angle2.Z + 100.f;

			pGetPositionFromAngle(&Angle, &X, &Y);

			X -= (int)(floor(Width / 2.f));

			pEnableAlpha(1);
			glColor4f(0.f, 0.f, 0.f, 0.5f);
			pDrawForm((float)(X - 1), (float)(Y - 12), 2.f + (float)(Width), 17.f);

			glColor3f(0.9f, 0.f, 0.f);
			pDrawForm((float)(X), 1.f + Y, (float)((Percent * Width) / 100.f), 3.f);
			pDisableAlpha();

			GetTextExtentPoint(pHDC, Viewport->Name, strlen(Viewport->Name), &Size);
			Size.cx = 80 - (LONG)((float)(Size.cx) / pScreenDivisorX);

			if (Size.cx < 0)
			{
				Size.cx = 0;
			}
			else
			{
				Size.cx /= 2;
			}

			/*switch (Monster->Level) {
				case 7:		// Boss
					glColor4f(0.2f, 0.6f, 1.0f, 1.0f);
					break;
				case 6:		// Extremely Hard
					glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
					break;
				case 5:		// Very Hard
					glColor4f(1.0f, 0.40f, 0.40f, 1.0f);
					break;
				case 4:		// Hard
					glColor4f(1.0f, 0.71f, 0.71f, 1.0f);
					break;
				case 3:		// Easy
					glColor4f(0.71f, 0.94f, 0.71f, 1.0f);
					break;
				case 2:		// Very Easy
					glColor4f(0.40f, 0.94f, 0.40f, 1.0f);
					break;
				case 1:		// Extremely Easy
					glColor4f(0.0f, 0.94f, 0.0f, 1.0f);
					break;
				default:	// Normal
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					break;
			}*/

			//glColor4f(0.2f, 0.6f, 1.0f, 1.0f);
			glColor4f(1.f, 1.f, 1.f, 1.f);

			X += Size.cx;
			Y -= 9;

			if ((X >= 0 && X <= (pScreenWidthBase - (Size.cx / 2))) && (Y >= 0 && Y <= pScreenHeightBase))
			{
				pDrawText(X, Y, Viewport->Name, 0, 0, 0);
			}
		}
	}

	pDisableAlphaBlend();
	glColor3f(1.f, 1.f, 1.f);

	pDrawMonsterHP();
}

void __declspec(naked) Monster::MonsterType()
{
	static DWORD Local[3] = {0x50AC79, 0x50AC92, 0x50ACBA};
	static int Id;
	static CustomMonster* Monster;

	__asm
	{
		MOV Id, ESI;
		PUSHAD;
	}

	Monster = gMonster.Get((WORD)(Id));

	if (Monster)
	{
		if (Monster->IsNpc)
		{
			__asm
			{
				POPAD;
				JMP Local[4];
			}
		}

		__asm
		{
			POPAD;
			JMP Local[8];
		}
	}

	__asm
	{
		POPAD;
		CMP ESI, 0xC8;
		JMP Local[0];
	}
}

void __declspec(naked) Monster::MonsterTalk()
{
	static DWORD Local[3] = {0x55B76F, 0x55B782, 0x55B789};
	static WORD Id;
	static CustomMonster* Monster;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Monster = gMonster.Get(Id);

	if (Monster)
	{
		if (Monster->IsNpc)
		{
			__asm
			{
				POPAD;
				MOV BYTE PTR DS : [0x788C829] , 0x01;
				JMP Local[8];
			}
		}
		
		__asm
		{
			POPAD;
			MOV BYTE PTR DS : [0x788C829] , 0x00;
			JMP Local[8];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xF3;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

Monster gMonster;
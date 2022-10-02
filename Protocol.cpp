#include "Library.h"
#include "Protocol.h"
#include "Visual.h"
#include "User.h"
#include "Monster.h"
#include "Camera.h"
#include "Reconnect.h"
#include "Security.h"

Protocol::Protocol()
{
}

Protocol::~Protocol()
{
}

void Protocol::Hook()
{
	Memory::Hook<false>(0x4DB63D, this->Core);
}

int Protocol::Core(DWORD Protocol, LPBYTE Data, int Size, int Index)
{
	switch (Protocol)
	{
		case 0x12:
			return gProtocol.ViewportPlayerRecv(Index, Data);
		case 0x17:
			return gProtocol.UserDieRecv(Index, (PMSG_USER_DIE_RECV*)(Data));
		case 0x26:
			return gProtocol.LifeRecv(Index, (PMSG_LIFE_RECV*)(Data));
		case 0x27:
			return gProtocol.ManaRecv(Index, (PMSG_MANA_RECV*)(Data));
		case 0x9C:
			return gProtocol.RewardExperienceRecv(Index, (PMSG_REWARD_EXPERIENCE_RECV*)(Data));
		case 0xA3:
			return gProtocol.QuestRewardRecv(Index, (PMSG_QUEST_REWARD_RECV*)(Data));
		case 0xD7:
			return gProtocol.DamageRecv(Index, (PMSG_DAMAGE_RECV*)(Data));
		case 0xF1:
		{
			switch (GET_SUBHEAD(Data))
			{
				case 0x00:
					return gProtocol.ConnectClientRecv(Index, (PMSG_CONNECT_CLIENT_RECV*)(Data));
			}
		} break;
		case 0xF3:
		{
			switch (GET_SUBHEAD(Data))
			{
				case 0x03:
					return gProtocol.CharacterInfoRecv(Index, (PMSG_CHARACTER_INFO_RECV*)(Data));
				case 0x04:
					return gProtocol.CharacterRegenRecv(Index, (PMSG_CHARACTER_REGEN_RECV*)(Data));
				case 0x05:
					return gProtocol.LevelUpRecv(Index, (PMSG_LEVEL_UP_RECV*)(Data));
				case 0x06:
					return gProtocol.LevelUpPointRecv(Index, (PMSG_LEVEL_UP_POINT_RECV*)(Data));
				case 0x07:
					return gProtocol.MonsterDamageRecv(Index, (PMSG_MONSTER_DAMAGE_RECV*)(Data));
				case 0x41:
					return gProtocol.ReconnectRecv(Index, (PMSG_RECONNECT_RECV*)(Data));
				case 0xE0:
					return gProtocol.NewCharacterInfoRecv(Index, (PMSG_NEW_CHARACTER_INFO_RECV*)(Data));
				case 0xE1:
					return gProtocol.NewCharacterCalcRecv(Index, (PMSG_NEW_CHARACTER_CALC_RECV*)(Data));
				case 0xE2:
					return gProtocol.NewHPBarRecv(Index, Data);
				case 0xE3:
					return gProtocol.SignsRecv(Index, (PMSG_SIGNS_RECV*)(Data));
				case 0xE4:
					return gProtocol.LockRecv(Index, (PMSG_LOCK_RECV*)(Data));
				case 0xE5:
					return gProtocol.PingRecv(Index, (PMSG_PING_RECV*)(Data));
				case 0xF1:
					return gReconnect.ExitMenu2();
			}
		} break;
	}

	return pProtocolCore(Protocol, Data, Size, Index);
}

int Protocol::ConnectClientRecv(int Index, PMSG_CONNECT_CLIENT_RECV* Data)
{
	if (Data->Downgrade[0] == 1)
	{
		// Remove D
		Memory::Update<BYTE>(0x00594B18 + 1, 0x2F);
	}
	if (Data->Downgrade[1] == 1)
	{
		// Remove F
		Memory::Update<BYTE>(0x00594AA6 + 1, 0x2F);
	}
	if (Data->Downgrade[2] == 1)
	{
		// Remove M
		Memory::Update<BYTE>(0x00594ADF + 1, 0x2F);
	}
	if (Data->Downgrade[3] == 1)
	{
		// Remove S
		Memory::Update<BYTE>(0x005D3DF6 + 1, 0x2F);
	}
	if (Data->Downgrade[4] == 1)
	{
		// Remove T
		Memory::Update<BYTE>(0x005949BF + 1, 0x2F);
	}
	if (Data->Downgrade[5] == 1)
	{
		// Remove Command
		Memory::Nop<5>(0x59028D); //Disable Command Function
		Memory::Nop<5>(0x408ADF); //Disable Command Text
	}
	if (Data->Downgrade[6] == 1)
	{
		// Remove PShop Function
		Memory::Nop<5>(0x5D3DB6); //Disable PShop Function
		// Remove PShop Graphic
		Memory::Update<BYTE>(0x5E14A2, 0xE9);
		Memory::Update<BYTE>(0x5E14A2 + 1, 0x28);
		Memory::Update<BYTE>(0x5E14A2 + 2, 0x02);
		Memory::Update<BYTE>(0x5E14A2 + 3, 0x00);
		Memory::Update<BYTE>(0x5E14A2 + 4, 0x00);
		Memory::Update<BYTE>(0x5E14A2 + 5, 0x90);
	}
	if (Data->Downgrade[7] == 1)
	{
		// Remove Quest
		Memory::Nop<5>(0x41AFDB); //Disable Quest Function
		Memory::Nop<5>(0x41B019); //Disable Quest Function
		Memory::Nop<5>(0x41B01E); //Disable Quest Function
		Memory::Nop<5>(0x41B052); //Disable Quest Function
		Memory::Nop<5>(0x419B62); //Disable Quest Function
		Memory::Nop<5>(0x419B6B); //Disable Quest Function
	}
	if (Data->Downgrade[8] == 1)
	{
		// Remove Friends
		Memory::Nop<5>(0x590237); //Disable Friends Function
		Memory::Nop<5>(0x599764); //Disable Friends Text
	}
	if (Data->Downgrade[9] == 1)
	{
		// Remove DL Pet
		Memory::Nop<15>(0x5E5C4E);
		Memory::Update<BYTE>(0x422B99, 0xEB);
	}
	if (Data->Downgrade[10] == 1)
	{
		// Remove Ancient
		Memory::Nop<24>(0x5E16CF);
		Memory::Nop<22>(0x40D065);
	}

	gUser.Index = MAKE_NUMBERW(Data->index[0], Data->index[1]);

	DWORD VolumeSerialNumber;

	if (GetVolumeInformation("C:\\", 0, 0, &VolumeSerialNumber, 0, 0, 0, 0) == 0)
	{
		return 0;
	}

	UUID uuid;
	UuidCreateSequential(&uuid);

	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);

	PMSG_HARDWARE_ID_SEND pMsg;
	pMsg.header.set(0xF3, 0x40, sizeof(pMsg));
	pMsg.HardwardID[0] = VolumeSerialNumber ^ 0x12B586FE;
	pMsg.HardwardID[1] = ((SystemInfo.wProcessorLevel & 0xFFFF) | (SystemInfo.wProcessorRevision << 16)) ^ 0xB542D8E1;

	DataSend((LPBYTE)(&pMsg), sizeof(pMsg));

	return pProtocolCore(0xF1, (LPBYTE)(Data), Data->header.size, Index);
}

int Protocol::ViewportPlayerRecv(int Index, LPBYTE Data)
{
	PMSG_VIEWPORT_RECV* Info = (PMSG_VIEWPORT_RECV*)(Data);

	if (Info->count > 0)
	{
		static BYTE Buffer[8192];

		PMSG_VIEWPORT_RECV* Info = (PMSG_VIEWPORT_RECV*)(Data);
		PMSG_VIEWPORT_RECV pMsg;
		int Size = sizeof(PMSG_VIEWPORT_RECV);

		PMSG_VIEWPORT_PLAYER_NEW* Player;

		gViewport.ClearCustom();

		for (BYTE i = 0; i < Info->count; ++i)
		{
			Player = (PMSG_VIEWPORT_PLAYER_NEW*)(&Data[sizeof(PMSG_VIEWPORT_RECV) + (i * sizeof(PMSG_VIEWPORT_PLAYER_NEW))]);
			gViewport.AddCustom(Player->index, Player->Sign, Player->Patent);

			memcpy(&Buffer[Size], &Data[sizeof(PMSG_VIEWPORT_RECV) + (i * sizeof(PMSG_VIEWPORT_PLAYER_NEW))], sizeof(PMSG_VIEWPORT_PLAYER));

			Size += sizeof(PMSG_VIEWPORT_PLAYER);
		}

		pMsg.header.set(0x12, Size);
		pMsg.count = Info->count;

		memcpy(Buffer, &pMsg, sizeof(pMsg));

		return pProtocolCore(0x12, Buffer, Size, Index);
	}

	return pProtocolCore(0x12, Data, MAKE_NUMBERW(Info->header.size[0], Info->header.size[1]), Index);
}

int Protocol::UserDieRecv(int Index, PMSG_USER_DIE_RECV * Data)
{
	int UserIndex = MAKE_NUMBERW(Data->index[0], Data->index[1]);

	if (UserIndex == gUser.Index)
	{
		gUser.HP = 0;

		gUser.Update(Index, [](UserObject * User)
		{
			User->HP = 0;
		});
	}

	return pProtocolCore(0x17, (LPBYTE)(Data), Data->header.size, Index);
}

int Protocol::LifeRecv(int Index, PMSG_LIFE_RECV * Data)
{
	switch (Data->type)
	{
		case 0xFE:
		{
			gUser.MaxHP = Data->HP;

			gUser.Update(Index, [](UserObject * User)
			{
				User->MaxHP = GET_MAX_WORD_VALUE(gUser.MaxHP);
			});
		} break;
		case 0xFF:
		{
			gUser.HP = ((gUser.HP == 0) ? gUser.HP : Data->HP);

			gUser.Update(Index, [&](UserObject * User)
			{
				User->HP = GET_MAX_WORD_VALUE(gUser.HP);
			});
		} break;
	}

	PMSG_LIFE_SEND pMsg;

	pMsg.header.set(0x26, sizeof(pMsg));
	pMsg.type = Data->type;
	pMsg.life[0] = SET_NUMBERHB(GET_MAX_WORD_VALUE(Data->HP));
	pMsg.life[1] = SET_NUMBERLB(GET_MAX_WORD_VALUE(Data->HP));
	pMsg.flag = Data->flag;

	return pProtocolCore(0x26, (LPBYTE)(&pMsg), sizeof(pMsg), Index);
}

int Protocol::ManaRecv(int Index, PMSG_MANA_RECV * Data)
{
	switch (Data->type)
	{
		case 0xFE:
		{
			gUser.MaxMP = Data->MP;
			gUser.MaxBP = Data->BP;

			gUser.Update(Index, [](UserObject * User)
			{
				User->MaxMP = GET_MAX_WORD_VALUE(gUser.MaxMP);
				User->MaxBP = GET_MAX_WORD_VALUE(gUser.MaxBP);
			});
		} break;
		case 0xFF:
		{
			gUser.MP = Data->MP;
			gUser.BP = Data->BP;

			gUser.Update(Index, [](UserObject * User)
			{
				User->MP = GET_MAX_WORD_VALUE(gUser.MP);
				User->BP = GET_MAX_WORD_VALUE(gUser.BP);
			});
		} break;
	}

	PMSG_MANA_SEND pMsg;

	pMsg.header.set(0x27, sizeof(pMsg));
	pMsg.type = Data->type;
	pMsg.mana[0] = SET_NUMBERHB(GET_MAX_WORD_VALUE(Data->MP));
	pMsg.mana[1] = SET_NUMBERLB(GET_MAX_WORD_VALUE(Data->MP));
	pMsg.bp[0] = SET_NUMBERHB(GET_MAX_WORD_VALUE(Data->BP));
	pMsg.bp[1] = SET_NUMBERLB(GET_MAX_WORD_VALUE(Data->BP));

	return pProtocolCore(0x27, (LPBYTE)(&pMsg), sizeof(pMsg), Index);
}

int Protocol::RewardExperienceRecv(int Index, PMSG_REWARD_EXPERIENCE_RECV * Data)
{
	gUser.Damage = Data->Damage;

	PMSG_REWARD_EXPERIENCE_SEND pMsg;

	pMsg.header.setE(0x9C, sizeof(pMsg));
	pMsg.index[0] = Data->index[0];
	pMsg.index[1] = Data->index[1];
	pMsg.experience[0] = Data->experience[0];
	pMsg.experience[1] = Data->experience[1];
	pMsg.damage[0] = SET_NUMBERHB(GET_MAX_WORD_VALUE(Data->Damage));
	pMsg.damage[1] = SET_NUMBERLB(GET_MAX_WORD_VALUE(Data->Damage));

	return pProtocolCore(0x9C, (LPBYTE)(&pMsg), sizeof(pMsg), Index);
}

int Protocol::QuestRewardRecv(int Index, PMSG_QUEST_REWARD_RECV * Data)
{
	gUser.LevelUpPoints = Data->LevelUpPoint;

	return pProtocolCore(0xA3, (LPBYTE)(Data), Data->header.size - 4, Index);
}

int Protocol::DamageRecv(int Index, PMSG_DAMAGE_RECV * Data)
{
	int UserIndex = MAKE_NUMBERW(Data->index[0], Data->index[1]);

	if (UserIndex == gUser.Index)
	{
		gUser.HP = Data->HP;

		gUser.Update(Index, [](UserObject * User)
		{
			User->HP = GET_MAX_WORD_VALUE(gUser.HP);
		});
	}

	gUser.Damage = Data->Damage;

	PMSG_DAMAGE_SEND pMsg;

	pMsg.header.set(0xD7, sizeof(pMsg));
	pMsg.index[0] = Data->index[0];
	pMsg.index[1] = Data->index[1];
	pMsg.type = Data->type;
	pMsg.damage[0] = SET_NUMBERHB(GET_MAX_WORD_VALUE(Data->Damage));
	pMsg.damage[1] = SET_NUMBERLB(GET_MAX_WORD_VALUE(Data->Damage));

	return pProtocolCore(0xD7, (LPBYTE)(&pMsg), sizeof(pMsg), Index);
}

int Protocol::CharacterInfoRecv(int Index, PMSG_CHARACTER_INFO_RECV* Data)
{
	gReconnect.SetStep(STEP_RECONNECT);
	gReconnect.SetState(RSTATE_ONLINE);

	gCamera.FixClip();

	gUser.HP = Data->HP;
	gUser.MaxHP = Data->MaxHP;
	gUser.MP = Data->MP;
	gUser.MaxMP = Data->MaxMP;
	gUser.BP = Data->BP;
	gUser.MaxBP = Data->MaxBP;
	gUser.LevelUpPoints = Data->LevelUpPoint;

	if (Data->Sign != 0)
	{
		gUser.Sign[0] = 16 + (Data->Sign - 1);
	}

	gUser.Patent = Data->Patent;

	PMSG_CHARACTER_INFO_SEND pMsg;

	pMsg.header.set(0xF3, 0x03, sizeof(pMsg));
	pMsg.X = Data->X;
	pMsg.Y = Data->Y;
	pMsg.Map = Data->Map;
	pMsg.Dir = Data->Dir;
	pMsg.Experience = Data->Experience;
	pMsg.NextExperience = Data->NextExperience;
	pMsg.LevelUpPoint = GET_MAX_WORD_VALUE(Data->LevelUpPoint);
	pMsg.Strength = Data->Strength;
	pMsg.Dexterity = Data->Dexterity;
	pMsg.Vitality = Data->Vitality;
	pMsg.Energy = Data->Energy;
	pMsg.HP = GET_MAX_WORD_VALUE(Data->HP);
	pMsg.MaxHP = GET_MAX_WORD_VALUE(Data->MaxHP);
	pMsg.MP = GET_MAX_WORD_VALUE(Data->MP);
	pMsg.MaxMP = GET_MAX_WORD_VALUE(Data->MaxMP);
	pMsg.BP = GET_MAX_WORD_VALUE(Data->BP);
	pMsg.MaxBP = GET_MAX_WORD_VALUE(Data->MaxBP);
	pMsg.Money = Data->Money;
	pMsg.PKLevel = Data->PKLevel;
	pMsg.CtlCode = Data->CtlCode;
	pMsg.FruitAddPoint = Data->FruitAddPoint;
	pMsg.MaxFruitAddPoint = Data->MaxFruitAddPoint;
	pMsg.Leadership = Data->Leadership;
	pMsg.FruitSubPoint = Data->FruitSubPoint;
	pMsg.MaxFruitSubPoint = Data->MaxFruitSubPoint;

	return pProtocolCore(0xF3, (LPBYTE)(&pMsg), sizeof(pMsg), Index);
}

int Protocol::CharacterRegenRecv(int Index, PMSG_CHARACTER_REGEN_RECV * Data)
{
	gUser.HP = Data->HP;
	gUser.MP = Data->MP;
	gUser.BP = Data->BP;

	PMSG_CHARACTER_REGEN_SEND pMsg;

	pMsg.header.set(0xF3, 0x04, sizeof(pMsg));
	pMsg.X = Data->X;
	pMsg.Y = Data->Y;
	pMsg.Map = Data->Map;
	pMsg.Dir = Data->Dir;
	pMsg.HP = GET_MAX_WORD_VALUE(Data->HP);
	pMsg.MP = GET_MAX_WORD_VALUE(Data->MP);
	pMsg.BP = GET_MAX_WORD_VALUE(Data->BP);
	pMsg.Experience = Data->Experience;
	pMsg.Money = Data->Money;

	return pProtocolCore(0xF3, (LPBYTE)(&pMsg), sizeof(pMsg), Index);
}

int Protocol::LevelUpRecv(int Index, PMSG_LEVEL_UP_RECV * Data)
{
	gUser.MaxHP = Data->MaxHP;
	gUser.MaxMP = Data->MaxMP;
	gUser.MaxBP = Data->MaxBP;
	gUser.LevelUpPoints = Data->LevelUpPoint;

	gUser.Update(Index, [&](UserObject * User) 
	{
		User->NextExperience = Data->NextExperience;
	});

	PMSG_LEVEL_UP_SEND pMsg;

	pMsg.header.set(0xF3, 0x05, sizeof(pMsg));
	pMsg.Level = Data->Level;
	pMsg.LevelUpPoint = GET_MAX_WORD_VALUE(Data->LevelUpPoint);
	pMsg.MaxHP = GET_MAX_WORD_VALUE(Data->MaxHP);
	pMsg.MaxMP = GET_MAX_WORD_VALUE(Data->MaxMP);
	pMsg.MaxBP = GET_MAX_WORD_VALUE(Data->MaxBP);
	pMsg.FruitAddPoint = Data->FruitAddPoint;
	pMsg.MaxFruitAddPoint = Data->MaxFruitAddPoint;
	pMsg.FruitSubPoint = Data->FruitSubPoint;
	pMsg.MaxFruitSubPoint = Data->MaxFruitSubPoint;

	return pProtocolCore(0xF3, (LPBYTE)(&pMsg), sizeof(pMsg), Index);
}

int Protocol::LevelUpPointRecv(int Index, PMSG_LEVEL_UP_POINT_RECV * Data)
{
	gUser.MaxHP = Data->MaxHP;
	gUser.MaxMP = Data->MaxMP;
	gUser.MaxBP = Data->MaxBP;
	gUser.LevelUpPoints = Data->LevelUpPoint;

	gUser.Update(Index, [&](UserObject * User)
	{
		User->LevelUpPoint = Data->LevelUpPoint > 0;

		switch (Data->result)
		{
			case 0x10:
				++User->Strength;
				break;
			case 0x11:
				++User->Dexterity;
				break;
			case 0x12:
				++User->Vitality;
				break;
			case 0x13:
				++User->Energy;
				break;
			case 0x14:
				++User->Leadership;
				break;
		}
	});

	return 1;
}

int Protocol::MonsterDamageRecv(int Index, PMSG_MONSTER_DAMAGE_RECV * Data)
{
	gUser.HP = Data->HP;
	gUser.Damage = Data->Damage;

	PMSG_MONSTER_DAMAGE_SEND pMsg;

	pMsg.header.set(0xF3, 0x07, sizeof(pMsg));
	pMsg.damage[0] = SET_NUMBERHB(GET_MAX_WORD_VALUE(Data->Damage));
	pMsg.damage[1] = SET_NUMBERLB(GET_MAX_WORD_VALUE(Data->Damage));

	return pProtocolCore(0xF3, (LPBYTE)(&pMsg), sizeof(pMsg), Index);
}

int Protocol::ReconnectRecv(int Index, PMSG_RECONNECT_RECV * Data)
{
	gReconnect.SetStep(Data->Step);
	return 1;
}

int Protocol::NewCharacterInfoRecv(int Index, PMSG_NEW_CHARACTER_INFO_RECV * Data)
{
	gUser.HP = Data->HP;
	gUser.MaxHP = Data->MaxHP;
	gUser.MP = Data->MP;
	gUser.MaxMP = Data->MaxMP;
	gUser.BP = Data->BP;
	gUser.MaxBP = Data->MaxBP;
	gUser.LevelUpPoints = Data->LevelUpPoint;
	gUser.Update(Index, [&](UserObject * User)
	{
		User->Level = Data->Level;
		User->LevelUpPoint = Data->LevelUpPoint;
		User->Experience = Data->Experience;
		User->NextExperience = Data->NextExperience;
		User->Strength = Data->Strength;
		User->Dexterity = Data->Dexterity;
		User->Vitality = Data->Vitality;
		User->Energy = Data->Energy;
		User->Leadership = Data->Leadership;	});


	return 1;
}

int Protocol::NewCharacterCalcRecv(int Index, PMSG_NEW_CHARACTER_CALC_RECV * Data)
{
	gUser.HP = Data->HP;
	gUser.MaxHP = Data->MaxHP;
	gUser.MP = Data->MP;
	gUser.MaxMP = Data->MaxMP;
	gUser.BP = Data->BP;
	gUser.MaxBP = Data->MaxBP;
	gUser.AttackDamageLeft[0] = Data->AttackDamageLeft[0];
	gUser.AttackDamageLeft[1] = Data->AttackDamageLeft[1];
	gUser.AttackDamageRight[0] = Data->AttackDamageRight[0];
	gUser.AttackDamageRight[1] = Data->AttackDamageRight[1];
	gUser.MagicDamage[0] = Data->MagicDamage[0];
	gUser.MagicDamage[1] = Data->MagicDamage[1];
	gUser.AttackRate = Data->AttackRate;
	gUser.AttackSpeed = Data->AttackSpeed;
	gUser.MagicSpeed = Data->MagicSpeed;
	gUser.Defense = Data->Defense;
	gUser.DefenseRate = Data->DefenseRate;

	return 1;
}

int Protocol::NewHPBarRecv(int Index, LPBYTE Data)
{
	gMonster.HPBar.Clear();

	PMSG_NEW_HEALTH_BAR_RECV* pMsg = (PMSG_NEW_HEALTH_BAR_RECV*)(Data);
	PMSG_NEW_HEALTH_BAR* Info;

	for (int i = 0; i < pMsg->count; ++i)
	{
		Info = (PMSG_NEW_HEALTH_BAR*)(&Data[sizeof(PMSG_NEW_HEALTH_BAR_RECV) + sizeof(PMSG_NEW_HEALTH_BAR) * i]);

		gMonster.HPBar.Add(Info->Index, Info->Percent);
	}

	return 1;
}

int Protocol::SignsRecv(int Index, PMSG_SIGNS_RECV* Data)
{
	for (BYTE i = 0; i < 5; ++i)
	{
		if (Data->Signs[i] != 0)
		{
			gUser.Sign[i] = 16 + (Data->Signs[i] - 1);
		}
		else
		{
			gUser.Sign[i] = 0;
		}
	}

	return 1;
}

int Protocol::LockRecv(int Index, PMSG_LOCK_RECV* Data)
{
	pLockMain = Data->lock;
	return 1;
}

int Protocol::PingRecv(int Index, PMSG_PING_RECV* Data)
{
	gSecurity.StartCheckProcesses();
	return 1;
}

Protocol gProtocol;
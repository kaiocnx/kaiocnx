#pragma once

class Protocol
{
public:
	Protocol();
	~Protocol();

public:
	void Hook();

public:
	static int Core(DWORD Protocol, LPBYTE Data, int Size, int Index);
	static int ConnectClientRecv(int Index, PMSG_CONNECT_CLIENT_RECV* Data);
	static int ViewportPlayerRecv(int Index, LPBYTE Data);
	static int UserDieRecv(int Index, PMSG_USER_DIE_RECV* Data);
	static int LifeRecv(int Index, PMSG_LIFE_RECV* Data);
	static int ManaRecv(int Index, PMSG_MANA_RECV* Data);
	static int RewardExperienceRecv(int Index, PMSG_REWARD_EXPERIENCE_RECV* Data);
	static int QuestRewardRecv(int Index, PMSG_QUEST_REWARD_RECV* Data);
	static int DamageRecv(int Index, PMSG_DAMAGE_RECV* Data);
	static int CharacterInfoRecv(int Index, PMSG_CHARACTER_INFO_RECV* Data);
	static int CharacterRegenRecv(int Index, PMSG_CHARACTER_REGEN_RECV* Data);
	static int LevelUpRecv(int Index, PMSG_LEVEL_UP_RECV* Data);
	static int LevelUpPointRecv(int Index, PMSG_LEVEL_UP_POINT_RECV* Data);
	static int MonsterDamageRecv(int Index, PMSG_MONSTER_DAMAGE_RECV* Data);
	static int ReconnectRecv(int Index, PMSG_RECONNECT_RECV* Data);
	static int NewCharacterInfoRecv(int Index, PMSG_NEW_CHARACTER_INFO_RECV* Data);
	static int NewCharacterCalcRecv(int Index, PMSG_NEW_CHARACTER_CALC_RECV* Data);
	static int NewHPBarRecv(int Index, LPBYTE Data);
	static int SignsRecv(int Index, PMSG_SIGNS_RECV* Data);
	static int LockRecv(int Index, PMSG_LOCK_RECV* Data);
	static int PingRecv(int Index, PMSG_PING_RECV* Data);
};

extern Protocol gProtocol;
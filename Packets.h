#pragma once

#define SET_NUMBERHB(x)						((BYTE)((DWORD)(x)>>(DWORD)8))
#define SET_NUMBERLB(x)						((BYTE)((DWORD)(x)&0xFF))
#define SET_NUMBERHW(x)						((WORD)((DWORD)(x)>>(DWORD)16))
#define SET_NUMBERLW(x)						((WORD)((DWORD)(x)&0xFFFF))
#define SET_NUMBERHDW(x)					((DWORD)((QWORD)(x)>>(QWORD)32))
#define SET_NUMBERLDW(x)					((DWORD)((QWORD)(x)&0xFFFFFFFF))
#define MAKE_NUMBERW(x,y)					((WORD)(((BYTE)((y)&0xFF))|((BYTE)((x)&0xFF)<<8)))
#define MAKE_NUMBERDW(x,y)					((DWORD)(((WORD)((y)&0xFFFF))|((WORD)((x)&0xFFFF)<<16)))
#define GET_SUBHEAD(data)					((data[0] == 0xC1) ? data[3] : data[4])

struct PBMSG_HEAD
{
	void set(BYTE head, BYTE size)
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
	}

	void setE(BYTE head, BYTE size)
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
	}

	BYTE type;
	BYTE size;
	BYTE head;
};

struct PSBMSG_HEAD
{
	void set(BYTE head, BYTE subh, BYTE size)
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head, BYTE subh, BYTE size)
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size;
	BYTE head;
	BYTE subh;
};

struct PWMSG_HEAD
{
	void set(BYTE head, WORD size)
	{
		this->type = 0xC2;
		this->size[0] = SET_NUMBERHB(size);
		this->size[1] = SET_NUMBERLB(size);
		this->head = head;
	}

	void setE(BYTE head, WORD size)
	{
		this->type = 0xC4;
		this->size[0] = SET_NUMBERHB(size);
		this->size[1] = SET_NUMBERLB(size);
		this->head = head;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
};

struct PSWMSG_HEAD
{
	void set(BYTE head, BYTE subh, WORD size)
	{
		this->type = 0xC2;
		this->size[0] = SET_NUMBERHB(size);
		this->size[1] = SET_NUMBERLB(size);
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head, BYTE subh, WORD size)
	{
		this->type = 0xC4;
		this->size[0] = SET_NUMBERHB(size);
		this->size[1] = SET_NUMBERLB(size);
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
	BYTE subh;
};

struct PMSG_CONNECT_CLIENT_RECV
{
	PSBMSG_HEAD header;
	BYTE result;
	BYTE index[2];
	BYTE ClientVersion[5];
	BYTE Downgrade[10];
};

struct PMSG_CONNECT_ACCOUNT_SEND
{
	PSBMSG_HEAD header;
	char account[10];
	char password[10];
	DWORD TickCount;
	BYTE ClientVersion[5];
	BYTE ClientSerial[16];
};

struct PMSG_HARDWARE_ID_SEND
{
	PSBMSG_HEAD header;
	DWORD HardwardID[2];
};

struct PMSG_USER_DIE_RECV
{
	PBMSG_HEAD header;
	BYTE index[2];
	BYTE skill;
	BYTE killer[2];
};

struct PMSG_DAMAGE_RECV
{
	PBMSG_HEAD header;
	BYTE index[2];
	BYTE type;
	DWORD HP;
	int Damage;
};

struct PMSG_DAMAGE_SEND
{
	PBMSG_HEAD header;
	BYTE index[2];
	BYTE damage[2];
	BYTE type;
};

struct PMSG_LIFE_RECV
{
	PBMSG_HEAD header;
	BYTE type;
	DWORD HP;
	BYTE flag;
};

struct PMSG_LIFE_SEND
{
	PBMSG_HEAD header;
	BYTE type;
	BYTE life[2];
	BYTE flag;
};

struct PMSG_MANA_RECV
{
	PBMSG_HEAD header;
	BYTE type;
	DWORD MP;
	DWORD BP;
};

struct PMSG_MANA_SEND
{
	PBMSG_HEAD header;
	BYTE type;
	BYTE mana[2];
	BYTE bp[2];
};

struct PMSG_REWARD_EXPERIENCE_RECV
{
	PBMSG_HEAD header;
	BYTE index[2];
	WORD experience[2];
	int Damage;
};

struct PMSG_REWARD_EXPERIENCE_SEND
{
	PBMSG_HEAD header;
	BYTE index[2];
	WORD experience[2];
	BYTE damage[2];
	int ViewDamage;
};

struct PMSG_CHARACTER_INFO_RECV
{
	PSBMSG_HEAD header;
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	DWORD Experience;
	DWORD NextExperience;
	DWORD LevelUpPoint;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	DWORD HP;
	DWORD MaxHP;
	DWORD MP;
	DWORD MaxMP;
	DWORD BP;
	DWORD MaxBP;
	DWORD Money;
	BYTE PKLevel;
	BYTE CtlCode;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD Leadership;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	BYTE Sign;
	BYTE Patent;
};

struct PMSG_CHARACTER_INFO_SEND
{
	PSBMSG_HEAD header;
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	DWORD Experience;
	DWORD NextExperience;
	WORD LevelUpPoint;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD HP;
	WORD MaxHP;
	WORD MP;
	WORD MaxMP;
	WORD BP;
	WORD MaxBP;
	DWORD Money;
	BYTE PKLevel;
	BYTE CtlCode;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD Leadership;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
};

struct PMSG_CHARACTER_REGEN_RECV
{
	PSBMSG_HEAD header; 
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	DWORD HP;
	DWORD MP;
	DWORD BP;
	DWORD Experience;
	DWORD Money;
};

struct PMSG_CHARACTER_REGEN_SEND
{
	PSBMSG_HEAD header; 
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	WORD HP;
	WORD MP;
	WORD BP;
	DWORD Experience;
	DWORD Money;
};

struct PMSG_LEVEL_UP_RECV
{
	PSBMSG_HEAD header;
	WORD Level;
	DWORD LevelUpPoint;
	DWORD MaxHP;
	DWORD MaxMP;
	DWORD MaxBP;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	DWORD NextExperience;
};

struct PMSG_LEVEL_UP_SEND
{
	PSBMSG_HEAD header;
	WORD Level;
	WORD LevelUpPoint;
	WORD MaxHP;
	WORD MaxMP;
	WORD MaxBP;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
};

struct PMSG_LEVEL_UP_POINT_RECV
{
	PSBMSG_HEAD header;
	BYTE result;
	DWORD MaxHP;
	DWORD MaxMP;
	DWORD MaxBP;
	DWORD LevelUpPoint;
};

struct PMSG_LEVEL_UP_POINT_SEND
{
	PSBMSG_HEAD header;
	BYTE result;
	WORD MaxHPAndMP;
	WORD MaxBP;
};

struct PMSG_MONSTER_DAMAGE_RECV
{
	PSBMSG_HEAD header;
	DWORD HP;
	int Damage;
};

struct PMSG_MONSTER_DAMAGE_SEND
{
	PSBMSG_HEAD header;
	BYTE damage[2];
};

struct PMSG_QUEST_REWARD_RECV
{
	PBMSG_HEAD header;
	BYTE index[2];
	BYTE QuestReward;
	BYTE QuestAmount;
	DWORD LevelUpPoint;
};

struct PMSG_NEW_CHARACTER_INFO_RECV
{
	PSBMSG_HEAD header;
	WORD Level;
	DWORD LevelUpPoint;
	DWORD Experience;
	DWORD NextExperience;
	DWORD Strength;
	DWORD Dexterity;
	DWORD Vitality;
	DWORD Energy;
	DWORD Leadership;
	DWORD HP;
	DWORD MaxHP;
	DWORD MP;
	DWORD MaxMP;
	DWORD BP;
	DWORD MaxBP;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	DWORD ViewReset;
};

struct PMSG_NEW_CHARACTER_CALC_RECV
{
	PSBMSG_HEAD header;
	DWORD HP;
	DWORD MaxHP;
	DWORD MP;
	DWORD MaxMP;
	DWORD BP;
	DWORD MaxBP;
	WORD AttackDamageLeft[2];
	WORD AttackDamageRight[2];
	WORD MagicDamage[2];
	WORD AttackRate;
	WORD AttackSpeed;
	WORD MagicSpeed;
	WORD Defense;
	WORD DefenseRate;
};

struct PMSG_NEW_HEALTH_BAR_RECV
{
	PSWMSG_HEAD header;
	BYTE count;
};

struct PMSG_NEW_HEALTH_BAR
{
	WORD Index;
	BYTE Percent;
};

struct PMSG_SERVER_INFO_RECV
{
	PSBMSG_HEAD header;
	char ServerAddress[16];
	WORD ServerPort;
};

struct PMSG_RECONNECT_SEND
{
	PSBMSG_HEAD header;
	char Account[10];
	char Password[10];
	char Name[10];
	DWORD TickCount;
	BYTE ClientVersion[5];
	BYTE ClientSerial[16];
};

struct PMSG_RECONNECT_RECV
{
	PSBMSG_HEAD header;
	BYTE Step;
};

struct PMSG_SIGNS_RECV
{
	PSBMSG_HEAD header;
	BYTE Signs[5];
};

struct PMSG_VIEWPORT_PLAYER
{
	BYTE index[2];
	BYTE x;
	BYTE y;
	BYTE CharSet[18];
	DWORD ViewSkillState;
	char name[10];
	BYTE tx;
	BYTE ty;
	BYTE DirAndPkLevel;
};

struct PMSG_VIEWPORT_PLAYER_NEW
{
	BYTE index[2];
	BYTE x;
	BYTE y;
	BYTE CharSet[18];
	DWORD ViewSkillState;
	char name[10];
	BYTE tx;
	BYTE ty;
	BYTE DirAndPkLevel;
	BYTE Sign;
	BYTE Patent;
};

struct PMSG_VIEWPORT_RECV
{
	PWMSG_HEAD header;
	BYTE count;
};

struct PMSG_LOCK_RECV
{
	PSBMSG_HEAD header;
	BYTE lock;
};

struct PMSG_PING_RECV
{
	PSBMSG_HEAD header;
};

struct PMSG_PONG_SEND
{
	PSBMSG_HEAD header;
};


struct PMSG_DETECT_SEND
{
	PSBMSG_HEAD header;
	BYTE result;
	char detect[64];
};
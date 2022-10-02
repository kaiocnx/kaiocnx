#pragma once

#pragma pack(push, 1)
struct UserObject
{
	char Name[11];				// 0
	BYTE Class;					// B
	BYTE Unknown[2];			// C
	short Level;				// E
	DWORD Experience;			// 10
	DWORD NextExperience;		// 14
	WORD Strength;				// 18
	WORD Dexterity;				// 1A
	WORD Vitality;				// 1C
	WORD Energy;				// 1E
	WORD Leadership;			// 20
	WORD HP;					// 22
	WORD MP;					// 24
	WORD MaxHP;					// 26
	WORD MaxMP;					// 28
	short AddStrength;			// 2A
	short AddDexterity;			// 2C
	short AddVitality;			// 2E
	short AddEnergy;			// 30
	short AddLeadership;		// 32
	BYTE Unknown5[4];			// 34
	WORD BP;					// 38
	WORD MaxBP;					// 3A
	BYTE IsUnkByte1;			// 3C
	BYTE IsUnkByte2;			// 3D
	WORD IsUnkWord1;			// 3E
	WORD IsUnkWord2;			// 40
	WORD IsUnkWord3;			// 42
	WORD AddPoint;				// 44
	WORD MaxAddPoint;			// 46
	WORD MinusPoint;			// 48
	WORD MaxMinusPoint;			// 4A
	WORD AttackSpeed;			// 4C
	WORD AttackRate;			// 4E
	WORD AttackDamageMinLeft;	// 50
	WORD AttackDamageMaxLeft;	// 52
	WORD AttackDamageMinRight;	// 54
	WORD AttackDamageMaxRight;	// 56
	WORD MagicSpeed;			// 58
	WORD MagicDamageMin;		// 5A
	WORD MagicDamageMax;		// 5C
	BYTE Unknown4[0x2];			// 5E
	WORD DefenseRate;			// 60
	WORD Defense;				// 62
	BYTE Unknown6[0x4];			// 64
	WORD LevelUpPoint;			// 68
	BYTE Unknown7[0xEA1];		// 6A
};
#pragma pack(pop)

#define USER_BASE				*(DWORD*)(0x7666A78)

class User
{
public:
	User();
	~User();

public:
	void Hook();
	void Update(int Index, std::function<void(UserObject*)> Callback);

public:
	static void DrawInfo(int X, int Y, float Unk1, float Unk2, int Unk3, int Unk4, char* Name, int Unk5);

public:
	static void UpdateInfo();
	static void SetSpeed();

public:
	int Index;
	DWORD HP;
	DWORD MaxHP;
	DWORD MP;
	DWORD MaxMP;
	DWORD BP;
	DWORD MaxBP;
	DWORD LevelUpPoints;
	int Damage;
	DWORD X;
	DWORD Y;
	WORD AttackDamageLeft[2];
	WORD AttackDamageRight[2];
	WORD MagicDamage[2];
	WORD AttackRate;
	WORD AttackSpeed;
	WORD MagicSpeed;
	WORD Defense;
	WORD DefenseRate;
	BYTE Sign[5];
	BYTE Patent;

public:
	std::function<void(UserObject*)> Callback;
};

extern User gUser;
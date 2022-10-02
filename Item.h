#pragma once

#define ITEM_MODEL					515
#define ITEM_GET(x,y)				((x * 512) + y)
#define ITEM_GET_MODEL(x,y)			(ITEM_GET(x, y) + ITEM_MODEL)

#pragma pack(push, 1)
struct ItemInfo
{
	WORD Index;				    // 0
	BYTE Unknown1[0x2];		    // 2
	DWORD Code;				    // 4
	BYTE Slot;                  // 8
	BYTE Unknown2;	            // 9
	BYTE TwoHand;               // A
	BYTE Unknown3;              // B
	WORD DamageMin;             // C
	WORD DamageMax;             // E
	WORD SuccessfulBlocking;    // 10
	WORD Defense;               // 12
	WORD MagicDefense;          // 14
	BYTE MagicPower;            // 16
	BYTE AttackSpeed;           // 17
	WORD MoveSpeed;             // 18
	BYTE Durability;		    // 1A
	BYTE NewOption;			    // 1B
	BYTE SetOption;			    // 1C
};
#pragma pack(pop)

struct ItemEffectInfo
{
	WORD Index;
	WORD Bone;
	float Color[3];
	float Size;
	BYTE Count;
};

struct ItemCustomInfo
{
	BYTE Type;
	BYTE Subtype;
	const char* Folder;
	char File[50];
	int Price;
	std::vector<ItemEffectInfo> Effect;
};

#include "Glow.h"
#include "Description.h"

class Item
{
public:
	enum ItemType
	{
		Sword = 0,
		Blade = 0,
		Axe = 1,
		Mace = 2,
		Scepter = 2,
		Spear = 3,
		Bow = 4,
		Staff = 5,
		Shield = 6,
		Helm = 7,
		Armor = 8,
		Pants = 9,
		Gloves = 10,
		Boots = 11,
		Wing = 12,
		Cape = 12,
		Ring = 13,
		Pet = 13,
		Jewel = 14,
		Box = 14,
		Scroll = 15,
		Crossbow = 16
	};

public:
	Item();
	~Item();

public:
	void Load();
	void Hook();
	void Add(BYTE Type, WORD Index, int Price = -1, const std::vector<ItemEffectInfo>& Effects = {}, BYTE Others = 0);
	ItemCustomInfo* Get(WORD Index);
	bool ApplyWingEffect(WORD Model, DWORD This, DWORD b, DWORD c, DWORD d);

public:
	static void SetGlow(int Model, float Alpha, DWORD Unk2, GlowColor* Color, DWORD Unk3);
	static void SetDescription(ItemInfo* Item);
	static void MakePreviewCharacter(int Index, BYTE* CharSet, int Address, int Mode);

public:
	static void SetDescriptionInfo();
	static void SetDescriptionColor1();
	static void SetDescriptionColor2();
	static void NewWings1();
	static void NewWings2();
	static void NewWings3();
	static void NewWings4();
	static void NewWings5();
	static void NewWings6();
	static void NewWings7();
	static void NewWings8();
	static void NewWings9();
	static void NewWings10();
	static void NewWings11();
	static void NewWings12();
	static void NewWings13();
	static void NewWings14();
	static void NewWings15();
	static void NewWings16();
	static void NewWings17();
	static void NewWings18();
	static void NewWings19();
	static void NewWings20();
	static void NewWings21();
	static void NewWings22();
	static void NewWings23();
	static void NewWings24();
	static void NewWings25();
	static void NewWings26();
	static void NewWings27();
	static void NewWings28();
	static void NewWings29();
	static void NewWings30();
	static void NewWings31();
	static void NewWings32();
	static void NewWings33();
	static void NewWings34();
	static void NewWings35();
	static void NewWings36();
	static void NewWings37();
	static void NewJewels1();
	static void NewJewels2();
	static void NewJewels3();
	static void NewJewels4();
	static void NewBows1();
	static void NewBows2();
	static void NewBows3();
	static void NewBows4();
	static void NewBows5();
	static void NewBows6();
	static void NewBows7();
	static void NewBows8();
	static void NewBows9();
	static void NewBows10();
	static void NewBows11();
	static void NewBows12();
	static void NewBows13();
	static void NewBows14();
	static void NewBows15();
	static void NewBows16();
	static void NewCrossbows1();
	static void NewCrossbows2();
	static void NewCrossbows3();
	static void NewCrossbows4();
	static void NewCrossbows5();
	static void NewCrossbows6();
	static void NewCrossbows7();
	static void NewCrossbows8();
	static void NewCrossbows9();
	static void MultipleShotSkillEffect();
	static void SingleShotSkillEffect();
	static void WingEffect();
	static void GlowEffect();

public:
	std::unordered_map<WORD, ItemCustomInfo> Items;

private:
	Glow Glow;
	Description Description;
};

extern Item gItem;
#pragma once

#include "HPBar.h"

struct CustomMonster
{
	WORD Model;
	const char* Folder;
	const char* File;
	bool IsNpc;
};

class Monster
{
public:
	Monster();
	~Monster();

public:
	void Load();
	void Hook();
	void Add(WORD Index, const char* Folder, const char* File, bool IsNpc);
	CustomMonster* Get(WORD Index);

private:
	static ViewportInfo* Renderize(int Index, DWORD Unk1, int Unk2, int Unk3);
	static void DrawHP();

public:
	static void MonsterType();
	static void MonsterTalk();

public:
	HPBar HPBar;

private:
	std::unordered_map<WORD, CustomMonster> Monsters;
};

extern Monster gMonster;
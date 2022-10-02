#pragma once

class Visual
{
public:
	Visual();
	~Visual();

public:
	void Hook();

public:
	static void DrawDamage(int Unk1, int Damage, int Unk2, int Unk3, char Unk4);
	//static float FormatPoint(float X, float Y, DWORD Point, float Unk1, float Unk2);

public:
	static void DrawHP1();
	static void DrawHP2();
	static void DrawHP3();
	static void DrawHP4();
	static void DrawHP5();
	static void DrawMP1();
	static void DrawMP2();
	static void DrawMP3();
	static void DrawMP4();
	static void CheckMP1();
	static void CheckMP2();
	static void CheckMP3();
	static void CheckMP4();
	static void CheckMP5();
	static void CheckMP6();
	static void CheckMP7();
	static void DrawBP1();
	static void DrawBP2();
	static void DrawBP3();
	static void CheckBP1();
	static void CheckBP2();
	static void CheckBP3();
	static void CheckBP4();
	static void CheckBP5();
	static void CheckBP6();
	static void DrawLevelUpPoints();
	static void GetX();
	static void GetY();
	static void AttackDamage();
	static void MagicDamage();
	static void AttackRate();
	static void Speed();
	static void DefenseRate();
	static void Defense();
};

extern Visual gVisual;
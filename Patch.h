#pragma once

class Patch
{
public:
	Patch();
	~Patch();

public:
	void Apply();

private:
	static void Optimize();
	static void SummonNameColor();
	static void LoadMapName();
	std::vector<std::string> GetDirectories(const std::string& s);
public:
	//static float FormatPoint(float X, float Y, DWORD Point, float Unk1, float Unk2);
};

extern Patch gPatch;
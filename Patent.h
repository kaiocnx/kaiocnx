#pragma once

struct PatentInfo
{
	const char* File;
	WORD Width;
	WORD Height;
	short X;
	short Y;
	short PaddingX;
	short PaddingY;
	short ScaleX;
	short ScaleY;
};

class Patent
{
public:
	Patent();
	~Patent();

public:
	void Load();
	void Add(BYTE Index, const char* File, WORD Width, WORD Height, short X, short Y, short PaddingX, short PaddingY, short ScaleX, short ScaleY);
	PatentInfo* Get(BYTE Index);
	void Draw(int X, int Y, ViewportInfo* Viewport, ViewportCustomInfo* Custom);

public:
	std::unordered_map<BYTE, PatentInfo> Patents;
};

extern Patent gPatent;
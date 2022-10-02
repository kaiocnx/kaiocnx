#pragma once

#define MAX_RESOLUTION_INFO 7

struct ResolutionInfo
{
	WORD Width;
	WORD Height;
	WORD Font;
	WORD Move[4];
};

class Resolution
{
public:
	Resolution();
	~Resolution();

public:
	void Hook();

public:
	static void WindowSize();
	static void FontSize();
	static void MoveListSize();
	static void MoveListClick();

private:
	ResolutionInfo Info;
};

extern Resolution gResolution;
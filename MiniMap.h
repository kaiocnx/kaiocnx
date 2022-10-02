#pragma once

class MiniMap
{
public:
	MiniMap();
	~MiniMap();

public:
	void Hook();
	
	static void LoadTexture();

	void Switch(int Type);

private:
	bool bEnabled;
	bool bSelect;
	int iLastMap;
};

extern MiniMap gMiniMap;
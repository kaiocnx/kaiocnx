#pragma once

struct SignInfo
{
	short Model;
	const char* Folder;
	const char* File;
	bool Glow;
};

class Sign
{
public:
	Sign();
	~Sign();

public:
	void Load();
	void Hook();
	void Add(BYTE Index, const char* Folder, const char* File, bool Glow = false);
	SignInfo* Get(BYTE Index);
	SignInfo* GetByModel(WORD Model);

private:
	static LPBYTE Create(ViewportInfo* Value);
	static void Destroy(ViewportInfo* Value);

private:
	static void Glow();

public:
	std::unordered_map<BYTE, SignInfo> Signs;
};

extern Sign gSign;
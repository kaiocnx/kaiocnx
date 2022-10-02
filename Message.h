#pragma once

#define MSG_WHISPER 0
#define MSG_INFO	1
#define MSG_ERROR	2
#define MSG_NORMAL	3
#define MSG_PARTY	4
#define MSG_GUILD	5
#define MSG_SUCCESS 100

class Message
{
public:
	Message();
	~Message();

public:
	void Load();
	void Hook();
	void Add(BYTE Language, const std::string& Text);
	const char* Get(size_t Index);
	const char* GetMapName(BYTE MapIndex);

public:
	static void CheckType();
	static void SetColor1();
	static void SetColor2();
	static void SetColor3();
	static void SetColor4();

private:
	BYTE Language;
	std::unordered_map<BYTE, std::vector<std::string>> Messages;
	DWORD Color[12][2];
};

extern Message gMessage;
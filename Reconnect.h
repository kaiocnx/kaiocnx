#pragma once

#define RSTATE_ONLINE			0
#define RSTATE_RECONNECT		1
#define RSTATE_DISCONNECT		2

#define DISCONNECT_EVENT		0x70

#define STEP_RECONNECT			0
#define STEP_AUTH				1
#define STEP_PROCESS			2
#define STEP_PROCESS2			3
#define STEP_FAILED				4

class Reconnect
{
public:
	Reconnect();
	~Reconnect();

public:
	void Hook();
	void SetState(BYTE State);
	BYTE GetState() const;
	void SetStep(BYTE Step);
	void Run();
	void DrawProgress();
	BYTE State;
	static void ExitMenu();
	static int ExitMenu2();

private:
	static int Connect(LPCSTR IpAddress, WORD Port);
	static void Draw(int Unk);

private:
	static void GetAccountInfo();
	static void Disconnect();

private:
	BYTE Step;
	int checkdc;
	char IpAddress[16];
	WORD Port;
	char Account[10];
	char Password[10];
	DWORD TickCount[2];
	BYTE Count;
};

extern Reconnect gReconnect;

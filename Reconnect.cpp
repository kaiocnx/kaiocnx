#include "Library.h"
#include "Message.h"
#include "Reconnect.h"

Reconnect::Reconnect() : State(RSTATE_ONLINE), Step(STEP_RECONNECT), IpAddress{0}, Port(0), Account{0}, TickCount{0,0}, Count(0)
{
}

Reconnect::~Reconnect()
{
}

void Reconnect::Hook()
{
	Memory::Hook<false>(0x411016, this->Connect);
	Memory::Hook<false>(0x4BC24F, this->Connect);
	Memory::Hook<false>(0x4DC04C, this->Connect);
	Memory::Hook<false>(0x620529, this->Connect);
	Memory::Hook<false>(0x620E78, this->Connect);
	Memory::Hook<false>(0x632977, this->Connect);
	Memory::Hook<false>(0x411016, this->Connect);
	Memory::Hook<false>(0x596E7F, this->Draw);
	Memory::Hook<true>(0x62110F, this->GetAccountInfo);
	Memory::Hook<true>(0x6104B0, this->ExitMenu);
	Memory::Hook<true>(0x4AD90A, this->Disconnect);

	Memory::Update<BYTE>(0x628FC8, 0xEB);
	Memory::Update<BYTE>(0x4BBA91, 0xEB);
	Memory::Nop<5>(0x4DC086);
}

void Reconnect::SetState(BYTE State)
{
	this->State = State;

	if (this->State == RSTATE_ONLINE)
	{
		gViewport.Clear();
	}
}

BYTE Reconnect::GetState() const
{
	return this->State;
}

void Reconnect::SetStep(BYTE Step)
{
	this->Step = Step;
}

void Reconnect::Run()
{
	if (this->State != RSTATE_RECONNECT)
	{
		return;
	}
	if (pState == STATE_SELECT_SERVER)
	{
		return;
	}
	
	auto Viewport = gViewport.GetMyself();

	Viewport->UnkValue368 = 0;
	//pPartyMemberCount = 0;
	pReconnectClear1 = 0;
	pReconnectClear2 = 6;
	pReconnectClear3 = 0;
	pReconnectClear4 = 0;
	pReconnectClear5 = 0;
	pReconnectClear6 = -1;
	pReconnectClear7 = -1;
	pReconnectClear8 = -1;
	pReconnectClear9 = -1;
	pReconnectClear10 = -1;
	pReconnectClear11 = -1;

	pPShopSet(Viewport);
	pRefreshGame(Viewport);

	this->DrawProgress();

	if (this->Step == STEP_AUTH && (GetTickCount() - this->TickCount[1]) >= 10000)
	{
		this->Step = STEP_RECONNECT;
	}

	if (pState != STATE_PLAYING || (GetTickCount() - this->TickCount[0]) < 1500)
	{
		return;
	}

	switch (pPlayerState)
	{
		case PSTATE_OFFLINE:
		{
			PMSG_SERVER_INFO_RECV pMsg;
			pMsg.header.set(0xF4, 0x03, sizeof(pMsg));
			pMsg.ServerPort = this->Port;
			memcpy(pMsg.ServerAddress, this->IpAddress, sizeof(pMsg.ServerAddress));

			pProtocolCore(0xF4, (LPBYTE)(&pMsg), sizeof(pMsg), 0);
			break;
		}
		case PSTATE_ONLINE:
		{
			if (this->Step == STEP_RECONNECT)
			{
				this->TickCount[1] = GetTickCount();

				PMSG_RECONNECT_SEND pMsg;
				pMsg.header.set(0xF3, 0x41, sizeof(pMsg));
				pMsg.TickCount = GetTickCount();
				memcpy(pMsg.Account, this->Account, sizeof(pMsg.Account));
				memcpy(pMsg.Password, this->Password, sizeof(pMsg.Password));
				memcpy(pMsg.Name, Viewport->Name, sizeof(pMsg.Name));
				memcpy(pMsg.ClientSerial, CONNECT_SERIAL, sizeof(pMsg.ClientSerial));
				memcpy(pMsg.ClientVersion, CONNECT_VERSION, sizeof(pMsg.ClientVersion));
				DataSend((LPBYTE)(&pMsg), sizeof(pMsg));
			}

			break;
		}
	}

	this->TickCount[0] = GetTickCount();
}

void Reconnect::DrawProgress()
{
	int X = (int)((pScreenWidth / pScreenDivisorX) - 180) / 2;
	int Y = (int)((pScreenHeight / pScreenDivisorY) - 50) / 2;

	if ((++this->Count) >= 152)
	{
		this->Count = 0;
	}

	pEnableAlpha(true);
	glColor4f(0.f, 0.f, 0.f, 0.60f);
	pDrawForm((float)(X), (float)(Y), 180.0f, 50.0f);
	pDisableAlpha();

	pEnableAlpha(true);
	glColor4f(1.f, 1.f, 1.f, 1.f);

	char Status[5][50];
	strcpy_s(Status[0], gMessage.Get(7));
	strcpy_s(Status[1], gMessage.Get(8));
	strcpy_s(Status[2], gMessage.Get(9));
	strcpy_s(Status[3], gMessage.Get(10));
	strcpy_s(Status[4], gMessage.Get(11));
	SIZE Size;

	GetTextExtentPoint(pHDC, Status[this->Step], strlen(Status[this->Step]), &Size);
	Size.cx = 180 - (LONG)((float)(Size.cx) / pScreenDivisorX);

	if (Size.cx < 0)
	{
		Size.cx = 0;
	}
	else
	{
		Size.cx /= 2;
	}

	pFixText();
	pDrawText(X + Size.cx, Y + 10, Status[this->Step], 0, 0, 0);

	float X2 = (pScreenWidth - (158 * pScreenDivisorX)) / 2;
	float Y2 = (float)((pScreenHeight / 2) - 5);
	
	pDrawImage(0x13, (float)(X2), (float)(Y2), 158.f, 19.f, 0.f, 0.f, 0.62f, 0.55f, 1, 1.f);
	pDrawImage(0x14, (float)(X2 + 7), (float)(Y2 + 8), this->Count, 10.f, 0.f, 0.f, (float)(this->Count * 0.003906250), 1.0f, 1, 1.f);
	
	pDisableAlphaBlend();
	glColor3f(1.f, 1.f, 1.f);
}

int Reconnect::Connect(LPCSTR IpAddress, WORD Port)
{
	if (Port != pConnectServerPort)
	{
		memcpy(gReconnect.IpAddress, IpAddress, sizeof(gReconnect.IpAddress));
		gReconnect.Port = Port;
	}
	
	return pConnect(IpAddress, Port);
}

void Reconnect::Draw(int Unk)
{
	gReconnect.Run();

	pInterfaceDraw1(Unk);
}

void __declspec(naked) Reconnect::GetAccountInfo()
{
	static DWORD Local = 0x621114;

	__asm
	{
		PUSH 0x777D7C0;
		PUSHAD;
	}

	XorArgument(gReconnect.Account, pReconnectAccount, sizeof(gReconnect.Account));
	XorArgument(gReconnect.Password, pReconnectPassword, sizeof(gReconnect.Password));

	__asm
	{
		POPAD;
		JMP Local;
	}
}

void __declspec(naked) Reconnect::ExitMenu()
{
	static DWORD Local = 0x6104C2;

	__asm
	{
		PUSHAD;
	}

	gReconnect.State = RSTATE_DISCONNECT;

	__asm
	{
		POPAD;
		JMP Local;
	}
}

int __declspec(naked) Reconnect::ExitMenu2()
{
		static DWORD Local = 0x4AD93A;
		gReconnect.State = RSTATE_DISCONNECT;
		__asm
		{
			PUSHAD;
		}

		pSetEvent(DISCONNECT_EVENT);

		__asm
		{
			POPAD;
			JMP Local;
		}
}

void __declspec(naked) Reconnect::Disconnect()
{
	static DWORD Local = 0x4AD93A;
	gReconnect.State = RSTATE_DISCONNECT;
	__asm
	{
		PUSHAD;
	}


	if (gReconnect.State != RSTATE_DISCONNECT)
	{
		pLoadJPG("Interface\\newui_Bar_switch01.jpg", 0x13, 0x2600, 0x2900, 0, 1);
		pLoadJPG("Interface\\newui_Bar_switch02.jpg", 0x14, 0x2600, 0x2900, 0, 1);

		gReconnect.State = RSTATE_RECONNECT;
	}
	else
	{
		pSetEvent(DISCONNECT_EVENT);
	}

	__asm
	{
		POPAD;
		JMP Local;
	}
}

Reconnect gReconnect;
#include "Library.h"
#include "Message.h"

Message::Message() :
	Color{{RGBA(255, 200, 32, 150), RGBA(0, 0, 0, 255)},
		{RGBA(0, 0, 0, 150), RGBA(100, 150, 255, 255)},
		{RGBA(0, 0, 0, 150), RGBA(255, 30, 0, 255)},
		{RGBA(0, 0, 0, 150), RGBA(205, 220, 239, 255)},
		{RGBA(0, 200, 255, 150), RGBA(0, 0, 0, 255)},
		{RGBA(0, 255, 150, 200), RGBA(0, 0, 0, 255)},
		{RGBA(255, 200, 32, 150), RGBA(0, 0, 0, 255)},
		{RGBA(0, 0, 0, 150), RGBA(0, 220, 0, 255)}}
	/*{RGBA(0, 0, 0, 150), RGBA(255, 51, 153, 255)},  // announce
	{RGBA(0, 0, 0, 150), RGBA(241, 196, 16, 255)},*/ // warning
{
}

Message::~Message()
{
}

void Message::Load()
{
	this->Language = Registry::Read<BYTE>("Language");

	// 0 - English
	this->Add(0, "AutoClick on.");
	this->Add(0, "AutoClick off.");
	this->Add(0, "%s\n\n%s in %s (%d/%d).");
	this->Add(0, "Fog on.");
	this->Add(0, "Fog off.");
	this->Add(0, "Camera on.");
	this->Add(0, "Camera off.");
	this->Add(0, "Reconnecting...");
	this->Add(0, "Authenticating...");
	this->Add(0, "Getting data...");
	this->Add(0, "Processing data...");
	this->Add(0, "Connection failed.");

	// 1 - Português
	this->Add(1, "AutoClick ativado.");
	this->Add(1, "AutoClick desativado.");
	this->Add(1, "%s\n\n%s em %s (%d/%d).");
	this->Add(1, "Névoa ativado.");
	this->Add(1, "Névoa desativado.");
	this->Add(1, "Câmera ativada.");
	this->Add(1, "Câmera desativada.");
	this->Add(0, "Reconectando...");
	this->Add(0, "Autenticando...");
	this->Add(0, "Obtendo dados...");
	this->Add(0, "Processando dados...");
	this->Add(0, "A conexão falhou.");

	// 2 - Español
	this->Add(2, "AutoClick activado.");
	this->Add(2, "AutoClick desactivado.");
	this->Add(2, "%s\n\n%s en %s (%d/%d).");
	this->Add(2, "Niebla activado.");
	this->Add(2, "Niebla desactivado.");
	this->Add(2, "Cámara activada.");
	this->Add(2, "Cámara desactivada.");
	this->Add(0, "Reconectando...");
	this->Add(0, "Autenticando...");
	this->Add(0, "Obteniendo datos...");
	this->Add(0, "Procesando datos...");
	this->Add(0, "La conexión falló.");

	this->Hook();
}

void Message::Hook()
{
	Memory::Hook<true>(0x457710, this->CheckType);
	Memory::Hook<true>(0x45779D, this->SetColor1);
	Memory::Hook<true>(0x45796F, this->SetColor2);
	Memory::Hook<true>(0x457AFE, this->SetColor3);
	Memory::Hook<true>(0x549A03, this->SetColor4);
}

void Message::Add(BYTE Language, const std::string& Text)
{
	this->Messages[Language].push_back(Text);
}

const char* Message::Get(size_t Index)
{
	if (this->Messages.count(this->Language) > 0)
	{
		if (this->Messages.at(this->Language).size() > Index)
		{
			return this->Messages.at(this->Language).at(Index).c_str();
		}
	}

	if (this->Messages.count(0) > 0)
	{
		if (this->Messages.at(0).size() > Index)
		{
			return this->Messages.at(0).at(Index).c_str();
		}
	}

	return "";
}

const char* Message::GetMapName(BYTE MapIndex)
{
	switch (MapIndex)
	{
		case 0:
			return "Lorencia";
		case 1:
			return "Dungeon";
		case 2:
			return "Devias";
		case 3:
			return "Noria";
		case 4:
			return "Lost Tower";
		case 5:
			return "Exile";
		case 6:
			return "Arena";
		case 7:
			return "Atlans";
		case 8:
			return "Tarkan";
		case 9:
			return "Devil Square";
		case 10:
			return "Icarus";
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
			return "Blood Castle";
		default:
			return "";
	}
}

void __declspec(naked) Message::CheckType()
{
	static DWORD Local[2] = {0x457715, 0x45775A};

	__asm
	{
		CMP EAX, MSG_ERROR;
		JE DontShowInTab;
		CMP EAX, MSG_SUCCESS;
		JE DontShowInTab;
		JMP Local[4];

	DontShowInTab:
		JMP Local[0];
	}
}

void __declspec(naked) Message::SetColor1()
{
	static DWORD Local = 0x457848;
	static DWORD Id;

	__asm
	{
		MOV Id, EAX;
		PUSHAD;
	}

	if (Id >= MSG_SUCCESS)
	{
		Id -= (MSG_SUCCESS - 7);

		pMessageBackgroundColor = gMessage.Color[Id][0];
		pMessageForegroundColor = gMessage.Color[Id][1];
	}
	else
	{
		pMessageBackgroundColor = gMessage.Color[Id][0];
		pMessageForegroundColor = gMessage.Color[Id][1];
	}

	__asm
	{
		POPAD;
		JMP Local;
	}
}

void __declspec(naked) Message::SetColor2()
{
	static DWORD Local = 0x457A07;
	static DWORD Id;

	__asm
	{
		MOV Id, EAX;
		PUSHAD;
	}

	if (Id >= MSG_SUCCESS)
	{
		Id -= (MSG_SUCCESS - 7);

		pMessageBackgroundColor = gMessage.Color[Id][0];
		pMessageForegroundColor = gMessage.Color[Id][1];
	}
	else
	{
		pMessageBackgroundColor = gMessage.Color[Id][0];
		pMessageForegroundColor = gMessage.Color[Id][1];
	}

	__asm
	{
		POPAD;
		JMP Local;
	}
}

void __declspec(naked) Message::SetColor3()
{
	static DWORD Local[2] = {0x457B03, 0x457B80};
	static DWORD Id;

	__asm
	{
		CMP EAX, 5;
		JA Above;
		JMP Local[0];
	Above:
		MOV Id, EAX;
		PUSHAD;
	}

	if (Id >= MSG_SUCCESS)
	{
		Id -= (MSG_SUCCESS - 7);

		pMessageBackgroundColor = gMessage.Color[Id][0];
		pMessageForegroundColor = gMessage.Color[Id][1];
	}
	else
	{
		pMessageBackgroundColor = gMessage.Color[Id][0];
		pMessageForegroundColor = gMessage.Color[Id][1];
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Message::SetColor4()
{
	static DWORD Local[2] = {0x549A0C, 0x549A95};
	static DWORD Id;

	__asm
	{
		CMP ECX, 5;
		JA Above;
		JMP Local[0];
	Above:
		MOV Id, ECX;
		PUSHAD;
	}

	if (Id >= MSG_SUCCESS)
	{
		Id -= (MSG_SUCCESS - 7);

		pMessageBackgroundColor = gMessage.Color[Id][0];
		pMessageForegroundColor = gMessage.Color[Id][1];
	}
	else
	{
		pMessageBackgroundColor = gMessage.Color[Id][0];
		pMessageForegroundColor = gMessage.Color[Id][1];
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

Message gMessage;
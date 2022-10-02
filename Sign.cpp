#include "Library.h"
#include "Sign.h"
#include "User.h"

Sign::Sign()
{
}

Sign::~Sign()
{
}

void Sign::Load()
{
	//--------------------------------------------------
	// Novas placas
	//--------------------------------------------------
	// Para adicionar uma nova placa, basta:
	// this->Add(<id>, <folder>, <file>, <glow*>);
	// Obs: O id não pode ser 0.
	this->Add(1, FOLDER_SKILL, "afksign");
	this->Add(2, FOLDER_SIGN, "sign01");
	this->Add(3, FOLDER_SIGN, "sign02");
	this->Add(4, FOLDER_SIGN, "sign03");
	this->Add(5, FOLDER_SIGN, "sign04");
	this->Add(6, FOLDER_SIGN, "sign05");	//Navidad
	this->Add(7, FOLDER_SIGN, "sign06");
	this->Add(8, FOLDER_SIGN, "sign07");
	this->Add(9, FOLDER_SIGN, "sign08");
	this->Add(10, FOLDER_SIGN, "sign09");
	this->Add(11, FOLDER_SIGN, "sign10");
	this->Add(12, FOLDER_SIGN, "sign11");
	this->Add(13, FOLDER_SIGN, "sign12");

	this->Hook();
}

void Sign::Hook()
{
	Memory::Hook<false>(0x504AE7, this->Create);
	Memory::Hook<false>(0x4124C9, this->Destroy);
	Memory::Hook<false>(0x428E32, this->Destroy);
	Memory::Hook<false>(0x428E63, this->Destroy);
	Memory::Hook<false>(0x428E94, this->Destroy);
	Memory::Hook<false>(0x428ECA, this->Destroy);
	Memory::Hook<false>(0x428EFD, this->Destroy);
	Memory::Hook<false>(0x429068, this->Destroy);
	Memory::Hook<false>(0x42907B, this->Destroy);
	Memory::Hook<false>(0x429115, this->Destroy);
	Memory::Hook<false>(0x42914A, this->Destroy);
	Memory::Hook<false>(0x429339, this->Destroy);
	Memory::Hook<false>(0x492446, this->Destroy);
	Memory::Hook<false>(0x507B72, this->Destroy);
	Memory::Hook<false>(0x507BFD, this->Destroy);
	Memory::Hook<false>(0x507C58, this->Destroy);
	Memory::Hook<false>(0x507DCA, this->Destroy);
	Memory::Hook<false>(0x507E1E, this->Destroy);
	Memory::Hook<false>(0x50949D, this->Destroy);
	Memory::Hook<false>(0x50A216, this->Destroy);
	Memory::Hook<false>(0x50A7E2, this->Destroy);
	Memory::Hook<false>(0x5AB8C3, this->Destroy);
	Memory::Hook<false>(0x5AC298, this->Destroy);
	Memory::Hook<false>(0x5AD2DA, this->Destroy);
	Memory::Hook<true>(0x5F010F, this->Glow);
}

void Sign::Add(BYTE Index, const char* Folder, const char* File, bool Glow)
{
	this->Signs[Index] = {(short)(MODEL_SIGN + Index), Folder, File, Glow};
}

SignInfo* Sign::Get(BYTE Index)
{
	if (this->Signs.count(Index) > 0)
	{
		return &this->Signs.at(Index);
	}

	return null;
}

SignInfo* Sign::GetByModel(WORD Model)
{
	for (auto it = this->Signs.begin(); it != this->Signs.end(); ++it)
	{
		if (it->second.Model == Model)
		{
			return &it->second;
		}
	}

	return null;
}

LPBYTE Sign::Create(ViewportInfo* Viewport)
{
	if (pState == STATE_SELECT_SERVER)
	{
		return null;
	}

	if (Viewport->Type == 1)
	{
		switch (pState)
		{
			case STATE_SELECT_CHARACTER:
			{
				if (Viewport->SignID == 0)
				{
					if (Viewport->Sign)
					{
						Destroy(Viewport);
					}

					if (gUser.Sign[Viewport->Index] != 0)
					{
						Viewport->SignID = gUser.Sign[Viewport->Index];
					}
					else if ((Viewport->ViewSkillState & 0x1000000) == 0x1000000 || Viewport->CtlCode == 8 || Viewport->CtlCode == 16 || Viewport->CtlCode == 32 || Viewport->CtlCode == 64)
					{
						Viewport->SignID = 5;
					}
				}
				else
				{
					if (gUser.Sign[Viewport->Index] != 0)
					{
						if (Viewport->SignID != gUser.Sign[Viewport->Index])
						{
							if (Viewport->Sign)
							{
								Destroy(Viewport);
							}

							Viewport->SignID = gUser.Sign[Viewport->Index];
						}
					}
					else if (Viewport->SignID != 5 && (Viewport->ViewSkillState & 0x1000000) == 0x1000000 || Viewport->CtlCode == 8 || Viewport->CtlCode == 16 || Viewport->CtlCode == 32 || Viewport->CtlCode == 64)
					{
						if (Viewport->Sign)
						{
							Destroy(Viewport);
						}

						Viewport->SignID = 5;
					}
				}

				break;
			}
			case STATE_PLAYING:
			{
				if (Viewport->Index == gUser.Index)
				{
					if (Viewport->SignID == 0)
					{
						if (Viewport->Sign)
						{
							Destroy(Viewport);
						}

						if (gUser.Sign[0] != 0)
						{
							Viewport->SignID = gUser.Sign[0];
						}
						else if ((Viewport->ViewSkillState & 0x1000000) == 0x1000000 || Viewport->CtlCode == 8 || Viewport->CtlCode == 16 || Viewport->CtlCode == 32 || Viewport->CtlCode == 64)
						{
							Viewport->SignID = 5;
						}
					}
					else
					{
						if (Viewport->SignID != 5 && (Viewport->ViewSkillState & 0x1000000) == 0x1000000 || Viewport->CtlCode == 8 || Viewport->CtlCode == 16 || Viewport->CtlCode == 32 || Viewport->CtlCode == 64)
						{
							if (Viewport->Sign)
							{
								Destroy(Viewport);
							}

							Viewport->SignID = 5;
						}
						else
						{
							// vc prefere que a sign do GM sempre seja prioridade ou a nova? pq o q ta acontecendo aqui é o seguinte
							// quando o char é gm, ele vem com a sign padrao
							// provavelmente o char ta configurado com alguma sign custom no banco e por isso ta uma sobrescrevendo a outra
							// por isso fica piscando
							// ele tem 0 no banco, mas, prioridade pra sign do gm sim. 0? ctz?
							if (!(Viewport->SignID == 5 && (Viewport->ViewSkillState & 0x1000000) == 0x1000000 || Viewport->CtlCode == 8 || Viewport->CtlCode == 16 || Viewport->CtlCode == 32 || Viewport->CtlCode == 64))
							{
								if (Viewport->SignID != gUser.Sign[0])
								{
									if (Viewport->Sign)
									{
										Destroy(Viewport);
									}

									Viewport->SignID = gUser.Sign[0];
								}
							}
						}
					}
				}
				else
				{
					auto Player = gViewport.GetCustom(Viewport->Index);

					if (Player)
					{
						if (Viewport->SignID == 0)
						{
							if (Viewport->Sign)
							{
								Destroy(Viewport);
							}

							if (Player->Sign != 0)
							{
								Viewport->SignID = Player->Sign;
							}
							else if ((Viewport->ViewSkillState & 0x1000000) == 0x1000000 || Viewport->CtlCode == 8 || Viewport->CtlCode == 16 || Viewport->CtlCode == 32 || Viewport->CtlCode == 64)
							{
								Viewport->SignID = 5;
							}
						}
						else
						{
							if (Player->Sign != 0)
							{
								if (Viewport->SignID != Player->Sign)
								{
									if (Viewport->Sign)
									{
										Destroy(Viewport);
									}

									Viewport->SignID = Player->Sign;
								}
							}
							else if (Viewport->SignID != 5 && (Viewport->ViewSkillState & 0x1000000) == 0x1000000 || Viewport->CtlCode == 8 || Viewport->CtlCode == 16 || Viewport->CtlCode == 32 || Viewport->CtlCode == 64)
							{
								if (Viewport->Sign)
								{
									Destroy(Viewport);
								}

								Viewport->SignID = 5;
							}
						}
					}
				}

				break;
			}
		}

		if (!Viewport->Sign)
		{
			if (Viewport->SignID >= 5 && Viewport->SignID < 255)
			{
				if (Viewport->SignID == 14 || Viewport->SignID == 15)
				{
				}
				else
				{
					BYTE* Buffer = new BYTE[472];

					if (Buffer)
					{
						if (Viewport->SignID == 5)
						{
							Viewport->Sign = pCreateSign(Buffer, 0x128, 20, 1, 70.f, -5.f, 0.0f, 0, 0, 45.f);
						}
						else if (Viewport->SignID >= 6 && Viewport->SignID <= 13)
						{
							Viewport->Sign = pCreateSign2(Buffer, 0x637, (Viewport->SignID + 1) % 7, 20, 120.f, 0.0f, 0.0f);
						}
						else if (Viewport->SignID >= 16 && Viewport->SignID < 255)
						{
							auto Sign = gSign.Get((Viewport->SignID + 1) - 16);

							if (Sign)
							{
								Viewport->Sign = pCreateSign(Buffer, Sign->Model, 20, 1, 70.f, -5.f, 0.0f, 0, 0, 45.f);
							}
						}
					}
				}
			}
		}

		return Viewport->Sign;
	}

	return null;
}

void Sign::Destroy(ViewportInfo* Viewport)
{
	if (Viewport->Sign)
	{
		delete[] Viewport->Sign;

		Viewport->SignID = 0;
		Viewport->Sign = null;
	}
}

void __declspec(naked) Sign::Glow()
{
	static DWORD Local[2] = {0x5F015C, 0x5F0115};
	static WORD Id;
	static SignInfo* Sign;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Sign = gSign.GetByModel(Id);

	if (Sign && Sign->Glow)
	{
		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0x128;
		JNZ NotZero;
		JMP Local[4];

	NotZero:
		JMP Local[0];
	}
}

Sign gSign;
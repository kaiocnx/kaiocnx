#include "Library.h"
#include "Patent.h"
#include "User.h"

Patent::Patent() : Patents{}
{
}

Patent::~Patent()
{
}

void Patent::Load()
{
	//--------------------------------------------------
	// Novas placas
	//--------------------------------------------------
	// Para adicionar uma nova placa, basta:
	// this->Add(<id>, <file>, <width>, <height>, <x>, <y>, <padding_x>, <padding_y>, <scale_x>, <scale_y>);
	// Obs: O id não pode ser 0.
	this->Add(1, "Customs\\Patentes\\Patent01.tga", 20, 23, -15, 0, 0, -5, 0, 0);
	this->Add(2, "Customs\\Patentes\\Patent02.tga", 20, 23, -15, 0, 0, -5, 0, 0);
	this->Add(3, "Customs\\Patentes\\Patent03.tga", 20, 23, -15, 0, 0, -5, 0, 0);

	this->Add(4, "Customs\\Patentes\\1reset.tga", 30, 30, -15, -15, 0, -5, 0, 0);
	this->Add(5, "Customs\\Patentes\\2reset.tga", 30, 30, -15, -15, 0, -5, 0, 0);
	this->Add(6, "Customs\\Patentes\\3reset.tga", 30, 30, -15, -15, 0, -5, 0, 0);
	this->Add(7, "Customs\\Patentes\\4reset.tga", 30, 30, -15, -15, 0, -5, 0, 0);
	this->Add(8, "Customs\\Patentes\\5reset.tga", 30, 30, -15, -15, 0, -5, 0, 0);
	this->Add(9, "Customs\\Patentes\\5death.tga", 30, 30, -15, -15, 0, -5, 0, 0);
	this->Add(10, "Customs\\Patentes\\4death.tga", 30, 30, -15, -15, 0, -5, 0, 0);
	this->Add(11, "Customs\\Patentes\\3death.tga", 30, 30, -15, -15, 0, -5, 0, 0);
	this->Add(12, "Customs\\Patentes\\2death.tga", 30, 30, -15, -15, 0, -5, 0, 0);
	this->Add(13, "Customs\\Patentes\\1death.tga", 30, 30, -15, -15, 0, -5, 0, 0);
}

void Patent::Add(BYTE Index, const char* File, WORD Width, WORD Height, short X, short Y, short PaddingX, short PaddingY, short ScaleX, short ScaleY)
{
	this->Patents[Index] = {File, Width, Height, X, Y, PaddingX, PaddingY, ScaleX, ScaleY};
}

PatentInfo* Patent::Get(BYTE Index)
{
	if (Index == 0)
	{
		return null;
	}

	if (this->Patents.count(Index) > 0)
	{
		return &this->Patents.at(Index);
	}

	return null;
}

void Patent::Draw(int X, int Y, ViewportInfo* Viewport, ViewportCustomInfo* Custom)
{
	BYTE Index = 0;

	if (Viewport->Index < 5 || gUser.Index == Viewport->Index)
	{
		if (gUser.Patent > 0)
		{
			Index = gUser.Patent;
		}
	}
	else if (Custom && Custom->Patent > 0)
	{
		Index = Custom->Patent;
	}

	if (Index != 0)
	{
		auto Patent = this->Get(Index);

		if (Patent)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			int PaddingX = 0, PaddingY = 0;

			if (Viewport->GuildIndex != -1)
			{
				PaddingX += Patent->PaddingX;
				PaddingY += Patent->PaddingY;
			}

			float X2 = (float)(X + ((Patent->X + PaddingX) * pScreenDivisorX) - ((Patent->Width / 2) * pScreenDivisorX));
			float Y2 = (float)(Y + ((Patent->Y + PaddingY) * pScreenDivisorY));
			float ScaleX = (float)(Patent->Width + Patent->ScaleX) * pImageDivisor;
			float ScaleY = (float)(Patent->Height + Patent->ScaleY) * pImageDivisor;

			pDrawImage(TEXTURE_PATENT + (Index - 1), X2, Y2, (float)(Patent->Width), (float)(Patent->Height), 0, 0, ScaleX, ScaleY, 1, 1);

			pDisableAlphaBlend();
			glColor3f(1.0f, 1.0f, 1.0f);
		}
	}

}

Patent gPatent;
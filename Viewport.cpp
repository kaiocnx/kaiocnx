#include "Library.h"
#include "Viewport.h"

Viewport::Viewport() : Custom{}
{
}

Viewport::~Viewport()
{
}

void Viewport::Clear()
{
	for (int i = 0; i < VIEWPORT_MAX; ++i)
	{
		((ViewportInfo*)(VIEWPORT_BASE + sizeof(ViewportInfo) * i))->Live = false;
	}
}

ViewportInfo* Viewport::GetMyself()
{
	return (ViewportInfo*)(pMyViewport);
}

ViewportInfo* Viewport::GetByPosition(int Position)
{
	if (Position >= VIEWPORT_MAX)
	{
		return null;
	}

	return (ViewportInfo*)(VIEWPORT_BASE + sizeof(ViewportInfo) * Position);
}

ViewportInfo* Viewport::GetByIndex(short Index)
{
	ViewportInfo* Viewport = null;

	for (int i = 0; i < VIEWPORT_MAX; ++i)
	{
		Viewport = (ViewportInfo*)(VIEWPORT_BASE + sizeof(ViewportInfo) * i);

		if (Viewport->Live && Viewport->Index == Index)
		{
			break;
		}
	}

	return Viewport;
}

ViewportInfo* Viewport::GetByName(char* Name)
{
	ViewportInfo* Viewport = null;

	for (int i = 0; i < VIEWPORT_MAX; ++i)
	{
		Viewport = (ViewportInfo*)(VIEWPORT_BASE + sizeof(ViewportInfo) * i);

		if (Viewport->Live && !strcmp(Viewport->Name, Name))
		{
			break;
		}
	}

	return Viewport;
}

void Viewport::ClearCustom()
{
	this->Custom.clear();
}

void Viewport::AddCustom(BYTE Index[2], BYTE Sign, BYTE Patent)
{
	short aIndex = 0;
	
	if ((Index[0] & 0x80) == 0x80)
	{
		aIndex = MAKE_NUMBERW((Index[0] & ~0x80), Index[1]);
	}
	else
	{
		aIndex = MAKE_NUMBERW(Index[0], Index[1]);
	}

	if (Sign != 0)
	{
		Sign = 16 + (Sign - 1);
	}

	this->Custom[aIndex] = {Sign, Patent};
}

ViewportCustomInfo* Viewport::GetCustom(short Index)
{
	if (this->Custom.count(Index) > 0)
	{
		return &this->Custom[Index];
	}

	return null;
}


Viewport gViewport;
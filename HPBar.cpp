#include "Library.h"
#include "HPBar.h"

HPBar::HPBar() : Percent{}
{
}

HPBar::~HPBar()
{
}

void HPBar::Clear()
{
	this->Percent.clear();
}

void HPBar::Add(WORD Index, BYTE Percent)
{
	this->Percent[Index] = Percent;
}

BYTE HPBar::GetPercent(WORD Index) const
{
	if (this->Percent.count(Index) > 0)
	{
		return this->Percent.at(Index);
	}

	return (BYTE)(-1);
}
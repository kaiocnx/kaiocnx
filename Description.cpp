#include "Library.h"
#include "Description.h"

Description::Description()
{
}

Description::~Description()
{
}

void Description::Add(int Item, const std::string& Text, const std::vector<BYTE>& Background, const std::vector<BYTE>& Foreground, BYTE Bold)
{
	this->Descriptions[Item].push_back({Text, RGBA(Background.at(0), Background.at(1), Background.at(2), Background.at(3)), RGBA(Foreground.at(0), Foreground.at(1), Foreground.at(2), Foreground.at(3)), Bold});
}

std::vector<DescriptionInfo>* Description::Get(int Item)
{
	if (this->Descriptions.count(Item) > 0)
	{
		return &this->Descriptions.at(Item);
	}

	return nullptr;
}
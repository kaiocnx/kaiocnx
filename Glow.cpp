#include "Library.h"
#include "Glow.h"

Glow::Glow() :
	Color{}
{
}

Glow::~Glow()
{
}

void Glow::Add(int Model, const std::vector<float>& Color)
{
	this->Color[Model] = {Color.at(0), Color.at(1), Color.at(2)};
}

GlowColor* Glow::Get(int Model)
{
	if (this->Color.count(Model) > 0)
	{
		return &this->Color.at(Model);
	}

	return nullptr;
}
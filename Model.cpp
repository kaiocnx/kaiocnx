#include "Library.h"
#include "Model.h"
#include "Sign.h"
#include "Item.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Hook()
{
	Memory::Hook<false>(0x60ABBB, this->LoadModels);
	Memory::Hook<false>(0x5D055C, this->ShowModel);
	Memory::Hook<false>(0x5D0595, this->ShowModel);
	Memory::Hook<false>(0x5D05C6, this->ShowModel);
	Memory::Hook<false>(0x5D05F7, this->ShowModel);
	Memory::Hook<false>(0x5D062C, this->ShowModel);
	Memory::Hook<false>(0x5D065D, this->ShowModel);
	Memory::Hook<false>(0x5D0697, this->ShowModel);
	Memory::Hook<false>(0x5D06D8, this->ShowModel);
	Memory::Hook<false>(0x5D0719, this->ShowModel);
	Memory::Hook<false>(0x5D075E, this->ShowModel);
	Memory::Hook<false>(0x5D0789, this->ShowModel);
	Memory::Hook<false>(0x5D07B4, this->ShowModel);
	Memory::Hook<false>(0x5D07FF, this->ShowModel);
	Memory::Hook<false>(0x5D082C, this->ShowModel);
	Memory::Hook<false>(0x5D0858, this->ShowModel);
	Memory::Hook<false>(0x5D089E, this->ShowModel);
	Memory::Hook<false>(0x5D08CA, this->ShowModel);
	Memory::Hook<false>(0x5D090F, this->ShowModel);
	Memory::Hook<false>(0x5D090F, this->ShowModel);
	Memory::Hook<false>(0x5D0987, this->ShowModel);
	Memory::Hook<false>(0x5D093B, this->ShowModel);
	Memory::Hook<false>(0x5D0987, this->ShowModel);
	Memory::Hook<false>(0x5D09B2, this->ShowModel);
	Memory::Hook<false>(0x5D09F0, this->ShowModel);
	Memory::Hook<false>(0x5D0A1D, this->ShowModel);
}

ModelInfo* Model::GetInfo(int Model)
{
	return (ModelInfo*)(Model * sizeof(ModelInfo) + MODEL_BASE); 
}

void Model::LoadModels()
{
	pLoadModels();

	for (auto it = gItem.Items.cbegin(); it != gItem.Items.cend(); ++it)
	{
		pLoadModel(it->first + ITEM_MODEL, it->second.Folder, it->second.File, -1);
	}

	for (auto it = gSign.Signs.begin(); it != gSign.Signs.end(); ++it)
	{
		pLoadModel(it->second.Model, it->second.Folder, it->second.File, -1);
	}
}

int Model::ShowModel(int Model, int Unk1, char Unk2, int Unk3, float* Unk4, int Unk5, char Unk6)
{
	return pShowModel(Model, Unk1, Unk2, Unk3, Unk4, Unk5, Unk6);
}

Model gModel;
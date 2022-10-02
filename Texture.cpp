#include "Library.h"
#include "Texture.h"
#include "Patent.h"
#include "Sign.h"
#include "Item.h"

TextureImage Image[TEXTURE_IMAGE_MAX];

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::Hook()
{
	Memory::Hook<false>(0x60F128, this->LoadInterfaces);
	Memory::Hook<false>(0x60F145, this->LoadInterfaces);
	Memory::Hook<false>(0x60ABC0, this->LoadTextures);

	// Texturas
	memset(&Image, 0, sizeof(Image));

	Memory::Update<DWORD>(0x4A982D, TEXTURE_IMAGE_MAX);
	Memory::Update<DWORD>(0x6086EF, (DWORD)(&Image));
	Memory::Update<DWORD>(0x534410, (DWORD)(&Image));
	Memory::Update<DWORD>(0x534A39, (DWORD)(&Image));
	Memory::Update<DWORD>(0x534A48, (DWORD)(&Image));
	Memory::Update<DWORD>(0x5E000D, (DWORD)(&Image));
	Memory::Update<DWORD>(0x5E9780, (DWORD)(&Image));
	Memory::Update<DWORD>(0x5FA7E9, (DWORD)(&Image));
	Memory::Update<DWORD>(0x5FA844, (DWORD)(&Image));
	Memory::Update<DWORD>(0x5FA9BC, (DWORD)(&Image));
	Memory::Update<DWORD>(0x62C4E6, (DWORD)(&Image));
	Memory::Update<DWORD>(0x62C93B, (DWORD)(&Image));
	Memory::Update<DWORD>(0x62CADD, (DWORD)(&Image));
	Memory::Update<DWORD>(0x62CB5C, (DWORD)(&Image));
	Memory::Update<DWORD>(0x44D909, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x44D9CA, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x44DA8A, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x460BB8, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x461570, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x53D284, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x53DF56, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x5484E4, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x5485F6, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x636CA2, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x636CC0, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x636CE9, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x636CFE, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x5E0006, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x5E9779, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x630A78, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x636D4F, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x636F6D, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x636FA0, (DWORD)(&Image->Width));
	Memory::Update<DWORD>(0x44D923, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x44D9B2, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x44DA74, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x460BA0, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x46142D, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x46155A, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x461B06, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x53D290, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x53DF5F, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x548403, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x5484CC, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x5485E0, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x5E90D9, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x636CB1, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x636CD4, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x636CF2, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x636D0D, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x53BACE, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x636D72, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x636FE5, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x63701A, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x6598D0, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x6599B5, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x659B2F, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x659B69, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x659BA2, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x659BEC, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x659C28, (DWORD)(&Image->Height));
	Memory::Update<DWORD>(0x44D9D7, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x451F6B, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x451FF3, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x4529AA, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x4529FE, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x460BC5, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x4E5487, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x4E54D4, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x4E606B, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x4E60B8, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x4E7ACD, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x4E7B03, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x53D2A5, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x53DD95, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x5484F1, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x60D718, (DWORD)(&Image->UnkDword28));
	Memory::Update<DWORD>(0x44D997, (DWORD)(&Image->Texture));
	Memory::Update<DWORD>(0x5484B4, (DWORD)(&Image->Texture));
	Memory::Update<DWORD>(0x60C935, (DWORD)(&Image->Texture));
	Memory::Update<DWORD>(0x60C991, (DWORD)(&Image->Texture));
	Memory::Update<DWORD>(0x637259, (DWORD)(&Image->Texture));
	Memory::Update<DWORD>(0x460B0D, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x4631D9, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x463209, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x60EF87, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x44D95F, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x44D9AC, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x4603BA, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x460B9A, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x46321E, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x548422, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x5484C6, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x5E90C5, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x534407, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x62CAD4, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x62CB53, (DWORD)(&Image->UnkPByte34));
	Memory::Update<DWORD>(0x5DFDF8, (DWORD)(&Image) + 0x790);
	Memory::Update<DWORD>(0x5E0375, (DWORD)(&Image) + 0x790);
	Memory::Update<DWORD>(0x5DFE06, (DWORD)(&Image) + 0x794);
	Memory::Update<DWORD>(0x5E0383, (DWORD)(&Image) + 0x794);
	Memory::Update<DWORD>(0x5DFF72, (DWORD)(&Image) + 0x798);
	Memory::Update<DWORD>(0x5E0432, (DWORD)(&Image) + 0x798);
	Memory::Update<DWORD>(0x5DFF56, (DWORD)(&Image) + 0x79C);
	Memory::Update<DWORD>(0x5E0419, (DWORD)(&Image) + 0x79C);
	Memory::Update<DWORD>(0x5DFE16, (DWORD)(&Image) + 0x7A4);
	Memory::Update<DWORD>(0x5DFF68, (DWORD)(&Image) + 0x7A4);
	Memory::Update<DWORD>(0x5E0393, (DWORD)(&Image) + 0x7A4);
	Memory::Update<DWORD>(0x5E03CB, (DWORD)(&Image) + 0x7A4);
	Memory::Update<DWORD>(0x5E042B, (DWORD)(&Image) + 0x7A4);
	Memory::Update<DWORD>(0x5E8C12, (DWORD)(&Image) + 0x7A8);
	Memory::Update<DWORD>(0x59CD95, (DWORD)(&Image) + 0x7D0);
	Memory::Update<DWORD>(0x6044AA, (DWORD)(&Image) + 0xE38);
	Memory::Update<DWORD>(0x6044B3, (DWORD)(&Image) + 0x1068);
	Memory::Update<DWORD>(0x6044FF, (DWORD)(&Image) + 0x1068);
	Memory::Update<DWORD>(0x604552, (DWORD)(&Image) + 0x1538);

	pMaxTexture = 15000;
	Memory::Nop<5>(0x5FA7B0);
}

void Texture::LoadInterfaces()
{
	pLoadInterfaces();

	for (auto it = gPatent.Patents.cbegin(); it != gPatent.Patents.cend(); ++it)
	{
		if (strstr(it->second.File, ".tga"))
		{
			pLoadTGA(it->second.File, TEXTURE_PATENT + (it->first - 1), GL_NEAREST, GL_CLAMP, 0, 1);
		}
		else
		{
			pLoadJPG(it->second.File, TEXTURE_PATENT + (it->first - 1), GL_NEAREST, GL_CLAMP, 0, 1);
		}
	}
}

void Texture::LoadTextures()
{
	pLoadTextures();

	for (auto it = gItem.Items.cbegin(); it != gItem.Items.cend(); ++it)
	{
		pLoadTexture(it->first + ITEM_MODEL, &it->second.Folder[5], GL_REPEAT, GL_NEAREST, 1);
	}

	for (auto it = gSign.Signs.begin(); it != gSign.Signs.end(); ++it)
	{
		pLoadTexture(it->second.Model, &it->second.Folder[5], GL_REPEAT, GL_NEAREST, 1);
	}
}

Texture gTexture;
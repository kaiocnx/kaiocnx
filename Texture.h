#pragma once

#define TEXTURE_IMAGE_MAX	0x488E
#define TEXTURE_PATENT		0x2000

struct TextureImage
{
	char Name[32];
	float Width;			// 20
	float Height;			// 24
	DWORD UnkDword28;		// 28
	GLuint Texture;			// 2C
	BYTE UnkByte30;			// 30
	BYTE Unknown3[0x03];	// 31
	BYTE* UnkPByte34;		// 34
};

class Texture
{
public:
	Texture();
	~Texture();

public:
	void Hook();

private:
	static void LoadInterfaces();
	static void LoadTextures();
};

extern Texture gTexture;
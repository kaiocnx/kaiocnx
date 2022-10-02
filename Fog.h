#pragma once

struct FogColor
{
	float R;
	float G;
	float B;
	float A;
};

class Fog
{
public:
	Fog();
	~Fog();

public:
	void Load();
	void Add(BYTE Map, BYTE Red, BYTE Green, BYTE Blue, BYTE Alpha);
	void Apply(GLenum Mode);
	bool Apply();

public:
	bool Active;

private:
	std::unordered_map<BYTE, FogColor> Color;
	FogColor Default;
	UINT Textures[5];
};

extern Fog gFog;
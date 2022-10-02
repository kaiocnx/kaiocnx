#pragma once

struct GlowColor
{
	float R;
	float G;
	float B;
};

class Glow
{
public:
	Glow();
	~Glow();

public:
	void Add(int Model, const std::vector<float>& Color);
	GlowColor* Get(int Model);

private:
	std::unordered_map<int, GlowColor> Color;
};
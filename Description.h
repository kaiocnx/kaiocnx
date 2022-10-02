#pragma once

struct DescriptionInfo
{
	std::string Text;
	DWORD Background;
	DWORD Foreground;
	BYTE Bold;
};

class Description
{
public:
	Description();
	~Description();

public:
	void Add(int Item, const std::string& Text, const std::vector<BYTE>& Background, const std::vector<BYTE>& Foreground, BYTE Bold);
	std::vector<DescriptionInfo>* Get(int Item);

private:
	std::unordered_map<int, std::vector<DescriptionInfo>> Descriptions;
};
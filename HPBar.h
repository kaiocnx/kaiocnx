#pragma once

class HPBar
{
public:
	HPBar();
	~HPBar();
	
public:
	void Clear();
	void Add(WORD Index, BYTE Percent);
	BYTE GetPercent(WORD Index) const;

private:
	std::unordered_map<WORD, BYTE> Percent;
};
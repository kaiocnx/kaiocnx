#pragma once

class Registry
{
public:
	Registry() = delete;
	~Registry() = delete;

public:
	template<typename T>
	static T Read(const std::string& Field)
	{
		T Value = T();
		HKEY Key;

		if (RegOpenKey(HKEY_CURRENT_USER, "Software\\Webzen\\MU\\Config", &Key) == 0)
		{
			DWORD Size = sizeof(Value);
			RegQueryValueEx(Key, Field.c_str(), nullptr, nullptr, (LPBYTE)(&Value), &Size);
			RegCloseKey(Key);
		}

		return Value;
	}

	template<>
	static bool Read(const std::string& Field)
	{
		bool Value = false;
		HKEY Key;

		if (RegOpenKey(HKEY_CURRENT_USER, "Software\\Webzen\\MU\\Config", &Key) == 0)
		{
			int Temp = 0;
			DWORD Size = sizeof(Temp);
			RegQueryValueEx(Key, Field.c_str(), nullptr, nullptr, (LPBYTE)(&Temp), &Size);
			RegCloseKey(Key);

			Value = (Temp > 0);
		}

		return Value;
	}
};
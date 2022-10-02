#pragma once

class Memory
{
public:
	Memory() = delete;
	~Memory() = delete;

public:
	template<typename T>
	static T Read(DWORD Offset)
	{
		return *(T*)(Offset);
	}

	template<>
	static char* Read(DWORD Offset)
	{
		return (char*)(Offset);
	}

	template<>
	static std::string Read(DWORD Offset)
	{
		return (std::string)((char*)(Offset));
	}

	template<typename T>
	static void Update(DWORD Offset, T Value)
	{
		*(T*)(Offset) = Value;
	}

	template<>
	static void Update(DWORD Offset, const char* Value)
	{
		memcpy((PVOID)(Offset), Value, strlen(Value) + 1);
	}

	template<>
	static void Update(DWORD Offset, char* Value)
	{
		memcpy((PVOID)(Offset), Value, strlen(Value) + 1);
	}

	template<>
	static void Update(DWORD Offset, std::string Value)
	{
		memcpy((PVOID)(Offset), Value.c_str(), Value.length() + 1);
	}

	template<typename T>
	static void Update(DWORD Offset, std::vector<T> Values)
	{
		WORD i = 0;

		for (const T& Value : Values)
		{
			*(T*)(Offset + i++) = Value;
		}
	}

	template<bool Jump = false>
	static void Hook(DWORD Offset, PVOID Function)
	{
		*(BYTE*)(Offset) = (Jump) ? 0xE9 : 0xE8;
		*(DWORD*)(Offset + 1) = (DWORD)(Function)-(Offset + 5);
	}

	template<int Count = 1>
	static void Nop(int Offset)
	{
		for (int i = 0; i < Count; ++i)
		{
			*(BYTE*)(Offset + i) = 0x90;
		}
	}
};
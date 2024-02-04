#pragma once
#include <Windows.h>
#include "Offsets.h"
#include <iostream>
#include <TlHelp32.h>
#include "Structures.h"

class Memory
{
public:
	HWND hWnd;
	HANDLE hSS;
	MODULEENTRY32 mEntry;
	void Setup();

	DWORD GetProcessID(const wchar_t* windowName);

	MODULEENTRY32 GetModule(DWORD pID, const wchar_t* moduleName);
	VOID GetModules();

	template<typename T>
	T ReadMemory(DWORD64 address)
	{
		T buffer;
		ReadProcessMemory(offsets.hProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
		return buffer;
	}

	template<typename T>
	BOOL WriteMemory(DWORD64 address, T value)
	{
		return WriteProcessMemory(offsets.hProcess, (LPVOID)address, &value, sizeof(value), NULL);
	}
};

extern Memory mem;


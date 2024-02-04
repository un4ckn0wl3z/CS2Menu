#include "Memory.h"
#include <QDebug>
Memory mem;

DWORD Memory::GetProcessID(const wchar_t* windowName)
{
	DWORD pID;
	do
	{
		offsets.hWnd = FindWindow(NULL, windowName);
		Sleep(50);
	} while (!offsets.hWnd);


	GetWindowThreadProcessId(offsets.hWnd, &pID);
	qDebug() << "[+] CS2 Process ID found: " << pID;
	return pID;
}

MODULEENTRY32 Memory::GetModule(DWORD pID, const wchar_t* moduleName)
{
	hSS = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pID);
	mEntry.dwSize = sizeof(MODULEENTRY32);
	if (hSS != INVALID_HANDLE_VALUE)
	{
		if (Module32First(hSS, &mEntry))
		{
			do
			{
				if (!wcscmp((const wchar_t*) mEntry.szModule, moduleName))
				{
					break;
				}
			} while (Module32Next(hSS, &mEntry));
		}
	}
	CloseHandle(hSS);
	return mEntry;
}

VOID Memory::GetModules()
{
	do
	{
		offsets.clientBase = (DWORD64)GetModule(offsets.processID, L"client.dll").modBaseAddr;
		Sleep(50);
	} while (!offsets.clientBase);

	if (offsets.clientBase)
	{
		qDebug() << "[+] clientBase: 0x" << std::hex << offsets.clientBase;
		config.foundGameProcess = 1;
		Sleep(1000);
	}
	else
	{
		qDebug() << "[-] Cannot open module handle for client.dll";
	}
}


void Memory::Setup()
{
	offsets.processID = GetProcessID(L"Counter-Strike 2");
	offsets.hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, offsets.processID);
	if (offsets.hProcess)
	{
		qDebug() << "[+] hProcess: 0x" << std::hex << offsets.hProcess;
		
	} 
	else 
	{
		qDebug() << "[-] Cannot open process handle for CS2";
	}
}



#pragma once
#include <Windows.h>


class Offsets
{
public:

	DWORD64 dwEntityList = 0x16E1C68;
	DWORD64 dwLocalPlayer = 0x16D4F48;
	DWORD64 dwViewMatrix = 0x182CEA0;

	DWORD m_iTeamNum = 0xE90;
	DWORD m_iHealth = 0xA6C;
	DWORD m_fPos = 0xCD8;
	DWORD m_fViewAngle = 0x1890F30;
	DWORD m_crosshairId = 0x1544;


	HWND hWnd = 0;
	HANDLE hProcess = 0;
	DWORD processID = 0;
	DWORD64 clientBase;
};

extern Offsets offsets;

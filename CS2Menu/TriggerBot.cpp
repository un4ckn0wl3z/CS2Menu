#include "TriggerBot.h"

void TriggerBot()
{

	DWORD64 localPlayer = mem.ReadMemory<DWORD64>(offsets.clientBase + offsets.dwLocalPlayer);
	DWORD crosshairId = mem.ReadMemory<DWORD>(localPlayer + offsets.m_crosshairId);
	DWORD localTeam = mem.ReadMemory<DWORD>(localPlayer + offsets.m_iTeamNum);
	DWORD playerHealth = mem.ReadMemory<DWORD>(localPlayer + offsets.m_iHealth);


	if (0 < playerHealth && playerHealth <= 100)
	{



		if (crosshairId != -1)
		{
			INPUT down;
			down.mi.dx = 0;
			down.mi.dy = 0;
			down.type = INPUT_MOUSE;
			down.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			down.mi.time = 0;
			down.mi.dwExtraInfo = 0;

			INPUT up;
			up.mi.dx = 0;
			up.mi.dy = 0;
			up.type = INPUT_MOUSE;
			up.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			up.mi.time = 0;
			up.mi.dwExtraInfo = 0;

			SendInput(1, &down, sizeof(down));
			Sleep(20);
			SendInput(1, &up, sizeof(up));
		}
	}

}

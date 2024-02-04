#include "AimBot.h"

void InMemAimBot()
{
	Vec3 localFovPos3, entityPosHead3, localPosHead3;
	Vec2 calcLocalAngle, calcLocalAngleDiff;
	Vec2 targetAngle;

	int tmpTargetAngleSum = CONFIG_FOV, targetHealth = 0;
	DWORD64 target = 0x0;


	DWORD64 localPlayer = mem.ReadMemory<DWORD64>(offsets.clientBase + offsets.dwLocalPlayer);
	DWORD localTeam = mem.ReadMemory<DWORD>(localPlayer + offsets.m_iTeamNum);

	Vec3 localPlayerPos3 = { 0 }; // character's world coord
	localPlayerPos3.x = mem.ReadMemory<float>(localPlayer + offsets.m_fPos + 0x0);
	localPlayerPos3.y = mem.ReadMemory<float>(localPlayer + offsets.m_fPos + 0x4);
	localPlayerPos3.z = mem.ReadMemory<float>(localPlayer + offsets.m_fPos + 0x8);

	localPosHead3.x = localPlayerPos3.x;
	localPosHead3.y = localPlayerPos3.y;
	localPosHead3.z = localPlayerPos3.z + 50.f;

	localFovPos3.x = localPosHead3.x;
	localFovPos3.y = localPosHead3.y;
	localFovPos3.z = localPosHead3.z;


	if (localTeam)
	{
		for (size_t i = 0; i < 32; i++)
		{
			DWORD64 entity = mem.ReadMemory<DWORD64>(offsets.clientBase + offsets.dwEntityList + i * 0x8);
			if (entity == localPlayer) continue;
			if (entity == 0) continue;

			Vec3 entityPos3 = { 0 }; // character's world coord

			entityPos3.x = mem.ReadMemory<float>(entity + offsets.m_fPos + 0x0);
			entityPos3.y = mem.ReadMemory<float>(entity + offsets.m_fPos + 0x4);
			entityPos3.z = mem.ReadMemory<float>(entity + offsets.m_fPos + 0x8);

			entityPosHead3.x = entityPos3.x;
			entityPosHead3.y = entityPos3.y;
			entityPosHead3.z = entityPos3.z + 50.f;

			DWORD teamID = mem.ReadMemory<DWORD>(entity + offsets.m_iTeamNum);
			if (teamID != 3 && teamID != 6) continue;

			// if (true) {
			if (config.team or teamID != localTeam) {
				DWORD entityHealth = mem.ReadMemory<DWORD>(entity + offsets.m_iHealth);

				if (0 < entityHealth && entityHealth <= 100)
				{

					CalcAngle(localFovPos3, entityPosHead3, calcLocalAngle, calcLocalAngleDiff);
					if (fabs(calcLocalAngleDiff.x) <= CONFIG_FOV / 2 && fabs(calcLocalAngleDiff.y) <= CONFIG_FOV / 2) {
						int tmpAngleSum = fabs(calcLocalAngleDiff.x) + fabs(calcLocalAngleDiff.y);
						if (tmpAngleSum < tmpTargetAngleSum) {
							tmpTargetAngleSum = tmpAngleSum;
							target = entity;
							targetAngle = calcLocalAngle;
							targetHealth = entityHealth;
							// break;
						}
					}
				}
			}
		}


		if (GetAsyncKeyState(VK_LMENU) < 0 && localPlayer != 0) {
			if (target != 0 && targetHealth > 0 && targetHealth <= 100) {
				mem.WriteMemory(offsets.clientBase + offsets.m_fViewAngle, targetAngle.y);
				mem.WriteMemory(offsets.clientBase + offsets.m_fViewAngle + 0x4, targetAngle.x);
			}
		}

	}



}

void ExternalAimBot()
{
	Vec3 localFovPos3, targetPos3, entityPosHead3, localPosHead3;
	Vec2 entityPos2, targetPos2, entityPosHead2;

	Vec2 calcLocalAngle, calcLocalAngleDiff;

	int screenCenterX = (draw.rectGame.right - draw.rectGame.left) / 2;
	int screenCenterY = (draw.rectGame.bottom - draw.rectGame.top) / 2 + 15;

	float smooth = 2.38f;
	float TargetX = 0.0f;
	float TargetY = 0.0f;
	bool bSmooth = false;

	int tmpTargetAngleSum = CONFIG_FOV, targetHealth = 0;
	DWORD target = 0x0;


	DWORD64 localPlayer = mem.ReadMemory<DWORD64>(offsets.clientBase + offsets.dwLocalPlayer);
	DWORD localTeam = mem.ReadMemory<DWORD>(localPlayer + offsets.m_iTeamNum);


	Vec3 localPlayerPos3 = { 0 }; // character's world coord

	localPlayerPos3.x = mem.ReadMemory<float>(localPlayer + offsets.m_fPos + 0x0);
	localPlayerPos3.y = mem.ReadMemory<float>(localPlayer + offsets.m_fPos + 0x4);
	localPlayerPos3.z = mem.ReadMemory<float>(localPlayer + offsets.m_fPos + 0x8);

	localPosHead3.x = localPlayerPos3.x;
	localPosHead3.y = localPlayerPos3.y;
	localPosHead3.z = localPlayerPos3.z + 50.f;

	localFovPos3.x = localPosHead3.x;
	localFovPos3.y = localPosHead3.y;
	localFovPos3.z = localPosHead3.z;



	if (localTeam)
	{
		for (size_t i = 0; i < 32; i++)
		{
			DWORD64 entity = mem.ReadMemory<DWORD64>(offsets.clientBase + offsets.dwEntityList + i * 0x8);
			if (entity == localPlayer) continue;
			if (entity == 0) continue;

			Vec3 entityPos3 = { 0 }; // character's world coord

			entityPos3.x = mem.ReadMemory<float>(entity + offsets.m_fPos + 0x0);
			entityPos3.y = mem.ReadMemory<float>(entity + offsets.m_fPos + 0x4);
			entityPos3.z = mem.ReadMemory<float>(entity + offsets.m_fPos + 0x8);

			entityPosHead3.x = entityPos3.x;
			entityPosHead3.y = entityPos3.y;
			entityPosHead3.z = entityPos3.z + 50.f;

			DWORD teamID = mem.ReadMemory<DWORD>(entity + offsets.m_iTeamNum);
			if (teamID != 3 && teamID != 6) continue;

			// if (true) {
			if (config.team or teamID != localTeam) {
				DWORD entityHealth = mem.ReadMemory<DWORD>(entity + offsets.m_iHealth);

				if (0 < entityHealth && entityHealth <= 100)
				{

					CalcAngle(localFovPos3, entityPosHead3, calcLocalAngle, calcLocalAngleDiff);
					if (fabs(calcLocalAngleDiff.x) <= CONFIG_FOV / 2 && fabs(calcLocalAngleDiff.y) <= CONFIG_FOV / 2) {
						int tmpAngleSum = fabs(calcLocalAngleDiff.x) + fabs(calcLocalAngleDiff.y);
						if (tmpAngleSum < tmpTargetAngleSum) {
							tmpTargetAngleSum = tmpAngleSum;
							target = entity;
							targetHealth = entityHealth;

							draw.WorldToScreen(entityPosHead3, entityPosHead2);
							targetPos3 = entityPosHead3;
							targetPos2 = entityPosHead2;
							// break;
						}
					}
				}
			}
		}

		//
		if (GetAsyncKeyState(VK_LMENU) < 0 && localPlayer != 0) {
			if (target != 0 && targetHealth > 0 && targetHealth <= 100) {


				if (targetPos2.x != 0)
				{
					if (targetPos2.x > screenCenterX)
					{
						TargetX = -(screenCenterX - targetPos2.x);
						TargetX /= 1;
						if (TargetX + screenCenterX > screenCenterX * 2) TargetX = 0;
					}

					if (targetPos2.x < screenCenterX)
					{
						TargetX = targetPos2.x - screenCenterX;
						TargetX /= 1;
						if (TargetX + screenCenterX < 0) TargetX = 0;
					}
				}
				if (targetPos2.y != 0)
				{
					if (targetPos2.y > screenCenterY)
					{
						TargetY = -(screenCenterY - targetPos2.y);
						TargetY /= 1;
						if (TargetY + screenCenterY > screenCenterY * 2) TargetY = 0;
					}

					if (targetPos2.y < screenCenterY)
					{
						TargetY = targetPos2.y - screenCenterY;
						TargetY /= 1;
						if (TargetY + screenCenterY < 0) TargetY = 0;
					}
				}
				if (!bSmooth)
				{
					mouse_event(MOUSEEVENTF_MOVE, (UINT)(TargetX), (UINT)(TargetY), NULL, NULL);
					Sleep(1);
					return;
				}
				else
				{
					TargetX /= smooth;
					TargetY /= smooth;
					if (fabs(TargetX) < 1)
					{
						if (TargetX > 0)
						{
							TargetX = 1;
						}
						if (TargetX < 0)
						{
							TargetX = -1;
						}
					}
					if (fabs(TargetY) < 1)
					{
						if (TargetY > 0)
						{
							TargetY = 1;
						}
						if (TargetY < 0)
						{
							TargetY = -1;
						}
					}
					mouse_event(MOUSEEVENTF_MOVE, (UINT)TargetX, (UINT)TargetY, NULL, NULL);
					Sleep(1);
					return;
				}

			}
		
		}


	}
}

void CalcAngle(Vec3 FOV, Vec3 headPos3, Vec2& calcLocalAngle, Vec2& calcLocalAngleDiff)
{
	Vec2 localAngle;
	localAngle.y = mem.ReadMemory<float>(offsets.clientBase + offsets.m_fViewAngle + 0x0);
	localAngle.x = mem.ReadMemory<float>(offsets.clientBase + offsets.m_fViewAngle + 0x4);


	if (headPos3.x >= FOV.x && headPos3.y >= FOV.y)
	{
		calcLocalAngle.x = (float)((double)atan2(headPos3.y - FOV.y, headPos3.x - FOV.x) * 180 / 3.1415);
	}
	if (headPos3.x <= FOV.x && headPos3.y >= FOV.y)
	{
		calcLocalAngle.x = 180 - (float)((double)atan2(headPos3.y - FOV.y, FOV.x - headPos3.x) * 180 / 3.1415);
	}
	if (headPos3.x <= FOV.x && headPos3.y <= FOV.y)
	{
		calcLocalAngle.x = -180 + (float)((double)atan2(FOV.y - headPos3.y, FOV.x - headPos3.x) * 180 / 3.1415);
	}
	if (headPos3.x >= FOV.x && headPos3.y <= FOV.y)
	{
		calcLocalAngle.x = -(float)((double)atan2(FOV.y - headPos3.y, headPos3.x - FOV.x) * 180 / 3.1415);
	}
	float lineDistance = sqrt((headPos3.x - FOV.x) * (headPos3.x - FOV.x) + (headPos3.y - FOV.y) * (headPos3.y - FOV.y));

	if (headPos3.z >= FOV.z)
	{
		calcLocalAngle.y = -(float)((double)atan2(headPos3.z - FOV.z, lineDistance) * 180 / 3.1415);
	}
	if (headPos3.z <= FOV.z)
	{
		calcLocalAngle.y = (float)((double)atan2(FOV.z - headPos3.z, lineDistance) * 180 / 3.1415);
	}

	calcLocalAngleDiff.x = localAngle.x - calcLocalAngle.x;
	if (calcLocalAngleDiff.x > 180) {
		calcLocalAngleDiff.x -= 360;
	}
	if (calcLocalAngleDiff.x < -180) {
		calcLocalAngleDiff.x += 360;
	}

	calcLocalAngleDiff.y = calcLocalAngle.y - localAngle.y;

}
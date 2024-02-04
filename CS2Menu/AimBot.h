#pragma once
#include "Memory.h"
#include "Structures.h"
#include "Draw.h"

void InMemAimBot();
void ExternalAimBot();
void CalcAngle(Vec3 FOV, Vec3 headPos3, Vec2& calcLocalAngle, Vec2& calcLocalAngleDiff);

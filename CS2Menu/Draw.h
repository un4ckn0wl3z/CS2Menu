#pragma once
#include <Windows.h>
#include "Structures.h"
#include "Offsets.h"
#include "Memory.h"

class Draw
{
public:

	HWND hExWnd; // Cheat HWND
	RECT rectGame; // CS2 RECT

	RECT rect;
	int width;
	int height;

	RECT rectEx;
	int widthEx;
	int heightEx;

	void GetWindowInfo();
	BOOL WorldToScreen(Vec3 &worldPos, Vec2 &screenPos);

	void DrawRect(HDC hDC, RECT rect);
	void DrawHP(HDC hDC, HBRUSH bBrush, RECT rect, float hp);
	void DrawLines(HDC hDC, Vec2 headPos2);
	void DrawHPStatus(HDC hDC, COLORREF color, DWORD entityHealth, Vec2 entityPos2);
	void DrawStr(HDC hDC, int x, int y, COLORREF color, const char* text);

	
};

extern Draw draw;


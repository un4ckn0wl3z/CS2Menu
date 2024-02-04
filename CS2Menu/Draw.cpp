#include "Draw.h"

Draw draw;

void Draw::GetWindowInfo()
{
	GetClientRect(offsets.hWnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	GetWindowRect(offsets.hWnd, &rectEx);
	widthEx = rectEx.right - rectEx.left;
	heightEx = rectEx.bottom - rectEx.top;
}

void Draw::DrawRect(HDC hDC, RECT rect)
{
	float width = rect.right - rect.left;
	int length = width / 3;

	MoveToEx(hDC, rect.left, rect.top + length, NULL);
	LineTo(hDC, rect.left, rect.top);
	LineTo(hDC, rect.left + length, rect.top);

	MoveToEx(hDC, rect.right, rect.top + length, NULL);
	LineTo(hDC, rect.right, rect.top);
	LineTo(hDC, rect.right - length, rect.top);

	MoveToEx(hDC, rect.left, rect.bottom - length, NULL);
	LineTo(hDC, rect.left, rect.bottom);
	LineTo(hDC, rect.left + length, rect.bottom);

	MoveToEx(hDC, rect.right, rect.bottom - length, NULL);
	LineTo(hDC, rect.right, rect.bottom);
	LineTo(hDC, rect.right - length, rect.bottom);
}

void Draw::DrawHP(HDC hDC, HBRUSH bBrush, RECT rect, float hp)
{
	int width = 5;
	RECT backgroundRect = {
		rect.left - width, 
		rect.top,
		rect.left - width / 2,
		rect.bottom
	};
	FillRect(hDC, &backgroundRect, bBrush);
	
	HBRUSH bBrush2 = CreateSolidBrush(RGB(57, 253, 5));
	float autoTop = (rect.bottom - rect.top) * ((100 - hp) / 100) + rect.top;

	RECT hpRect = {
	backgroundRect.left,
	autoTop,
	backgroundRect.right,
	backgroundRect.bottom
	};
	FillRect(hDC, &hpRect, bBrush2);
	DeleteObject(bBrush2);

}

void Draw::DrawLines(HDC hDC, Vec2 headPos2)
{
	MoveToEx(hDC, draw.widthEx / 2, 0, NULL);
	LineTo(hDC, headPos2.x, headPos2.y);
}

void Draw::DrawHPStatus(HDC hDC, COLORREF color, DWORD entityHealth, Vec2 entityPos2)
{
	wchar_t buffer[MAXBYTE];
	wsprintf(buffer, L"HP: %d", entityHealth);
	SetTextColor(hDC, color);
	TextOut(hDC, entityPos2.x, entityPos2.y, buffer, 7);
}



BOOL Draw::WorldToScreen(Vec3& worldPos, Vec2& screenPos)
{
	GetWindowInfo();
	float matrix[4][4];
	ReadProcessMemory(offsets.hProcess, (LPVOID)(offsets.clientBase + offsets.dwViewMatrix), matrix, 64, NULL);
	Vec4 clipPos;
	clipPos.x = matrix[0][0] * worldPos.x + matrix[0][1] * worldPos.y + matrix[0][2] * worldPos.z + matrix[0][3];
	clipPos.y = matrix[1][0] * worldPos.x + matrix[1][1] * worldPos.y + matrix[1][2] * worldPos.z + matrix[1][3];
	clipPos.z = matrix[2][0] * worldPos.x + matrix[2][1] * worldPos.y + matrix[2][2] * worldPos.z + matrix[2][3];
	clipPos.w = matrix[3][0] * worldPos.x + matrix[3][1] * worldPos.y + matrix[3][2] * worldPos.z + matrix[3][3];

	if (clipPos.w < 0.01) { return false; }

	Vec3 NDC;

	NDC.x = clipPos.x / clipPos.w;
	NDC.y = clipPos.y / clipPos.w;
	NDC.z = clipPos.z / clipPos.w;

	screenPos.x = width / 2 + (width / 2) * NDC.x;
	screenPos.y = height / 2 - (height / 2) * NDC.y + 30;

	return true;
}



void Draw::DrawStr(HDC hDC, int x, int y, COLORREF color, const char* text)
{
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, color);
	//SelectObject(hDC, hFont);
	TextOutA(hDC, x, y, text, strlen(text));
}
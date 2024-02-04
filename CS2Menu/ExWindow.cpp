#include "ExWindow.h"

/*

*/

void Loop()
{
	COLORREF RED(RGB(255, 0, 0));
	COLORREF GREEN(RGB(57, 253, 5));
	COLORREF WHITE(RGB(255, 255, 255));

	HDC hDC = GetDC(draw.hExWnd);
	HDC dcMem = CreateCompatibleDC(hDC);
	HBITMAP bmpMem = CreateCompatibleBitmap(hDC, draw.rectGame.right - draw.rectGame.left, draw.rectGame.bottom - draw.rectGame.top);

	SelectObject(dcMem, bmpMem);

	HBRUSH hDefaultHealthTabBrush = {0};
	hDefaultHealthTabBrush = CreateSolidBrush(RGB(229, 148, 10));

	HPEN hBoxPen = CreatePen(PS_DASHDOT, 2, RGB(255, 0, 0));
	HPEN hLinePen = CreatePen(PS_DOT, 1, RGB(0, 255, 255));
	HPEN hFovArc = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hCrosshair = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	
	SetBkMode(dcMem, TRANSPARENT);

	HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, NULL);

	SelectObject(dcMem, hFont);


#if 1
	SetTextColor(dcMem, RED);
	wchar_t title_buffer[MAXBYTE];
	wsprintf(title_buffer, L"[ Counter Strike 2 Private Assister v0.0.1 ]");
	TextOut(dcMem, 10, (draw.heightEx / 2), title_buffer, 44);

	SetTextColor(dcMem, GREEN);
	wchar_t logo_buffer[MAXBYTE];
	wsprintf(logo_buffer, L"Research and Development: unknownclub.net");
	TextOut(dcMem, 10, (draw.heightEx / 2) + 20, logo_buffer, 41);

	wchar_t developer_buffer[MAXBYTE];
	wsprintf(developer_buffer, L"Programmer: un4ckn0wl3z");
	TextOut(dcMem, 10, (draw.heightEx / 2) + 40, developer_buffer, 23);
#endif // 1


	DWORD64 localPlayer = mem.ReadMemory<DWORD64>(offsets.clientBase + offsets.dwLocalPlayer);
	DWORD localTeam = mem.ReadMemory<DWORD>(localPlayer + offsets.m_iTeamNum);
	
	if (localTeam)
	{
		for (size_t i = 0; i < 32; i++)
		{
			DWORD64 entity = mem.ReadMemory<DWORD64>(offsets.clientBase + offsets.dwEntityList + i * 0x8);
			if (entity == localPlayer) continue;
			if (entity == 0) continue;

			Vec3 entityPos3 = {0}; // character's world coord
			Vec2 entityPos2 = {0}; // screen coord

			Vec3 entityHeadPos3;
			Vec2 entityHeadPos2;

			Vec3 localPos3;

			entityPos3.x = mem.ReadMemory<float>(entity + offsets.m_fPos + 0x0);
			entityPos3.y = mem.ReadMemory<float>(entity + offsets.m_fPos + 0x4);
			entityPos3.z = mem.ReadMemory<float>(entity + offsets.m_fPos + 0x8);


			localPos3.x = mem.ReadMemory<float>(localPlayer + offsets.m_fPos + 0x0);
			localPos3.y = mem.ReadMemory<float>(localPlayer + offsets.m_fPos + 0x4);
			localPos3.z = mem.ReadMemory<float>(localPlayer + offsets.m_fPos + 0x8);

			entityHeadPos3.x = entityPos3.x;
			entityHeadPos3.y = entityPos3.y;
			entityHeadPos3.z = entityPos3.z + 50.f;

			DWORD teamID = mem.ReadMemory<DWORD>(entity + offsets.m_iTeamNum);
			if (teamID != 3 && teamID != 6) continue;
			
			// if (true) {
			if (config.team or teamID != localTeam) {
				DWORD entityHealth = mem.ReadMemory<DWORD>(entity + offsets.m_iHealth);
				if (0 < entityHealth && entityHealth <= 100 && draw.WorldToScreen(entityPos3, entityPos2))
				{

					if (draw.WorldToScreen(entityHeadPos3, entityHeadPos2))
					{

						int dotSize = 4;
						Rectangle(dcMem, entityHeadPos2.x, entityHeadPos2.y, entityHeadPos2.x + dotSize, entityHeadPos2.y + dotSize);

						float height = entityPos2.y - entityHeadPos2.y;
						float width = height / 2;

						if (config.healthStatus)
						{
							draw.DrawHPStatus(dcMem, WHITE, entityHealth, entityHeadPos2);
						}

						RECT rect;
						rect.left = entityPos2.x - (width / 2);
						rect.top = entityHeadPos2.y;
						rect.right = entityPos2.x + (width / 2);
						rect.bottom = entityPos2.y;

						// FrameRect(dcMem, &rect, hBrush);
						if (config.boxes)
						{
							SelectObject(dcMem, hBoxPen);
							draw.DrawRect(dcMem, rect);
						}

						if (config.healthBar)
						{
							draw.DrawHP(dcMem, hDefaultHealthTabBrush, rect, entityHealth);
						}

						if (config.lines)
						{
							SelectObject(dcMem, hLinePen);
							draw.DrawLines(dcMem, entityHeadPos2);
						}

						if (config.distance) {
							unsigned int distance = (sqrt((localPos3.x - entityPos3.x) * (localPos3.x - entityPos3.x) + (localPos3.y - entityPos3.y) * (localPos3.y - entityPos3.y)
								+ (localPos3.z - entityPos3.z) * (localPos3.z - entityPos3.z))) / 100;
							char tmpStr[255];
							char prefix[] = "[";
							char suffix[] = "m]";
							_itoa_s(distance, tmpStr, 10);
							std::string endStr = prefix + (std::string)tmpStr + suffix;
							draw.DrawStr(dcMem, entityPos2.x - 5, entityPos2.y + 2, distance < 5 ? RED : WHITE, endStr.c_str());

						}

					}

				}
			}
		}

		if (config.aimbot) {
			SelectObject(dcMem, hFovArc);
			int circleRadius = (draw.rectGame.right - draw.rectGame.left) * CONFIG_FOV / 2 / 130;
			int centerX = (draw.rectGame.right - draw.rectGame.left) / 2;
			int centerY = (draw.rectGame.bottom - draw.rectGame.top) / 2 + 15;

			Arc(dcMem,
				centerX - circleRadius, centerY - circleRadius,
				centerX + circleRadius, centerY + circleRadius,
				centerX - circleRadius, centerY,
				centerX - circleRadius, centerY);
		}

		if (config.crosshair) {
			SelectObject(dcMem, hCrosshair);

			int centerXCh = (draw.rectGame.right - draw.rectGame.left);
			int centerYCh = (draw.rectGame.bottom - draw.rectGame.top);

			//	DRAW HORIZONTAL SECTION
			MoveToEx(dcMem, ((centerXCh / 2) - (10 / 2)), (centerYCh / 2) + 15, NULL);
			LineTo(dcMem, ((centerXCh / 2) + (10 / 2)), (centerYCh / 2) + 15);

			//	DRAW VERTICAL SECTION
			MoveToEx(dcMem, (centerXCh / 2), (((centerYCh / 2) + 15) - (10 / 2)), NULL);
			LineTo(dcMem, (centerXCh / 2), (((centerYCh / 2) + 15) + (10 / 2)));
		}





		BitBlt(hDC, 0, 0, draw.rectGame.right - draw.rectGame.left, draw.rectGame.bottom - draw.rectGame.top, dcMem, 0, 0, SRCCOPY);
	}

	DeleteObject(hCrosshair);
	DeleteObject(hBoxPen);
	DeleteObject(hFovArc);
	DeleteObject(hLinePen);
	DeleteObject(hDefaultHealthTabBrush);
	DeleteObject(dcMem);
	DeleteObject(bmpMem);
	DeleteObject(hFont);
	ReleaseDC(draw.hExWnd, hDC);
}


LRESULT CALLBACK Wndproc(HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4)
{
	switch (unnamedParam2)
	{
	case WM_PAINT:
		Loop();
		break;
	case WM_CREATE:
		break;
	case WM_DESTROY:
		DestroyWindow(unnamedParam1);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4);
	}
}


void CreateExternalWindows()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	GetWindowRect(offsets.hWnd, &draw.rectGame);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)Wndproc;

	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)RGB(0, 0, 0);
	wc.lpszClassName = L"ExternalWindow";

	RegisterClassEx(&wc);
	draw.hExWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
		wc.lpszClassName, L"ExWindow", WS_POPUP, 
		draw.rectGame.left, draw.rectGame.top, 
		draw.rectGame.right - draw.rectGame.left, 
		draw.rectGame.bottom - draw.rectGame.top,
		NULL, NULL, wc.hInstance, NULL
		);

	if (draw.hExWnd == NULL)
	{
		return;
	}
	SetLayeredWindowAttributes(draw.hExWnd, RGB(0,0,0), 0, LWA_COLORKEY);
	ShowWindow(draw.hExWnd, SW_SHOW);
	UpdateWindow(draw.hExWnd);

	while (msg.message != WM_QUIT)
	{
		SetWindowPos(draw.hExWnd, HWND_TOPMOST,
			draw.rectGame.left, draw.rectGame.top,
			draw.rectGame.right - draw.rectGame.left,
			draw.rectGame.bottom - draw.rectGame.top,
			SWP_SHOWWINDOW
		);
		GetWindowRect(offsets.hWnd, &draw.rectGame);

		if (PeekMessage(&msg, draw.hExWnd, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

}



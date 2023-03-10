#include <Windows.h>

void lineMidPointAlgorithm(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
	int dx = x2 - x1, dy = y2 - y1;
	int x = x1, y = y1;
	SetPixel(hdc, x1, y1, c);
	int dInitial = 2 * dx - dy;
	int change1 = 2 * dx - 2 * dy;
	int change2 = 2 * dx;
	while (y < y2)
	{
		if (dInitial > 0)
		{
			x++, y++;
			dInitial += change1;
		}
		else
		{
			y++;
			dInitial += change2;
		}
		SetPixel(hdc, x, y, c);

	}
}
LRESULT WINAPI WndProc(HWND hWnd, UINT m, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	static int x, y;
	switch (m)
	{
	case WM_LBUTTONDBLCLK:
		hdc = GetDC(hWnd);
		lineMidPointAlgorithm(hdc, 10, 10, 100, 150, RGB(255, 0, 0));
		ReleaseDC(hWnd, hdc);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return DefWindowProc(hWnd, m, wp, lp);
	}
	return 0;
}
int APIENTRY WinMain(HINSTANCE h, HINSTANCE p, LPSTR cmd, int csh)
{
	WNDCLASS wc;
	wc.lpszClassName = L"MyClass";
	wc.lpszMenuName = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.style = CS_DBLCLKS;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = h;
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(L"MyClass", L"Hello", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, h, 0);
	ShowWindow(hWnd, csh);
	UpdateWindow(hWnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
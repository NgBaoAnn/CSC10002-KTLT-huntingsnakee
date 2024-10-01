#include "Logic.h"
#include "Graphics.h"
#include "WinConsole.h"
#include "Menu.h"
#include "Sound.h"
#include "Global.h"

#define KEY_NONE	-1

// trả về mã phím người dùng bấm
int inputKey()
{
	if (_kbhit()) //true
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}
	return KEY_NONE;
}

// hàm khoá kích thước màn hình
void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

// hàm ẩn thanh kéo scrollbar
void ShowScrollbar(bool Show)
{
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, Show);
}

// hàm lấy toàn màn hình 
void FullScreenConsole()
{
	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_MAXIMIZE);
}

// hàm cài đặt hiển thị của con trỏ chuột
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

// hàm di chuyển con trỏ tới một vị trí trong màn b  hình console
void gotoXY(short x, short y)
{
	COORD coord{ x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// hàm đóng cửa sổ window
void closeWindow()
{
	HWND hwnd = GetForegroundWindow();
	if (hwnd != NULL) {
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

// hàm chặn người chơi thao tác chuột
void DisableSelection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

// hàm đổi font chữ
void SetFont(int fontWidth, int fontHeight, const wchar_t s[])
{
	// Thiết lập kích thước phông chữ lớn hơn
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.nFont = 0;
	fontInfo.dwFontSize.X = fontWidth;
	fontInfo.dwFontSize.Y = fontHeight;
	fontInfo.FontFamily = FF_DONTCARE;
	fontInfo.FontWeight = FW_NORMAL;
	wcscpy_s(fontInfo.FaceName, s); // Sửa đổi thành wcscpy_s

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);
}
#pragma once
#include "Global.h"

// trả về mã phím người dùng bấm
int inputKey();

// hàm khoá kích thước màn hình
void FixConsoleWindow();

// hàm ẩn thanh kéo scrollbar
void ShowScrollbar(bool Show);

// hàm lấy toàn màn hình 
void FullScreenConsole();

// hàm cài đặt hiển thị của con trỏ chuột
void ShowCur(bool CursorVisibility);

// hàm di chuyển con trỏ tới một vị trí trong màn b  hình console
void gotoXY(short x, short y);

// hàm đóng cửa sổ window
void closeWindow();

// hàm chặn người chơi thao tác chuột
void DisableSelection();

// hàm đổi font chữ
void SetFont(int fontWidth, int fontHeight, const wchar_t s[]);



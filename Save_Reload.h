#pragma once
#include "Global.h"

// vẽ bảng reload
void Reload();

// hàm thông báo đã lưu người chơi thành công
void ShowSuccess();

// hàm lưu tên hợp lệ
void inputLimitedString(int maxLength, PLAYER& player);

// tạo hàm pause để dừng màn chơi và thực hiện thao tác save    (còn menu)
void Pause(int x, int y, HANDLE t);

// hàm ghi dữ liệu người chơi ra file
void writeSaveFile();

// hàm tải lại dữ liệu người chơi từ file đã lưu
void loadSaveFile();

// hàm lưu game
void SaveGame();

// hàm kiểm tra tên đã có trước đó
bool UsedName(wstring ten);
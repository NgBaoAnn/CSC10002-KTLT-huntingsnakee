#pragma once
#include "Header.h"
#include "Global.h"
// hàm kiểm tra tình trạng con rắn sống hay chết
bool IsValid(int x, int y);

// hàm lấy toạ độ vật cản từ file
void GetWallCord(const string& file_path, const string& check_flag, vector <Point>& wall);

// hàm tạo đồ ăn
void GenerateFood();

// hàm reset lại dữ liệu
void ResetData();

// hàm bắt đầu 1 level mới
void StartLevel();

// hàm chạy màn chơi
void StartGame();

// hàm ăn đồ ăn lớn
void EatBigFood();

// hàm ăn đồ ăn thường
void Eat();

// hàm xử lí quá trình chết
void ProcessDead();

// hàm xử lí chết trong từng level
void ProcessDeadInLevel();

// hàm xử lí chết khi chuyển level (đụng cổng)
void ProcessDeadInChangeLevel();

// hàm thay đổi level
void ChangeLevel();

// các hàm xử lí con rắn di chuyển
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();

// hàm chạy luồng cho premenu trong màn chơi
void ThreadPreMenu();

// hàm chạy luồng chơi chính cho luồng chơi
void ThreadFunc();

// hàm tạo menu pause game
void PauseGame(HANDLE t);

// hàm thực hiện màn chơi    (còn pause game và menu)
void Play();

#pragma once
#include "Global.h"

// hàm cài đặt màu cho kí tự   // hàm cũ là SetColor
void SetCharacterColor(WORD color);

// hàm cài đặt màu tương phản giữa kí tự và nền      // hàm cũ là setTextColor
void SetBackgroundColor(int color);

// hàm đưa màn hình về khung trắng               // hàm cũ là reset
void CleanBackground(int x, int y, int w, int h);

// hàm đọc file để vẽ 
void printMyFile(const string& file_path, int x, int y, int t_color, const string& check_flag);

// hàm thiết kế và tạo ra Intro của game
void Loading();

// hàm vẽ con rắn
void DrawSnake(int n, int m);

// hàm vẽ đồ ăn
void DrawFood();

// hàm vẽ cổng vào và lưu toạ độ cổng vào
void Gate_Start();

// hàm vẽ cổng ra và lưu toạ độ cổng ra
void Gate_End();

// hàm xoá tường và vật cản
void DeleteWall(vector<Point> wall);

// hàm xoá rắn và đồ ăn
void DeleteSnakeAndFood();

// hàm xoá cổng vào
void Delete_Gate_Start();

// hàm xoá cổng ra
void Delete_Gate_End();

void DrawButton(int x, int y, int w, int h, int color1, int color2);

// hàm vẽ hộp trong màn chơi               // hàm cũ là DrawBoxNoSave
void DrawPlayBox(int x, int y, int w, int h);

// hàm vẽ menu con trong màn chơi
void DrawPreMenu();

// hàm vẽ map level 1 và lưu toạ độ vật cản
void Level_1();

// hàm vẽ map level 2 và lưu toạ độ vật cản
void Level_2();

// hàm vẽ map level 3 và lưu toạ độ vật cản
void Level_3();

// hàm vẽ map level 4 và lưu toạ độ vật cản
void Level_4();

// hàm vẽ map level 5 và lưu toạ độ vật cản
void Level_5();

// hàm vẽ ra map theo level của con rắn
void DrawLevel();

// hàm vẽ hộp có màu cho setting
void DrawColorBox(int x, int y, int w, int h, int s_color, int b_color);

// hàm vẽ con rắn tuỳ chọn màu
void PrintColorSnake(int x, int y, int s_color);

// hàm vẽ hộp 2 đường viền
void Draw2LineBox(int x, int y, int w, int h, int t_color);

// hàm vẽ thanh sáng
void DrawLightBar(int x, int y, int w, int h, int b_color);

// vẽ bên trong phần setting (trong setting gồm chọn màu rắn và tắt nhạc)
void DrawSetting();

// hàm vẽ hộp rỗng
void DrawEmptyBox(int x, int y, int w, int h, int t_color);

// hàm thực hiện phân đoạn load game lúc vào màn chơi
void LoadGame();

// hàm vẽ hộp tên
void DrawNameBox();

// vẽ tay cầm playstation
void DrawController(int x, int y);

// hàm vẽ Introduction trong About
void DrawIntroduction();

// hàm vẽ outro của game
void DrawOutro();

// hàm vẽ gameover
void DrawGameover();




#pragma once
#include "Header.h"
#include "WinConsole.h"

#define LIGHT_RED 200
#define RED 70
#define GREEN 300
#define BLUE 280
#define YELLOW 100
#define BACKGROUND 120
#define PURPLE 13
#define GREY 130
#define WHITE 240

// cấu trúc toạ độ
typedef struct
{
    int x;
    int y;
} Point;


// cấu trúc con rắn
struct  Snake {

    // Chuỗi lưu tọa độ thân rắn
    Point snake[40];

    // Chuỗi lưu tọa độ thức ăn
    Point food[6];

    // Chuỗi lưu tọa độ tường từng màn
    vector <Point> wall;

    // Chuỗi lưu tọa độ cổng
    vector<Point> gate;

    // Chuỗi lưu tọa độ tường từng màn
    // (Tại một thời điểm, có một hướng mà con rắn của tôi không thể di chuyển đến)
    int CHAR_LOCK;

    // được sử dụng để xác định hướng mà con rắn của tôi có thể di chuyển đến 
    // (Tại một thời điểm, có ba hướng mà con rắn của tôi có thể di chuyển đến)
    int MOVING;

    // Đại diện cho cấp độ, càng cao cấp độ, tốc độ càng nhanh
    float SPEED;

    // chỉ số thức ăn hiện tại
    int FOOD_INDEX;

    // kích thước của con rắn, ban đầu có thể là 5 đơn vị và kích thước tối đa có thể là 40
    int SIZE_SNAKE;

    // Trạng thái của con rắn: chết hoặc sống
    int STATE;

    // Bật tắt chế độ tạo đồ ăn
    int STOP_DRAW_FOOD;

    // Chỉ số lưu màn chơi
    int LEVEL;

    // Cờ lưu thời gian xuất hiện big food
    int TIMEBIGFOOD;

    // Cờ lưu tổng điểm
    int SCORE;
    // Cờ lưu màu rắn
    int SNAKE_COLOR;
    Snake() {
        snake[39] = { 0 };
        food[5] = { 0 };
        wall;
        gate;
        CHAR_LOCK = 0;
        MOVING = 0;
        SPEED = 0;
        FOOD_INDEX = 0;
        SIZE_SNAKE = 0;
        STATE = 0;
        STOP_DRAW_FOOD = 0;
        LEVEL = 0;
        TIMEBIGFOOD = 0;
        SCORE = 0;
        SNAKE_COLOR = 0;
    }
};

// lấy tọa độ x của con trỏ hiện tại
#define KEY_NONE	-1

// Chuỗi lưu ký tự thân rắn
extern wstring snake_body;

// Độ rộng và chiều cao của màn hình console
extern int MIN_WIDTH_PB, MAX_WIDTH_PB, MIN_HEIGHT_PB, MAX_HEIGHT_PB;

extern Snake snake_current;

extern int CheckSound;

// cấu trúc người chơi để nhập tên
typedef struct 
{
    wstring ten;
} PLAYER;

extern PLAYER player;

// Cờ kiểm tra thực hiện xong lệnh nhập từ phím
extern int check_input;

extern int check_game_over;

extern int check_reload;

extern int check_color;

extern int see_reload;

struct Save
{
    std::wstring name;
    std::chrono::system_clock::time_point saveTime;
    int sound;
    Snake snak;


    void output(int x, int y) {
        time_t t = chrono::system_clock::to_time_t(saveTime);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &t);
        wstring wstr(buffer, buffer + strlen(buffer));
        wstr.pop_back();
        gotoXY(x + 2, y);  wcout << name;
        gotoXY(x + 31, y); wcout << snak.SCORE;
        gotoXY(x + 59, y); wcout << snak.LEVEL;
        gotoXY(x + 70, y); wcout << &wstr[0] << endl;
    }
};

// dùng để thực hiện save và reload
 extern vector<Save> save;
 extern wifstream fin;

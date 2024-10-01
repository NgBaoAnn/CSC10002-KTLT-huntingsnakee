#include "Global.h"
#include "WinConsole.h"
#include "Graphics.h"
#include "Menu.h"
#include "Sound.h"
#include "Logic.h"
#include "Save_Reload.h"



// hàm cài đặt màu cho kí tự   // hàm cũ là SetColor
void SetCharacterColor(WORD color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

// hàm cài đặt màu tương phản giữa kí tự và nền      // hàm cũ là setTextColor
void SetBackgroundColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// hàm đưa màn hình về khung trắng               // hàm cũ là reset
void CleanBackground(int x, int y, int w, int h) 
{
    for (int iy = y + 1; iy <= y + h - 1; iy++) {
        for (int ix = x + 1; ix <= x + w - 1; ix++) {
            gotoXY(ix, iy); cout << " ";
        }
    }
}

// hàm đọc file để vẽ 
void printMyFile(const string& file_path, int x, int y, int t_color, const string& check_flag)
{
    SetCharacterColor(t_color);
    ifstream file(file_path);
    string line;
    bool print = false;

    while (std::getline(file, line)) {
        if (line == check_flag) {
            print = true;
            continue; // Bỏ qua dòng chứa cờ check
        }

        if (print) {
            if (line == "end") {
                print = false; // Dừng in khi gặp cờ "end"
                break; // Nếu muốn dừng ngay khi gặp "end"
            }
            gotoXY(x, y++);
            cout << line << std::endl;
        }
    }
    file.close();
}

// hàm thiết kế và tạo ra Intro của game
void Loading()
{
    // phát nhạc intro game
    INtroSound();
    // Đổi nền thành màu trắng
    system("color 70");

    // in ra con rắn intro và đổi màu cho nó
    for (int i = 249; i < 253; i++) {

        printMyFile("intro_menu_outro.txt", 58, 14, i, "snakeintro");
        Sleep(1000);
        system("cls");
    }
    Sleep(500);
    system("color 70");
    // in màn hình vào game
    printMyFile("intro_menu_outro.txt", 50, 17, 244, "snakegame");
    gotoXY(76, 32);
    cout << "Loading...\n";
    gotoXY(76, 34);
    for (int i = 1; i <= 50; i++)
    {
        for (int t = 0; t <= 88888888; t++);
        SetBackgroundColor(244);
        cout << "Û";
    }
    Sleep(500);
    gotoXY(70, 36);
    for (int i = 1; i <= 2; ++i)
    {
        Sleep(250);
        gotoXY(70, 36);
        //cout << "                          ";
        Sleep(250);
        gotoXY(90, 36);
        cout << "PRESS SPACE TO BEGIN" << endl;
    }
    char c = 0;  // bấm enter để vào menu game
    while (c != 32) {
        c = _getch();
    }
    system("cls");
    system("color 70");
}

// hàm vẽ con rắn
void DrawSnake(int n, int m) {
    for (int i = n; i < m; i++) {
        if (i == 0) {
            switch (snake_current.SNAKE_COLOR)
            {
            case RED:
                SetBackgroundColor(102);
                break;
            case GREEN:
                SetBackgroundColor(204);
                break;
            case BLUE:
                SetBackgroundColor(136);
                break;
            default:
                SetBackgroundColor(68);
                break;
            }
        }
        else {
            SetBackgroundColor(snake_current.SNAKE_COLOR);
        }
        gotoXY(snake_current.snake[i].x, snake_current.snake[i].y);
        wcout << snake_body[i];
    }
}

// hàm vẽ đồ ăn
void DrawFood()
{
    if (snake_current.TIMEBIGFOOD == 2 && snake_current.FOOD_INDEX != 6)
    {
        SetBackgroundColor(114);
        gotoXY(snake_current.food[snake_current.FOOD_INDEX].x, snake_current.food[snake_current.FOOD_INDEX].y);
        cout << (char)5;
    }
    else if (snake_current.FOOD_INDEX != 6)
    {
        SetBackgroundColor(116);
        gotoXY(snake_current.food[snake_current.FOOD_INDEX].x, snake_current.food[snake_current.FOOD_INDEX].y);
        cout << (char)3;
    }
}

// hàm vẽ cổng vào và lưu toạ độ cổng vào
void Gate_Start()
{
    gotoXY(MIN_WIDTH_PB, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) - 2);
    cout << " ";
    gotoXY(MIN_WIDTH_PB + 1, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) - 1);
    SetBackgroundColor(230);
    cout << char(219);
    cout << char(219);
    gotoXY(MIN_WIDTH_PB + 1, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) - 3);
    cout << char(219);
    cout << char(219);
}

// hàm vẽ cổng ra và lưu toạ độ cổng ra
void Gate_End()
{
    snake_current.gate.resize(0);
    Point cordinate = { 0, 0 };
    gotoXY(MAX_WIDTH_PB, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 18);
    cout << " ";
    gotoXY(MAX_WIDTH_PB - 2, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 19);
    cordinate = { MAX_WIDTH_PB - 2, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 19 };
    snake_current.gate.push_back(cordinate);
    cordinate = { MAX_WIDTH_PB - 1, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 19 };
    snake_current.gate.push_back(cordinate);
    SetBackgroundColor(230);
    cout << char(219);
    cout << char(219);
    gotoXY(MAX_WIDTH_PB - 2, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 17);
    cordinate = { MAX_WIDTH_PB - 2, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 17 };
    snake_current.gate.push_back(cordinate);
    cordinate = { MAX_WIDTH_PB - 1, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 17 };
    snake_current.gate.push_back(cordinate);
    cout << char(219);
    cout << char(219);
}

// hàm xoá tường và vật cản
void DeleteWall(vector<Point> wall)
{
    for (int i = 0; i < wall.size(); ++i)
    {
        gotoXY(wall[i].x, wall[i].y);
        cout << " ";
    }
}

// hàm xoá rắn và đồ ăn
void DeleteSnakeAndFood()
{
    SetBackgroundColor(BACKGROUND);
    gotoXY(snake_current.food[snake_current.FOOD_INDEX].x, snake_current.food[snake_current.FOOD_INDEX].y);
    cout << " ";
    for (int i = 0; i < snake_current.SIZE_SNAKE; i++) {
        gotoXY(snake_current.snake[i].x, snake_current.snake[i].y);
        cout << " ";
    }
}

// hàm xoá cổng vào
void Delete_Gate_Start()
{
    gotoXY(MIN_WIDTH_PB, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) - 2);
    cout << char(219);
    gotoXY(MIN_WIDTH_PB + 1, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) - 3);
    cout << "  ";
    gotoXY(MIN_WIDTH_PB + 1, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) - 1);
    cout << "  ";
}

// hàm xoá cổng ra
void Delete_Gate_End()
{
    gotoXY(MAX_WIDTH_PB, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 18);
    cout << char(219);
    gotoXY(MAX_WIDTH_PB - 2, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 19);
    cout << "  ";
    gotoXY(MAX_WIDTH_PB - 2, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 17);
    cout << "  ";
}

// hàm vẽ nút button
void DrawButton(int x, int y, int w, int h, int color1, int color2) 
{
    SetBackgroundColor(color1);
    CleanBackground(x - 2, y, w + 4, h - 1);
    SetBackgroundColor(0);
    for (int ix = x; ix <= x + w; ix++) {
        gotoXY(ix, y);
        cout << " ";
        gotoXY(ix, y + h);
        cout << " ";
    }
    gotoXY(x - 1, y + 1); cout << " ";
    gotoXY(x - 1, y + h - 1); cout << " ";
    gotoXY(x + w + 1, y + 1); cout << " ";
    gotoXY(x + w + 1, y + h - 1); cout << " ";

    for (int iy = y + 2; iy <= y + h - 2; iy++) {
        gotoXY(x - 2, iy);
        cout << " ";
        gotoXY(x + w + 2, iy);
        cout << " ";
    }
    SetBackgroundColor(color2);
    for (int ix = x; ix <= x + w; ix++) {
        gotoXY(ix, y + h - 1);
        cout << " ";
    }
    gotoXY(x - 1, y + h - 2); cout << " ";
    gotoXY(x + w + 1, y + h - 2); cout << " ";
    SetBackgroundColor(color1);
}

// hàm vẽ hộp trong màn chơi               // hàm cũ là DrawBoxNoSave
void DrawPlayBox(int x, int y, int w, int h) 
{
    int i = 0;
    for (int ix = x; ix <= x + w; ix++) {
        gotoXY(ix, y);
        if (ix % 2 == 0) cout << char(219);
        else cout << char(176);
        gotoXY(ix, y + h);
        if (ix % 2 == 0) cout << char(219);
        else cout << char(176);
    }
    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        if (iy % 2 == 0) cout << char(219);
        else cout << char(176);
        gotoXY(x + w, iy);
        if (iy % 2 == 0) cout << char(219);
        else cout << char(176);
    }
}

// hàm vẽ menu con trong màn chơi
void DrawPreMenu()
{
    for (int iy = 8; iy <= 32; iy++) {
        gotoXY(50, iy);
        cout << char(219);
    }
    DrawPlayBox(52, 8, 15, 24);
    gotoXY(56, 12);
    wcout << "LEVEL: ";
    gotoXY(56, 14);
    wcout << "SCORE: ";
    gotoXY(54, 29);
    wcout << "Press SPACE";
    gotoXY(56, 30);
    wcout << "to Pause";
}

// hàm vẽ map level 1 và lưu toạ độ vật cản
void Level_1()
{
    snake_current.wall.resize(0);
    system("color 70");
    Delete_Gate_Start();
    DrawPreMenu();
    printMyFile("Map.txt", 12, 8, 0, "level1");
}

// hàm vẽ map level 2 và lưu toạ độ vật cản
void Level_2()
{
    snake_current.wall.resize(0);
    system("color 70");
    Delete_Gate_Start();
    DrawPreMenu();
    printMyFile("Map.txt", 12, 8, 0, "level2");
    GetWallCord("MapCordinate.txt", "wall2", snake_current.wall);
}

// hàm vẽ map level 3 và lưu toạ độ vật cản
void Level_3()
{
    snake_current.wall.resize(0);
    system("color 70");
    Delete_Gate_Start();
    DrawPreMenu();
    printMyFile("Map.txt", 12, 8, 0, "level3");
    GetWallCord("MapCordinate.txt", "wall3", snake_current.wall);
}

// hàm vẽ map level 4 và lưu toạ độ vật cản
void Level_4()
{
    snake_current.wall.resize(0);
    system("color 70");
    Delete_Gate_Start();
    DrawPreMenu();
    printMyFile("Map.txt", 12, 8, 0, "level4");
    GetWallCord("MapCordinate.txt", "wall4", snake_current.wall);
}

// hàm vẽ map level 5 và lưu toạ độ vật cản
void Level_5()
{
    snake_current.wall.resize(0);
    Delete_Gate_Start();
    DrawPreMenu();
    printMyFile("Map.txt", 12, 8, 0, "level5");
    GetWallCord("MapCordinate.txt", "wall5", snake_current.wall);
}

// hàm vẽ ra map theo level của con rắn
void DrawLevel()
{
    if (snake_current.LEVEL == 1)
    {
        Level_1();
    }
    else if (snake_current.LEVEL == 2)
    {
        Level_2();
    }
    else if (snake_current.LEVEL == 3)
    {
        Level_3();
    }
    else if (snake_current.LEVEL == 4)
    {
        Level_4();
    }
    else if (snake_current.LEVEL == 5)
    {
        Level_5();
    }
}

// hàm vẽ hộp có màu cho setting
void DrawColorBox(int x, int y, int w, int h, int s_color, int b_color) {
    SetBackgroundColor(b_color);
    CleanBackground(x, y, w, h);
    SetBackgroundColor(s_color);
    CleanBackground(x + 2, y + 1, w - 4, h - 2);
}

// hàm vẽ con rắn tuỳ chọn màu
void PrintColorSnake(int x, int y, int s_color) {
    SetBackgroundColor(s_color);
    printMyFile("intro_menu_outro.txt", x, y, 0, "snake");
    SetCharacterColor(7);
    gotoXY(x + 9, y + 3); cout << "Û";
    gotoXY(x + 17, y + 3); cout << "Û";
    SetBackgroundColor(BACKGROUND);
    gotoXY(x, y); cout << "        ";
    gotoXY(x + 18, y); cout << "            ";
    gotoXY(x, y + 1); cout << "      ";
    gotoXY(x + 20, y + 1); cout << "          ";
    gotoXY(x + 3, y + 1); cout << "   ";
    gotoXY(x, y + 2); cout << "      ";
    gotoXY(x + 22, y + 2); cout << "          ";
    gotoXY(x, y + 3); cout << "    ";
    gotoXY(x + 22, y + 3); cout << "          ";
    gotoXY(x, y + 4); cout << "    ";
    gotoXY(x + 24, y + 4); cout << "        ";
    gotoXY(x, y + 5); cout << "    ";
    gotoXY(x + 24, y + 5); cout << "        ";
    gotoXY(x, y + 6); cout << "      ";
    gotoXY(x + 22, y + 6); cout << "          ";
    gotoXY(x, y + 7); cout << "        ";
    gotoXY(x + 22, y + 7); cout << "          ";
    gotoXY(x, y + 8); cout << "    ";
    gotoXY(x + 24, y + 8); cout << "        ";
    gotoXY(x, y + 9); cout << "  ";
    gotoXY(x + 26, y + 9); cout << "     ";
    gotoXY(x + 28, y + 10); cout << "  ";
    gotoXY(x, y + 13); cout << "  ";
    gotoXY(x, y + 14); cout << "    ";
    gotoXY(x + 28, y + 14); cout << "  ";
    gotoXY(x + 22, y + 14); cout << "    ";
}

// hàm vẽ hộp 2 đường viền
void Draw2LineBox(int x, int y, int w, int h, int t_color) {
    SetCharacterColor(t_color);
    for (int ix = x; ix <= x + w; ix++) {
        gotoXY(ix, y);
        cout << char(205);
        gotoXY(ix, y + h);
        cout << char(205);
    }
    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << char(186);
        gotoXY(x + w, iy);
        cout << char(186);
    }
    gotoXY(x, y);			cout << char(201);
    gotoXY(x + w, y);		cout << char(187);
    gotoXY(x, y + h);		cout << char(200);
    gotoXY(x + w, y + h);	cout << char(188);
}

// hàm vẽ thanh sáng
void DrawLightBar(int x, int y, int w, int h, int b_color) 
{
    SetBackgroundColor(b_color);
    for (int iy = y + 1; iy <= y + h - 1; iy++) {
        for (int ix = x + 1; ix <= x + w - 1; ix++) {
            gotoXY(ix, iy); cout << " ";
        }
    }
}

// vẽ bên trong phần setting (trong setting gồm chọn màu rắn và tắt nhạc)  // hàm cũ là ChooseSnake_Sound
void DrawSetting() 
{
    check_color = 1;
    system("cls");
    printMyFile("Setting.txt", 53, 35, 0, "chooseSound");
    //printMyFile("ChooseSound.txt", 53, 35, 0);
    printMyFile("Setting.txt", 142, 34, 0, "soundOn");
    //printMyFile("SoundOn.txt", 142, 34, 0);
    printMyFile("Setting.txt", 62, 6, 12, "choosenSnakecolor");
    //printMyFile("ChooseColorSnake.txt", 62, 6, 12);
    printMyFile("Setting.txt", 58, 41, 0, "saveSettings");
    //printMyFile("SaveSettings.txt", 58, 41, 0);
    SetBackgroundColor(RED);
    CleanBackground(74, 34, 9, 5);
    CleanBackground(78, 40, 23, 5);
    SetBackgroundColor(LIGHT_RED);
    CleanBackground(73, 33, 9, 5);
    CleanBackground(77, 39, 23, 5);
    printMyFile("Setting.txt", 76, 35, 0, "printN");
    //printMyFile("PrintN.txt", 76, 35, 0);
    printMyFile("Setting.txt", 79, 41, 0, "printEnter");
    //printMyFile("PrintEnter.txt", 79, 41, 0);
    int xcolor = 40, ycolor = 27;
    SetBackgroundColor(BACKGROUND);
    Draw2LineBox(20, 5, 170, 40, PURPLE);
    int check = 1, checkcu = check;
    int checkSound = 1;
    PrintColorSnake(xcolor - 7, ycolor - 15, RED);
    PrintColorSnake(xcolor + 33, ycolor - 15, GREEN);
    PrintColorSnake(xcolor + 73, ycolor - 15, BLUE);
    PrintColorSnake(xcolor + 113, ycolor - 15, YELLOW);
    DrawColorBox(xcolor, ycolor, 12, 5, RED, GREY);
    DrawColorBox(xcolor + 40, ycolor, 12, 5, GREEN, WHITE);
    DrawColorBox(xcolor + 80, ycolor, 12, 5, BLUE, WHITE);
    DrawColorBox(xcolor + 120, ycolor, 12, 5, YELLOW, WHITE);
    bool kt = false;
    while (true) {
        if (kt == true) {
            if (checkcu == 1) {
                DrawColorBox(xcolor, ycolor, 12, 5, RED, WHITE);
                SetBackgroundColor(BACKGROUND);
                printMyFile("Setting.txt", 62, 6, 12, "choosenSnakecolor");
                //printMyFile("ChooseColorSnake.txt", 62, 6, 12);
            }
            else if (checkcu == 2) {
                DrawColorBox(xcolor + 40, ycolor, 12, 5, GREEN, WHITE);
                SetBackgroundColor(BACKGROUND);
                printMyFile("Setting.txt", 62, 6, 2, "choosenSnakecolor");
                //printMyFile("ChooseColorSnake.txt", 62, 6, 2);
            }
            else if (checkcu == 3) {
                DrawColorBox(xcolor + 80, ycolor, 12, 5, BLUE, WHITE);
                SetBackgroundColor(BACKGROUND);
                printMyFile("Setting.txt", 62, 6, 1, "choosenSnakecolor");
                //printMyFile("ChooseColorSnake.txt", 62, 6, 1);
            }
            else {
                DrawColorBox(xcolor + 120, ycolor, 12, 5, YELLOW, WHITE);
                SetBackgroundColor(BACKGROUND);
                printMyFile("Setting.txt", 62, 6, 6, "choosenSnakecolor");
                //printMyFile("ChooseColorSnake.txt", 62, 6, 6);
            }
            if (check == 1) {
                SetBackgroundColor(BACKGROUND);
                printMyFile("Setting.txt", 62, 6, 12, "choosenSnakecolor");
                //printMyFile("ChooseColorSnake.txt", 62, 6, 12);
                DrawColorBox(xcolor, ycolor, 12, 5, RED, GREY);
                SetBackgroundColor(BACKGROUND);
                CleanBackground(xcolor - 8, ycolor - 16, 31, 16);
                Sleep(250);
                PrintColorSnake(xcolor - 7, ycolor - 15, RED);
            }
            else if (check == 2) {
                SetBackgroundColor(BACKGROUND);
                printMyFile("Setting.txt", 62, 6, 2, "choosenSnakecolor");
                //printMyFile("ChooseColorSnake.txt", 62, 6, 2);
                DrawColorBox(xcolor + 40, ycolor, 12, 5, GREEN, GREY);
                SetBackgroundColor(BACKGROUND);
                CleanBackground(xcolor + 32, ycolor - 16, 31, 16);
                Sleep(250);
                PrintColorSnake(xcolor + 33, ycolor - 15, GREEN);
            }
            else if (check == 3) {
                SetBackgroundColor(BACKGROUND);
                printMyFile("Setting.txt", 62, 6, 1, "choosenSnakecolor");
                //printMyFile("ChooseColorSnake.txt", 62, 6, 1);
                DrawColorBox(xcolor + 80, ycolor, 12, 5, BLUE, GREY);
                SetBackgroundColor(BACKGROUND);
                CleanBackground(xcolor + 72, ycolor - 16, 31, 16);
                Sleep(250);
                PrintColorSnake(xcolor + 73, ycolor - 15, BLUE);
            }
            else if (check == 4) {
                SetBackgroundColor(BACKGROUND);
                printMyFile("Setting.txt", 62, 6, 6, "choosenSnakecolor");
                //printMyFile("ChooseColorSnake.txt", 62, 6, 6);
                DrawColorBox(xcolor + 120, ycolor, 12, 5, YELLOW, GREY);
                SetBackgroundColor(BACKGROUND);
                CleanBackground(xcolor + 112, ycolor - 16, 31, 16);
                Sleep(250);
                PrintColorSnake(xcolor + 113, ycolor - 15, YELLOW);
            }
            if (checkSound == 1) {
                CleanBackground(141, 33, 19, 6);
                printMyFile("Setting.txt", 142, 34, 0, "soundOn");
                //printMyFile("SoundOn.txt", 142, 34, 0);
            }
            else if (checkSound == 2) {
                CleanBackground(141, 33, 19, 6);
                printMyFile("Setting.txt", 142, 34, 0, "soundOff");
                //printMyFile("SoundOff.txt", 142, 34, 0);
            }
            kt = false;
        }
        if (_kbhit()) {
            char c = _getch();
            kt = true;
            checkcu = check;
            if (c == -32) {
                c = _getch();
            }
            if (c == 'n' && checkSound == 2) {
                checkSound = 1;
                CheckSound = 1;
            }
            else if (c == 'n') {
                checkSound++;
                CheckSound = 0;
            }
            else if (c == 13) {
                if (CheckSound == 1) EnterBut();
                if (check == 1) {
                    snake_current.SNAKE_COLOR = RED;
                }
                else if (check == 2) {
                    snake_current.SNAKE_COLOR = GREEN;
                }
                else if (check == 3) {
                    snake_current.SNAKE_COLOR = BLUE;
                }
                else {
                    snake_current.SNAKE_COLOR = YELLOW;
                }
                SetBackgroundColor(BACKGROUND);
                system("cls");
                Menu();
            }
            if (c == 'a' && check == 1) {
                check = 4;
            }
            else if (c == 'a') {
                check--;
            }
            else if (c == 'd' && check == 4)
            {
                check = 1;
            }
            else if (c == 'd') {
                check++;
            }
        }
    }
}


// hàm vẽ hộp rỗng    // hàm cũ là box phụ
void DrawEmptyBox(int x, int y, int w, int h, int t_color) {
    SetCharacterColor(t_color);
    for (int ix = x; ix <= x + w; ix++) {
        gotoXY(ix, y);
        cout << char(196);
        gotoXY(ix, y + h);
        cout << char(196);
    }
    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << char(179);
        gotoXY(x + w, iy);
        cout << char(179);
    }
    gotoXY(x, y);			cout << char(218);
    gotoXY(x + w, y);		cout << char(191);
    gotoXY(x, y + h);		cout << char(192);
    gotoXY(x + w, y + h);	cout << char(217);
}

// hàm thực hiện phân đoạn load game
void LoadGame()
{
    SetFont(0, 27, L"Consolas");
    if (CheckSound == 1)
        CountSound();
    ShowCur(0);
    Draw2LineBox(42, 7, 34, 16, 5);
    printMyFile("play_gameover.txt", 55, 13, 13, "number3");
    //number3();
    Sleep(1000);
    system("cls");
    Draw2LineBox(42, 7, 34, 16, 5);
    printMyFile("play_gameover.txt", 55, 13, 13, "number2");
    //number2();
    Sleep(1000);
    system("cls");
    Draw2LineBox(42, 7, 34, 16, 5);
    printMyFile("play_gameover.txt", 57, 13, 13, "number1");
    //number1();
    Sleep(1000);
    system("cls");
}

// hàm vẽ hộp tên
void DrawNameBox()
{
    SetFont(20, 20, L"Terminal");
    ShowCur(1);
    Draw2LineBox(20, 17, 24, 5, 0);
    gotoXY(25, 18);
    cout << "Enter your name";
    DrawEmptyBox(21, 19, 22, 2, 4);
    DrawLightBar(20, 18, 24, 4, 0);
    SetCharacterColor(14);
    gotoXY(24, 20);
}

// vẽ tay cầm playstation
void DrawController(int x, int y) {
    printMyFile("intro_menu_outro.txt", x, y, 0, "controller");
    SetCharacterColor(2);
    gotoXY(x + 8, y + 3); cout << "ÛÛÛÛ";
    gotoXY(x + 8, y + 4); cout << "ÛÛÛÛ";
    gotoXY(x + 4, y + 5); cout << "ÛÛÛÛÛÛÛÛÛÛÛÛ";
    gotoXY(x + 4, y + 6); cout << "ÛÛÛÛÛÛÛÛÛÛÛÛ";
    gotoXY(x + 8, y + 7); cout << "ÛÛÛÛ";
    gotoXY(x + 8, y + 8); cout << "ÛÛÛÛ";
    SetCharacterColor(6);
    gotoXY(x + 31, y + 3); cout << "ÛÛÛÛÛ";
    gotoXY(x + 31, y + 4); cout << "ÛÛÛÛÛ";
    SetCharacterColor(4);
    gotoXY(x + 38, y + 4); cout << "ÛÛÛÛÛ";
    gotoXY(x + 38, y + 5); cout << "ÛÛÛÛÛ";
    SetCharacterColor(1);
    gotoXY(x + 30, y + 6); cout << "ÛÛÛÛÛ";
    gotoXY(x + 30, y + 7); cout << "ÛÛÛÛÛ";
    SetCharacterColor(2);
    gotoXY(x + 37, y + 7); cout << "ÛÛÛÛÛ";
    gotoXY(x + 37, y + 8); cout << "ÛÛÛÛÛ";
}

// hàm vẽ Introduction trong About
void DrawIntroduction()
{
    system("color 70");
    ShowCur(0);
    printMyFile("About.txt", 37, 8, 4, "team5");
    printMyFile("About.txt", 105, 8, 4, "howtoplay");
    Draw2LineBox(20, 15, 80, 28, 9);
    Draw2LineBox(108, 15, 80, 28, 9);
    SetCharacterColor(0);
    gotoXY(55, 18);
    cout << "Members";
    gotoXY(44, 21);
    cout << "Hoang Quoc Viet" << "\t" << "23120189";
    gotoXY(44, 24);
    cout << "Nguyen Le The Vinh" << "\t" << "23120190";
    gotoXY(44, 27);
    cout << "Pham Quang Vinh" << "\t" << "23120202";
    gotoXY(44, 30);
    cout << "Nguyen Bao An         23120207";
    gotoXY(44, 33);
    cout << "Duong Tuan Anh" << "\t" << "23120208";
    gotoXY(135, 18);
    cout << "Control your snake by A   D";
    gotoXY(159, 17);
    cout << "W";
    gotoXY(159, 19);
    cout << "S";
    gotoXY(135, 22);
    cout << "Avoid hitting walls";
    gotoXY(135, 25);
    cout << "Avoid hitting yourself";
    gotoXY(135, 28);
    cout << "Try to eat enough food to";
    gotoXY(146, 29);
    cout << "pass each level";
    gotoXY(135, 31);
    cout << "Press Space to pause the game";
    gotoXY(132, 34); SetCharacterColor(21);
    cout << "FROM GROUP 5 HCMUS - 23CTT3 (^^)>3 ";
    gotoXY(135, 38); SetCharacterColor(0);
    cout << "PRESS ENTER TO RETURN MENU";
    gotoXY(25, 40); SetCharacterColor(17);
    cout << "*-----------------------GROUP 5 WITH LOVE---------------------------*";
}

// hàm vẽ outro của game
void DrawOutro() 
{
    int check = 1;
    if (CheckSound == 1)
        ExitSound();
    printMyFile("intro_menu_outro", 69, 3, 0, "thank");
    Draw2LineBox(65, 17, 80, 27, 3);
    SetCharacterColor(0);
    gotoXY(87, 19);
    cout << "DO AN CUOI KI MON KI THUAT LAP TRINH";
    gotoXY(89, 20);
    cout << "TRUONG DAI HOC KHOA HOC TU NHIEN";
    gotoXY(83, 22);
    cout << "Giao vien huong dan: ";
    gotoXY(100, 23);
    cout << "Truong Toan Thinh";
    gotoXY(83, 25);
    cout << "Lop:";
    gotoXY(100, 26);
    cout << "23CTT3";
    gotoXY(83, 27);
    cout << "Nhom:";
    gotoXY(100, 28);
    cout << "5";
    gotoXY(83, 29);
    cout << "Thanh vien:";
    gotoXY(100, 30);
    cout << "Nguyen Bao An (C)";
    gotoXY(100, 31);
    cout << "Nguyen Le The Vinh";
    gotoXY(100, 32);
    cout << "Pham Quang Vinh";
    gotoXY(100, 33);
    cout << "Duong Tuan Anh";
    gotoXY(100, 34);
    cout << "Hoang Quoc Viet";
    printMyFile("intro_menu_outro.txt", 89, 37, 6, "bye");
    gotoXY(92, 40);
    cout << "PRESS ESC TO CLOSE GAME";
    for (int i = 1; i < 50; i++) {

        printMyFile("intro_menu_outro.txt", 54, 9, i, "snakegame");
        Sleep(100);
        if (_getch() == 27) {
            check = 0;
            break;
        }
    }
    while (check) {
        if (_getch() == 27) {
            closeWindow();
        }
    }
    writeSaveFile();
    closeWindow();
}

// hàm vẽ gameover
void DrawGameover() 
{
    system("cls");
    SetFont(0, 16, L"Consolas");
    system("color 70");
    for (int i = 290; i < 297; ++i)
    {
        Sleep(250);
        printMyFile("play_gameover.txt", 20, 13, i, "gameover");
    }
    check_game_over = 1;
}

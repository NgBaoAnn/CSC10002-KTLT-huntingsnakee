#include "Global.h"
#include "Graphics.h"
#include "WinConsole.h"
#include "Logic.h"
#include "Sound.h"
#include "Menu.h"
#include "Save_Reload.h"
Snake snake_current;
wstring snake_body = L"2312019023120189231202022312020723120208";
int check_input = 0;
int check_game_over = 0;
int check_reload = 1;
int check_color = 0;
int MIN_WIDTH_PB = 12, MAX_WIDTH_PB = 48, MIN_HEIGHT_PB = 8, MAX_HEIGHT_PB = 32;

// hàm kiểm tra tình trạng con rắn sống hay chết
bool IsValid(int x, int y)
{
    size_t n = snake_current.wall.size();
    for (int i = 0; i < snake_current.SIZE_SNAKE; ++i)
        if (snake_current.snake[i].x == x && snake_current.snake[i].y == y)
            return false;
    for (int i = 0; i < n; ++i)
    {
        if (snake_current.wall[i].x == x && snake_current.wall[i].y == y)
            return false;
    }
    return true;
}

// hàm lấy toạ độ vật cản từ file
void GetWallCord(const string& file_path, const string& check_flag, vector <Point>& wall)
{
    ifstream file(file_path);
    string line;
    bool check = false;

    while (getline(file, line)) {
        if (line == check_flag) {
            check = true;
            continue;   // bỏ qua dòng chứa cờ check
        }
        if (check) {
            if (line == "end") {
                check = false;
                break;
            }
            stringstream ss(line);
            Point cord = { 0, 0 };
            while (ss >> cord.x >> cord.y) {
                wall.push_back(cord);
            }
        }
    }
    file.close();
}

// hàm tạo đồ ăn
void GenerateFood() 
{
    int x, y;
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < 6; i++) {
        do {
            x = rand() % ((MAX_WIDTH_PB - 1) - (MIN_WIDTH_PB + 1)) + MIN_WIDTH_PB + 1;
            y = rand() % ((MAX_HEIGHT_PB - 1) - (MIN_HEIGHT_PB + 1)) + MIN_HEIGHT_PB + 1;
        } while (IsValid(x, y) == false);
        snake_current.food[i] = { x,y };
    }
}

// hàm reset lại dữ liệu
void ResetData() 
{
    // Khởi tạo các biến cục bộ
    snake_current.CHAR_LOCK = 'A', snake_current.MOVING = 'D', snake_current.SPEED = 1;
    snake_current.FOOD_INDEX = 0, snake_current.SIZE_SNAKE = 4, snake_current.LEVEL = 1;
    snake_current.snake[0] = { MIN_WIDTH_PB + 1, (MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2 };
    snake_current.TIMEBIGFOOD = 0;
    snake_current.SCORE = 0;
    if (check_color == 0)
        snake_current.SNAKE_COLOR = 300;
}

// hàm bắt đầu 1 level mới
void StartLevel()
{
    Gate_Start();
    snake_current.snake[0] = { MIN_WIDTH_PB + 1, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) - 2 };
    int add_body = 2;
    while (add_body < snake_current.SIZE_SNAKE)
    {
        DeleteSnakeAndFood();
        for (int i = add_body - 2; i >= 0; --i)
        {
            snake_current.snake[i + 1].x = snake_current.snake[i].x;
            snake_current.snake[i + 1].y = snake_current.snake[i].y;
        }
        add_body++;
        snake_current.snake[0].x++;
        SetBackgroundColor(snake_current.SNAKE_COLOR - add_body);
        for (int j = 0; j < add_body - 1; j++) {
            gotoXY(snake_current.snake[j].x, snake_current.snake[j].y);
            wcout << snake_body[j];
        }
        Sleep(100);
    }
    DrawLevel();
    GenerateFood();
    snake_current.STOP_DRAW_FOOD = 0;
}

// hàm chạy màn chơi
void StartGame() {
    system("cls");
    if (check_reload)
    {
        ResetData(); // Khởi tạo dữ liệu ban 
        Level_1();
        StartLevel();
    }
    else {
        check_reload = 1;
        system("cls");
        LoadGame();
        SetFont(20, 20, L"Terminal");
        DrawLevel();
        if (snake_current.FOOD_INDEX == 6)
            Gate_End();
    }
    snake_current.STATE = 1;// Bắt đầu chạy luồng
}

// hàm ăn đồ ăn lớn
void EatBigFood()
{
    snake_current.FOOD_INDEX += 2;
    snake_current.SIZE_SNAKE += 2;
    if (snake_current.MOVING == 'D')
    {
        int pos = 1;
        snake_current.snake[snake_current.SIZE_SNAKE - 1].x = snake_current.food[snake_current.FOOD_INDEX].x;
        snake_current.snake[snake_current.SIZE_SNAKE - 1].y = snake_current.food[snake_current.FOOD_INDEX].y;
        for (int i = 0; i >= 0; --i)
        {
            snake_current.snake[snake_current.SIZE_SNAKE - i].x = snake_current.food[snake_current.FOOD_INDEX].x + pos++;
            snake_current.snake[snake_current.SIZE_SNAKE - i].y = snake_current.food[snake_current.FOOD_INDEX].y;
        }
    }
    if (snake_current.MOVING == 'A')
    {
        int pos = 1;
        snake_current.snake[snake_current.SIZE_SNAKE - 1].x = snake_current.food[snake_current.FOOD_INDEX].x;
        snake_current.snake[snake_current.SIZE_SNAKE - 1].y = snake_current.food[snake_current.FOOD_INDEX].y;
        for (int i = 0; i >= 0; --i)
        {
            snake_current.snake[snake_current.SIZE_SNAKE - i].x = snake_current.food[snake_current.FOOD_INDEX].x - pos++;
            snake_current.snake[snake_current.SIZE_SNAKE - i].y = snake_current.food[snake_current.FOOD_INDEX].y;
        }
    }
    if (snake_current.MOVING == 'S')
    {
        int pos = 1;
        snake_current.snake[snake_current.SIZE_SNAKE - 1].x = snake_current.food[snake_current.FOOD_INDEX].x;
        snake_current.snake[snake_current.SIZE_SNAKE - 1].y = snake_current.food[snake_current.FOOD_INDEX].y;
        for (int i = 0; i >= 0; --i)
        {
            snake_current.snake[snake_current.SIZE_SNAKE - i].x = snake_current.food[snake_current.FOOD_INDEX].x;
            snake_current.snake[snake_current.SIZE_SNAKE - i].y = snake_current.food[snake_current.FOOD_INDEX].y + pos++;
        }
    }
    if (snake_current.MOVING == 'W')
    {
        int pos = 1;
        snake_current.snake[snake_current.SIZE_SNAKE - 1].x = snake_current.food[snake_current.FOOD_INDEX].x;
        snake_current.snake[snake_current.SIZE_SNAKE - 1].y = snake_current.food[snake_current.FOOD_INDEX].y;
        for (int i = 0; i >= 0; --i)
        {
            snake_current.snake[snake_current.SIZE_SNAKE - i].x = snake_current.food[snake_current.FOOD_INDEX].x;
            snake_current.snake[snake_current.SIZE_SNAKE - i].y = snake_current.food[snake_current.FOOD_INDEX].y - pos++;
        }
    }
}

// hàm ăn đồ ăn thường
void Eat() 
{
    if (snake_current.TIMEBIGFOOD == 2)
    {
        if (CheckSound == 1)
            eatBfood();
        EatBigFood();
        snake_current.TIMEBIGFOOD = 0;
        snake_current.SCORE += 2;
    }
    else
    {
        if (CheckSound == 1)
            EatSound();
        snake_current.SCORE++;
        snake_current.FOOD_INDEX++;
        snake_current.SIZE_SNAKE++;
        snake_current.snake[snake_current.SIZE_SNAKE].x = snake_current.food[snake_current.FOOD_INDEX].x;
        snake_current.snake[snake_current.SIZE_SNAKE].y = snake_current.food[snake_current.FOOD_INDEX].y;
        snake_current.TIMEBIGFOOD++;
    }
}

// hàm xử lí quá trình chết
void ProcessDead() 
{
    snake_current.STATE = 0;
    if (CheckSound == 1)
        gameOver();
}

// hàm xử lí chết trong từng level
void ProcessDeadInLevel()
{
    size_t n = snake_current.wall.size();
    for (int i = 0; i < n; ++i)
    {
        if (snake_current.MOVING == 'D')
        {
            if (snake_current.snake[0].x + 1 == snake_current.wall[i].x && snake_current.snake[0].y == snake_current.wall[i].y)
                ProcessDead();
        }
        else if (snake_current.MOVING == 'S')
        {
            if (snake_current.snake[0].x == snake_current.wall[i].x && snake_current.snake[0].y + 1 == snake_current.wall[i].y)
                ProcessDead();
        }
        else if (snake_current.MOVING == 'W')
        {
            if (snake_current.snake[0].x == snake_current.wall[i].x && snake_current.snake[0].y - 1 == snake_current.wall[i].y)
                ProcessDead();
        }
        else
        {
            if (snake_current.snake[0].x - 1 == snake_current.wall[i].x && snake_current.snake[0].y == snake_current.wall[i].y)
                ProcessDead();

        }
    }
}

// hàm xử lí chết khi chuyển level (đụng cổng)
void ProcessDeadInChangeLevel()
{
    size_t n = snake_current.gate.size();
    for (int i = 0; i < n; ++i)
    {
        if (snake_current.MOVING == 'D')
        {
            if (snake_current.snake[0].x + 1 == snake_current.gate[i].x && snake_current.snake[0].y == snake_current.gate[i].y)
                ProcessDead();
        }
        else if (snake_current.MOVING == 'S')
        {
            if (snake_current.snake[0].x == snake_current.gate[i].x && snake_current.snake[0].y + 1 == snake_current.gate[i].y)
                ProcessDead();
        }
        else if (snake_current.MOVING == 'W')
        {
            if (snake_current.snake[0].x == snake_current.gate[i].x && snake_current.snake[0].y - 1 == snake_current.gate[i].y)
                ProcessDead();
        }
        else
        {
            if (snake_current.snake[0].x - 1 == snake_current.gate[i].x && snake_current.snake[0].y == snake_current.gate[i].y)
                ProcessDead();

        }
    }
}

// hàm thay đổi level
void ChangeLevel()
{
    snake_current.LEVEL += 1;
    int i = 0;
    int delete_body = 0;
    int head = 0;
    while (delete_body < snake_current.SIZE_SNAKE)
    {
        SetBackgroundColor(0);
        gotoXY(MAX_WIDTH_PB, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 17);
        cout << char(219);
        DeleteSnakeAndFood();
        SetBackgroundColor(i);
        for (i = snake_current.SIZE_SNAKE - 2; i >= delete_body; --i) {
            snake_current.snake[i + 1].x = snake_current.snake[i].x;
            snake_current.snake[i + 1].y = snake_current.snake[i].y;
        }
        snake_current.snake[head++] = { MIN_WIDTH_PB + 1, ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) - 2 };
        delete_body++;
        SetBackgroundColor(snake_current.SNAKE_COLOR + i);
        for (int j = delete_body; j < snake_current.SIZE_SNAKE; j++) {
            gotoXY(snake_current.snake[j].x, snake_current.snake[j].y);
            wcout << snake_body[j];
        }
        Sleep(100);
    }
    if (CheckSound == 1)
        PassLevel();
    DeleteWall(snake_current.wall);
    if (snake_current.LEVEL > 5)
    {
        snake_current.LEVEL = 1;
        snake_current.SPEED++;
    }
    DrawLevel();
    Delete_Gate_End();
    snake_current.FOOD_INDEX = 0;
    snake_current.TIMEBIGFOOD = 0;
}

// các hàm xử lí con rắn di chuyển
void MoveRight() {
    if (snake_current.FOOD_INDEX == 6)
    {
        snake_current.STOP_DRAW_FOOD = 1;
        Gate_End();
    }

    bool check_body = true;
    for (int i = snake_current.SIZE_SNAKE - 1; i >= 1; --i)
    {
        if (snake_current.snake[i].x == snake_current.snake[0].x + 1 && snake_current.snake[i].y == snake_current.snake[0].y)
            check_body = false;
    }
    if (check_body == false)
        ProcessDead();
    ProcessDeadInLevel();
    if (snake_current.STOP_DRAW_FOOD)
        ProcessDeadInChangeLevel();
    if (snake_current.snake[0].x + 1 == MAX_WIDTH_PB && snake_current.snake[0].y == ((MAX_HEIGHT_PB - MIN_HEIGHT_PB) / 2) + 18 && snake_current.STOP_DRAW_FOOD)
    {
        ChangeLevel();
        StartLevel();
        snake_current.SPEED += 0.5;
        snake_current.STOP_DRAW_FOOD = 0;
    }
    else if (snake_current.snake[0].x + 1 == MAX_WIDTH_PB)
        ProcessDead();
    else {
        if (snake_current.snake[0].x + 1 == snake_current.food[snake_current.FOOD_INDEX].x && snake_current.snake[0].y == snake_current.food[snake_current.FOOD_INDEX].y && !snake_current.STOP_DRAW_FOOD) {
            Eat();

        }
        for (int i = snake_current.SIZE_SNAKE - 2; i >= 0; --i) {
            snake_current.snake[i + 1].x = snake_current.snake[i].x;
            snake_current.snake[i + 1].y = snake_current.snake[i].y;
        }
        snake_current.snake[0].x++;
    }
}
void MoveLeft() {
    if (snake_current.FOOD_INDEX % 6 == 0 && snake_current.FOOD_INDEX > 5)
    {
        snake_current.STOP_DRAW_FOOD = 1;
        Gate_End();
    }
    bool check_body = true;
    for (int i = snake_current.SIZE_SNAKE - 1; i >= 1; --i)
    {
        if (snake_current.snake[i].x == snake_current.snake[0].x - 1 && snake_current.snake[i].y == snake_current.snake[0].y)
            check_body = false;
    }
    if (check_body == false)
        ProcessDead();
    ProcessDeadInLevel();
    if (snake_current.STOP_DRAW_FOOD)
        ProcessDeadInChangeLevel();
    if (snake_current.snake[0].x - 1 == MIN_WIDTH_PB) {
        ProcessDead();
    }
    else {
        if (snake_current.snake[0].x - 1 == snake_current.food[snake_current.FOOD_INDEX].x && snake_current.snake[0].y == snake_current.food[snake_current.FOOD_INDEX].y && !snake_current.STOP_DRAW_FOOD)
        {
            Eat();

        }
        for (int i = snake_current.SIZE_SNAKE - 2; i >= 0; --i) {
            snake_current.snake[i + 1].x = snake_current.snake[i].x;
            snake_current.snake[i + 1].y = snake_current.snake[i].y;
        }
        snake_current.snake[0].x--;
    }
}
void MoveDown() {
    if (snake_current.FOOD_INDEX == 6)
    {
        snake_current.STOP_DRAW_FOOD = 1;
        Gate_End();
    }
    bool check_body = true;
    for (int i = snake_current.SIZE_SNAKE - 1; i >= 1; --i)
    {
        if (snake_current.snake[i].x == snake_current.snake[0].x && snake_current.snake[i].y == snake_current.snake[0].y + 1)
            check_body = false;
    }
    if (check_body == false)
        ProcessDead();
    if (snake_current.STOP_DRAW_FOOD)
        ProcessDeadInChangeLevel();
    ProcessDeadInLevel();
    if (snake_current.snake[0].y + 1 == MAX_HEIGHT_PB) {
        ProcessDead();
    }
    else {
        if (snake_current.snake[0].x == snake_current.food[snake_current.FOOD_INDEX].x && snake_current.snake[0].y + 1 == snake_current.food[snake_current.FOOD_INDEX].y && !snake_current.STOP_DRAW_FOOD)
        {
            Eat();
        }
        for (int i = snake_current.SIZE_SNAKE - 2; i >= 0; --i) {
            snake_current.snake[i + 1].x = snake_current.snake[i].x;
            snake_current.snake[i + 1].y = snake_current.snake[i].y;
        }
        snake_current.snake[0].y++;
    }
}
void MoveUp() {
    if (snake_current.FOOD_INDEX == 6)
    {
        snake_current.STOP_DRAW_FOOD = 1;
        Gate_End();
    }
    bool check_body = true;
    for (int i = snake_current.SIZE_SNAKE - 1; i >= 1; --i)
    {
        if (snake_current.snake[i].x == snake_current.snake[0].x && snake_current.snake[i].y == snake_current.snake[0].y - 1)
            check_body = false;
    }
    if (check_body == false)
        ProcessDead();
    if (snake_current.STOP_DRAW_FOOD)
        ProcessDeadInChangeLevel();
    ProcessDeadInLevel();
    if (snake_current.snake[0].y - 1 == MIN_HEIGHT_PB) {
        ProcessDead();
    }
    else {
        if (snake_current.snake[0].x == snake_current.food[snake_current.FOOD_INDEX].x && snake_current.snake[0].y - 1 == snake_current.food[snake_current.FOOD_INDEX].y && !snake_current.STOP_DRAW_FOOD)
        {
            Eat();
        }
        for (int i = snake_current.SIZE_SNAKE - 2; i >= 0; --i) {
            snake_current.snake[i + 1].x = snake_current.snake[i].x;
            snake_current.snake[i + 1].y = snake_current.snake[i].y;
        }
        snake_current.snake[0].y--;
    }
}

// hàm chạy luồng cho premenu trong màn chơi
void ThreadPreMenu()
{
    SetBackgroundColor(112);
    gotoXY(63, 12);
    cout << snake_current.LEVEL;
    gotoXY(63, 14);
    cout << snake_current.SCORE;

    SetBackgroundColor(32);
    int n = 28 - 2 * snake_current.FOOD_INDEX;
    for (int i = 0; i < snake_current.FOOD_INDEX * 2; ++i)
    {
        gotoXY(56, n++);
        for (int j = 0; j < 8; ++j)
            wcout << " ";
    }
}

// hàm chạy luồng chơi chính cho luồng chơi
void ThreadFunc() 
{
    while (snake_current.STATE == 1) {
        HWND console = GetConsoleWindow();
        ShowCur(false);
        if (snake_current.STATE == 1) { // Nếu rắn còn sống
            DeleteSnakeAndFood();
            switch (snake_current.MOVING) {
            case 'A':
                MoveLeft();
                check_input = 0;
                break;
            case 'D':
                MoveRight();
                check_input = 0;
                break;
            case 'W':
                MoveUp();
                check_input = 0;
                break;
            case 'S':
                MoveDown();
                check_input = 0;
                break;
            }
            DrawSnake(0, snake_current.SIZE_SNAKE);
            ThreadPreMenu();
            if (snake_current.STOP_DRAW_FOOD == 0)
                DrawFood();
            Sleep(100.0 / snake_current.SPEED); // Hàm điều chỉnh tốc độ khung 
        }
    }
    if (snake_current.STATE == 0)
    {
        SetBackgroundColor(120);
        system("cls");
        if (CheckSound == 1) gameOver();
        DrawGameover();
    }
}

// hàm tạo menu pause game
void PauseGame(HANDLE t) 
{
    SuspendThread(t);
    DrawPlayBox(52, 8, 15, 24);
    gotoXY(56, 12);
    wcout << "       ";
    gotoXY(56, 14);
    wcout << "       ";
    gotoXY(54, 29);
    wcout << "           ";
    gotoXY(56, 30);
    wcout << "           ";
    Pause(56, 12, t);
}

// hàm thực hiện màn chơi    (còn pause game và menu)
void Play()
{
    int temp;
    StartGame();
    thread t1(ThreadFunc);
    HANDLE handle_t1 = t1.native_handle();
    while (1) {
        temp = toupper(_getch());
        if (snake_current.STATE == 1) {
            if (temp == 32) {
                PauseGame(handle_t1);
            }
            else if (temp == 27) {
                closeWindow();
            }
            else {
                ResumeThread(handle_t1);
                if ((temp != snake_current.CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S') && check_input == 0) {
                    if (temp == 'D') {
                        snake_current.CHAR_LOCK = 'A';
                        check_input = 1;
                    }
                    else if (temp == 'W') {
                        snake_current.CHAR_LOCK = 'S';
                        check_input = 1;
                    }
                    else if (temp == 'S') {
                        snake_current.CHAR_LOCK = 'W';
                        check_input = 1;
                    }
                    else {
                        snake_current.CHAR_LOCK = 'D';
                        check_input = 1;
                    }
                    snake_current.MOVING = temp;
                }
            }
        }
        else
        {
            if (temp == 13 && check_game_over) {
                check_game_over = 0;
                system("cls");
                SetFont(20, 20, L"Terminal");
                DrawSnake(0, snake_current.SIZE_SNAKE);
                DrawFood();
                DrawLevel();
                PauseGame(handle_t1);
                Play();
            }
            else if (temp == 32 && check_game_over)
            {
                check_game_over = 0;
                system("cls");
                Menu();
            }
        }
    }
}
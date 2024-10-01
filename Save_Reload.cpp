#include "Global.h"
#include "WinConsole.h"
#include "Graphics.h"
#include "Menu.h"
#include "Sound.h"
#include "Logic.h"
#include "Save_Reload.h"

int see_reload;
PLAYER player;
vector<Save> save;
wifstream fin;

// hàm thông báo đã lưu người chơi thành công
void ShowSuccess() 
{
    ShowCur(0);
    system("color 70");
    gotoXY(35, 18);
    SetCharacterColor(0);
    cout << "SUCCESS!!";
    gotoXY(26, 34);
    cout << "PRESS ANYKEY TO PLAY CONTINUE";
    if (_getch()) {
        if (CheckSound == 1) EnterBut();
        system("cls");
        system("color 70");
    }
}

// hàm lưu tên hợp lệ
void inputLimitedString(int maxLength, PLAYER& player) 
{
    if (see_reload == 1) return;
    DrawNameBox();

    while (true) {

        getline(wcin, player.ten);
        if (CheckSound == 1)
            EnterBut();
        // Kiểm tra xem chuỗi có vượt quá giới hạn không

        if (player.ten.length() > maxLength || player.ten.length() == 0) {
            player.ten.clear();
            SetBackgroundColor(120);
            gotoXY(24, 25);
            SetCharacterColor(0);
            cout << "NAME IS TOO LONG OR EMTY";
            DrawNameBox();
            continue;
        }
        else if (UsedName(player.ten)) {
            player.ten.clear();
            SetBackgroundColor(120);
            gotoXY(24, 25);
            SetCharacterColor(0);
            cout << "NAME WAS USED           ";
            DrawNameBox();
            continue;

        }
        else {
            break;
        }
    }
}

// hàm kiểm tra tên đã có trước đó
bool UsedName(wstring ten)
{
    for (int i = 0; i < save.size(); i++)
    {
        if (save[i].name == ten) {
            return true;
        }
    }
    return false;
}




// tạo hàm pause để dừng màn chơi và thực hiện thao tác save    (còn menu)
void Pause(int x, int y, HANDLE t) 
{
    int check = 1, checkcu = check;
    system("color 70");
    DrawButton(x, y, 7, 4, 190, 60);
    SetCharacterColor(0);
    gotoXY(x + 1, y + 2); wcout << "RESUME";
    DrawButton(x, y + 6, 7, 4, 230, 100);
    SetCharacterColor(0);
    gotoXY(x + 2, y + 8);  wcout << "SAVE";
    DrawButton(x, y + 12, 7, 4, 230, 100);
    SetCharacterColor(0);
    gotoXY(x + 2, y + 14); wcout << "MENU";
    SetBackgroundColor(snake_current.SNAKE_COLOR);
    DrawSnake(0, snake_current.SIZE_SNAKE);
    SetBackgroundColor(64);
    DrawFood();
    bool kt = false;
    while (true) {
        if (kt == true) {
            if (checkcu == 1) {
                DrawButton(x, y, 7, 4, 230, 100);
                SetCharacterColor(0);
                gotoXY(x + 1, y + 2); wcout << "RESUME";
            }
            else if (checkcu == 2) {
                DrawButton(x, y + 6, 7, 4, 230, 100);
                SetCharacterColor(0);
                gotoXY(x + 2, y + 8); wcout << "SAVE";
            }
            else if (checkcu == 3) {
                DrawButton(x, y + 12, 7, 4, 230, 100);
                SetCharacterColor(0);
                gotoXY(x + 2, y + 14); wcout << "MENU";
            }

            if (check == 1) {
                DrawButton(x, y, 7, 4, 190, 60);
                SetCharacterColor(0);
                gotoXY(x + 1, y + 2); wcout << "RESUME";
            }
            else if (check == 2) {
                DrawButton(x, y + 6, 7, 4, 190, 60);
                SetCharacterColor(0);
                gotoXY(x + 2, y + 8); wcout << "SAVE";
            }
            else if (check == 3) {
                DrawButton(x, y + 12, 7, 4, 190, 60);
                SetCharacterColor(0);
                gotoXY(x + 2, y + 14); wcout << "MENU";
            }

            kt = false;
        }
        if (_kbhit()) {
            kt = true;
            checkcu = check;
            char c = _getch();
            if (c == -32) {
                c = _getch();
            }
            if (c == 'w' && check == 1) {
                check = 3;
            }
            else if (c == 'w') {
                check--;
            }
            else if (c == 's' && check == 3)
            {
                check = 1;
            }
            else if (c == 's') {
                check++;
            }
            if (c == 13) {
                if (CheckSound == 1) EnterBut();
                break;
            }
        }
    }
    if (check == 1) {
        SetBackgroundColor(120);
        CleanBackground(52, 9, 14, 23);
        SetCharacterColor(0);
        gotoXY(56, 12);
        wcout << "LEVEL: ";
        gotoXY(56, 14);
        wcout << "SCORE: ";
        gotoXY(54, 29);
        wcout << "Press SPACE";
        gotoXY(56, 30);
        wcout << "to Pause";
        ResumeThread(t);
    }
    else if (check == 2) {
        SetBackgroundColor(120);
        inputLimitedString(15, player);
        if (player.ten.length() <= 15 && player.ten.length() > 0) {
            SaveGame();
            writeSaveFile();
            system("cls");
            ShowSuccess();
            DrawLevel();
            SetBackgroundColor(120);
            CleanBackground(52, 9, 14, 23);
            SetCharacterColor(0);
            gotoXY(56, 12);
            wcout << "LEVEL: ";
            gotoXY(56, 14);
            wcout << "SCORE: ";
            gotoXY(54, 29);
            wcout << "Press SPACE";
            gotoXY(56, 30);
            wcout << "to Pause";
            ResumeThread(t);
        }
    }
    if (check == 3) {
        SetFont(0, 16, L"Consolas");
        SetBackgroundColor(120);
        system("cls");
        Menu();
    }
}


// hàm ghi dữ liệu người chơi ra file
void writeSaveFile()
{
    fin.close();
    wofstream fout;
    fout.open("SaveGame.txt");
    fout << save.size() << '\n';
    for (auto i : save)
    {
        fout << (wstring)i.name << '\n';
        fout << chrono::system_clock::to_time_t(i.saveTime) << '\n';
        fout << i.sound << '\n';
        fout << i.snak.SNAKE_COLOR << '\n';
        fout << i.snak.LEVEL << '\n'; // Save level
        fout << i.snak.SCORE << '\n'; // Save total score
        fout << i.snak.STATE << '\n'; // Save state (dead or alive)
        fout << i.snak.SPEED << '\n'; // Save speed
        fout << i.snak.SIZE_SNAKE << '\n'; // Save snake size
        fout << i.snak.FOOD_INDEX << '\n'; // Save food index
        fout << i.snak.STOP_DRAW_FOOD << '\n'; // Save draw food state
        fout << i.snak.TIMEBIGFOOD << '\n'; // Save big food time
        fout << i.snak.CHAR_LOCK << '\n'; // Save character lock direction
        fout << i.snak.MOVING << '\n'; // Save moving direction



        // Save snake body coordinates
        for (int j = 0; j < i.snak.SIZE_SNAKE; j++)
        {
            fout << i.snak.snake[j].x << ' ' << i.snak.snake[j].y << '\n';
        }

        // Save food coordinates
        for (int j = 0; j < 6; j++)
        {
            fout << i.snak.food[j].x << ' ' << i.snak.food[j].y << '\n';
        }



        // Save wall coordinates
        fout << i.snak.wall.size() << '\n';
        for (const auto& point : i.snak.wall)
        {
            fout << point.x << ' ' << point.y << '\n';
        }

        // Save gate coordinates
        fout << i.snak.gate.size() << '\n';
        for (const auto& point : i.snak.gate)
        {
            fout << point.x << ' ' << point.y << '\n';
        }
    }
    fout.close();
}

// hàm tải lại dữ liệu người chơi từ file đã lưu
void loadSaveFile()
{
    fin.close();
    fin.open("SaveGame.txt");
    int n;
    time_t T;
    fin >> n;
    if (n > 0)
        save.resize(n);
    for (int i = 0; i < n; i++)
    {
        fin.ignore(); // Ignore newline character
        getline(fin, save[i].name); // Read the name
        fin >> T;
        save[i].saveTime = chrono::system_clock::from_time_t(T);


        // Load snake level and other attributes
        fin >> save[i].sound;
        fin >> save[i].snak.SNAKE_COLOR;
        fin >> save[i].snak.LEVEL;
        fin >> save[i].snak.SCORE;
        fin >> save[i].snak.STATE;
        fin >> save[i].snak.SPEED;
        fin >> save[i].snak.SIZE_SNAKE;
        fin >> save[i].snak.FOOD_INDEX;
        fin >> save[i].snak.STOP_DRAW_FOOD;
        fin >> save[i].snak.TIMEBIGFOOD;
        fin >> save[i].snak.CHAR_LOCK;
        fin >> save[i].snak.MOVING;

        // Load snake body coordinates
        for (int j = 0; j < save[i].snak.SIZE_SNAKE; j++)
        {
            fin >> save[i].snak.snake[j].x >> save[i].snak.snake[j].y;
        }

        // Load food coordinates
        for (int j = 0; j < 6; j++)
        {
            fin >> save[i].snak.food[j].x >> save[i].snak.food[j].y;
        }

        // Load wall coordinates
        int wallSize;
        fin >> wallSize;
        save[i].snak.wall.resize(wallSize);
        for (int j = 0; j < wallSize; j++)
        {
            fin >> save[i].snak.wall[j].x >> save[i].snak.wall[j].y;
        }

        // Load gate coordinates
        int gateSize;
        fin >> gateSize;
        save[i].snak.gate.resize(gateSize);
        for (int j = 0; j < gateSize; j++)
        {
            fin >> save[i].snak.gate[j].x >> save[i].snak.gate[j].y;
        }
    }
    fin.close();
}

// hàm lưu game
void SaveGame()
{
    Save save_current = { player.ten , chrono::system_clock::now() , CheckSound, snake_current };
    if (UsedName(player.ten)) {
        for (int i = 0; i < save.size(); i++)
        {
            if (save[i].name == player.ten) save[i] = save_current;
        }
    }
    else {
        save.insert(save.begin(), save_current);
    }
}

// vẽ bảng reload
void Reload()
{
    printMyFile("Setting.txt", 66, 2, 0, "reload");
    Draw2LineBox(54, 15, 100, 30, 0);
    gotoXY(60, 16);
    cout << "NAME";
    gotoXY(84, 16);
    cout << "SCORE";
    gotoXY(112, 16);
    cout << "LEVEL";
    gotoXY(136, 16);
    cout << "DATE/TIME";
    for (int i = 55; i < 154; i++) {
        gotoXY(i, 17);
        cout << (char)205;
    }
    gotoXY(90, 11);
    cout << "PRESS ESC TO RETURN MENU";
    int check = 0, checkcu = 0;
    int n = save.size();
    bool kt = false;
    SetBackgroundColor(YELLOW);
    CleanBackground(54, 17, 100, 2);
    gotoXY(55, 18); save[0].output(55, 18);
    SetBackgroundColor(BACKGROUND);
    for (int i = 1; i < n; i++) {
        gotoXY(55, 18 + i); save[i].output(55, 18 + i);
    }
    while (true) {
        if (kt == true) {
            SetBackgroundColor(BACKGROUND);
            CleanBackground(54, 17 + checkcu, 100, 2);
            save[checkcu].output(55, 18 + checkcu);
            SetBackgroundColor(YELLOW);
            CleanBackground(54, 17 + check, 100, 2);
            save[check].output(55, 18 + check);
            kt = false;
        }
        if (_kbhit()) {
            kt = true;
            checkcu = check;
            char c = _getch();
            if (c == -32) {
                c = _getch();
            }
            if (c == 'w' && check == 0) {
                check = n - 1;
            }
            else if (c == 'w') {
                check--;
            }
            else if (c == 's' && check == n - 1)
            {
                check = 0;
            }
            else if (c == 's') {
                check++;
            }
            if (c == 13) {
                if (CheckSound == 1) EnterBut();
                break;
            }
            if (c == 27) {
                if (CheckSound == 1) EnterBut();
                system("cls");
                system("color 70");
                Menu();
            }
        }
    }
    player.ten = save[check].name;
    snake_current = save[check].snak;
    CheckSound = save[check].sound;
    see_reload = 1;
    check_reload = 0;
    Play();
}


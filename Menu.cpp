#include "Header.h"
#include "Global.h"
#include "Graphics.h"
#include "WinConsole.h"
#include "Logic.h"
#include "Sound.h"
#include "Save_Reload.h"

// hàm tạo menu
void Menu() 
{
    system("cls");
    StopSound();
    if (CheckSound == 1) BackgroundSound();
    ShowScrollbar(0);
    system("color 70");
    ShowCur(0);
    loadSaveFile();
    DisableSelection();
    FullScreenConsole();
    FixConsoleWindow();
    Draw2LineBox(20, 5, 170, 40, 13);
    Draw2LineBox(45, 7, 115, 14, 6);
    printMyFile("intro_menu_outro.txt", 50, 10, 6, "snakegame");
    printMyFile("intro_menu_outro.txt", 63, 25, 13, "newgame");
    PrintColorSnake(24, 25, 160);
    PrintColorSnake(158, 25, 160);
    DrawController(82, 32);
    int check = 1;
    bool kt = false;

    while (true) {
        if (kt == true) {
            CleanBackground(55, 22, 100, 10);
            if (check == 1)         printMyFile("intro_menu_outro.txt", 63, 25, 13, "newgame");
            else if (check == 2)    printMyFile("intro_menu_outro.txt", 64, 25, 13, "continue");
            else if (check == 3)    printMyFile("intro_menu_outro.txt", 70, 25, 13, "reload");
            else if (check == 4)    printMyFile("intro_menu_outro.txt", 75, 25, 13, "about");
            else if (check == 5)    printMyFile("intro_menu_outro.txt", 64, 25, 13, "settings");
            else if (check == 6)    printMyFile("intro_menu_outro.txt", 83, 25, 13, "exit");
            kt = false;
        }
        if (_kbhit()) {
            kt = true;
            char c = tolower(_getch());
            if (c == -32) {
                c = _getch();
            }
            if (c == 100 && check == 6) {
                check = 1;
            }
            else if (c == 97 && check == 1) {
                check = 6;
            }
            else if (c == 100) check++;
            else if (c == 97)  check--;
            if (check != 0) {
                if (c == 13) {
                    if (CheckSound == 1)
                        EnterBut();
                    system("cls");
                    system("color 70");
                    break;
                }
            }
        }
    }
    if (check == 1) {
        see_reload = 0;
        LoadGame();
        SetFont(20, 20, L"Terminal");
        Play();
    }
    else if (check == 2) {
        player.ten = save[0].name;
        snake_current = save[0].snak;
        CheckSound = save[0].sound;
        see_reload = 1;
        check_reload = 0;
        Play();
    }
    else if (check == 3) Reload();
    else if (check == 4) {
        DrawIntroduction();
        while (true) {
            if (_getch() == 13) {
                if (CheckSound == 1)
                    EnterBut();
                system("cls");
                Menu();
                break;
            }
        }
    }
    else if (check == 5) DrawSetting();
    else if (check == 6) DrawOutro();
}




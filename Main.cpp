#include "Menu.h"
#include "Graphics.h"
#include "WinConsole.h"
#include "Logic.h"
#include "Sound.h"
#include "Save_Reload.h"

int main()
{
    ShowScrollbar(0);
    system("color 70");
    ShowCur(0);
    DisableSelection();
    FullScreenConsole();
    FixConsoleWindow();
    //Loading();
    //Menu();
    DrawIntroduction();

    (void)_getch();
    return 0;

}
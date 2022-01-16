#include "delayTime.h"
#include "playingGame.h"
#include "UI.h"
#include "Menu.h"

int main()
{
    UI_logIn();
    loginOrSignup();

    MENU();
    printLoading();

    playingGame();

    gotoxy(0, 50);
}

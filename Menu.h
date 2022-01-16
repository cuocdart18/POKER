#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "UI.h"

void intro();
void menu();
void menuchon(int chon, int choncu);
int wherex();
int wherey();
void gotoxy(int x, int y);
void SetTeColor(WORD color);

void MENU()
{
    menu();
}

//
void menu()
{
    printVienNgoai();
    int chon = 1, choncu = 0;
    SetTeColor(10);
    gotoxy(78, 21); // 25;3
    printf(" Bat dau");
    gotoxy(78, 22); // 25;4
    printf("Huong Dan");
    gotoxy(78, 23); // 25;5
    printf("Thong Tin\n");
    menuchon(1, 0);
    while (1)
    {
        char phim;
        if (kbhit())
        {
            phim = getch();
            if (phim == 13)
                break;
            if (phim == 80)
            {
                if (chon < 3)
                {
                    chon++;
                    choncu = chon - 1;
                    menuchon(chon, choncu);
                }
            }
            if (phim == 72)
            {
                if (chon > 1)
                {
                    chon--;
                    choncu = chon + 1;
                    menuchon(chon, choncu);
                }
            }
        }
    }
    if (chon == 1)
        return;
    if (chon == 2)
    {
        printVienNgoai();
        gotoxy(58, 20);
        printf("Huong dan chi tiet vui long click vao link duoi day");
        gotoxy(54, 22);
        SetTeColor(green);
        printf("https://www.poker.org/beginners-guide-to-the-rules-of-poker/");
        SetTeColor(default);
        gotoxy(73, 37);
        printf("Press [ENTER] to exit");
        gotoxy(0, 50);
        char enter;
        while (1)
        {
            enter = getch();
            if (enter == 13)
                break;
        }
        menu();
    }

    if (chon == 3)
    {
        printVienNgoai();
        intro();
    }
}
//

//
//
void intro()
{
    SetTeColor(green);
    gotoxy(78, 17);
    printf("Design by");
    SetTeColor(default);
    gotoxy(73, 19);
    printf("-> Cuoc Dat");
    gotoxy(73, 20);
    printf("-> Minh Nguyen");
    gotoxy(73, 21);
    printf("-> Quoc Khanh");
    SetTeColor(green);
    gotoxy(73, 37);
    printf("Press [ENTER] to exit");
    gotoxy(0, 50);
    char enter;
    while (1)
    {
        enter = getch();
        if (enter == 13)
            break;
    }
    menu();
}
//
//

//
void menuchon(int chon, int choncu)
{
    if (chon == 1)
    {
        if (choncu == 2)
        {
            gotoxy(76, 22);
            printf(" ");
            gotoxy(88, 22);
            printf(" ");
        }
        gotoxy(76, 21);
        printf("%c", 16);
        gotoxy(88, 21);
        printf("%c", 17);
    }
    if (chon == 2)
    {
        if (choncu == 1)
        {
            gotoxy(76, 21);
            printf(" ");
            gotoxy(88, 21);
            printf(" ");
        }
        if (choncu == 3)
        {
            gotoxy(76, 23);
            printf(" ");
            gotoxy(88, 23);
            printf(" ");
        }
        gotoxy(76, 22);
        printf("%c", 16);
        gotoxy(88, 22);
        printf("%c", 17);
    }
    if (chon == 3)
    {
        if (choncu == 2)
        {
            gotoxy(76, 22);
            printf(" ");
            gotoxy(88, 22);
            printf(" ");
        }
        gotoxy(76, 23);
        printf("%c", 16);
        gotoxy(88, 23);
        printf("%c", 17);
    }
}
//

//
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    return coninfo.dwCursorPosition.X;
}
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    return coninfo.dwCursorPosition.Y;
}

#endif
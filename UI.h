#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "delayTime.h"
#include "playingGame.h"

#define default 7
#define green 10
#define yellow 6
#define violet 5
#define red 20
#define blue 11
#define pink 13
#define milk 14
#define white 15
#define tanghinh 16

void gotoxy(int x, int y);
void SetTeColor(WORD color);

void UI_inGame();
void UI_logIn();
void UI_signUp();
void printFormSignup(int x, int y);
void printFormAccPass(int x, int y);
void printLoginSignup(int x, int y);
void printPlay(int x, int y);
void printLoading();

void printVienNgoai();
void printMyMoney();
void printTable();
void printNotification();
void printAllBet();
void print1LaBai(int x, int y);
void print5LaBai();
void print1Player(int x, int y);
void printBangDieuKhien();
void printHinhChuNhat(int doc, int ngang, int x, int y);
void printSoChipMuonCuoc();
void printName();
void printDealerSmallBigBlind();
void printSoChipCuocCacPlayer();
void printStatus();
void printRankAndSuit(char rank, char suit, int x, int y);

// UI [DETAIL]
void printfPOT(int POT);
void printfSoChip(int p1, int p2, int p3, int p4);
void printfPosition(char *p1, char *p2, char *p3, char *p4);
void printfNoti(char *noti);
void printfStatus(int p1, int p2, int p3, int p4);
void printfBaiCuaPlayer(char rank1, char suit1, char rank2, char suit2, int soThuTu);
void dayLaLuotCua(char *name);
void printfChoosePlayer(char choose, char *name);
void printfChooseBot(int choose, char *name);
void printfLa_1(char rank, char suit);
void printfLa_2(char rank, char suit);
void printfLa_3(char rank, char suit);
void printfLa_4(char rank, char suit);
void printfLa_5(char rank, char suit);

//

// ve giao dien oanh poker
void UI_inGame()
{
    system("cls");

    printVienNgoai();
    printNotification();
    printTable();
    printSoChipMuonCuoc();
    printAllBet();
    print5LaBai();

    print1Player(8, 9);    // player 1
    print1Player(134, 9);  // Player 2
    print1Player(134, 33); // Player 3
    print1Player(8, 33);   // Player 4

    printName();
    printSoChipCuocCacPlayer();
    printStatus();

    printBangDieuKhien();
    printMyMoney();

    printDealerSmallBigBlind();

    gotoxy(0, 50);
}
//

// ve giao dien dang nhap
void UI_logIn()
{
    system("cls");
    printVienNgoai();

    printFormAccPass(59, 16);
    printLoginSignup(72, 23);
}
//

// ve giao dien dang ky
void UI_signUp()
{
    system("cls");
    printVienNgoai();

    printFormSignup(59, 16);
    printPlay(80, 27);

    // gotoxy(0, 51); // dong cuoi
}
//

/*---------------------------------------------System function---------------------------------------------*/

void SetTeColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//

//
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}
//

/*
POKER_Bo mon huy diet gioi tre
----------------------------------------------------------------------------------------------------------------
*/

//

//

//

//

//

//

//

//

// in man hinh loading. . . . . trong 5s
void printLoading()
{
    printVienNgoai();

    gotoxy(72, 24);
    printf("LOADING");
    for (int i = 0; i < 5; i++)
    {
        printf(". ");
        delay(1);
    }
}
//

// in thanh tai khoan va mat khau --- luc dang ky
void printFormSignup(int x, int y)
{
    gotoxy(x + 26, y - 3);
    SetTeColor(blue);
    printf("SIGN UP");

    gotoxy(x, y);
    printf("Your name  ");
    SetTeColor(default);
    gotoxy(x + 12, y - 1);
    printHinhChuNhat(3, 35, x + 12, y - 1);

    gotoxy(x, y + 4);
    SetTeColor(blue);
    printf("Account ");
    SetTeColor(default);
    gotoxy(x + 12, y + 3);
    printHinhChuNhat(3, 35, x + 12, y + 3);

    gotoxy(x, y + 8);
    SetTeColor(blue);
    printf("Password ");
    SetTeColor(default);
    gotoxy(x + 12, y + 7);
    printHinhChuNhat(3, 35, x + 12, y + 7);
}
//

// in thanh tai khoan va mat khau --- luc dang nhap
void printFormAccPass(int x, int y)
{
    // 59;16
    gotoxy(x + 26, y - 3);
    SetTeColor(blue);
    printf("LOG IN");

    gotoxy(x, y);
    printf("Account ");
    SetTeColor(default);
    gotoxy(x + 12, y - 1);
    printHinhChuNhat(3, 35, x + 12, y - 1);

    gotoxy(x, y + 4);
    SetTeColor(blue);
    printf("Password ");
    SetTeColor(default);
    gotoxy(x + 12, y + 3);
    printHinhChuNhat(3, 35, x + 12, y + 3);
}
//

// in nut login va signup
void printLoginSignup(int x, int y)
{
    gotoxy(x, y);
    SetTeColor(blue);
    printf("[Q]. Log in");
    gotoxy(x + 20, y);
    printf(" [W]. Sign up");
    SetTeColor(default);
}
//

// in nut login va signup
void printPlay(int x, int y)
{
    gotoxy(x, y);
    SetTeColor(blue);
    printf("[Enter]. START");
    SetTeColor(default);
}
//

// in trang thai cac Player
void printStatus()
{
    SetTeColor(14);
    gotoxy(10, 19);
    printf("Status: ");
    gotoxy(136, 19);
    printf("Status: ");
    gotoxy(10, 43);
    printf("Status: ");
    gotoxy(136, 43);
    printf("Status: ");
    SetTeColor(7);
}
//

// in so chip cuoc cua moi nguoi
void printSoChipCuocCacPlayer()
{
    SetTeColor(14);
    gotoxy(12, 17);
    printf("Chip cuoc: ");
    gotoxy(138, 17);
    printf("Chip cuoc: ");
    gotoxy(12, 41);
    printf("Chip cuoc: ");
    gotoxy(138, 41);
    printf("Chip cuoc: ");
    SetTeColor(7);
}
//

// in ten Dealer - Small - Big
void printDealerSmallBigBlind()
{
    gotoxy(0, 0);
    SetTeColor(13);
    printf("+------------------------------+");

    gotoxy(0, 1);
    SetTeColor(13);
    printf("| ");
    SetTeColor(14);
    printf("Dealer:");
    SetTeColor(7);
    printf("                      |");

    gotoxy(0, 2);
    SetTeColor(13);
    printf("| ");
    SetTeColor(14);
    printf("Small blind:");
    SetTeColor(7);
    printf("                 |");

    gotoxy(0, 3);
    SetTeColor(13);
    printf("| ");
    SetTeColor(14);
    printf("Big blind:");
    SetTeColor(7);
    printf("                   |");

    gotoxy(0, 4);
    SetTeColor(13);
    printf("+");
    SetTeColor(7);
    printf("------------------------------+");
}
//

// in so tien ban dang co tai vi tri x, y
void printMyMoney()
{
    gotoxy(59, 47);
    printf("+----------------------------------------------+");
    gotoxy(59, 47 + 1);
    printf("|  ");
    SetTeColor(10);
    printf("So chip ban dang co:");
    SetTeColor(7);
    printf("                        |");
    gotoxy(59, 47 + 2);
    SetTeColor(13);
    printf("+----------------------------------------------+");
    SetTeColor(7);
}
//

// in so tien cuoc Tong
void printAllBet()
{
    gotoxy(62, 14);
    SetTeColor(10);
    printf("+----------------------------------------+");
    gotoxy(62, 14 + 1);
    printf("|");
    SetTeColor(7);
    printf("  >> ");
    SetTeColor(11);
    printf("Pot");
    SetTeColor(7);
    printf(" << :                           ");
    SetTeColor(10);
    printf("|");
    gotoxy(62, 14 + 2);
    printf("+----------------------------------------+");
    SetTeColor(7);
}
//

// in thong bao dieu khien tro choi
void printNotification()
{
    int x = 55, y = 4;
    gotoxy(x, y);

    // in noti
    SetTeColor(20);
    printHinhChuNhat(5, 56, x, y);
    SetTeColor(7);
}
//

// in thanh dieu khien
void printBangDieuKhien()
{
    gotoxy(47, 32);
    printf("+----------------+------------------+-----------------+----------------+");

    gotoxy(47, 33);
    printf("| ");
    SetTeColor(14);
    printf("[Q].Bo bai");
    SetTeColor(7);
    printf("     | ");
    SetTeColor(14);
    printf("[W].Theo cuoc");
    SetTeColor(7);
    printf("    | ");
    SetTeColor(14);
    printf("[E].Xem bai");
    SetTeColor(7);
    printf("     | ");
    SetTeColor(14);
    printf("[R].Them cuoc");
    SetTeColor(7);
    printf("  |");

    gotoxy(47, 34);
    printf("+----------------+------------------+-----------------+----------------+");
}
//

// in so chip cuoc ma minh muon choi
void printSoChipMuonCuoc()
{
    gotoxy(63, 38);
    printf("+--------------------------------------+");
    gotoxy(63, 39);
    printf("| ");
    SetTeColor(10);
    printf("Nhap so chip cuoc:");
    SetTeColor(7);
    printf("                   |");
    gotoxy(63, 40);
    printf("+--------------------------------------+");
}
//

// in ten nguoi choi
void printName()
{
    SetTeColor(11);
    gotoxy(16, 8);
    printf("Player 1");
    gotoxy(142, 8);
    printf("Player 2");
    gotoxy(16, 32);
    printf("Player 4");
    gotoxy(142, 32);
    printf("Player 3");
    SetTeColor(7);
}
//

// in gia tri va chat cua 1 la bai tai vi tri x, y
void printRankAndSuit(char rank, char suit, int x, int y)
{
    gotoxy(x, y);
    printf("%c", rank); // in goc tren - trai
    gotoxy(x + 3, y + 2);
    printf("%c", suit); // in suit o giua
    gotoxy(x + 2, y + 3);
    printf("%c", suit); // in suit o giua
    gotoxy(x + 5, y + 5);
    printf("%c", rank); // in goc duoi - phai
}
//

// in vien ngoai
void printVienNgoai()
{
    gotoxy(0, 0);

    // in vien hinh chu nhat
    SetTeColor(13);
    printHinhChuNhat(50, 166, 0, 0);
    SetTeColor(7);

    // in ten Game va slogan
    gotoxy(66, 0);
    printf("| ");
    SetTeColor(11);
    printf("POKER_Bo mon huy diet gioi tre");
    SetTeColor(7);
    printf(" |");
}
//

// in ban poker rong tai vi tri x, y
void printTable()
{
    int x = 41, y = 16;
    gotoxy(x, y);

    // in ban
    SetTeColor(10);
    printHinhChuNhat(18, 84, x, y);
    SetTeColor(7);
}
//

// in 1 la bai co tai vi tri x, y
void print1LaBai(int x, int y)
{
    gotoxy(x, y);
    // in 1 la bai
    SetTeColor(10);
    printHinhChuNhat(8, 8, x, y);
    SetTeColor(7);
}
//

// in 5 la bai trong ban poker
void print5LaBai()
{
    // in bai 1
    print1LaBai(47, 21);
    // in bai 2
    print1LaBai(63, 21);
    // in bai 3
    print1LaBai(79, 21);
    // in bai 4
    print1LaBai(95, 21);
    // in bai 5
    print1LaBai(111, 21);
}
//

// in 1 nguoi choi tai vi tri x, y
void print1Player(int x, int y)
{
    print1LaBai(x, y);
    print1LaBai(x + 16, y);
}
//

// ve hinh chu nhat voi chieu dai va rong
void printHinhChuNhat(int doc, int ngang, int x, int y)
{
    for (int i = 0; i < doc; i++)
    {
        for (int j = 0; j < ngang; j++)
        {
            if (i == 0 || i == doc - 1)
            {
                if (j == 0 || j == ngang - 1)
                {
                    printf("+");
                }
                else
                {
                    printf("-");
                }
            }
            else
            {
                if (j == 0 || j == ngang - 1)
                {
                    printf("|");
                }
                else
                {
                    printf(" ");
                }
            }
        }
        gotoxy(x, y + i + 1);
    }
}
//

//

//

//

//

//

//

//
// UI chi tiet

// print POT
void printfPOT(int POT)
{
    gotoxy(77, 15);
    printf("                         ");
    gotoxy(77, 15);
    printf("%d", POT);
}
//

// print so chip moi player
void printfSoChip(int p1, int p2, int p3, int p4)
{
    gotoxy(23, 17); // 1
    printf("%d  ", p1);

    gotoxy(149, 17); // 2
    printf("%d  ", p2);

    gotoxy(23, 41); // 4
    printf("%d  ", p4);

    gotoxy(149, 41); // 3
    printf("%d  ", p3);
}
//

// in ten cho ngoi moi nguoi
void printfPosition(char *p1, char *p2, char *p3, char *p4)
{
    SetTeColor(11);
    gotoxy(16, 8);
    printf("%s    ", p1);

    gotoxy(142, 8);
    printf("%s    ", p2);

    gotoxy(16, 32);
    printf("%s    ", p4);

    gotoxy(142, 32);
    printf("%s    ", p3);

    SetTeColor(7);
}
//

// in so chip dang co cua minh
void printfMyChip(int money)
{
    gotoxy(83, 48);
    printf("%d       ", money);
}
//

// in thong bao
void printfNoti(char *noti)
{
    gotoxy(57, 6);
    printf("                                                     ");
    gotoxy(57, 6);
    printf("%s", noti);
}
//

// in trang thai nguoi choi
void printfStatus(int p1, int p2, int p3, int p4)
{
    gotoxy(18, 19); // 1
    if (p1 == 1)
        printf("Folded  ");
    else
        printf("Playing");

    gotoxy(144, 19); // 2
    if (p2 == 1)
        printf("Folded  ");
    else
        printf("Playing");

    gotoxy(18, 43); // 4
    if (p4 == 1)
        printf("Folded  ");
    else
        printf("Playing");

    gotoxy(144, 43); // 3
    if (p3 == 1)
        printf("Folded  ");
    else
        printf("Playing");
}
//

// in bai cua player
void printfBaiCuaPlayer(char rank1, char suit1, char rank2, char suit2, int soThuTu)
{
    if (soThuTu == 1)
    {
        printRankAndSuit(rank1, suit1, 9, 10);
        printRankAndSuit(rank2, suit2, 25, 10);
    }

    if (soThuTu == 2)
    {
        printRankAndSuit(rank1, suit1, 135, 10);
        printRankAndSuit(rank2, suit2, 151, 10);
    }

    if (soThuTu == 3)
    {
        printRankAndSuit(rank1, suit1, 135, 34);
        printRankAndSuit(rank2, suit2, 151, 34);
    }

    if (soThuTu == 4)
    {
        printRankAndSuit(rank1, suit1, 9, 34);
        printRankAndSuit(rank2, suit2, 25, 34);
    }
}
//

// in thong bao turn "Day la luot cua XNXX"
void dayLaLuotCua(char *name)
{
    gotoxy(57, 6);
    printf("                                                     ");
    gotoxy(57, 6);
    printf("Day la luot cua %s", name);
}
//

// in thong bao choose "XNXX chon VLXX" [PLAYER]
void printfChoosePlayer(char choose, char *name)
{
    if (choose == 'Q')
    {
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("%s da chon Fold", name);
    }
    if (choose == 'W')
    {
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("%s da chon Call", name);
    }
    if (choose == 'E')
    {
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("%s da chon Check", name);
    }
    if (choose == 'R')
    {
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("%s da chon Raise", name);
    }
}
//

// in thong bao choose "XNXX chon VLXX" [BOT]
void printfChooseBot(int choose, char *name)
{
    if (choose >= 96 && choose <= 100)
    {
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("%s da chon Fold", name);
    }
    if (choose >= 46 && choose <= 80)
    {
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("%s da chon Call", name);
    }
    if (choose >= 1 && choose <= 45)
    {
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("%s da chon Check", name);
    }
    if (choose >= 81 && choose <= 95)
    {
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("%s da chon Raise", name);
    }
}
//

//
void printfLa_1(char rank, char suit)
{
    printRankAndSuit(rank, suit, 48, 22);
}
void printfLa_2(char rank, char suit)
{
    printRankAndSuit(rank, suit, 64, 22);
}
void printfLa_3(char rank, char suit)
{
    printRankAndSuit(rank, suit, 80, 22);
}
void printfLa_4(char rank, char suit)
{
    printRankAndSuit(rank, suit, 96, 22);
}
void printfLa_5(char rank, char suit)
{
    printRankAndSuit(rank, suit, 112, 22);
}
//

#endif

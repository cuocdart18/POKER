#ifndef PLAY_H
#define PLAY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "UI.h"
#include "Menu.h"
#include "delayTime.h"

// tao 1 doi tuong Card
typedef struct
{
    char rank;
    char suit;
} Card;

// tao 1 struct doi tuong player
//  minh se la player 1 ~~ pHead, duoc phep nhap thong tin va so lieu
typedef struct
{
    Card card[5];                  // moi player se giu 5 la bai, trong do 2 la bai la random[REAL]
    char name[30];                 // name hien thi o UI
    int status;                    // 1, fold//2, call//3, check//4, raise//5, ALL IN ~ 1 Wait to last game
    unsigned int soChipCuocBanDau; // do user nhap, 1 ban poker, moi player deu co 1 soTienCuoc nhu nhau
    int soThuTu;                   // de tim ra SB, nguoi cuoc dau tien trong 1 vong
    int Level;                     // so cap do bai
} Player;

// 1 node ~ 1 player
struct NODE
{
    Player player;
    struct NODE *pNext;
};
typedef struct NODE NODE;

// 1 node trong Queue
struct NODEofQueue
{
    int soPlayerTruCuoc;
    int soTienCuoc;
    struct NODEofQueue *pNext;
};
typedef struct NODEofQueue NODEofQueue;
//

// cau truc 1 dslk vong
typedef struct
{
    NODE *pHead;
    NODE *pTail;
} LIST;
//

// global variable, kiem tra nguoi dang truoc cuoc bao nhieu, suy ra cac status ma nguoi dang sau co
int minOfBet = 0;

//
//
typedef struct
{
    char taiKhoan[20];
    char matKhau[20];
    char name[30];
    int tien;
} ACCOUNT;
//

//
ACCOUNT listAcc[200];  // luu tru cac tai khoan
int count = 0;         // dem so luong acc
int indexOfPlayer = 0; // luu vi tri cua nguoi choi trong mang
//

//
typedef struct
{
    NODEofQueue *pHead;
} LISTq;
//

// tro vao winner
NODE *lastPlayer = NULL;
//

// prototype [MAIN]
int genRandom(int max, int min);
NODE *khoiTaoGiaTriCho1Player();
void khoiTaoDslk(LIST *l);
void nhapSoChipCuoc(LIST *l);
void timDealerVaSetTurn(LIST *l, int Dealer);

// play
void pre_Flop(LIST *l, int *pot, Card *baiTrenBan, LISTq *q);
void Flop(LIST *l, int *pot, Card *baiTrenBan, LISTq *q);
void Turn(LIST *l, int *pot, Card *baiTrenBan, LISTq *q);
void River(LIST *l, int *pot, Card *baiTrenBan, LISTq *q);
void checkActionOfBot(int random, LIST *l, NODE *obj, int *pot, LISTq *q);
void checkActionOfPlayer(char choose, LIST *l, NODE *obj, int *pot, LISTq *q);
void playerTurn(LIST *l, NODE *obj, int *pot, LISTq *q);
void resetStatus(LIST *l);
bool checkNguoi(NODE *me, LIST *l);
bool checkTienCuocBangNhau(LIST l);
bool checkCon1Player(LIST *l);
void addTienPot(LIST *l, int POT);

// QUEUE CUOC
int soPlayerTrongVan(LIST l);
bool isEmpty(LISTq q);
void add1VongCuoc(NODEofQueue *add, LISTq *q);
NODEofQueue *khoiTaoGiaTriCho1Node(int chipAdd);
void khoiTaoQueue(LISTq *q);

//[UNIT TEST PROTOTYPE]
void printDslk(LIST l); //[UNIT TEST]
void printLaBaiTrenBan(Card *baiTrenBan);
void genRandomBoBai(LIST *l, Card *baiTrenBan);
void printfSoTienConLai(LIST *l);
bool checkLapLai(Card *BaiDaDuocMo, int nSize, char rank, char suit);
char GetSuit(int suit);
char GetRank(int rank);
void PokerHand(Card *baiTrenBan, LIST *l);
int GanGiaTri(char bai);
//

// login signup
//-----[PROTOTYPE]-----//
void loginOrSignup();
void readDataFromFile();
void saveInfor();
void printInforInFile();
void pressLogin();
void pressSignUp();
bool checkTaiKhoanMatKhau(char *taiKhoanInput, char *matKhauInput);
bool checkTaiKhoan(char *taiKhoanInput);
bool check2Chuoi(char *s1, char *s2);
bool checkFormatInput(char *str);
//

//

//

//

//

//

//

//

// vong preflop
void pre_Flop(LIST *l, int *pot, Card *baiTrenBan, LISTq *q)
{
    NODE *p_STT_1 = NULL; // SB
    NODE *p_STT_2 = NULL; // BB
    NODE *p_STT_3 = NULL; // no one
    NODE *p_STT_4 = NULL; // D

    // Tim SB, nguoi co stt 1
    int count = 1;
    for (NODE *k = l->pHead; count != 5; k = k->pNext)
    {
        if (k->player.soThuTu == 1)
        {
            p_STT_1 = k;
            p_STT_2 = k->pNext;
            p_STT_3 = k->pNext->pNext;
            p_STT_4 = k->pNext->pNext->pNext;
            break;
        }
    }
    //

    // in D SB BB
    gotoxy(10, 1);
    printf("                     ");
    gotoxy(10, 1);
    printf("%s", p_STT_4->player.name);
    gotoxy(15, 2);
    printf("                ");
    gotoxy(15, 2);
    printf("%s", p_STT_1->player.name);
    gotoxy(13, 3);
    printf("                  ");
    gotoxy(13, 3);
    printf("%s", p_STT_2->player.name);
    //

    // in ten moi cho ngoi
    printfPosition(p_STT_1->player.name,
                   p_STT_2->player.name,
                   p_STT_3->player.name,
                   p_STT_4->player.name);
    //

    // in so chip
    printfSoChip(p_STT_1->player.soChipCuocBanDau,
                 p_STT_2->player.soChipCuocBanDau,
                 p_STT_3->player.soChipCuocBanDau,
                 p_STT_4->player.soChipCuocBanDau);
    //

    // in status
    printfStatus(p_STT_1->player.status,
                 p_STT_2->player.status,
                 p_STT_3->player.status,
                 p_STT_4->player.status);
    //

    //
    delayTimeIn(5);
    //

    // in noti
    gotoxy(57, 6);
    printf("                                                     ");
    gotoxy(57, 6);
    printf("Small blind va Big blind dat chip vao POT");
    //

    int chipOfStt1 = 1;
    int chipOfStt2 = 2;
    *pot = chipOfStt1 + chipOfStt2;
    // dat so tien min de cuoc
    minOfBet = chipOfStt2;

    // Tong tien cuoc
    // printf("\nPOT: %d\n", *pot);
    printfPOT(*pot);
    //

    // STT 1, tru tien cuoc
    p_STT_1->player.soChipCuocBanDau -= chipOfStt1;
    // STT 2, tru tien cuoc
    p_STT_2->player.soChipCuocBanDau -= chipOfStt2;
    //

    //
    printfSoChip(p_STT_1->player.soChipCuocBanDau,
                 p_STT_2->player.soChipCuocBanDau,
                 p_STT_3->player.soChipCuocBanDau,
                 p_STT_4->player.soChipCuocBanDau);
    //

    // hien 2 la bai moi player, theo luat
    // printf("Bai cua ban la: %c%c %c%c", l->pHead->player.card[0].rank, l->pHead->player.card[0].suit, l->pHead->player.card[1].rank, l->pHead->player.card[1].suit);
    printfBaiCuaPlayer(l->pHead->player.card[0].rank,
                       l->pHead->player.card[0].suit,
                       l->pHead->player.card[1].rank,
                       l->pHead->player.card[1].suit,
                       l->pHead->player.soThuTu);
    //

    //
    delayTimeIn(5);
    //

    // bat dau vong cuoc thu nhat
    // xuat phat tu STT 3
    NODE *k = p_STT_3;
    int check = 0;
    while (true)
    {
        // neu chi con 1 nguoi, tat ca folded
        if (checkCon1Player(l))
        {
            addTienPot(l, *pot);
            break;
        }

        // neu so cuoc bang nhau het, thi thoi
        if (checkTienCuocBangNhau(*l))
            break;

        // bat dau tu nguoi STT3
        if (k->player.status != 1)
        {
            dayLaLuotCua(k->player.name);
            delayTimeIn(5);
            playerTurn(l, k, pot, q);
        }
        k = k->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        // neu so cuoc bang nhau het, thi thoi
        if (checkTienCuocBangNhau(*l))
            break;

        // neu chi con 1 nguoi, tat ca folded
        if (checkCon1Player(l))
        {
            addTienPot(l, *pot);
            break;
        }

        // tiep den la Dealer
        if (k->player.status != 1)
        {
            dayLaLuotCua(k->player.name);
            delayTimeIn(5);
            playerTurn(l, k, pot, q);
        }
        k = k->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        // neu so cuoc bang nhau het, thi thoi
        if (checkTienCuocBangNhau(*l))
            break;

        // neu chi con 1 nguoi, tat ca folded
        if (checkCon1Player(l))
        {
            addTienPot(l, *pot);
            break;
        }

        // tiep theo la SB
        if (k->player.status != 1)
        {
            if (check == 0)
                minOfBet = 1; // cuoc 1$ tu vong dau tien, nen SB chi can tru 1
            dayLaLuotCua(k->player.name);
            delayTimeIn(5);
            playerTurn(l, k, pot, q);
            minOfBet = 0;
        }
        k = k->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        if (check != 0)
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        // printfSoTienConLai(l);

        // neu chi con 1 nguoi, tat ca folded
        if (checkCon1Player(l))
        {
            addTienPot(l, *pot);
            break;
        }

        // tiep theo la BB
        if (k->player.status != 1)
        {
            dayLaLuotCua(k->player.name);
            delayTimeIn(5);
            playerTurn(l, k, pot, q);
        }
        k = k->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);
        check++;
    }

    gotoxy(57, 6);
    printf("                                                     ");
    gotoxy(57, 6);
    printf("Da ket thuc vong cuoc Pre-Flop");
    delayTimeIn(5);
}
//

//

//

// vong Flop
void Flop(LIST *l, int *pot, Card *baiTrenBan, LISTq *q)
{
    NODE *p_STT_1 = NULL; // SB
    NODE *p_STT_2 = NULL; // BB
    NODE *p_STT_3 = NULL; // no one
    NODE *p_STT_4 = NULL; // D

    // Tim SB, nguoi co stt 1
    int count1 = 1;
    for (NODE *k = l->pHead; count1 != 5; k = k->pNext)
    {
        if (k->player.soThuTu == 1)
        {
            p_STT_1 = k;
            p_STT_2 = k->pNext;
            p_STT_3 = k->pNext->pNext;
            p_STT_4 = k->pNext->pNext->pNext;
            break;
        }
    }
    //

    // dong tren de print update POT and status
    NODE *p_STT_SB = NULL; // SB

    // Tim SB, nguoi co stt 1
    int count = 1;
    for (NODE *k = l->pHead; count != 5; k = k->pNext)
    {
        if (k->player.soThuTu == 1)
        {
            p_STT_SB = k;
            break;
        }
    }

    // bat dau cuoc
    int check = 0;
    while (true)
    {
        // bat dau tu SB
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        if (check != 0) // neu luot sau do = nhau thi break luon
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        //  BB
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        if (check != 0) // neu luot sau do = nhau thi break luon
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        // No one
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        if (check != 0) // neu luot sau do = nhau thi break luon
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        // D
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        // neu chi con 1 nguoi, tat ca folded
        if (checkCon1Player(l))
        {
            printf("\nCo 1 player chien thang, nhung luoi chua code :D\n", p_STT_SB->player.soThuTu);
            break;
        }

        // neu so cuoc bang nhau het, thi thoi
        if (checkTienCuocBangNhau(*l))
            break;

        check++;
    }

    gotoxy(57, 6);
    printf("                                                     ");
    gotoxy(57, 6);
    printf("Da ket thuc vong cuoc Flop");
    delayTimeIn(5);
}
//

//

//

// vong Turn
void Turn(LIST *l, int *pot, Card *baiTrenBan, LISTq *q)
{
    NODE *p_STT_1 = NULL; // SB
    NODE *p_STT_2 = NULL; // BB
    NODE *p_STT_3 = NULL; // no one
    NODE *p_STT_4 = NULL; // D

    // Tim SB, nguoi co stt 1
    int count1 = 1;
    for (NODE *k = l->pHead; count1 != 5; k = k->pNext)
    {
        if (k->player.soThuTu == 1)
        {
            p_STT_1 = k;
            p_STT_2 = k->pNext;
            p_STT_3 = k->pNext->pNext;
            p_STT_4 = k->pNext->pNext->pNext;
            break;
        }
    }
    //

    // dong tren de print update POT and status
    NODE *p_STT_SB = NULL; // SB

    // Tim SB, nguoi co stt 1
    int count = 1;
    for (NODE *k = l->pHead; count != 5; k = k->pNext)
    {
        if (k->player.soThuTu == 1)
        {
            p_STT_SB = k;
            break;
        }
    }

    // bat dau cuoc
    int check = 0;
    while (true)
    {
        // bat dau tu SB
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        if (check != 0) // neu luot sau do = nhau thi break luon
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        //  BB
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        if (check != 0) // neu luot sau do = nhau thi break luon
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        // No one
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        if (check != 0) // neu luot sau do = nhau thi break luon
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        // D
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        // neu chi con 1 nguoi, tat ca folded
        if (checkCon1Player(l))
        {
            printf("\nCo 1 player chien thang, nhung luoi chua code :D\n", p_STT_SB->player.soThuTu);
            break;
        }

        // neu so cuoc bang nhau het, thi thoi
        if (checkTienCuocBangNhau(*l))
            break;

        check++;
    }

    gotoxy(57, 6);
    printf("                                                     ");
    gotoxy(57, 6);
    printf("Da ket thuc vong cuoc Turn");
    delayTimeIn(5);
}
//

//

//

// vong River
void River(LIST *l, int *pot, Card *baiTrenBan, LISTq *q)
{
    NODE *p_STT_1 = NULL; // SB
    NODE *p_STT_2 = NULL; // BB
    NODE *p_STT_3 = NULL; // no one
    NODE *p_STT_4 = NULL; // D

    // Tim SB, nguoi co stt 1
    int count1 = 1;
    for (NODE *k = l->pHead; count1 != 5; k = k->pNext)
    {
        if (k->player.soThuTu == 1)
        {
            p_STT_1 = k;
            p_STT_2 = k->pNext;
            p_STT_3 = k->pNext->pNext;
            p_STT_4 = k->pNext->pNext->pNext;
            break;
        }
    }
    //

    // dong tren de print update POT and status
    NODE *p_STT_SB = NULL; // SB

    // Tim SB, nguoi co stt 1
    int count = 1;
    for (NODE *k = l->pHead; count != 5; k = k->pNext)
    {
        if (k->player.soThuTu == 1)
        {
            p_STT_SB = k;
            break;
        }
    }

    // bat dau cuoc
    int check = 0;
    while (true)
    {
        // bat dau tu SB
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        if (check != 0) // neu luot sau do = nhau thi break luon
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        //  BB
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        if (check != 0) // neu luot sau do = nhau thi break luon
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        // No one
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        if (check != 0) // neu luot sau do = nhau thi break luon
        {
            // neu so cuoc bang nhau het, thi thoi
            if (checkTienCuocBangNhau(*l))
                break;
        }

        // D
        if (p_STT_SB->player.status != 1)
        {
            dayLaLuotCua(p_STT_SB->player.name);
            delayTimeIn(5);
            playerTurn(l, p_STT_SB, pot, q);
        }
        p_STT_SB = p_STT_SB->pNext;

        // in so chip
        printfSoChip(p_STT_1->player.soChipCuocBanDau,
                     p_STT_2->player.soChipCuocBanDau,
                     p_STT_3->player.soChipCuocBanDau,
                     p_STT_4->player.soChipCuocBanDau);
        //

        // in status
        printfStatus(p_STT_1->player.status,
                     p_STT_2->player.status,
                     p_STT_3->player.status,
                     p_STT_4->player.status);
        //

        // printfSoTienConLai(l);

        // neu chi con 1 nguoi, tat ca folded
        if (checkCon1Player(l))
        {
            printf("\nCo 1 player chien thang, nhung luoi chua code :D\n", p_STT_SB->player.soThuTu);
            break;
        }

        // neu so cuoc bang nhau het, thi thoi
        if (checkTienCuocBangNhau(*l))
            break;

        check++;
    }

    gotoxy(57, 6);
    printf("                                                     ");
    gotoxy(57, 6);
    printf("Da ket thuc vong cuoc River");
    delayTimeIn(5);
}
//

//

//

//

//

int genRandom(int max, int min)
{
    return min + rand() % (max - min + 1);
}
//

// khoi tao gia tri cho 1 node ~ 1 thang player
NODE *khoiTaoGiaTriCho1Player()
{
    // tao 1 con tro quan li node
    NODE *p_Quan_li = (NODE *)malloc(sizeof(NODE));
    p_Quan_li->pNext = NULL;
    return p_Quan_li;
}
//

// khoi tao 1 dslk gom 4 player
void khoiTaoDslk(LIST *l)
{
    l->pHead = NULL;

    // tao player 1__ME__
    NODE *player_1 = khoiTaoGiaTriCho1Player();
    strcpy(player_1->player.name, listAcc[indexOfPlayer].name);

    // tao player 2
    NODE *player_2 = khoiTaoGiaTriCho1Player();
    strcpy(player_2->player.name, "Ronaldo");

    // tao player 3
    NODE *player_3 = khoiTaoGiaTriCho1Player();
    strcpy(player_3->player.name, "Messi");

    // tao player 4
    NODE *player_4 = khoiTaoGiaTriCho1Player();
    strcpy(player_4->player.name, "Neymar");

    // lien ket cac player
    l->pHead = player_1;
    player_1->pNext = player_2;
    player_2->pNext = player_3;
    player_3->pNext = player_4;
    player_4->pNext = player_1;
}
//

// khoi tao 1 queue
void khoiTaoQueue(LISTq *q)
{
    q->pHead = NULL;
}
//

// tao 1 lan tru cuoc
NODEofQueue *khoiTaoGiaTriCho1Node(int chipAdd)
{
    NODEofQueue *pQuanLi = (NODEofQueue *)malloc(sizeof(NODEofQueue));
    pQuanLi->soPlayerTruCuoc = 0;
    pQuanLi->soTienCuoc = chipAdd;
    pQuanLi->pNext = NULL;
    return pQuanLi;
}
//

// them 1 node CUOC vao queue
void add1VongCuoc(NODEofQueue *add, LISTq *q)
{
    if (isEmpty(*q))
    {
        q->pHead = add;
    }
    else
    {
        for (NODEofQueue *k = q->pHead; k != NULL; k = k->pNext)
        {
            if (k->pNext == NULL)
            {
                // thang node cuoi
                k->pNext = add;
                break;
            }
        }
    }
}
//

// check empty queue
// rong -> T
// ko rong -> F
bool isEmpty(LISTq q)
{
    if (q.pHead == NULL)
        return true;
    return false;
}
//

// xoa node dau, neu nhu da full
// void xoaCuocDau(LIST *q)
// {
//     if (q->pHead == NULL)
//         return;
//     else
//     {
//         NODEofQueue *pQuanLi = q->pHead->pNext;
//         q->pHead = pQuanLi;
//     }
// }
//

// tim so nguoi dang choi
int soPlayerTrongVan(LIST l)
{
    int countPlayer = 0;
    int c = 1;
    for (NODE *k = l.pHead; c != 5; c++, k = k->pNext)
    {
        if (k->player.status != 1 && k->player.status != 5)
            countPlayer++;
    }
    return countPlayer;
}
//

// nhap so chip cuoc cho cac players
void nhapSoChipCuoc(LIST *l)
{
    // int soChipCuoc = 100;
    // printf("So chip muon choi trong 1 van 100");

    int count = 0;
    for (NODE *k = l->pHead; count != 4; count++, k = k->pNext)
    {
        k->player.soChipCuocBanDau = 100;
    }
}
//

// tim D roi set stt cho tung player
void timDealerVaSetTurn(LIST *l, int Dealer)
{
    int count = 1;
    for (NODE *k = l->pHead; count != 5; count++, k = k->pNext)
    {
        if (Dealer == count)
        {
            k->player.soThuTu = 4;                      // this is D
            k->pNext->player.soThuTu = 1;               // this is SB
            k->pNext->pNext->player.soThuTu = 2;        // this is BB
            k->pNext->pNext->pNext->player.soThuTu = 3; // null
            break;
        }
    }
}
//

// kiem tra hanh dong cua bot
void checkActionOfBot(int random, LIST *l, NODE *obj, int *pot, LISTq *q)
{
    delayTimeIn(5);
    printfChooseBot(random, obj->player.name);
    delayTimeIn(5);

    if (random >= 96 && random <= 100)
    {
        // printf("\nBOT %d chon --fold\n", obj->player.soThuTu); // do sth
        obj->player.status = 1; // status = 1 nghia la ko trong van bai
    }

    else if (random >= 46 && random <= 80)
    {
        // printf("\nBOT %d chon --call\n", obj->player.soThuTu); // do sth

        // duyet xem nhung thang dang truoc day co Cuoc khong, neu co thi tru di
        if (isEmpty(*q))
        {
            obj->player.soChipCuocBanDau -= (minOfBet);
            *(pot) = *pot + (minOfBet);
            printfPOT(*pot);
        }
        else
        {
            obj->player.soChipCuocBanDau -= (minOfBet);
            *(pot) = *pot + (minOfBet);
            for (NODEofQueue *k = q->pHead; k != NULL; k = k->pNext)
            {
                if (k->soPlayerTruCuoc < soPlayerTrongVan(*l))
                {
                    obj->player.soChipCuocBanDau -= (k->soTienCuoc);
                    *(pot) = *pot + (k->soTienCuoc);
                    k->soPlayerTruCuoc++;
                }
            }
            printfPOT(*pot);
        }
    }

    else if (random >= 1 && random <= 45)
    {
        // printf("\nBOT %d chon --check\n", obj->player.soThuTu); // do sth
    }

    else if (random >= 81 && random <= 95)
    {
        // printf("\nBOT %d chon --raise---", obj->player.soThuTu); // do sth

        if (obj->player.soChipCuocBanDau > minOfBet)
        {
            int chipAdd = genRandom(obj->player.soChipCuocBanDau / 10, 1);
            // printf("%d\n", chipAdd);
            gotoxy(80, 6);
            printf("%d", chipAdd);
            delayTimeIn(5);

            // Neu raise, them node CUOC vao sau queue
            add1VongCuoc(khoiTaoGiaTriCho1Node(chipAdd), q);
            // chay loop tru cuoc
            obj->player.soChipCuocBanDau -= (minOfBet);
            *(pot) = *pot + (minOfBet);
            for (NODEofQueue *k = q->pHead; k != NULL; k = k->pNext)
            {
                if (k->soPlayerTruCuoc < soPlayerTrongVan(*l))
                {
                    obj->player.soChipCuocBanDau -= (k->soTienCuoc);
                    *(pot) = *pot + (k->soTienCuoc);
                    k->soPlayerTruCuoc++;
                }
            }
            printfPOT(*pot);
        }
        else // chua code xong, vi ti le ra thap vkl,
        {
            obj->player.status = 5; // Wait
            // Neu raise, them node CUOC vao sau queue
            add1VongCuoc(khoiTaoGiaTriCho1Node(obj->player.soChipCuocBanDau), q);
            *(pot) = *pot + (obj->player.soChipCuocBanDau + minOfBet);
            obj->player.soChipCuocBanDau = 0;
            // printf("\n----Ban %d ALL IN----\n", obj->player.soThuTu);
            gotoxy(57, 6);
            printf("                                                     ");
            gotoxy(57, 6);
            printf("%s da chon ALL IN", obj->player.name);
            delayTimeIn(5);

            printfPOT(*pot);
        }
    }
}
//

// kiem tra hanh dong cua nguoi
void checkActionOfPlayer(char choose, LIST *l, NODE *obj, int *pot, LISTq *q)
{
    printfChoosePlayer(choose, obj->player.name);
    delayTimeIn(5);

    if (choose == 'Q')
    {
        // printf("\nBan %d chon --fold\n", obj->player.soThuTu); // do sth
        obj->player.status = 1; // status = 1 nghia la ko trong van bai
        // ngoi xem BOT choi den luc END GAME
    }

    else if (choose == 'W')
    {
        // printf("\nBan %d chon --call\n", obj->player.soThuTu); // do sth

        // duyet xem nhung thang dang truoc da co Cuoc khong, neu co thi tru di
        if (isEmpty(*q))
        {
            obj->player.soChipCuocBanDau -= (minOfBet);
            *(pot) = *pot + (minOfBet);
            printfPOT(*pot);
        }
        else
        {
            obj->player.soChipCuocBanDau -= (minOfBet);
            *(pot) = *pot + (minOfBet);
            for (NODEofQueue *k = q->pHead; k != NULL; k = k->pNext)
            {
                if (k->soPlayerTruCuoc < soPlayerTrongVan(*l))
                {
                    obj->player.soChipCuocBanDau -= (k->soTienCuoc);
                    *(pot) = *pot + (k->soTienCuoc);
                    k->soPlayerTruCuoc++;
                }
            }
            printfPOT(*pot);
        }
    }

    else if (choose == 'E')
    {
        // printf("\nBan %d chon --check--\n", obj->player.soThuTu); // do sth
    }

    else if (choose == 'R')
    {
        // printf("\nBan %d chon --raise\n", obj->player.soThuTu); // do sth

        if (obj->player.soChipCuocBanDau > minOfBet)
        {
            // printf("\nNhap vao so tien muon raise: ");
            int chipAdd;

            while (true)
            {
                gotoxy(84, 39);
                printf("                 ");
                gotoxy(84, 39);
                scanf("%d", &chipAdd);
                getchar();

                if (chipAdd > 0 && chipAdd <= obj->player.soChipCuocBanDau)
                    break;
            }

            gotoxy(80, 6);
            printf("%d", chipAdd);
            delayTimeIn(5);

            // Neu raise, them node CUOC vao sau queue
            add1VongCuoc(khoiTaoGiaTriCho1Node(chipAdd), q);
            // chay loop tru cuoc
            obj->player.soChipCuocBanDau -= (minOfBet);
            *(pot) = *pot + (minOfBet);
            for (NODEofQueue *k = q->pHead; k != NULL; k = k->pNext)
            {
                if (k->soPlayerTruCuoc < soPlayerTrongVan(*l))
                {
                    obj->player.soChipCuocBanDau -= (k->soTienCuoc);
                    *(pot) = *pot + (k->soTienCuoc);
                    k->soPlayerTruCuoc++;
                }
            }
            printfPOT(*pot);
        }
        else // chua code xong, vi ti le ra thap vkl,
        {

            obj->player.status = 5; // Wait
            // Neu raise, them node CUOC vao sau queue
            add1VongCuoc(khoiTaoGiaTriCho1Node(obj->player.soChipCuocBanDau), q);
            *(pot) = *pot + (obj->player.soChipCuocBanDau + minOfBet);
            obj->player.soChipCuocBanDau = 0;
            gotoxy(57, 6);
            printf("                                                     ");
            gotoxy(57, 6);
            printf("%s da chon ALL IN", obj->player.name);
            delayTimeIn(5);
            printfPOT(*pot);
            // printf("\n----Ban %d ALL IN----\n", obj->player.soThuTu);
        }
    }
}
//

// hanh dong 1 player
void playerTurn(LIST *l, NODE *obj, int *pot, LISTq *q)
{
    if (checkNguoi(obj, l))
    {
        // printf("\n____Ban se co cac lua chon o DAY____\n");
        char input;
        while (true)
        {
            // printf("Nhap [Q]--fold, [W]--call, [E]--check, [R]--raise\n");
            gotoxy(0, 50);
            printf("  ");
            gotoxy(0, 50);
            input = getchar();
            getchar();
            if (input >= 97 && input <= 122)
                input -= 32;
            if (input == 'Q' || input == 'W' || input == 'E' || input == 'R')
            {
                if (input == 'E' && checkTienCuocBangNhau(*l)) // neu genRan ra check, ma tien cuoc so nguoi choi bang nhau, -> dc phep chon
                    break;
                else if (input != 'E')
                    break;
            }
        }
        checkActionOfPlayer(input, l, obj, pot, q);
    }
    else
    {
        int random;
        while (true)
        {
            random = genRandom(100, 1);                                   // ti le pick Q W E R
            if (random >= 1 && random <= 45 && checkTienCuocBangNhau(*l)) // neu genRan ra check, ma tien cuoc so nguoi choi bang nhau, -> dc phep chon
                break;
            else if (random >= 46 && random <= 100)
                break;
        }
        checkActionOfBot(random, l, obj, pot, q);
    }
    /*
    1-45 check
    46-80 call
    81-95 raise
    96-100 fold
    */
}
//

// kiem tra cac players co so tien cuoc bang nhau hay chua
// tat ca deu bang -> T
// chua ai bang -> F
bool checkTienCuocBangNhau(LIST l)
{
    int count = 1;
    int tempTienCuoc;
    for (NODE *k = l.pHead; count != 5; k = k->pNext, count++)
    {
        if (k->player.status != 1 && k->player.status != 5)
        {
            tempTienCuoc = k->player.soChipCuocBanDau; // tim ra 1 thang playing, set tempTC de check cho ca dslk
            break;
        }
    }

    count = 1;
    for (NODE *k = l.pHead; count != 5; k = k->pNext, count++)
    {
        if (k->player.status != 1 && k->player.status != 5)
        {
            if (k->player.soChipCuocBanDau != tempTienCuoc)
                return false;
        }
    }
    return true;
}
//

// kiem tra xem co phai Minh khong hay la BOT
//  neu la nguoi, --> T
//  neu la BOT, --> F
bool checkNguoi(NODE *me, LIST *l)
{
    if (me->player.card[0].rank == l->pHead->player.card[0].rank &&
        me->player.card[0].suit == l->pHead->player.card[0].suit)
    {
        return true;
    }
    return false;
}
//

// kiem tra xem con duy nhat 1 nguoi ko
// neu con 1 nguoi -> T
// neu van con nguoi choi -> false
bool checkCon1Player(LIST *l)
{
    int count = 1;
    int checkPlayerOutGame = 0;
    for (NODE *k = l->pHead; count != 5; count++, k = k->pNext)
    {
        if (k->player.status == 1 || k->player.status == 5)
        {
            checkPlayerOutGame++;
            if (checkPlayerOutGame == 3) // 3 nguoi da false, thi con 1 nguoi choi --> WIN
            {
                return true;
            }
        }
    }
    return false;
}

// set lai status sau moi vong choi
void resetStatus(LIST *l)
{
    int count = 1;
    for (NODE *k = l->pHead; count != 5; count++, k = k->pNext)
    {
        k->player.status = 0;
    }
}
//

// set tien cho nguoi giai nhat
void addTienPot(LIST *l, int POT)
{
    NODE *winner = NULL;

    // if (checkCon1Player(l))
    // {
    //     // winner la thg cao nhat
    //     lastPlayer->player.soChipCuocBanDau += POT;
    //     gotoxy(57, 6);
    //     printf("                                                     ");
    //     gotoxy(57, 6);
    //     printf("WINNER: %s", lastPlayer->player.name);
    //     return;
    // }

    int count = 1;
    for (NODE *k = l->pHead; count != 5; count++, k = k->pNext)
    {
        if (k->player.status != 1)
        {
            winner = k; // tro vao thang dang choi
            lastPlayer = k;
        }
    }

    count = 1;
    for (NODE *k = l->pHead; count != 5; count++, k = k->pNext)
    {
        if (k->player.Level > winner->player.Level && k->player.status != 1)
            winner = k; // tro vao thang cao nhat
    }

    // winner la thg cao nhat
    winner->player.soChipCuocBanDau += POT;
    gotoxy(57, 6);
    printf("                                                     ");
    gotoxy(57, 6);
    printf("WINNER: %s", winner->player.name);
    delayTimeIn(7);

    // printf("\nNguoi thang la Player %d\n", winner->player.soThuTu);
    // printf("\tSo tien %d\n", winner->player.soChipCuocBanDau);
}
//

//

//

//

//

//

//

//[UNIT TEST]______________Kiem tra tu duy thuat toan co dung khong
// in dslk [UNIT TEST]
void printDslk(LIST l)
{
    int count = 0;
    for (NODE *k = l.pHead; count != 4; count++, k = k->pNext)
    {
        printf("Nguoi thu: %d\tSO CHIP: %d\tLA BAI: %c%c %c%c\n", k->player.soThuTu, k->player.soChipCuocBanDau, k->player.card[0].rank, k->player.card[0].suit, k->player.card[1].rank, k->player.card[1].suit);
    }
}
//

// in nhung la bai tren ban
void printLaBaiTrenBan(Card *baiTrenBan)
{
    printf("\nBai tren ban: %c%c %c%c %c%c %c%c %c%c\n", baiTrenBan[0].rank, baiTrenBan[0].suit, baiTrenBan[1].rank, baiTrenBan[1].suit, baiTrenBan[2].rank, baiTrenBan[2].suit, baiTrenBan[3].rank, baiTrenBan[3].suit, baiTrenBan[4].rank, baiTrenBan[4].suit);
}
//

// kiem tra nhung la bai ko trung nhau khi gen random bai
//  return T - la bai nay chua co trong bo bai
//  return F - la bai nay da xuat hien trong bo
bool checkLapLai(Card *BaiDaDuocMo, int nSize, char rank, char suit)
{
    for (int i = 0; i < nSize; i++)
    {
        if (rank == BaiDaDuocMo[i].rank && suit == BaiDaDuocMo[i].suit)
        {
            return false;
        }
    }
    return true;
}
//

// chia bai cho moi nguoi 2 la
void genRandomBoBai(LIST *l, Card *baiTrenBan)
{
    Card baiDaDuocMo[13];
    int size = 0;

    // chia bai cho tung nguoi trong dslk
    int count = 1;
    for (NODE *k = l->pHead; count != 5; count++, k = k->pNext)
    {
        for (int i = 0; i < 2;)
        {
            char rank = GetRank(genRandom(12, 0));
            char suit = GetSuit(genRandom(3, 0));
            if (checkLapLai(baiDaDuocMo, size, rank, suit))
            {
                k->player.card[i].rank = rank;
                k->player.card[i].suit = suit;
                baiDaDuocMo[size].rank = rank;
                baiDaDuocMo[size].suit = suit;
                size++;
                i++;
            }
        }
    }
    NODE *k = l->pHead;
    // chia 5 la tren ban
    for (int i = 0; i < 5;)
    {
        char rank = GetRank(genRandom(12, 0));
        char suit = GetSuit(genRandom(3, 0));
        if (checkLapLai(baiDaDuocMo, size, rank, suit))
        {
            baiTrenBan[i].rank = rank;
            baiTrenBan[i].suit = suit;
            baiDaDuocMo[size].rank = rank;
            baiDaDuocMo[size].suit = suit;
            size++;
            i++;
        }
    }
}
//

// in so tien cuoc sau 1 turn
void printfSoTienConLai(LIST *l)
{
    int count = 1;
    printf("So tien lan luot la: ");
    for (NODE *k = l->pHead; count != 5; k = k->pNext, count++)
    {
        printf("%d  ", k->player.soChipCuocBanDau);
    }
    printf("\n");
}
//

//
char GetRank(int rank)
{
    switch (rank)
    {
    case 0:
    {
        return 'A';
    }
    case 1:
    {
        return '2';
    }
    case 2:
    {
        return '3';
    }
    case 3:
    {
        return '4';
    }
    case 4:
    {
        return '5';
    }
    case 5:
    {
        return '6';
    }
    case 6:
    {
        return '7';
    }
    case 7:
    {
        return '8';
    }
    case 8:
    {
        return '9';
    }
    case 9:
    {
        return 'X';
    }
    case 10:
    {
        return 'J';
    }
    case 11:
    {
        return 'Q';
    }
    case 12:
    {
        return 'K';
    }
    }
}
//

//
char GetSuit(int suit)
{
    switch (suit)
    {
    case 0:
    {
        return '\x03';
    }
    case 1:
    {
        return '\x04';
    }
    case 2:
    {
        return '\x05';
    }
    case 3:
    {
        return '\x06';
    }
    }
}
//

// Chuyen doi gia tri card
int GanGiaTri(char bai)
{
    if (bai == 'A')
        return 1;
    if (bai == '2')
        return 2;
    if (bai == '3')
        return 3;
    if (bai == '4')
        return 4;
    if (bai == '5')
        return 5;
    if (bai == '6')
        return 6;
    if (bai == '7')
        return 7;
    if (bai == '8')
        return 8;
    if (bai == '9')
        return 9;
    if (bai == 'X')
        return 10;
    if (bai == 'J')
        return 11;
    if (bai == 'Q')
        return 12;
    if (bai == 'K')
        return 13;
    if (bai == '\x06')
        return 14;
    if (bai == '\x05')
        return 15;
    if (bai == '\x04')
        return 16;
    if (bai == '\x03')
        return 17;
}
//

// Check gia tri bo bai
void PokerHand(Card *baiTrenBan, LIST *l)
{
    int count = 1;
    for (NODE *k = l->pHead; count != 5; count++, k = k->pNext)
    {
        if (k->player.status == 1)
            continue;
        int setRank[10];
        int setSuit[10];
        int BaiLap[20];
        int dem = 0;
        bool Flush = false;
        bool Straight = false;
        bool OnePair = false;
        bool TwoPair = false;
        bool ThreeOfAKind = false;
        bool FourOfAKind = false;
        bool FULLHOUSE = false;
        int prev = 0;
        setRank[1] = GanGiaTri(k->player.card[1].rank);
        setSuit[0] = GanGiaTri(k->player.card[0].suit);
        setSuit[1] = GanGiaTri(k->player.card[1].suit);
        setRank[0] = GanGiaTri(k->player.card[0].rank);
        BaiLap[setRank[0]] = 1;
        BaiLap[setRank[1]] = 1;
        if (setRank[0] == setRank[1])
            BaiLap[setRank[0]]++;
        for (int i = 0; i < 5; i++)
        {
            setRank[i + 2] = GanGiaTri(baiTrenBan[i].rank);
            setSuit[i + 2] = GanGiaTri(baiTrenBan[i].suit);
        }
        // Check Pair
        for (int i = 2; i < 7; i++)
        {
            if (setRank[0] == setRank[i])
                BaiLap[setRank[0]]++;
            if (setRank[1] == setRank[i] && setRank[0] != setRank[1])
                BaiLap[setRank[1]]++;
            if (setRank[0] != setRank[1] && setRank[1] != setRank[i] && setRank[0] != setRank[i])
            {
                BaiLap[setRank[i]] = 1;
                for (int j = 2; j < 7; j++)
                {
                    if (i != j && setRank[i] == setRank[j])
                        BaiLap[setRank[i]]++;
                }
                if (BaiLap[setRank[i]] == 4)
                    FourOfAKind = true;
                if (BaiLap[setRank[i]] == 3)
                    ThreeOfAKind = true;
                if (BaiLap[setRank[i]] == 2 && setRank[i] != prev)
                {
                    dem++;
                    prev = setRank[i];
                }
                if (BaiLap[setRank[i]] > 1)
                    BaiLap[setRank[i]] = 1;
            }
        }
        // printf("\t Player %d: %d %d %d\n", k->player.soThuTu,BaiLap[setRank[0]],BaiLap[setRank[1]],dem);
        if (BaiLap[setRank[0]] == 4 || BaiLap[setRank[1]] == 4)
            FourOfAKind = true;
        if (BaiLap[setRank[0]] == 3 || BaiLap[setRank[1]] == 3)
            ThreeOfAKind = true;

        if ((BaiLap[setRank[0]] == 2 && BaiLap[setRank[1]] == 2 && setRank[0] != setRank[1]) || dem == 2 || ((BaiLap[setRank[0]] == 2 || BaiLap[setRank[1]] == 2) && dem == 1))
            TwoPair = true;
        else if (BaiLap[setRank[0]] == 2 || BaiLap[setRank[1]] == 2 || (dem >= 1 && setRank[0] != setRank[1]))
            OnePair = true;
        // Check Flush
        for (int i = 0; i < 7; i++)
        {
            dem = 1;
            for (int j = 0; j < 7; j++)
            {
                if (i != j && setSuit[i] == setSuit[j])
                    dem++;
            }
            if (dem >= 5)
            {
                Flush = true;
                break;
            }
        }
        // Check Straight
        dem = 0;
        int c = 0;
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (setRank[j] < setRank[j + 1])
                {
                    int temp = setRank[j];
                    setRank[j] = setRank[j + 1];
                    setRank[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < 6; i++)
        {
            if (setRank[i + 1] == setRank[i] - 1)
            {
                for (int j = i; j < 6; j++)
                {
                    if (setRank[j + 1] == setRank[j])
                    {
                        dem = 0;
                        break;
                    }
                    if (setRank[j + 1] != setRank[j] - 1 && setRank[j + 1] != setRank[j] && j > 2)
                    {
                        c = 1;
                        break;
                    }
                    else
                        dem++;
                }
                if (c == 0)
                    break;
                else if (i > 2)
                {
                    c = 1;
                    break;
                }
            }
        }
        if (c == 0 && dem >= 4)
        {
            Straight = true;
        }
        // Check FullHouse
        c = 0;
        int d = 0;
        dem = 1;
        int max;
        for (int i = 0; i < 6; i++)
        {
            if (setRank[i + 1] == setRank[i])
            {
                for (int j = i; j < 6; j++)
                {
                    if (setRank[j] == setRank[j + 1])
                    {
                        dem++;
                    }
                    else
                    {
                        max = j;
                        break;
                    }
                }
            }
            if (dem == 3)
                c = 1;
            if (dem == 2)
                d = 1;
            if (i < max)
                continue;
            dem = 1;
        }
        if (c == 1 && d == 1)
        {
            FULLHOUSE = true;
        }
        // Conclusion
        if (Straight == true && Flush == true)
        {
            k->player.Level = 8;
            // printf("\t player %d : STRAIGHT FLUSH\n", k->player.soThuTu);
        }
        else if (FourOfAKind)
        {
            k->player.Level = 7;
            // printf("\t player %d : Four of a kind\n", k->player.soThuTu);
        }
        else if (FULLHOUSE)
        {
            k->player.Level = 6;
            // printf("\t player %d : FullHouse\n", k->player.soThuTu);
        }
        else if (Flush)
        {
            k->player.Level = 5;
            // printf("\t player %d : FLUSH\n", k->player.soThuTu);
        }
        else if (Straight)
        {
            k->player.Level = 4;
            // printf("\t player %d : STRAIGHT\n", k->player.soThuTu);
        }
        else if (ThreeOfAKind)
        {
            k->player.Level = 3;
            // printf("\t player %d : Three of a kind\n", k->player.soThuTu);
        }
        else if (TwoPair)
        {
            k->player.Level = 2;
            // printf("\t player %d : Two pair\n", k->player.soThuTu);
        }
        else if (OnePair)
        {
            k->player.Level = 1;
            // printf("\t player %d : One pair\n", k->player.soThuTu);
        }
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

//

//

// playing
void playingGame()
{
    srand((unsigned int)time(NULL));

    // tao 1 danh sach hinh tron cac players
    LIST l;
    LISTq q;
    khoiTaoDslk(&l); // ket noi cac players thanh 1 vong tron

    // tim dealer 1 lan
    int Dealer = genRandom(4, 1);

    do // choi luot ke tiep
    {
        lastPlayer = NULL;
        UI_inGame();

        if (listAcc[indexOfPlayer].tien < 100) // ko du tien
        {
            char hetTien[20] = "Ban khong du tien";
            printfNoti(hetTien);
            printfMyChip(listAcc[indexOfPlayer].tien);
            delayTimeIn(20);
            saveInfor();
            gotoxy(0, 50);
            system("pause");
            break;
        }

        // in chip cua minh
        printfMyChip(listAcc[indexOfPlayer].tien);
        //

        khoiTaoQueue(&q); // reset vong cuoc, [QUEN CHUA GIAI PHONG]
        resetStatus(&l);

        //
        Card baiTrenBan[5]; // mang luu nhung la bai tren ban
        //

        // chia bai cho 4 players, tren Ban
        genRandomBoBai(&l, baiTrenBan);

        int POT = 0;

        nhapSoChipCuoc(&l); // gan so chip cuoc cho cac player, moi nguoi 100

        // printf("\n\nDealer la nguoi so: %d\n", Dealer);
        timDealerVaSetTurn(&l, Dealer);
        // stt 1 la SB
        // stt 2 la BB
        // stt 4 la Dealer
        // printf("\n");
        // printDslk(l);
        // printLaBaiTrenBan(baiTrenBan);
        // printf("\nPOT: %d\n", POT);

        //******************* THE PRE-FLOP, BET bat dau tu SB va BB, Chia bai, BB.next tha cuoc
        minOfBet = 0;
        // printf("\nBat dau vong Pre-flop\n");
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("Bat dau vong Pre-Flop");
        delayTimeIn(5);
        pre_Flop(&l, &POT, baiTrenBan, &q);
        printfPOT(POT);

        if (lastPlayer != NULL)
            goto label;

        //[UNIT TEST]
        // printfSoTienConLai(&l);

        //******************* THE FLOP, mo 3 la, BET *******************
        khoiTaoQueue(&q); // reset vong cuoc, [QUEN CHUA GIAI PHONG]
        // printf("\nMo 3 la bai: %c%c  %c%c  %c%c", baiTrenBan[0].rank, baiTrenBan[0].suit, baiTrenBan[1].rank, baiTrenBan[1].suit, baiTrenBan[2].rank, baiTrenBan[2].suit);
        // printf("\n\nBat dau vong Flop\n");
        printfLa_1(baiTrenBan[0].rank, baiTrenBan[0].suit);
        printfLa_2(baiTrenBan[1].rank, baiTrenBan[1].suit);
        printfLa_3(baiTrenBan[2].rank, baiTrenBan[2].suit);
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("Bat dau vong Flop");
        delayTimeIn(5);
        Flop(&l, &POT, baiTrenBan, &q);
        printfPOT(POT);

        if (lastPlayer != NULL)
            goto label;
        //[UNIT TEST]
        // printfSoTienConLai(&l);

        //******************* THE TURN, mo la 4, BET *******************
        khoiTaoQueue(&q); // reset vong cuoc, [QUEN CHUA GIAI PHONG]
        // printf("\nMo 4 la bai: %c%c  %c%c  %c%c  %c%c", baiTrenBan[0].rank, baiTrenBan[0].suit, baiTrenBan[1].rank, baiTrenBan[1].suit, baiTrenBan[2].rank, baiTrenBan[2].suit, baiTrenBan[3].rank, baiTrenBan[3].suit);
        // printf("\n\nBat dau vong Turn\n");
        printfLa_4(baiTrenBan[3].rank, baiTrenBan[3].suit);
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("Bat dau vong Turn");
        delayTimeIn(5);
        Turn(&l, &POT, baiTrenBan, &q);
        printfPOT(POT);

        if (lastPlayer != NULL)
            goto label;
        //[UNIT TEST]
        // printfSoTienConLai(&l);

        //******************* THE RIVER, mo la 5, BET *******************
        khoiTaoQueue(&q); // reset vong cuoc, [QUEN CHUA GIAI PHONG]
        // printf("\nMo 5 la bai: %c%c  %c%c  %c%c  %c%c  %c%c", baiTrenBan[0].rank, baiTrenBan[0].suit, baiTrenBan[1].rank, baiTrenBan[1].suit, baiTrenBan[2].rank, baiTrenBan[2].suit, baiTrenBan[3].rank, baiTrenBan[3].suit, baiTrenBan[4].rank, baiTrenBan[4].suit);
        // printf("\n\nBat dau vong River\n");
        printfLa_5(baiTrenBan[4].rank, baiTrenBan[4].suit);
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("Bat dau vong River");
        delayTimeIn(5);
        River(&l, &POT, baiTrenBan, &q);
        printfPOT(POT);

        if (lastPlayer != NULL)
            goto label;
        //[UNIT TEST]
        // printfSoTienConLai(&l);

        // ******************* SHOWDOWN, hien thi la bai nhung nguoi con lai, mang di so sanh
        // printf("\n\nSo sanh la bai\n\n");
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("-> SHOWDOWN");
        //

        delayTimeIn(5);

        // show bai cac players
        int count = 1;
        for (NODE *k = l.pHead; count != 5; k = k->pNext, count++)
        {
            printfBaiCuaPlayer(k->player.card[0].rank,
                               k->player.card[0].suit,
                               k->player.card[1].rank,
                               k->player.card[1].suit,
                               k->player.soThuTu);
        }
        //
        // show card in tb

        //
        delayTimeIn(10);
        //

        //
        PokerHand(baiTrenBan, &l);
        //

        //
        addTienPot(&l, POT);
        //
    label:
        //

        Dealer--; // neu Dealer = 4, cuoi vong, thi set lai tu 1
        if (Dealer == 0)
        {
            Dealer = 4;
        }

        // cap nhat tien nguoi choi
        listAcc[indexOfPlayer].tien = listAcc[indexOfPlayer].tien - (100 - l.pHead->player.soChipCuocBanDau);
        //

        delayTimeIn(5);

        saveInfor();
        // printLoading();
        // system("pause");
        // system("cls");
        gotoxy(57, 6);
        printf("                                                     ");
        gotoxy(57, 6);
        printf("[1].Thoat   [2].Tiep tuc");

        char pickk;
        while (true)
        {
            gotoxy(0, 50);
            pickk = getchar();
            getchar();
            if (pickk == '1' || pickk == '2')
                break;
        }

        if (pickk == '1')
        {
            printLoading();
            break;
        }

        delayTimeIn(5);

    } while (true);

    gotoxy(0, 50);
    system("pause");
}
//

//

//

//

//

//

//

// ---------------------------------login_signup_failed---------------------------------
//  MAIN
void loginOrSignup()
{
    readDataFromFile();
    // printInforInFile();

    // printf("[Q]. dang nhap   [W]. dang ki\n");
    char pick;

    while (true)
    {
        gotoxy(0, 50);
        printf("                   ");

        gotoxy(0, 50);
        pick = getchar();

        if (pick >= 97 && pick <= 122)
            pick -= 32;
        if (pick == 'Q' || pick == 'W')
            break;
    }

    if (pick == 'Q')
    {
        pressLogin();
    }
    else if (pick == 'W')
    {
        UI_signUp();
        pressSignUp();
    }
}
//

// doc data tu file roi luu vao mang account
// "data.txt"
void readDataFromFile()
{
    char read[200][80];
    FILE *fr = fopen("data.txt", "r");

    int i = 0;
    while (true)
    {
        fgets(read[i], 80, fr);
        if (strlen(read[i]) == 0) // doc het thi dung
            break;
        sscanf(read[i], "%s %s %s %d", listAcc[i].taiKhoan, listAcc[i].matKhau, listAcc[i].name, &(listAcc[i].tien));
        i++;
    }
    count = i;
    fclose(fr);
}
//

//[UNIT TEST] in thong tin doc duoc tu trong file
void printInforInFile()
{
    for (int i = 0; i < count; i++)
    {
        printf("%s_and_%s_and_%s_and_%d\n", listAcc[i].taiKhoan, listAcc[i].matKhau, listAcc[i].name, listAcc[i].tien);
    }
}
//

// neu an login
void pressLogin()
{
    getchar();
    char taiKhoanInput[20];
    char matKhauInput[20];

    while (true)
    {
        // printf("\nnhap tai khoan roi mat khau: ");
        gotoxy(72, 16);
        printf("                                 ");
        gotoxy(72, 20);
        printf("                                 ");

        gotoxy(72, 16);
        gets(taiKhoanInput);
        gotoxy(72, 20);
        gets(matKhauInput);
        if (checkTaiKhoanMatKhau(taiKhoanInput, matKhauInput) && checkFormatInput(taiKhoanInput) && checkFormatInput(matKhauInput)) // neu ton tai va dung dinh dang
            break;
    }

    // neu dung thi ket thuc, chuyen qua menu
}
//

// neu an signup
void pressSignUp()
{
    getchar();
    char taiKhoanInput[20];
    char matKhauInput[20];
    char nameInput[30];

    while (true)
    {
        gotoxy(72, 16);
        printf("                                 ");
        gotoxy(72, 20);
        printf("                                 ");
        gotoxy(72, 24);
        printf("                                 ");

        gotoxy(72, 16);
        gets(nameInput);
        gotoxy(72, 20);
        gets(taiKhoanInput);
        gotoxy(72, 24);
        gets(matKhauInput);

        if (checkTaiKhoan(taiKhoanInput) && checkFormatInput(nameInput) && checkFormatInput(taiKhoanInput) && checkFormatInput(matKhauInput)) // neu ton tai va dung dinh dang
            break;
    }

    // them thong tin user vao cuoi danh sach
    strcpy(listAcc[count].taiKhoan, taiKhoanInput);
    strcpy(listAcc[count].matKhau, matKhauInput);
    strcpy(listAcc[count].name, nameInput);
    listAcc[count].tien = 1000;
    indexOfPlayer = count;
    count++;
    saveInfor();

    // neu dung thi ket thuc, chuyen qua menu
}
//

// luu toan bo thong tin vao file "data.txt"
void saveInfor()
{
    FILE *fw = fopen("data.txt", "w");

    for (int i = 0; i < count; i++)
    {
        fprintf(fw, "%s %s %s %d\n", listAcc[i].taiKhoan, listAcc[i].matKhau, listAcc[i].name, listAcc[i].tien);
    }

    fclose(fw);
}
//

// kiem tra tai khoan, mat khau co dung trong data khong [DUNG CHO LOGIN]
//  co -> T
//  khong -> F
bool checkTaiKhoanMatKhau(char *taiKhoanInput, char *matKhauInput)
{
    for (int i = 0; i < count; i++)
    {
        if (check2Chuoi(listAcc[i].taiKhoan, taiKhoanInput) && check2Chuoi(listAcc[i].matKhau, matKhauInput))
        {
            indexOfPlayer = i;
            return true;
        }
    }
    return false;
}
//

// kiem tra tai khoan da ton tai trong data khong [DUNG CHO SIGN UP]
//  co -> F
//  khong -> T
bool checkTaiKhoan(char *taiKhoanInput)
{
    for (int i = 0; i < count; i++)
    {
        if (check2Chuoi(listAcc[i].taiKhoan, taiKhoanInput))
            return false;
    }
    return true;
}
//

// check 2 chuoi giong nhau
// giong -> T
// khac -> F
bool check2Chuoi(char *s1, char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // neu do dai khac nhau -> khac
    if (len1 != len2)
        return false;
    // neu do dai giong nhau, thi so tung ki tu
    else
    {
        for (int i = 0; i < len1; i++)
        {
            if (s1[i] != s2[i])
                return false;
        }
        return true;
    }
}
//

// kiem tra dinh dang 1 chuoi, xem co thoa man khong
// khong co spcae, ki tu dac biet, do dai >=6 va <=18
// thoa man -> T
// sai dinh dang -> F
bool checkFormatInput(char *str)
{
    int len = strlen(str);
    if (len < 6 || len > 18) // check do dai
        return false;
    // check space, ki tu dac biet
    for (int i = 0; i < len; i++)
    {
        if (str[i] < 48 || (str[i] > 57 && str[i] < 65) || (str[i] > 90 && str[i] < 97) || str[i] > 122)
            return false;
    }
    return true;
}
//
//

//

//

//

//

//

#endif
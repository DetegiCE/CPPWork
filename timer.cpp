#include<stdio.h>
#include<iostream>

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define BACKSPACE 8
#define LEFT 75 //방향키
#define RIGHT 77 //방향키
#define UP 72 //방향키
#define DOWN 80 //방향키
#define ESC 27 // 나가기
#define ENTER 13 // 게임시작
#define SHIFT 16
#define CTRL 17
#define AKEY 97 // 63번 색 : 머리
#define BKEY 98 // 31번 색 : 머리
#define CKEY 99 // 컬러설정
#define DKEY 100 // 207번 색 : 프레임
#define EKEY 101 // 143번 색
#define FKEY 102 // 111번 색 : 머리
#define GKEY 103 // 47번 색 : 머리
#define HKEY 104 // 191번 색 : 프레임
#define IKEY 105 // 175번 색 : 프레임
#define JKEY 106
#define KKEY 107 // 127번 색 : 머리
#define LKEY 108 // 159번 색 : 프레임
#define MKEY 109 // MIDDLE
#define NKEY 110 // 223번 색 : 프레임
#define OKEY 111 // HARD
#define PKEY 112 // 95번 색 : 머리
#define QKEY 113 // 하드코어
#define RKEY 114 // 79번 색 : 머리
#define SKEY 115 //개발자 도구
#define TKEY 116 //Reset
#define UKEY 117 //DEV BLOG
#define VKEY 118 // No Head Mode
#define WKEY 119 // 239번 색 : 프레임
#define XKEY 120 // 다시 타이틀로
#define YKEY 121 // SMALL
#define ZKEY 122 // 255번 색 : 프레임
#define SEMICOLON 59 // 점수추가
#define EQUAL 61
#define COMMA 44
#define MINUS 45
#define DOT 46 // 어치브먼트
#define SLASH 47
#define APHOSTROPHEE 96
#define LEFTBRACKET 91 // 속도 감소
#define BACKSLASH 92
#define RIGHTBRACKET 93 // 속도 증가
#define QUOTATION 39
#define LIMIT1 300
#define LIMIT2 500
#define LIMIT3 800
#define LIMIT4 1200
#define LIMIT5 1700

#define ACH_NUM 6

#define MAP_ADJ_X 2
#define MAP_ADJ_Y 2

#define BLANK printf("  ")

int key=0;
int input_hour1;
int input_hour2;
int input_min1;
int input_min2;
int input_sec1;
int input_sec2;

int hour;
int minute;
int second;
int key2=0;

int color_border=255;

int totalsecond;

int color(int color_number)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
}

void cursorhide()
{
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void gotoxy(int x,int y)   //x값을 2x로 변경, 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입
{
    COORD pos= {2*x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void digitals(int type,int x,int y)
{
    /*   <Type>
    *   ---1---
    *   2     3
    *   ---4---
    *   5     6
    *   ---7---
    */
    int i;
    if(type==1){
        gotoxy(x,y);
        for(i=1 ; i<=5 ; i++) BLANK;
    }
    else if(type==2){
        for(i=1 ; i<=5 ; i++){
            gotoxy(x,y+i-1);
            BLANK;
        }
    }
    else if(type==3){
        for(i=1 ; i<=5 ; i++){
            gotoxy(x+4,y+i-1);
            BLANK;
        }
    }
    else if(type==4){
        gotoxy(x,y+4);
        for(i=1 ; i<=5 ; i++) BLANK;
    }
    else if(type==5){
        for(i=1 ; i<=5 ; i++){
            gotoxy(x,y+i+3);
            BLANK;
        }
    }
    else if(type==6){
        for(i=1 ; i<=5 ; i++){
            gotoxy(x+4,y+i+3);
            BLANK;
        }
    }
    else if(type==7){
        gotoxy(x,y+8);
        for(i=1 ; i<=5 ; i++) BLANK;
    }
}

void number(int num,int x,int y)
{
    int i;
    color(255);
    if(num==0){
        digitals(1,x,y);
        digitals(2,x,y);
        digitals(3,x,y);
        digitals(5,x,y);
        digitals(6,x,y);
        digitals(7,x,y);
    }
    else if(num==1){
        digitals(3,x,y);
        digitals(6,x,y);
    }
    else if(num==2){
        digitals(1,x,y);
        digitals(3,x,y);
        digitals(4,x,y);
        digitals(5,x,y);
        digitals(7,x,y);
    }
    else if(num==3){
        digitals(1,x,y);
        digitals(3,x,y);
        digitals(4,x,y);
        digitals(6,x,y);
        digitals(7,x,y);
    }
    else if(num==4){
        digitals(2,x,y);
        digitals(3,x,y);
        digitals(4,x,y);
        digitals(6,x,y);
    }
    else if(num==5){
        digitals(1,x,y);
        digitals(2,x,y);
        digitals(4,x,y);
        digitals(6,x,y);
        digitals(7,x,y);
    }
    else if(num==6){
        digitals(1,x,y);
        digitals(2,x,y);
        digitals(4,x,y);
        digitals(5,x,y);
        digitals(6,x,y);
        digitals(7,x,y);
    }
    else if(num==7){
        digitals(1,x,y);
        digitals(3,x,y);
        digitals(6,x,y);
    }
    else if(num==8){
        for(i=1 ; i<=7 ; i++) digitals(i,x,y);
    }
    else if(num==9){
        for(i=1 ; i<=7 ; i++){
            if(i==5) continue;
            digitals(i,x,y);
        }
    }
}

void border()
{
    int i;
    color(color_border);
    gotoxy(1,1);
    for(i=0 ; i<=42 ; i++)
        BLANK;
    gotoxy(1,13);
    for(i=0 ; i<=42 ; i++)
        BLANK;
    for(i=1 ; i<=13 ; i++){
        gotoxy(1,i);
        BLANK;
    }
    for(i=1 ; i<=13 ; i++){
        gotoxy(43,i);
        BLANK;
    }
    gotoxy(12,18);
    color(15);
    printf("Copyright (c) 2016 by DetegiCE (blog.TeamCE.kr)");
    gotoxy(12,19);
    printf("Made by GSA 3G : 16-017 (ver1.2 : 2017.01.05.)");
    gotoxy(12,20);
    printf("Contact : martinok1103@naver.com / ceo@teamce.kr");
}

void start_page()
{
    int i;
    color(176);
    gotoxy(3,3);
    for(i=1 ; i<=7 ; i++) BLANK;
    for(i=1 ; i<=8 ; i++){
        gotoxy(6,3+i);
        BLANK;
    }

    gotoxy(11,3);
    for(i=1 ; i<=7 ; i++) BLANK;
    for(i=1 ; i<=7 ; i++){
        gotoxy(14,3+i);
        BLANK;
    }
    gotoxy(11,11);
    for(i=1 ; i<=7 ; i++) BLANK;

    for(i=1 ; i<=9 ; i++){
        gotoxy(19,2+i);
        BLANK;
        gotoxy(25,2+i);
        BLANK;
    }
    gotoxy(20,4); BLANK;
    gotoxy(21,5); BLANK;
    gotoxy(22,6); BLANK;
    gotoxy(23,5); BLANK;
    gotoxy(24,4); BLANK;

    for(i=1 ; i<=9 ; i++){
        gotoxy(27,2+i);
        BLANK;
    }
    gotoxy(28,3);
    for(i=1 ; i<=6 ; i++) BLANK;
    gotoxy(28,7);
    for(i=1 ; i<=5 ; i++) BLANK;
    gotoxy(28,11);
    for(i=1 ; i<=6 ; i++) BLANK;

    for(i=1 ; i<=9 ; i++){
        gotoxy(35,2+i);
        BLANK;
    }
    gotoxy(36,3);
    for(i=1 ; i<=5 ; i++) BLANK;
    gotoxy(36,7);
    for(i=1 ; i<=5 ; i++) BLANK;
    for(i=1 ; i<=8 ; i++){
        gotoxy(41,3+i);
        if(i==4) continue;
        BLANK;
    }

    gotoxy(12,15);
    color(11);
    printf("Press \"S\" to Start / Press \"C\" to set Color");



}

void time_set_hour()
{
    int i,j;
    system("cls");
    border();
    color(112);

    for(i=1 ; i<=9 ; i++){
        gotoxy(3,2+i);
        BLANK;
        gotoxy(7,2+i);
        BLANK;
    }
    gotoxy(4,7);
    for(i=1 ; i<=3 ; i++) BLANK;
    gotoxy(9,5); BLANK;
    gotoxy(9,9); BLANK;
    gotoxy(16,15);
    color(15);
    printf("Type Two Digits of Hour and Wait (00~23)");

    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case 48:
            number(0,11,3);
            key=0;
            input_hour1=999;
            break;
        case 49:
            number(1,11,3);
            key=0;
            input_hour1=1;
            break;
        case 50:
            number(2,11,3);
            key=0;
            input_hour1=2;
            break;
        case 51:
            number(3,11,3);
            key=0;
            input_hour1=3;
            break;
        case 52:
            number(4,11,3);
            key=0;
            input_hour1=4;
            break;
        case 53:
            number(5,11,3);
            key=0;
            input_hour1=5;
            break;
        case 54:
            number(6,11,3);
            key=0;
            input_hour1=6;
            break;
        case 55:
            number(7,11,3);
            key=0;
            input_hour1=7;
            break;
        case 56:
            number(8,11,3);
            key=0;
            input_hour1=8;
            break;
        case 57:
            number(9,11,3);
            key=0;
            input_hour1=9;
            break;
        default:
            break;
        }
        if(input_hour1>0) break;
    }
    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case 48:
            number(0,17,3);
            key=0;
            input_hour2=998;
            break;
        case 49:
            number(1,17,3);
            key=0;
            input_hour2=1;
            break;
        case 50:
            number(2,17,3);
            key=0;
            input_hour2=2;
            break;
        case 51:
            number(3,17,3);
            key=0;
            input_hour2=3;
            break;
        case 52:
            number(4,17,3);
            key=0;
            input_hour2=4;
            break;
        case 53:
            number(5,17,3);
            key=0;
            input_hour2=5;
            break;
        case 54:
            number(6,17,3);
            key=0;
            input_hour2=6;
            break;
        case 55:
            number(7,17,3);
            key=0;
            input_hour2=7;
            break;
        case 56:
            number(8,17,3);
            key=0;
            input_hour2=8;
            break;
        case 57:
            number(9,17,3);
            key=0;
            input_hour2=9;
            break;
        default:
            break;
        }
        if(input_hour2>0) break;
    }
    if(input_hour1==999 && input_hour2==998){
        hour=0;
    }
    else if(input_hour1==999){
        hour=input_hour2;
    }
    else if(input_hour2==998){
        hour=input_hour1*10;
    }
    else{
        hour=input_hour1*10+input_hour2;
    }
    gotoxy(0,15);
}

void time_set_minute()
{
    int i,j;
    system("cls");
    border();
    color(112);

    for(i=1 ; i<=9 ; i++){
        gotoxy(3,2+i);
        BLANK;
        gotoxy(7,2+i);
        BLANK;
    }
    gotoxy(4,4); BLANK;
    gotoxy(5,5); BLANK;
    gotoxy(6,4); BLANK;
    gotoxy(9,5); BLANK;
    gotoxy(9,9); BLANK;
    gotoxy(16,15);
    color(15);
    printf("Type Two Digits of Minute and Wait (00~59)");
    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case 48:
            number(0,11,3);
            key=0;
            input_min1=999;
            break;
        case 49:
            number(1,11,3);
            key=0;
            input_min1=1;
            break;
        case 50:
            number(2,11,3);
            key=0;
            input_min1=2;
            break;
        case 51:
            number(3,11,3);
            key=0;
            input_min1=3;
            break;
        case 52:
            number(4,11,3);
            key=0;
            input_min1=4;
            break;
        case 53:
            number(5,11,3);
            key=0;
            input_min1=5;
            break;
        case 54:
            number(6,11,3);
            key=0;
            input_min1=6;
            break;
        case 55:
            number(7,11,3);
            key=0;
            input_min1=7;
            break;
        case 56:
            number(8,11,3);
            key=0;
            input_min1=8;
            break;
        case 57:
            number(9,11,3);
            key=0;
            input_min1=9;
            break;
        default:
            break;
        }
        if(input_min1>0) break;
    }
    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case 48:
            number(0,17,3);
            key=0;
            input_min2=998;
            break;
        case 49:
            number(1,17,3);
            key=0;
            input_min2=1;
            break;
        case 50:
            number(2,17,3);
            key=0;
            input_min2=2;
            break;
        case 51:
            number(3,17,3);
            key=0;
            input_min2=3;
            break;
        case 52:
            number(4,17,3);
            key=0;
            input_min2=4;
            break;
        case 53:
            number(5,17,3);
            key=0;
            input_min2=5;
            break;
        case 54:
            number(6,17,3);
            key=0;
            input_min2=6;
            break;
        case 55:
            number(7,17,3);
            key=0;
            input_min2=7;
            break;
        case 56:
            number(8,17,3);
            key=0;
            input_min2=8;
            break;
        case 57:
            number(9,17,3);
            key=0;
            input_min2=9;
            break;
        default:
            break;
        }
        if(input_min2>0) break;
    }
    if(input_min1==999 && input_min2==998){
        minute=0;
    }
    else if(input_min1==999){
        minute=input_min2;
    }
    else if(input_min2==998){
        minute=input_min1*10;
    }
    else{
        minute=input_min1*10+input_min2;
    }
    gotoxy(0,15);

}

void time_set_second()
{
    int i,j;
    system("cls");
    border();
    color(112);

    gotoxy(4,3); BLANK;BLANK;BLANK;
    gotoxy(7,4); BLANK;
    gotoxy(3,4); BLANK;
    gotoxy(3,5); BLANK;
    gotoxy(3,6); BLANK;
    gotoxy(4,7); BLANK;BLANK;BLANK;
    gotoxy(7,8); BLANK;
    gotoxy(7,9); BLANK;
    gotoxy(7,10); BLANK;
    gotoxy(3,10); BLANK;
    gotoxy(4,11); BLANK;BLANK;BLANK;


    gotoxy(9,5); BLANK;
    gotoxy(9,9); BLANK;
    gotoxy(16,15);
    color(15);
    printf("Type Two Digits of Second and Wait (00~59)");
    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case 48:
            number(0,11,3);
            key=0;
            input_sec1=999;
            break;
        case 49:
            number(1,11,3);
            key=0;
            input_sec1=1;
            break;
        case 50:
            number(2,11,3);
            key=0;
            input_sec1=2;
            break;
        case 51:
            number(3,11,3);
            key=0;
            input_sec1=3;
            break;
        case 52:
            number(4,11,3);
            key=0;
            input_sec1=4;
            break;
        case 53:
            number(5,11,3);
            key=0;
            input_sec1=5;
            break;
        case 54:
            number(6,11,3);
            key=0;
            input_sec1=6;
            break;
        case 55:
            number(7,11,3);
            key=0;
            input_sec1=7;
            break;
        case 56:
            number(8,11,3);
            key=0;
            input_sec1=8;
            break;
        case 57:
            number(9,11,3);
            key=0;
            input_sec1=9;
            break;
        default:
            break;
        }
        if(input_sec1>0) break;
    }
    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case 48:
            number(0,17,3);
            key=0;
            input_sec2=998;
            break;
        case 49:
            number(1,17,3);
            key=0;
            input_sec2=1;
            break;
        case 50:
            number(2,17,3);
            key=0;
            input_sec2=2;
            break;
        case 51:
            number(3,17,3);
            key=0;
            input_sec2=3;
            break;
        case 52:
            number(4,17,3);
            key=0;
            input_sec2=4;
            break;
        case 53:
            number(5,17,3);
            key=0;
            input_sec2=5;
            break;
        case 54:
            number(6,17,3);
            key=0;
            input_sec2=6;
            break;
        case 55:
            number(7,17,3);
            key=0;
            input_sec2=7;
            break;
        case 56:
            number(8,17,3);
            key=0;
            input_sec2=8;
            break;
        case 57:
            number(9,17,3);
            key=0;
            input_sec2=9;
            break;
        default:
            break;
        }
        if(input_sec2>0) break;
    }
    if(input_sec1==999 && input_sec2==998){
        second=0;
    }
    else if(input_sec1==999){
        second=input_sec2;
    }
    else if(input_sec2==998){
        second=input_sec1*10;
    }
    else{
        second=input_sec1*10+input_sec2;
    }
    gotoxy(0,15);

}

void color_set()
{
    int i,t=0;
    int key3;
    system("cls");
    border();
    gotoxy(3,3);
    color(14);
    printf("Color Setting : ");
    color(15);
    printf("Type the code that you want to set the border of timer.");
    gotoxy(4,4);
    printf("Color Code : ");
    for(i=1 ; i<=15 ; i++){
        color(i);
        printf(" %X ",i);
    }
    t=0;
    while(1){
        if(kbhit())
        do{
            key3=getch();
        }while(key3==224);
        switch(key3){
        case 49:
            t=1;
            key3=0;
            break;
        case 50:
            t=2;
            key3=0;
            break;
        case 51:
            t=3;
            key3=0;
            break;
        case 52:
            t=4;
            key3=0;
            break;
        case 53:
            t=5;
            key3=0;
            break;
        case 54:
            t=6;
            key3=0;
            break;
        case 55:
            t=7;
            key3=0;
            break;
        case 56:
            t=8;
            key3=0;
            break;
        case 57:
            t=9;
            key3=0;
            break;
        case AKEY:
            t=10;
            key3=0;
            break;
        case BKEY:
            t=11;
            key3=0;
            break;
        case CKEY:
            t=12;
            key3=0;
            break;
        case DKEY:
            t=13;
            key3=0;
            break;
        case EKEY:
            t=14;
            key3=0;
            break;
        case FKEY:
            t=15;
            key3=0;
            break;

        }
        if(t>=1 && t<=15) break;
    }
    color_border=(t+1)*16-1;
    gotoxy(0,15);
}

void resetz()
{
    key=0;
    input_hour1=0;
    input_hour2=0;
    input_min1=0;
    input_min2=0;
    input_sec1=0;
    input_sec2=0;
    hour=0;
    minute=0;
    second=0;
    key2=0;
    totalsecond=0;
}

int main()
{
    int i;
    int scmplt=0;
    again:
    resetz();
    system("cls");
    system("mode con: lines=30 cols=90");
    border();
    color(15);
    start_page();
    color(15);
    gotoxy(0,15);

    scmplt=0;
    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case SKEY:
            time_set_hour();
            color(15);
            Sleep(500);
            time_set_minute();
            color(15);
            Sleep(500);
            time_set_second();
            Sleep(500);
            scmplt=1;
            key=0;
            break;

        case CKEY:
            color_set();
            scmplt=1;
            key=0;
            goto again;
            break;
        }
        if(scmplt==1) break;
    }
    color(15);

    if(hour>=23) hour=23;
    if(minute>=59) minute=59;
    if(second>=59) second=59;

    gotoxy(0,20);
    totalsecond=second+minute*60+hour*3600;

    system("cls");

    int timer_hour_ten;
    int timer_hour_one;
    int timer_min_ten;
    int timer_min_one;
    int timer_sec_ten;
    int timer_sec_one;
    int save;

    save=totalsecond;

    timer_sec_one=second%10;
    timer_sec_ten=second/10;
    timer_min_one=minute%10;
    timer_min_ten=minute/10;
    timer_hour_one=hour%10;
    timer_hour_ten=hour/10;


    border();
    number(timer_hour_ten,3,3);
    number(timer_hour_one,9,3);
    gotoxy(15,5); BLANK;
    gotoxy(15,9); BLANK;
    number(timer_min_ten,17,3);
    number(timer_min_one,23,3);
    gotoxy(29,5); BLANK;
    gotoxy(29,9); BLANK;
    number(timer_sec_ten,31,3);
    number(timer_sec_one,37,3);

    gotoxy(1,15);
    color(15);
    printf("START : S   STOP : T   RESET : R");

    int stopstart=0;

    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case SKEY:
            totalsecond--;
            system("cls");
            gotoxy(0,20);
            timer_sec_one=totalsecond%10;
            timer_sec_ten=(totalsecond%60)/10;
            timer_min_one=(((totalsecond-(totalsecond%60))%3600)/60)%10;
            timer_min_ten=(((totalsecond-(totalsecond%60))%3600)/60)/10;
            timer_hour_one=((totalsecond-(totalsecond%3600))/3600)%10;
            timer_hour_ten=((totalsecond-(totalsecond%3600))/3600)/10;
            border();
            number(timer_hour_ten,3,3);
            number(timer_hour_one,9,3);
            gotoxy(15,5); BLANK;
            gotoxy(15,9); BLANK;
            number(timer_min_ten,17,3);
            number(timer_min_one,23,3);
            gotoxy(29,5); BLANK;
            gotoxy(29,9); BLANK;
            number(timer_sec_ten,31,3);
            number(timer_sec_one,37,3);

            gotoxy(1,15);
            color(15);
            printf("START : S   STOP : T   RESET : R");
            break;
        case TKEY:
            gotoxy(1,16);
            color(12);
            printf("STOP");
            stopstart=0;
            while(1){
                if(kbhit())
                do{
                    key2=getch();
                }while(key2==224);
                switch(key2){
                case SKEY:
                    stopstart=1;
                    break;
                case RKEY:
                    main();
                    break;
                }
                if(stopstart==0) break;
            }
            break;
        case RKEY:
            goto again;
            break;
        }
        if(totalsecond==0) break;
        Sleep(1000);
    }
    for(i=1 ; i<=5 ; i++){
        printf("\a");
        Sleep(300);
    }
    system("cls");
    border();
    color(14);
    gotoxy(12,4);
    printf("+------------+");
    gotoxy(12,5);
    printf("| TIME OVER! |");
    gotoxy(12,6);
    printf("+------------+");
    gotoxy(12,8);
    color(15);
    printf("Type \"R\" to Restart");
    gotoxy(12,9);
    printf("Type \"E\" to End this program");
    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case RKEY:
            main();
            break;
        case EKEY:
            exit(0);
            break;
        }
    }
}


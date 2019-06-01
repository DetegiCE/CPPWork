#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<iostream>

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

#define BLANK printf("  ")

int color_border=255;
int key=0;
int ans,door[4],choose;
int result;

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

void border()
{
    int i;
    color(color_border);
    gotoxy(1,1);
    for(i=1 ; i<=33 ; i++)
        BLANK;
    gotoxy(1,15);
    for(i=1 ; i<=33 ; i++)
        BLANK;
    for(i=1 ; i<=15 ; i++){
        gotoxy(1,i);
        BLANK;
    }
    for(i=1 ; i<=15 ; i++){
        gotoxy(33,i);
        BLANK;
    }
    gotoxy(6,19);
    color(15);
    printf("Copyright (c) 2017 by DetegiCE (blog.TeamCE.kr)");
    gotoxy(6,20);
    printf("Made by GSA 3G : 16-017 (ver1.0KR : 2017.01.06.)");
    gotoxy(6,21);
    printf("Contact : martinok1103@naver.com / ceo@teamce.kr");
}

void titles()
{
    int i;

    color(255);

    gotoxy(3,3);
    for(i=1 ; i<=5 ; i++) BLANK;
    for(i=1 ; i<=4 ; i++){
        gotoxy(3,3+i); BLANK;
        gotoxy(5,3+i); BLANK;
        gotoxy(7,3+i); BLANK;
    }

    gotoxy(9,3);
    for(i=1 ; i<=5 ; i++) BLANK;
    gotoxy(9,7);
    for(i=1 ; i<=5 ; i++) BLANK;
    for(i=1 ; i<=3 ; i++){
        gotoxy(9,3+i); BLANK;
        gotoxy(13,3+i); BLANK;
    }

    gotoxy(15,3);
    for(i=1 ; i<=3 ; i++) BLANK;
    gotoxy(19,3); BLANK;
    gotoxy(15,7); BLANK;
    gotoxy(17,7);
    for(i=1 ; i<=3 ; i++) BLANK;
    for(i=1 ; i<=3 ; i++){
        gotoxy(15,3+i); BLANK;
        gotoxy(17,3+i); BLANK;
        gotoxy(19,3+i); BLANK;
    }

    gotoxy(21,3);
    for(i=1 ; i<=5 ; i++) BLANK;
    for(i=1 ; i<=4 ; i++){
        gotoxy(23,3+i); BLANK;
    }

    gotoxy(27,3); BLANK;
    gotoxy(31,3); BLANK;
    gotoxy(27,4); BLANK;
    gotoxy(31,4); BLANK;
    gotoxy(27,5);
    for(i=1 ; i<=5 ; i++) BLANK;
    gotoxy(29,6); BLANK;
    gotoxy(29,7); BLANK;

    for(i=1 ; i<=5 ; i++){
        gotoxy(6,8+i); BLANK;
        gotoxy(10,8+i); BLANK;
    }
    gotoxy(7,11);
    for(i=1 ; i<=3 ; i++) BLANK;

    gotoxy(12,9);
    for(i=1 ; i<=5 ; i++) BLANK;
    for(i=1 ; i<=4 ; i++){
        gotoxy(12,9+i); BLANK;
        gotoxy(16,9+i); BLANK;
    }
    gotoxy(13,11);
    for(i=1 ; i<=3 ; i++) BLANK;

    for(i=1 ; i<=5 ; i++){
        gotoxy(18,8+i); BLANK;
        gotoxy(24,8+i); BLANK;
    }
    gotoxy(19,13);
    for(i=1 ; i<=4 ; i++) BLANK;
    gotoxy(25,13);
    for(i=1 ; i<=4 ; i++) BLANK;

    color(15);

    gotoxy(12,17);
    color(11);
    printf("\"S\"를 눌러 시작하세요!");
}

void choosepage()
{
    int i,j;
    system("cls");
    color_border=143;
    border();

    color(143);
    for(i=1 ; i<=13 ; i++){
        gotoxy(2,1+i); BLANK;
        gotoxy(12,1+i); BLANK;
        gotoxy(22,1+i); BLANK;
        gotoxy(32,1+i); BLANK;
    }

    color(239);
    for(i=3 ; i<=11 ; i++){
        for(j=2 ; j<=14 ; j++){
            gotoxy(i,j);
            BLANK;
        }
    }

    color(175);
    for(i=13 ; i<=21 ; i++){
        for(j=2 ; j<=14 ; j++){
            gotoxy(i,j);
            BLANK;
        }
    }

    color(191);
    for(i=23 ; i<=31 ; i++){
        for(j=2 ; j<=14 ; j++){
            gotoxy(i,j);
            BLANK;
        }
    }

    color(111);
    gotoxy(6,5); BLANK;
    gotoxy(6,12); BLANK;
    gotoxy(8,12); BLANK;
    for(i=4 ; i<=12 ; i++){
        gotoxy(7,i);
        BLANK;
    }

    color(47);
    gotoxy(15,5); BLANK;
    gotoxy(15,6); BLANK;
    gotoxy(18,8); BLANK;
    gotoxy(17,9); BLANK;
    gotoxy(16,10); BLANK;
    gotoxy(15,11); BLANK;
    for(i=16 ; i<=18 ; i++){
        gotoxy(i,4);
        BLANK;
    }
    for(i=5 ; i<=7 ; i++){
        gotoxy(19,i);
        BLANK;
    }
    gotoxy(15,12);
    for(i=1 ; i<=5 ; i++) BLANK;

    color(31);
    gotoxy(25,5); BLANK;
    gotoxy(27,8); BLANK;
    gotoxy(28,8); BLANK;
    gotoxy(25,11); BLANK;
    for(i=1 ; i<=3 ; i++){
        gotoxy(25+i,4); BLANK;
        gotoxy(25+i,12); BLANK;
        gotoxy(29,4+i); BLANK;
        gotoxy(29,8+i); BLANK;
    }

    color(10);
    gotoxy(12,17);
    printf("문의 번호를 고르세요. (1~3)");
}

void choose1()
{
    int i,j;
    color(111);
    for(i=3 ; i<=11 ; i++){
        for(j=2 ; j<=14 ; j++){
            gotoxy(i,j);
            BLANK;
        }
    }

    color(239);
    gotoxy(6,5); BLANK;
    gotoxy(6,12); BLANK;
    gotoxy(8,12); BLANK;
    for(i=4 ; i<=12 ; i++){
        gotoxy(7,i);
        BLANK;
    }
}

void choose2()
{
    int i,j;

    color(47);
    for(i=13 ; i<=21 ; i++){
        for(j=2 ; j<=14 ; j++){
            gotoxy(i,j);
            BLANK;
        }
    }

    color(175);
    gotoxy(15,5); BLANK;
    gotoxy(15,6); BLANK;
    gotoxy(18,8); BLANK;
    gotoxy(17,9); BLANK;
    gotoxy(16,10); BLANK;
    gotoxy(15,11); BLANK;
    for(i=16 ; i<=18 ; i++){
        gotoxy(i,4);
        BLANK;
    }
    for(i=5 ; i<=7 ; i++){
        gotoxy(19,i);
        BLANK;
    }
    gotoxy(15,12);
    for(i=1 ; i<=5 ; i++) BLANK;
}

void choose3()
{
    int i,j;
    color(31);
    for(i=23 ; i<=31 ; i++){
        for(j=2 ; j<=14 ; j++){
            gotoxy(i,j);
            BLANK;
        }
    }

    color(191);
    gotoxy(25,5); BLANK;
    gotoxy(27,8); BLANK;
    gotoxy(28,8); BLANK;
    gotoxy(25,11); BLANK;
    for(i=1 ; i<=3 ; i++){
        gotoxy(25+i,4); BLANK;
        gotoxy(25+i,12); BLANK;
        gotoxy(29,4+i); BLANK;
        gotoxy(29,8+i); BLANK;
    }
}

void drawbomb(int x,int y)
{
    int i,j;
    color(15);
    for(i=3 ; i<=5 ; i++){
        for(j=4 ; j<=11 ; j++){
            gotoxy(x+i,y+j);
            BLANK;
        }
    }
    for(i=1 ; i<=7 ; i++){
        for(j=6 ; j<=9 ; j++){
            gotoxy(x+i,y+j);
            BLANK;
        }
    }
    gotoxy(x+2,y+5); BLANK;
    gotoxy(x+2,y+10); BLANK;
    gotoxy(x+6,y+5); BLANK;
    gotoxy(x+6,y+10); BLANK;

    color(207);
    gotoxy(x+7,y+3); BLANK;

    color(127);
    gotoxy(x+7,y+2); BLANK;
    gotoxy(x+5,y+1); BLANK;
    gotoxy(x+6,y+1); BLANK;
    gotoxy(x+4,y+2); BLANK;
    gotoxy(x+4,y+3); BLANK;

    color(143);
    for(i=1 ; i<=4 ; i++){
        gotoxy(x+2,y+5+i);
        BLANK;
    }


}

void show_bomb(int doornum)
{
    int i,j;

    if(doornum==1){
        color(239);
        for(i=3 ; i<=11 ; i++){
            for(j=2 ; j<=14 ; j++){
                gotoxy(i,j);
                BLANK;
            }
        }
        drawbomb(3,2);
    }
    else if(doornum==2){
        color(175);
        for(i=13 ; i<=21 ; i++){
            for(j=2 ; j<=14 ; j++){
                gotoxy(i,j);
                BLANK;
            }
        }
        drawbomb(13,2);
    }
    else{
        color(191);
        for(i=23 ; i<=31 ; i++){
            for(j=2 ; j<=14 ; j++){
                gotoxy(i,j);
                BLANK;
            }
        }
        drawbomb(23,2);
    }
}

void drawcoin(int x,int y)
{
    int i,j;
    color(111);
    for(i=2 ; i<=6 ; i++){
        for(j=4 ; j<=8 ; j++){
            gotoxy(x+i,y+j);
            BLANK;
        }
    }
    for(i=1 ; i<=3 ; i++){
        gotoxy(x+2+i,y+3); BLANK;
        gotoxy(x+2+i,y+9); BLANK;
        gotoxy(x+1,y+4+i); BLANK;
        gotoxy(x+7,y+4+i); BLANK;
    }

    color(239);
    for(i=1 ; i<=3 ; i++){
        gotoxy(x+6,y+4+i); BLANK;
        gotoxy(x+2+i,y+8); BLANK;
    }
}

void show_coin(int doornum)
{
    int i,j;

    if(doornum==1){
        color(239);
        for(i=3 ; i<=11 ; i++){
            for(j=2 ; j<=14 ; j++){
                gotoxy(i,j);
                BLANK;
            }
        }
        drawcoin(3,2);
    }
    else if(doornum==2){
        color(175);
        for(i=13 ; i<=21 ; i++){
            for(j=2 ; j<=14 ; j++){
                gotoxy(i,j);
                BLANK;
            }
        }
        drawcoin(13,2);
    }
    else{
        color(191);
        for(i=23 ; i<=31 ; i++){
            for(j=2 ; j<=14 ; j++){
                gotoxy(i,j);
                BLANK;
            }
        }
        drawcoin(23,2);
    }
}

void congrats()
{
    color(175);
    int i,j;
    for(i=3 ; i<=13 ; i++){
        if(i==8) continue;
        for(j=6 ; j<=28 ; j++){
            if(i==3) if(j==11 || j==17 || j==21 || j==23) continue;
            if(i==4) if((j>=7 && j<=11)||(j>=13 && j<=15)||j==17||j==19||j==21||j==23||j>=25) continue;
            if(i==5) if((j>=7 && j<=11)||(j>=13 && j<=15)||j==17||j==19||j==21||j==23||j==25) continue;
            if(i==6) if((j>=7 && j<=11)||(j>=13 && j<=15)||j==17||j==19||j==21||j==23||(j>=25 && j<=27)) continue;
            if(i==7) if(j==11||j==17||j==19||j==23) continue;
            if(i==9) if(j==10||j==11||j==17||j==23) continue;
            if(i==10) if((j>=7&&j<=9)||j==11||(j>=13&&j<=15)||(j>=17&&j<=19)||(j>=21&&j<=23)||j>=25) continue;
            if(i==11) if(j==10||j==11||(j>=17&&j<=19)||(j>=21&&j<=23)) continue;
            if(i==12) if((j>=7&&j<=9)||j==11||(j>=13&&j<=15)||(j>=17&&j<=19)||(j>=21&&j<=27)) continue;
            if(i==13) if((j>=7&&j<=9)||j==11||(j>=13&&j<=15)||(j>=17&&j<=19)||(j>=21&&j<=23)) continue;
            gotoxy(j,i);
            BLANK;
        }
    }
    color(224);
    gotoxy(2,17);
    printf("몬티홀 게임을 이겼습니다! \"R\"을 눌러 재시작, \"E\"를 눌러 종료");
}

void fail()
{
    int i,j;
    color(207);
    for(i=6 ; i<=10 ; i++){
        for(j=6 ; j<=28 ; j++){
            if(i==6) if(j==11||j==17||j==23||j>=25) continue;
            if(i==7) if((j>=7&&j<=11)||(j>=13&&j<=15)||(j>=17&&j<=19)||(j>=21&&j<=23)||j>=25) continue;
            if(i==8) if(j==11||(j>=17&&j<=19)||(j>=21&&j<=23)||j>=25) continue;
            if(i==9) if((j>=7&&j<=11)||(j>=13&&j<=15)||(j>=17&&j<=19)||(j>=21&&j<=23)||j>=25) continue;
            if(i==10) if((j>=7&&j<=11)||(j>=13&&j<=15)||j==17||j==23) continue;
            gotoxy(j,i);
            BLANK;
        }
    }
    color(128);
    gotoxy(8,17);
    printf("실패... \"R\"을 눌러 재시작, \"E\"를 눌러 종료");
}



int main()
{
    again:
    int i;
    int temp;
    int scmplt=0;
    color(15);
    system("cls");
    color_border=255;
    system("mode con: lines=23 cols=70");

    border();
    titles();
    key=0;
    scmplt=0;
    while(1){
        if(kbhit())
        do{
            key=getch();
        }while(key==224);
        switch(key){
        case SKEY:
            choosepage();
            key=0;
            scmplt=1;
            break;
        }
        if(scmplt==1) break;
    }

    int key2=0;

    choose=0;
    while(1){
        if(kbhit())
        do{
            key2=getch();
        }while(key2==224);
        switch(key2){
        case 49:
            choose=1;
            choose1();
            key2=0;
            break;
        case 50:
            choose=2;
            choose2();
            key2=0;
            break;
        case 51:
            choose=3;
            choose3();
            key2=0;
            break;
        }
        if(choose>0) break;
    }

    gotoxy(0,23);

    srand(time(NULL));
    ans=(rand()%3)+1;
    for(i=1 ; i<=3 ; i++) door[i]=0;
    door[ans]=1;

    color(11);
     gotoxy(12,17);
    for(i=1 ; i<=20 ; i++) BLANK;
    gotoxy(10,17);
    printf("폭탄이 어디에 있는지 알려드리겠습니다.");
    Sleep(2000);

    color(11);



    if(choose==1){
        if(door[1]==1){
            temp=(rand()%2)+2;
            show_bomb(temp);
        }
        else if(door[2]==0) show_bomb(2);
        else show_bomb(3);
    }
    else if(choose==2){
        if(door[2]==1){
            temp=(rand()%2)+1;
            if(temp==1) show_bomb(1);
            else show_bomb(3);
        }
        else if(door[1]==0) show_bomb(1);
        else show_bomb(3);
    }
    else if(choose==3){
        if(door[3]==1){
            temp=(rand()%2)+1;
            show_bomb(temp);
        }
        else if(door[1]==0) show_bomb(1);
        else show_bomb(2);
    }

    color(11);
     gotoxy(12,17);
    for(i=1 ; i<=20 ; i++) BLANK;
    gotoxy(5,17);
    printf("선택한 문을 바꾸시겠습니까? 문의 번호를 입력하세요.");

    int key3=0;

    choose=0;
    while(1){
        if(kbhit())
        do{
            key3=getch();
        }while(key3==224);
        switch(key3){
        case 49:
            choose=1;
            choose1();
            key3=0;
            break;
        case 50:
            choose=2;
            choose2();
            key3=0;
            break;
        case 51:
            choose=3;
            choose3();
            key3=0;
            break;
        }
        if(choose>0) break;
    }

    Sleep(2000);

    if(choose==1){
        if(door[1]==0){
            show_bomb(1);
            result=0;
        }
        else{
            show_coin(1);
            result=1;
        }
    }
    else if(choose==2){
        if(door[2]==0){
            show_bomb(2);
            result=0;
        }
        else{
            show_coin(2);
            result=1;
        }
    }
    else{
        if(door[3]==0){
            show_bomb(3);
            result=0;
        }
        else{
            show_coin(3);
            result=1;
        }
    }

    Sleep(2000);

    system("cls");
    color_border=255;
    border();

    if(result==1){
        congrats();
    }
    else{
        fail();
    }

    int key4=0;


    while(1){
        if(kbhit())
        do{
            key4=getch();
        }while(key4==224);
        switch(key4){
        case RKEY:
            goto again;
            key4=0;
            break;
        case EKEY:
            exit(0);
            break;
        }
    }
}

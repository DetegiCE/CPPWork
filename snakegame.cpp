#include<stdio.h>

#include<windows.h>

#include<conio.h>

#include<stdlib.h>

#include<time.h>

#include<algorithm>

 

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

#define JKEY 106 // 랭킹

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

int MAP_X=30;

int MAP_Y=20;

 

int color(int color_number)

{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);

}

 

 

int ach[ACH_NUM+2];

int x[100], y[100]; //x,y 좌표값을 저장 총 100개

int food_x, food_y; //food의 좌표값을 저장

int length; //몸길이를 기억

int speed; //게임 속도

double score; //점수 저장  --reset함수에 의해 초기화됨

double bestscore=0; //최고 점수 저장 --reset함수에 의해 초기화 되지 않음

int dir; //이동방향 저장

int key; //입력받은 키 저장

int status_on=0; // 개발자용 status 표시활성화 변수.. 게임중에 S키를 누르면 활성

//int statusf=1;

int green=0;

int pink=0;

int random_box=0;

int mcolor=255;

int hcolor=176;

int tcolor=128;

int best_check=0;

char bestscorename[16];

int gameplays=0;

int level=0;

int exp=0;

int leveluplim=0;

 

int an_frame=0;

int an_tail=0;

 

int rnkSv=0; //저장된 랭킹인간 수

struct ranking{

    int rnk;

    char name[20];

    int score;

}RRR[5000];

 

void cursorhide()

{

    CONSOLE_CURSOR_INFO ConsoleCursor;

    ConsoleCursor.bVisible = FALSE;

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);

}

 

/*void remove_scrollbar()

{

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(handle, &info);

    COORD new_size =

    {

        info.srWindow.Right - info.srWindow.Left + 1,

        info.srWindow.Bottom - info.srWindow.Top + 1

    };

    SetConsoleScreenBufferSize(handle, new_size);

}*/

 

void gotoxy(int x,int y,char* s)   //x값을 2x로 변경, 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입

{

    COORD pos= {2*x,y};

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);

    printf("%s",s);

}

 

void title(void);

void reset(void);

void draw_map(void); // 게임판 테두리를 그림

void move(int dir); //뱀머리를 이동

void game_over(void);

void food(void);

void status(void);

void maincolor(void);

void achievements(void);

//void status_off(void);

 

void bscore(void)

{

    bestscore=bestscore>score?bestscore:score;

}

 

void rbox(void)

{

    int r=0;

    int s=0;

    int t=0;

    int k,l;

    srand((unsigned)time(NULL)+r);

    if(rand()%5==0)

    {

        srand((unsigned)time(NULL)+s);

        speed+=(k=rand()%10); //속도 느려짐

        score+=(l=rand()%10); //30점 추가

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," SPEED -");

        printf("%d",k);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+20," SCORE +");

        printf("%d",l);

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"            ");

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+20,"            ");

    }

    else if(rand()%5==1)

    {

        srand((unsigned)time(NULL)+s);

        speed-=(k=rand()%10); //속도 빨라짐

        length+=(l=rand()%10); //길어짐

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," SPEED +");

        printf("%d",k);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+20," LENGTH +");

        printf("%d",l);

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"            ");

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+20,"            ");

    }

    else if(rand()%5==2)

    {

        mcolor=15;

        tcolor=15; //하드코어 모드 실행

        draw_map();

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," ACTIVATE HARDCORE");

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"                     ");

    }

    else if(rand()%10==3)

    {

        mcolor=255;

        hcolor=176;

        tcolor=128;

        draw_map();

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," DEACTIVATE HARDCORE");

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"                      ");

    }

    /*else if(rand()%10==4)

    {

        score/=2; //점수 2배

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," HALF SCORE");

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"             ");

    }*/

    /*else if(rand()%10==5)

    {

        speed-=20; //속도 아주 빠름

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," SPEED UUUUUUUP");

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"                ");

    }

    else if(rand()%10==6)

    {

        speed+=20; //속도 아주 느림

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," SPEED DOOOOOOWN");

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"                  ");

    }

    else if(rand()%10==7)

    {

        speed+=30;

        length=5;

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," SPEED DOOOOOOOOOOWN");

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+20,"    LENGTH RESET");

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"                     ");

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+20,"                     ");

    }*/

    /*else if(rand()%10==8)

    {

        score=0;

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," SCORE RESET");

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"                     ");

    }*/

    else

    {

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19," NO EFFECT");

        Sleep(500);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+19,"            ");

    }

 

}

 

void showRank()

{

    int i;

    system("cls");

    draw_map();

    //while (kbhit()) getch();

 

    if(rnkSv<9){

        for(i=rnkSv ; i<10 ; i++){

            strcpy(RRR[i].name,"----------");

            RRR[i].score=0;

        }

    }

 

    color(15);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+4," < Current TOP 10 > ");

    color(14);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+5," ");

    printf("%2d %.10s %05d",1,RRR[0].name,RRR[0].score);

    color(8);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+6," ");

    printf("%2d %.10s %05d",2,RRR[1].name,RRR[1].score);

    color(6);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+7," ");

    printf("%2d %.10s %05d",3,RRR[2].name,RRR[2].score);

    for(i=3 ; i<10 ; i++){

        color(15);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+i+5," ");

        printf("%2d %.10s %05d",i+1,RRR[i].name,RRR[i].score);

    }

 

}

 

void title(void)

{

    int i,j;

 

    while (kbhit()) getch(); //버퍼에 있는 키값을 버림

 

    draw_map();    //맵 테두리를 그림

    for(i=MAP_ADJ_Y+1; i<MAP_ADJ_Y+MAP_Y-1; i++) // 맵 테두리 안쪽을 빈칸으로 채움

    {

        for(j=MAP_ADJ_X+1; j<MAP_ADJ_X+MAP_X-1; j++) gotoxy(j,i,"  ");

    }

    color(14);

    //gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+4,"                  release002");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+5,"+--------------------------+");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+6,"|  THE SNAKE GAME v.GSA    |");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+7,"+--------------------------+");

    if(mcolor==15)

    {

        color(12);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+5,"+--------------------------+");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+6,"| THE SNAKE GAME  HARDCORE |");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+7,"+--------------------------+");

    }

 

    color(10);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+9,"    Press Enter to START!");

    color(11);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+10,"Press \"c\" to Change Mode & Color");

    color(12);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+11,"Press \".\" to check Achievements");

    color(14);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+12,"Press \"j\" to check Ranking");

    color(15);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+13,"   Made by. GSA 3G : 16-017");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+14,"       (ceo@TeamCE.kr)");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+16,"Developer BLOG : blog.TeamCE.kr ");

    color(15);

 

    while(1)

    {

        if(kbhit())  //키입력받음

        {

            key=getch();

            if(key==ENTER) break;

            else if(key==CKEY) maincolor();

            else if(key==DOT) achievements();

            else if(key==JKEY) showRank();

            else if(key==ESC) exit(0); // ESC키면 종료

            else break; //아니면 그냥 계속 진행

        }

 

    }

    draw_map();

    reset(); // 게임을 초기화

}

 

void achievements()

{

    color(15);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+4," < Achievements >                  ");

 

    if(ach[1])

    {

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+5,"O ");

        color(15);

    }

    else

    {

        color(12);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+5,"X ");

        color(15);

    }

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+5,"001 You Are A Player!              ");

 

    if(ach[2])

    {

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+6,"O ");

        color(15);

    }

    else

    {

        color(12);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+6,"X ");

        color(15);

    }

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+6,"002 Hundred Points!                ");

 

    if(ach[3])

    {

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+7,"O ");

        color(15);

    }

    else

    {

        color(12);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+7,"X ");

        color(15);

    }

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+7,"003 Thousand Points!               ");

 

    if(ach[4])

    {

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+8,"O ");

        color(15);

    }

    else

    {

        color(12);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+8,"X ");

        color(15);

    }

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+8,"004 Hundred Plays! (100 Plays)     ");

 

    if(ach[5])

    {

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+9,"O ");

        color(15);

    }

    else

    {

        color(12);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+9,"X ");

        color(15);

    }

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+9,"005 Celebrater!                    ");

 

    if(ach[6])

    {

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+10,"O ");

        color(15);

    }

    else

    {

        color(12);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+10,"X ");

        color(15);

    }

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+10,"006 Ranker! (Level 10)             ");

 

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+11,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+12,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-8,MAP_ADJ_Y+13,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+14,"Press X to go to title.              ");

    while(1)

    {

        if(kbhit())  //키입력받음

        {

            key=getch();

            if(key==XKEY) title();

            else break; //아니면 그냥 계속 진행

        }

 

    }

}

 

void maincolor()

{

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+4," < Mode & Color Setting >       ");

    color(15);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+5,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+6,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+7,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+8,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+9,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+10,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-13,MAP_ADJ_Y+11,"                                           ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+12,"                                   ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+13,"                                   ");

    color(15);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-11,MAP_ADJ_Y+6," HEAD :");

    color(31);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+6," B ");

    color(47);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-5,MAP_ADJ_Y+6," G ");

    color(63);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-3,MAP_ADJ_Y+6," A ");

    color(79);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-1,MAP_ADJ_Y+6," R ");

    color(95);

    gotoxy(MAP_ADJ_X+(MAP_X/2)+1,MAP_ADJ_Y+6," P ");

    color(111);

    gotoxy(MAP_ADJ_X+(MAP_X/2)+3,MAP_ADJ_Y+6," F ");

    color(127);

    gotoxy(MAP_ADJ_X+(MAP_X/2)+5,MAP_ADJ_Y+6," K (2.0 ANNIV!) ");

    color(15);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-11,MAP_ADJ_Y+8,"FRAME :");

    color(159);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+8," L ");

    color(160);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-5,MAP_ADJ_Y+8," I ");

    color(176);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-3,MAP_ADJ_Y+8," H ");

    color(207);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-1,MAP_ADJ_Y+8," D ");

    color(223);

    gotoxy(MAP_ADJ_X+(MAP_X/2)+1,MAP_ADJ_Y+8," N ");

    color(224);

    gotoxy(MAP_ADJ_X+(MAP_X/2)+3,MAP_ADJ_Y+8," W ");

    color(240);

    gotoxy(MAP_ADJ_X+(MAP_X/2)+5,MAP_ADJ_Y+8," Z (2.0 ANNIV!) ");

    color(12);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-13,MAP_ADJ_Y+10,"HARDCORE ON/OFF : Q (Invisible Tail & Frame) (x1.5)");

    color(14);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-13,MAP_ADJ_Y+11,"       MAP SIZE : BIG : Y, MIDDLE : M, SMALL : O");

    color(13);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-13,MAP_ADJ_Y+12,"   NO HEAD MODE : V (x1.2)               ");

    color(10);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-13,MAP_ADJ_Y+13,"          RESET : T                      ");

    //color(11);

    //gotoxy(MAP_ADJ_X+(MAP_X/2)-13,MAP_ADJ_Y+14,"BESTSCORE RESET : U                      ");

    //color(11);

    //gotoxy(MAP_ADJ_X+(MAP_X/2)-13,MAP_ADJ_Y+14,"        RANKING : J                      ");

    color(15);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-13,MAP_ADJ_Y+15,"          Title : X                      ");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-13,MAP_ADJ_Y+16,"      Developer : U                      ");

}

 

void reset(void)

{

    int i;

    system("cls"); //화면을 지움

    draw_map(); //맵 테두리를 그림

    while (kbhit()) getch(); //버퍼에 있는 키값을 버림

 

    dir=LEFT; // 방향 초기화

    speed=100; // 속도 초기화

    length=5; //뱀 길이 초기화

    score=0; //점수 초기화

    for(i=0; i<length; i++) //뱀 몸통값 입력

    {

        x[i]=MAP_X/2+i;

        y[i]=MAP_Y/2;

        color(tcolor);

        gotoxy(MAP_ADJ_X+x[0],MAP_ADJ_Y+y[0],"  ");

        color(15);

    }

    color(hcolor);

    gotoxy(MAP_ADJ_X+x[0],MAP_ADJ_Y+y[0],"  ");

    color(15);

    food(); // food 생성

 

}

 

void levelcount()

{

    int i,sum=0;

    if(exp>=495001)

    {

        level=100;

    }

    else

    {

        for(i=1 ; i<=99 ; i++)

        {

            sum+=i;

            if(exp<=sum*100)

            {

                level=i;

                leveluplim=sum;

                break;

            }

        }

    }

}

 

 

 

int main()

{

    int i;

    system("mode con: lines=40 cols=120");

    //FILE *fp = fopen("BSsource.dll","r");

    FILE *fpgp = fopen("GPsource.dll","r");

    FILE *fpac = fopen("ACsource.dll","r");

    FILE *fpxp = fopen("XPsource.dll","r");

    FILE *fprk = fopen("RKsource.dll","r");

 

    /*if(fp==NULL)

    {

        bestscore=0;

        sprintf(bestscorename,"System");

    }

    else fscanf(fp,"%lf %s",&bestscore,bestscorename);*/

    if(fpgp==NULL)

    {

        gameplays=0;

    }

    else fscanf(fpgp,"%d",&gameplays);

    for(i=1 ; i<=ACH_NUM ; i++)

    {

        fscanf(fpac,"%d ",&ach[i]);

    }

    fscanf(fpxp,"%d",&exp);

    fscanf(fprk,"%d",&rnkSv);

    for(i=0 ; i<rnkSv ; i++){

        fscanf(fprk,"%d %s %d",&RRR[i].rnk,RRR[i].name,&RRR[i].score);

    }

 

    //fclose(fp);

    fclose(fpgp);

    fclose(fpac);

    fclose(fpxp);

    fclose(fprk);

 

    title();

    levelcount();

    draw_map();

    cursorhide();

 

    //remove_scrollbar();

    best_check=0;

 

    while(1)

    {

        if(kbhit()) do

            {

                key=getch();

            }

            while(key==224);

        Sleep(speed);

        bscore();

        switch(key)

        {

        case LEFT:

        case RIGHT:

        case UP:

        case DOWN:

            if((dir==LEFT&&key!=RIGHT)||(dir==RIGHT&&key!=LEFT)||(dir==UP&&key!=DOWN)||

                    (dir==DOWN&&key!=UP))//180회전이동을 방지하기 위해 필요.

                dir=key;

            key=0; // 키값을 저장하는 함수를 reset

            break;

        case SKEY: //S키를 누르면 개발자용 status를 활성화 시킴

            if(status_on==0) status_on=1;

            else status_on=0;

            key=0;

            break;

        //case 100:

        //if(statusf==1) statusf=0;

        //else statusf=1;

        //key=0;

        //break;

        case SEMICOLON:

            score+=10; // ; 키로 점수 추가

            break;

        case RIGHTBRACKET:

            speed-=1;

            break;

        case LEFTBRACKET:

            speed+=1;

            break;

        case COMMA:

            length+=1;

            break;

        case DOT:

            length-=1;

            break;

        case ESC: //ESC키를 누르면 프로그램 종료

            exit(0);

        case XKEY:

            title();

            break;

        case YKEY:

            MAP_Y=30;

            system("cls");

            draw_map();

            main();

            break;

        case MKEY:

            MAP_Y=20;

            system("cls");

            draw_map();

            main();

            break;

        case OKEY:

            MAP_Y=15;

            system("cls");

            draw_map();

            main();

            break;

        case AKEY:

            hcolor=63;

            break;

        case BKEY:

            hcolor=31;

            break;

        case DKEY:

            mcolor=207;

            an_frame=0;

            draw_map();

            break;

        case EKEY:

            hcolor=143;

            break;

        case FKEY:

            hcolor=111;

            break;

        case GKEY:

            hcolor=47;

            break;

        case HKEY:

            mcolor=191;

            an_frame=0;

            draw_map();

            break;

        case IKEY:

            mcolor=175;

            an_frame=0;

            draw_map();

            break;

        case KKEY:

            hcolor=127;

            an_tail=1;

            break;

        case LKEY:

            mcolor=159;

            an_frame=0;

            draw_map();

            break;

        case NKEY:

            mcolor=223;

            an_frame=0;

            draw_map();

            break;

        case PKEY:

            hcolor=95;

            break;

        case RKEY:

            hcolor=79;

            break;

        case WKEY:

            mcolor=239;

            an_frame=0;

            draw_map();

            break;

        case ZKEY:

            mcolor=255;

            an_frame=1;

            draw_map();

            break;

        case VKEY:

            hcolor=15;

            system("cls");

            main();

            break;

        case QKEY:

            if(mcolor!=15 && tcolor!=15)

            {

                mcolor=15;

                an_frame=0;

                tcolor=15;

                an_tail=0;

                system("cls");

                main();

                break;

            }

            else if(mcolor==15 && tcolor==15)

            {

                mcolor=255;

                an_frame=0;

                tcolor=128;

                an_tail=0;

                hcolor=176;

                system("cls");

                main();

                break;

            }

        case TKEY:

            mcolor=255;

            an_frame=0;

            tcolor=128;

            an_tail=0;

            hcolor=176;

            MAP_Y=20;

            system("cls");

            main();

            break;

        case UKEY:

            system("explorer.exe http://blog.naver.com/martinok1103");

            key=0;

            break;

        case ENTER:

            break;

        }

        move(dir);

        /*color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+6,"LEVEL: ");

        printf("%d (EXP : %d)",level,exp);*/

        color(15);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+6,"SCORE: ");

        printf("%.2lf",score);

        /*color(14);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+8,"BESTSCORE: ");

        printf("%.2lf",bestscore);

        color(15);

        if(best_check==0) printf(" by %s",bestscorename);

        else printf(" by YOU                         ");*/

        if(an_frame==1) draw_map();

        /*if(score>=bestscore)

        {

            color(11);

            gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+1,"+------------+");

            gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+2,"| BESTSCORE! |");

            gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+3,"+------------+");

            best_check=1;

        }

        else

        {

            color(15);

            gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+1,"               ");

            gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+2,"               ");

            gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+3,"               ");

        }*/

 

        if(status_on==1) status(); // status표시

        //if(statusf==0) status_off();

    }

}

 

void draw_map(void)  //맵 테두리 그리는 함수

{

    int i,j,t;

    srand(time(NULL));

    if(an_frame==1)

    {

        for(i=0; i<MAP_X; i++)

        {

            t=rand()%255;

            color(t);

            gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y,"  ");

            color(0);

        }

        for(i=MAP_ADJ_Y+1; i<MAP_ADJ_Y+MAP_Y-1; i++)

        {

            t=rand()%255;

            color(t);

            gotoxy(MAP_ADJ_X,i,"  ");

            color(0);

            t=rand()%255;

            color(t);

            gotoxy(MAP_ADJ_X+MAP_X-1,i,"  ");

            color(0);

        }

        for(i=0; i<MAP_X; i++)

        {

            t=rand()%255;

            color(t);

            gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y+MAP_Y-1,"  ");

            color(0);

        }

    }

    else

    {

        for(i=0; i<MAP_X; i++)

        {

            color(mcolor);

            gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y,"  ");

            color(0);

        }

        for(i=MAP_ADJ_Y+1; i<MAP_ADJ_Y+MAP_Y-1; i++)

        {

            color(mcolor);

            gotoxy(MAP_ADJ_X,i,"  ");

            color(0);

            color(mcolor);

            gotoxy(MAP_ADJ_X+MAP_X-1,i,"  ");

            color(0);

        }

        for(i=0; i<MAP_X; i++)

        {

            color(mcolor);

            gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y+MAP_Y-1,"  ");

            color(0);

        }

    }

    color(224);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+10,"  ");

    color(15);

    printf(" : FOOD");

    color(160);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+12,"  ");

    color(15);

    printf(" : SPEED DOWN");

    color(208);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+14,"  ");

    color(15);

    printf(" : SHORTEN");

    color(192);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+16,"  ");

    color(15);

    printf(" : RANDOM BOX");

    if(mcolor==15)

    {

        color(12);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+18,"  HARDCORE");

    }

    else

    {

        color(12);

        gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+18,"           ");

    }

    color(15);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+23,"");

    if(level==100)

    {

        printf("Level 100! You are the Best! GREAT! (EXP : %d)",exp);

    }

    else

    {

        printf("%d ",level);

        for(i=1 ; i<=25 ; i++)

        {

            if((leveluplim*100-(leveluplim-level)*100)/25*i<=(exp-(leveluplim-level)*100)) color(165);

            else color(15);

            printf(" ");

        }

        color(15);

        printf(" %d (EXP : %d)",level+1,exp);

    }

}

 

void move(int dir)

{

    int i;

 

    if(x[0]==food_x&&y[0]==food_y)  //food와 충돌했을 경우

    {

        if(mcolor==15 && MAP_Y==30 && hcolor==15) // LARGE UNSEEN

        {

            if(score<LIMIT1) score+=7*1.5*10;

            else if(score>=LIMIT1 && score<LIMIT2) score+=7*1.2*1.5*10;

            else if(score>=LIMIT2 && score<LIMIT3) score+=7*1.4*1.5*10;

            else if(score>=LIMIT3 && score<LIMIT4) score+=7*1.6*1.5*10;

            else if(score>=LIMIT4 && score<LIMIT5) score+=7*1.8*1.5*10;

            else if(score>=LIMIT5) score+=7*2.0*1.5*10;

        }

        else if(mcolor==15 && MAP_Y==30) // LARGE HARDCORE

        {

            if(score<LIMIT1) score+=7*1.5;

            else if(score>=LIMIT1 && score<LIMIT2) score+=7*1.2*1.5;

            else if(score>=LIMIT2 && score<LIMIT3) score+=7*1.4*1.5;

            else if(score>=LIMIT3 && score<LIMIT4) score+=7*1.6*1.5;

            else if(score>=LIMIT4 && score<LIMIT5) score+=7*1.8*1.5;

            else if(score>=LIMIT5) score+=7*2.0*1.5;

        }

        else if(mcolor==15 && MAP_Y==20 && hcolor==15) // MIDDLE UNSEEN

        {

            if(score<LIMIT1) score+=10*1.5*10;

            else if(score>=LIMIT1 && score<LIMIT2) score+=10*1.2*1.5*10;

            else if(score>=LIMIT2 && score<LIMIT3) score+=10*1.4*1.5*10;

            else if(score>=LIMIT3 && score<LIMIT4) score+=10*1.6*1.5*10;

            else if(score>=LIMIT4 && score<LIMIT5) score+=10*1.8*1.5*10;

            else if(score>=LIMIT5) score+=10*2.0*1.5*10;

        }

        else if(mcolor==15 && MAP_Y==20) // MIDDLE HARDCORE

        {

            if(score<LIMIT1) score+=10*1.5;

            else if(score>=LIMIT1 && score<LIMIT2) score+=10*1.2*1.5;

            else if(score>=LIMIT2 && score<LIMIT3) score+=10*1.4*1.5;

            else if(score>=LIMIT3 && score<LIMIT4) score+=10*1.6*1.5;

            else if(score>=LIMIT4 && score<LIMIT5) score+=10*1.8*1.5;

            else if(score>=LIMIT5) score+=10*2.0*1.5;

        }

        else if(mcolor==15 && MAP_Y==15 && hcolor==15) // SMALL UNSEEN

        {

            if(score<LIMIT1) score+=13*1.5*10;

            else if(score>=LIMIT1 && score<LIMIT2) score+=13*1.2*1.5*10;

            else if(score>=LIMIT2 && score<LIMIT3) score+=13*1.4*1.5*10;

            else if(score>=LIMIT3 && score<LIMIT4) score+=13*1.6*1.5*10;

            else if(score>=LIMIT4 && score<LIMIT5) score+=13*1.8*1.5*10;

            else if(score>=LIMIT5) score+=13*2.0*1.5*10;

        }

        else if(mcolor==15 && MAP_Y==15) // SMALL HARDCORE

        {

            if(score<LIMIT1) score+=13*1.5;

            else if(score>=LIMIT1 && score<LIMIT2) score+=13*1.2*1.5;

            else if(score>=LIMIT2 && score<LIMIT3) score+=13*1.4*1.5;

            else if(score>=LIMIT3 && score<LIMIT4) score+=13*1.6*1.5;

            else if(score>=LIMIT4 && score<LIMIT5) score+=13*1.8*1.5;

            else if(score>=LIMIT5) score+=13*2.0*1.5;

        }

        else if(MAP_Y==30 && hcolor==15) // LARGE NOHEAD

        {

            if(score<LIMIT1) score+=7*1.2;

            else if(score>=LIMIT1 && score<LIMIT2) score+=7*1.2*1.2;

            else if(score>=LIMIT2 && score<LIMIT3) score+=7*1.4*1.2;

            else if(score>=LIMIT3 && score<LIMIT4) score+=7*1.6*1.2;

            else if(score>=LIMIT4 && score<LIMIT5) score+=7*1.8*1.2;

            else if(score>=LIMIT5) score+=7*2.0*1.2;

        }

        else if(MAP_Y==30) // LARGE DEFAULT

        {

            if(score<LIMIT1) score+=7;

            else if(score>=LIMIT1 && score<LIMIT2) score+=7*1.2;

            else if(score>=LIMIT2 && score<LIMIT3) score+=7*1.4;

            else if(score>=LIMIT3 && score<LIMIT4) score+=7*1.6;

            else if(score>=LIMIT4 && score<LIMIT5) score+=7*1.8;

            else if(score>=LIMIT5) score+=7*2.0;

        }

        else if(MAP_Y==15 && hcolor==15) // SMALL NOHEAD

        {

            if(score<LIMIT1) score+=13*1.2;

            else if(score>=LIMIT1 && score<LIMIT2) score+=13*1.2*1.2;

            else if(score>=LIMIT2 && score<LIMIT3) score+=13*1.4*1.2;

            else if(score>=LIMIT3 && score<LIMIT4) score+=13*1.6*1.2;

            else if(score>=LIMIT4 && score<LIMIT5) score+=13*1.8*1.2;

            else if(score>=LIMIT5) score+=13*2.0*1.2;

        }

        else if(MAP_Y==15) // SMALL DEFAULT

        {

            if(score<LIMIT1) score+=13;

            else if(score>=LIMIT1 && score<LIMIT2) score+=13*1.2;

            else if(score>=LIMIT2 && score<LIMIT3) score+=13*1.4;

            else if(score>=LIMIT3 && score<LIMIT4) score+=13*1.6;

            else if(score>=LIMIT4 && score<LIMIT5) score+=13*1.8;

            else if(score>=LIMIT5) score+=13*2.0;

        }

        else if(MAP_Y==20 && hcolor==15)//MIDDLE NOHEAD

        {

            if(score<LIMIT1) score+=10*1.2;

            else if(score>=LIMIT1 && score<LIMIT2) score+=10*1.2*1.2;

            else if(score>=LIMIT2 && score<LIMIT3) score+=10*1.4*1.2;

            else if(score>=LIMIT3 && score<LIMIT4) score+=10*1.6*1.2;

            else if(score>=LIMIT4 && score<LIMIT5) score+=10*1.8*1.2;

            else if(score>=LIMIT5) score+=10*2.0*1.2;

        }

        else //MIDDLE DEFAULT

        {

            if(score<LIMIT1) score+=10;

            else if(score>=LIMIT1 && score<LIMIT2) score+=10*1.2;

            else if(score>=LIMIT2 && score<LIMIT3) score+=10*1.4;

            else if(score>=LIMIT3 && score<LIMIT4) score+=10*1.6;

            else if(score>=LIMIT4 && score<LIMIT5) score+=10*1.8;

            else if(score>=LIMIT5) score+=10*2.0;

        }

 

        if(green==1 && pink==0 && random_box==0)

        {

            speed+=5;

            green=0;

        }

        else if(green==0 && pink==1 && random_box==0)

        {

            if(speed-3<=0) speed=1;

            else speed-=3;

            length-=2;

            pink=0;

        }

        else if(green==0 && pink==0 && random_box==1)

        {

            rbox();

            random_box=0;

        }

        else

        {

            if(speed-3<=0) speed=1;

            else speed-=3;

        }

        food(); //새로운 food 추가

        //if(green) speed+=3;

        //else speed-=3;

 

 

        length++; //길이증가

        x[length-1]=x[length-2]; //새로만든 몸통에 값 입력

        y[length-1]=y[length-2];

    }

    if(x[0]==0||x[0]==MAP_X-1||y[0]==0||y[0]==MAP_Y-1)  //벽과 충돌했을 경우

    {

        game_over();

        return; //game_over에서 게임을 다시 시작하게 되면 여기서부터 반복

    }

    for(i=1; i<length; i++) //자기몸과 충돌했는지 검사

    {

        if(x[0]==x[i]&&y[0]==y[i])

        {

            game_over();

            return;

        }

    }

    color(15);

    gotoxy(MAP_ADJ_X+x[length-1],MAP_ADJ_Y+y[length-1],"  "); //몸통 마지막을 지움

    for(i=length-1; i>0; i--) //몸통좌표를 한칸씩 옮김

    {

        x[i]=x[i-1];

        y[i]=y[i-1];

    }

    int t;

    srand(time(NULL));

    if(an_tail==1)

    {

 

        t=rand()%255;

        color(t);

        gotoxy(MAP_ADJ_X+x[0],MAP_ADJ_Y+y[0],"  ");

    }

    else

    {

        color(tcolor);

        gotoxy(MAP_ADJ_X+x[0],MAP_ADJ_Y+y[0],"  ");

    }

    color(15);

    if(dir==LEFT) --x[0];

    if(dir==RIGHT) ++x[0];

    if(dir==UP) --y[0];

    if(dir==DOWN) ++y[0];

    color(hcolor);

    gotoxy(MAP_ADJ_X+x[0],MAP_ADJ_Y+y[0],"  ");

    color(15);

}

 

void ach_check(void)

{

    if(ach[1]==0)

    {

        ach[1]=1;

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"| ACHIEVEMENT 1 CLEAR! |");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");

        exp+=10;

    }

    if(score>=100 && ach[2]==0)

    {

        ach[2]=1;

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"| ACHIEVEMENT 2 CLEAR! |");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");

        exp+=20;

    }

    if(score>=1000 && ach[3]==0)

    {

        ach[3]=1;

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"| ACHIEVEMENT 3 CLEAR! |");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");

        exp+=80;

    }

    if(gameplays>=100 && ach[4]==0)

    {

        ach[4]=1;

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"| ACHIEVEMENT 4 CLEAR! |");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");

        exp+=50;

    }

    if(an_tail==1 && an_frame==1 && ach[5]==0)

    {

        ach[5]=1;

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"| ACHIEVEMENT 5 CLEAR! |");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");

        exp+=20;

    }

    if(level>=10 && ach[6]==0)

    {

        ach[6]=1;

        color(10);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"| ACHIEVEMENT 6 CLEAR! |");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");

        exp+=100;

    }

}

 

bool comp(ranking a,ranking b)

{

    return a.score>b.score;

}

 

void game_over(void)  //게임종료 함수

{

    int i,j;

    char yourName[20];

    color(12);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"|       GAME OVER!     |");

    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");

    color(15);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+8," YOUR SCORE : ");

    color(11);

    printf("%.2lf",score);

    exp+=(int)score/10;

    levelcount();

    gameplays++;

    ach_check();

 

    //if(best_check==1)

    //{

        color(15);

        gotoxy(MAP_ADJ_X+(MAP_X/2)-4,MAP_ADJ_Y+11,"(No Space, Eng 16, Kor 8 Limited)");

        gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y+10," YOUR NAME : ");

        scanf("%s",yourName);

    //}

    //FILE *fpe = fopen("BSsource.dll","w");

    FILE *fpgpe = fopen("GPsource.dll","w");

    FILE *fpace = fopen("ACsource.dll","w");

    FILE *fpxpe = fopen("XPsource.dll","w");

    FILE *fprke = fopen("RKsource.dll","w");

    //fprintf(fpe,"%lf %s",bestscore,bestscorename);

    fprintf(fpgpe,"%d",gameplays);

    for(i=1 ; i<=ACH_NUM ; i++)

    {

        fprintf(fpace,"%d ",ach[i]);

    }

    fprintf(fpxpe,"%d",exp);

 

    rnkSv++;

    RRR[rnkSv-1].rnk=rnkSv;

    RRR[rnkSv-1].score=(int)score;

    strcpy(RRR[rnkSv-1].name,yourName);

 

    std::sort(RRR,RRR+rnkSv,comp);

 

    fprintf(fprke,"%d\n",rnkSv);

    for(i=0 ; i<rnkSv ; i++){

        fprintf(fprke,"%d %s %d\n",i,RRR[i].name,RRR[i].score);

    }

 

    //fclose(fpe);

    fclose(fpgpe);

    fclose(fpace);

    fclose(fpxpe);

    fclose(fprke);

    color(15);

    color(12);

    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+12,"     ENTER : RESTART");

    color(15);

    best_check=0;

 

    Sleep(500);

    while (kbhit()) getch();

    key=getch();

    title();

}

 

void food(void)

{

    int i;

 

    int food_crush_on=0;//food가 뱀 몸통좌표에 생길 경우 on

    int r=0; //난수 생성에 사동되는 변수

 

    while(1)

    {

        food_crush_on=0;

 

        srand((unsigned)time(NULL)+r); //난수표생성

        if(rand()%10==0) //속도 느려짐

        {

            food_x=(rand()%(MAP_X-2))+1;    //난수를 좌표값에 넣음

            food_y=(rand()%(MAP_Y-2))+1;

 

            for(i=0; i<length; i++) //food가    뱀 몸통과 겹치는지 확인

            {

                if(food_x==x[i]&&food_y==y[i])

                {

                    food_crush_on=1; //겹치면 food_crush_on 를 on

                    r++;

                    break;

                }

            }

 

            if(food_crush_on==1) continue; //겹쳤을 경우 while문을 다시 시작

 

            color(160);

            gotoxy(MAP_ADJ_X+food_x,MAP_ADJ_Y+food_y,"  ");

            color(15);

            green=1;

            //speed+=5;

            break;

        }

        else if(rand()%20==0) // 길이 짧아짐

        {

            food_x=(rand()%(MAP_X-2))+1;    //난수를 좌표값에 넣음

            food_y=(rand()%(MAP_Y-2))+1;

 

            for(i=0; i<length; i++) //food가    뱀 몸통과 겹치는지 확인

            {

                if(food_x==x[i]&&food_y==y[i])

                {

                    food_crush_on=1; //겹치면 food_crush_on 를 on

                    r++;

                    break;

                }

            }

 

            if(food_crush_on==1) continue; //겹쳤을 경우 while문을 다시 시작

 

            color(208);

            gotoxy(MAP_ADJ_X+food_x,MAP_ADJ_Y+food_y,"  ");

            color(15);

            pink=1;

            //speed-=3;

            //length-=1;

            break;

        }

        else if(rand()%50==0) // 랜덤박스

        {

            food_x=(rand()%(MAP_X-2))+1;    //난수를 좌표값에 넣음

            food_y=(rand()%(MAP_Y-2))+1;

 

            for(i=0; i<length; i++) //food가    뱀 몸통과 겹치는지 확인

            {

                if(food_x==x[i]&&food_y==y[i])

                {

                    food_crush_on=1; //겹치면 food_crush_on 를 on

                    r++;

                    break;

                }

            }

 

            if(food_crush_on==1) continue; //겹쳤을 경우 while문을 다시 시작

 

            color(192);

            gotoxy(MAP_ADJ_X+food_x,MAP_ADJ_Y+food_y,"  ");

            color(15);

            random_box=1;

            //speed-=3;

            //length-=1;

            break;

        }

        else

        {

            green=0;

            food_x=(rand()%(MAP_X-2))+1;    //난수를 좌표값에 넣음

            food_y=(rand()%(MAP_Y-2))+1;

 

            for(i=0; i<length; i++) //food가 뱀 몸통과 겹치는지 확인

            {

                if(food_x==x[i]&&food_y==y[i])

                {

                    food_crush_on=1; //겹치면 food_crush_on 를 on

                    r++;

                    break;

                }

            }

 

            if(food_crush_on==1) continue; //겹쳤을 경우 while문을 다시 시작

            color(224);

            gotoxy(MAP_ADJ_X+food_x,MAP_ADJ_Y+food_y,"  ");

            green=0;

            color(15);

            //speed-=3;

            break;

        }

    }

}

 

 

void status(void)  //각종 스텟을 볼수 있는 함수

{

    color(15);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y,"HEAD : ");

    printf("%2d,%2d",x[0],y[0]);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+1,"FOOD : ");

    printf("%2d,%2d",food_x,food_y);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+2,"LENG : ");

    printf("%2d",length);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+3,"KEY  : ");

    printf("%3d",key);

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+4,"SPEED: ");

    printf("%3d",100-speed);

 

}

 

/*void status_off(void)

{

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y,"              ");

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+1,"              ");

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+2,"              ");

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+3,"              ");

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+4,"              ");

    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+6,"              ");

}*/


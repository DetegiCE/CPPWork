#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<vector>
#include<random>
#include<queue>
#include<utility>
#include<stack>
#include<map>
#include <fstream>

using namespace std;
#define PBMIN 1
#define PBMAX 15
#define RANDOM(__min__, __max__) (rand()%((__max__)-(__min__)+1)+(__min__))

int cheatnum;
char inp[13] = "test001.in";
char oup[13] = "test001.out";
FILE* fin, *fout;

////////////////////////////////////////////////

int ar[102][102];

int probMain(FILE* ffin, FILE* ffout)
{
    for(int i=0 ; i<102 ; i++) {
        for(int j=0 ; j<102 ; j++) {
            ar[i][j] = 0;
        }
    }
    int i,j,k;
    int x1,y1,x2,y2;
    for(i=1 ; i<=4 ; i++){
        fscanf(ffin,"%d %d %d %d",&x1,&y1,&x2,&y2);
        for(j=x1 ; j<x2 ; j++){
            for(k=y1 ; k<y2 ; k++){
                ar[j][k]=1;
            }
        }
    }
    int cnt=0;
    for(i=1 ; i<=100 ; i++){
        for(j=1 ; j<=100 ; j++){
            cnt+=ar[i][j];
        }
    }
    fprintf(ffout,"%d",cnt);
    return 0;
}

vector<int> vps;
void makeFiles(int num) {
    printf("Generating Input File %d/%d\n",num,PBMAX);
    inp[6] = (num%10)+'0';
    inp[5] = (num/10)%10+'0';
    inp[4] = (num/100)+'0';
    fin = fopen(inp, "w");

    ////////////////////////////////////

    /*
     * HOW TO GENERATE RANDOM SHUFFLE VECTOR
     *
     * random_device rd;
     * mt19937 g(rd());
     * shuffle(v.begin(), v.end(), g);
     *
     */

    for(int i=0 ; i<4 ; i++) {
        int x1 = RANDOM(1,99);
        int y1 = RANDOM(1,99);
        int x2 = RANDOM(x1+1,100);
        int y2 = RANDOM(y1+1,100);
        fprintf(fin,"%d %d %d %d\n",x1,y1,x2,y2);
    }

    ////////////////////////////////////

    fclose(fin);
}

int solveFiles(int num) {
    printf("Answer File Generating %d/%d\n",num,PBMAX);
    oup[6] = (num%10)+'0';
    oup[5] = (num/10)%10+'0';
    oup[4] = (num/100)+'0';
    fout = fopen(oup, "w");
    inp[6] = (num%10)+'0';
    inp[5] = (num/10)%10+'0';
    inp[4] = (num/100)+'0';
    fin = fopen(inp, "r");

    int sftmp = probMain(fin, fout);

    fclose(fin);
    fclose(fout);

    return sftmp;
}

int main()
{
    srand(time(NULL));
    for(int i=PBMIN ; i<=PBMAX ; i++) {
        cheatnum = i;
        makeFiles(i);
        int mntmp = solveFiles(i);
        if(mntmp == 1) i--;
    }
    printf("Complete!\n");
}

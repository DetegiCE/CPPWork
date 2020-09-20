#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<vector>
#include<random>
#include<queue>
#include<utility>
#include<stack>
#include <fstream>

using namespace std;
#define PBMIN 24
#define PBMAX 25
#define RANDOM(__min__, __max__) (rand()%((__max__)-(__min__)+1)+(__min__))

int cheatnum;
char inp[13] = "test001.in";
char oup[13] = "test001.out";
FILE* fin, *fout;

////////////////////////////////////////////////

int n, m, r;
int robot[1000005];
int rdif[2000005];

int sum, mxsum;

int probMain(FILE* ffin, FILE* ffout)
{
    n=m=r=0;
    for(int i=0 ; i<1000005 ; i++) robot[i] = 0;
    for(int i=0 ; i<2000005 ; i++) rdif[i] = 0;
    sum = mxsum = 0;

    fscanf(ffin,"%d",&n);
    fscanf(ffin,"%d %d",&r,&m);
    for(int i=0 ; i<n ; i++) {
        fscanf(ffin,"%d",&robot[i]);
    }
    sort(robot,robot+n);
    robot[n] = robot[0] + m;
    for(int i=0 ; i<n ; i++) {
        rdif[i] = rdif[i+n] = robot[i+1] - robot[i] - r * 2;
    }
    for(int i=0 ; i<2*n-1 ; i++) {
        sum += rdif[i];
        if(sum < 0) sum = 0;
        mxsum = mxsum>sum?mxsum:sum;
    }
    fprintf(ffout,"%d",(mxsum+1)/2);
    if((mxsum+1)/2==0) return 1;
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

    vps.clear();

    int nfn, nfr, nfm;
    nfn = RANDOM(1,1000000);
    nfr = RANDOM(1,1000000000);
    nfm = RANDOM(nfn,15000000);

    //nfn = RANDOM(1,3);
    //nfr = RANDOM(1,5/nfn);
    //nfm = RANDOM(nfn,2*nfr*nfn);

    //nfn = RANDOM(1,7000);
    //nfr = RANDOM(1,100000);
    //nfm = RANDOM(nfn,min(2*nfr*nfn,50000));

    fprintf(fin,"%d\n%d %d\n",nfn,nfr,nfm);
    printf("%d\n%d %d\n",nfn,nfr,nfm);
    for(int i=0 ; i<nfm ; i++) vps.push_back(i);

    random_device rd;
    mt19937 g(rd());
    shuffle(vps.begin(),vps.end(),g);
    for(int i=0 ; i<nfn ; i++) {
        fprintf(fin,"%d ",vps[i]);
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

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
#define PBMIN 11
#define PBMAX 20
#define RANDOM(__min__, __max__) (rand()%((__max__)-(__min__)+1)+(__min__))

int cheatnum;
char inp[13] = "test001.in";
char oup[13] = "test001.out";
FILE* fin, *fout;

////////////////////////////////////////////////

int n, m, x;
vector<int> good[100001];
vector<int> bad[100001];

bool goodvis[100001];
bool badvis[100001];

int checkGood(int pos) {
    int sum = 0;
    goodvis[pos] = true;
    for(auto k: good[pos]) {
        if(!goodvis[k]) sum += checkGood(k);
    }
    return sum + 1;
}

int checkBad(int pos) {
    int sum = 0;
    badvis[pos] = true;
    for(auto k: bad[pos]) {
        if(!badvis[k]) sum += checkBad(k);
    }
    return sum + 1;
}

int probMain(FILE* ffin, FILE* ffout)
{
    n=m=x=0;
    for(int i=0 ; i<100001 ; i++) {
        good[i].clear();
        bad[i].clear();
        goodvis[i] = badvis[i] = 0;
    }
    fscanf(ffin,"%d %d %d",&n,&m,&x);
    for(int i=0 ; i<m ; i++) {
        int z, y;
        fscanf(ffin,"%d %d",&z,&y);
        bad[z].push_back(y);
        good[y].push_back(z);
    }
    fprintf(ffout,"%d %d",checkGood(x),n-checkBad(x)+1);
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

    int nfn = RANDOM(2,100000);
    int nfm;
    if(nfn<=1000) nfm = RANDOM(1,nfn*(nfn-1)/2);
    else nfm = RANDOM(1,500000);
    int nfx = RANDOM(1,nfn);

    vps.clear();
    for(int i=1 ; i<=nfn ; i++) vps.push_back(i);
    random_device rd;
    mt19937 g(rd());
    shuffle(vps.begin(),vps.end(),g);

    fprintf(fin,"%d %d %d\n",nfn,nfm,nfx);

    vector<pair<int,int> > vpii;
    int flg = 0;
    for(int i=0 ; i<nfm ; i++) {
        int nfx = RANDOM(0,nfn-2);
        int nfy = RANDOM(nfx+1,nfn-1);
        flg = 0;
        for(int j=0 ; j<i ; j++) {
            if(vpii[j].first == nfx && vpii[j].second == nfy) {
                i--;
                flg = 1;
                break;
            }
        }
        if(flg == 0) vpii.push_back({nfx,nfy});
    }
    for(int i=0 ; i<nfm ; i++) {
        fprintf(fin,"%d %d\n",vps[vpii[i].first],vps[vpii[i].second]);
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

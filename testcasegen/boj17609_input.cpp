#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include<stack>
using namespace std;

#define TCMIN 21
#define TCMAX 30

char fileIn[10];

long long random(long long from, long long to) {
    return min(to, (long long)((double)rand() / RAND_MAX * (to-from)) + from + (rand() %2));
}

void gen()
{
    FILE* f = fopen(fileIn,"w");
    stack<char> st;

    int t = random(1,5);
    fprintf(f, "%d\n", t);
    for(int i=0 ; i<t ; i++) {
        int len = random(3,20);

        int choice = random(0,5);
        if(choice == 0) { //아주 랜덤
            for(int j=0 ; j<len ; j++) {
                char a = random('a','z');
                fprintf(f,"%c",a);
            }
        }
        else if(choice == 1) { //회문 짝수
            for(int j=0 ; j<len/2 ; j++) {
                char a = random('a','z');
                fprintf(f,"%c",a);
                st.push(a);
            }
            while(!st.empty()) {
                fprintf(f,"%c",st.top());
                st.pop();
            }
        }
        else if(choice == 2){ //회문 홀수
            for(int j=0 ; j<len/2 ; j++) {
                char a = random('a','z');
                fprintf(f,"%c",a);
                st.push(a);
            }
            st.pop();
            while(!st.empty()) {
                fprintf(f,"%c",st.top());
                st.pop();
            }
        }
        else if(choice == 3) { //유사회문 앞쪽
            int pos = random(1,len/2-2);
            for(int j=0 ; j<len/2 ; j++) {
                char a = random('a','z');
                char b = random('a','z');
                fprintf(f,"%c",a);
                if(j==pos) fprintf(f,"%c",b);
                st.push(a);
            }
            while(!st.empty()) {
                fprintf(f,"%c",st.top());
                st.pop();
            }
        }
        else if(choice == 4) { //유사회문 뒤쪽
            int pos = random(1,len/2-2);
            for(int j=0 ; j<len/2 ; j++) {
                char a = random('a','z');
                fprintf(f,"%c",a);
                st.push(a);
            }
            int cur = 0;
            while(!st.empty()) {
                fprintf(f,"%c",st.top());
                if(cur==pos){
                    char b = random('a','z');
                    fprintf(f,"%c",b);
                }
                cur++;
                st.pop();
            }
        }
        else { //유사유사회문
            int pos1 = random(1,len/2-2);
            int pos2 = random(1,len/2-2);
            for(int j=0 ; j<len/2 ; j++) {
                char a = random('a','z');
                char b = random('a','z');
                fprintf(f,"%c",a);
                if(j==pos1) fprintf(f,"%c",b);
                st.push(a);
            }
            int cur = 1;
            while(!st.empty()) {
                fprintf(f,"%c",st.top());
                char b = random('a','z');
                if(cur==pos2) fprintf(f,"%c",b);
                cur++;
                st.pop();
            }
        }
        fprintf(f,"\n");
    }

    fclose(f);
}

int main()
{   
    srand(time(NULL));
    strcpy(fileIn, "test1.in");    
    for(int i=TCMIN ; i<=TCMAX ; i++) {
        if(i<10) {
            fileIn[4] = i+'0';
        }
        else if(i<100) {
            strcpy(fileIn, "test10.in");
            fileIn[4] = (i/10)+'0',fileIn[5] = (i%10)+'0';
            fileIn[6] = '.',fileIn[7] = 'i',fileIn[8] = 'n';
        }
        cout << fileIn << '\n';
        gen();
    }
}

#include<stdio.h>
#include<string.h>
#include<ctype.h>

char prod[20][20],first[26][20],follow[26][20];
int n, firstCnt[26],followCnt[26];

int add(char set[],int *cnt,char c){
    for(int i=0;i<(*cnt);i++){
        if(set[i]==c){
            return 0;
        }
    }
    set[(*cnt)++]=c;
    return 1;
}


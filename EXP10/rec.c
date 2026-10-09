#include<stdio.h>
#include<stdlib.h>

char input[50];
int pos=0;

void S();
void A();
void E();
void Eprime();
void T();


void error(){
    printf("Rejected\n");
    exit(0);
}

void match(char t){
    if(input[pos]==t){
        pos++;
    }
    else{
        error();
    }
}

void S(){
    if(input[pos]=='i'){
        A();
        S();
    }
}

void A(){
        match('i');
        match('=');
        E();
        match(';');
}

void E(){
    T();
    Eprime();
}

void Eprime(){
    if(input[pos]=='+'){
        match('+');
        T();
        Eprime();
    }
}

void T(){
    if(input[pos]=='i'){
        match('i');
    }
    else if(input[pos]=='n'){
        match('n');
    }
    else if(input[pos]=='('){
        match('(');
        E();
        match(')');
    }
    else{
        error();
    }
}

int main(){
    printf("Enter the input string:");
    scanf("%s",input);
    S();

    if(input[pos]=='\0'){
        printf("Accepted\n");
    }
    else{
        error();
    }
    return 0;
}
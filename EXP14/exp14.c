#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 500

void initialize(){
    printf("8086 Assembly code\n");
    printf("MOV AX,@DATA\n");
    printf("MOV DS,AX\n\n");
}

void generate(char *s){
    char lhs[20],op1[20],op2[20];
    char op,rel[3],label[30];

    if(sscanf(s,"if %19s %2s %19s goto %19s",op1,rel,op2,label)==4)
    {
        printf("MOV AX,%s\n",op1);
        printf("CMP AX,%s\n",op2);

        if(strcmp(rel,"<")==0){
            printf("JL %s",label);
        }
        else if(strcmp(rel,">")==0){
            printf("JG %s\n",label);
        }
        else if(strcmp(rel,"<=")==0){
            printf("JLE %s\n",label);
        }
        else if(strcmp(rel,">=")==0){
            printf("JGE %s\n",label);
        }
        else if(strcmp(rel,"==")==0){
            printf("JE %s\n",label);
        }
        else if(strcmp(rel,"!=")==0){
            printf("JNE %s\n",label);
        }
        printf("\n");
    }
    else if(sscanf(s,"goto %19s",label)==1){
        printf("JMP %s\n\n",label);
    }
    else if(s[strlen(s)-1]==':'){
        s[strlen(s)-1]='\0';
        printf("%s\n",s);
    }
    else if(sscanf(s,"%19[^=]=%19[^+-*/]%c%19s",lhs,op1,&op,op2)==4){
        printf("MOV AX,%s\n",op1);

        if(op=='+'){
            printf("ADD AX,%s\n",op2);
        }
        else if(op=='-'){
            printf("SUB AX,%s\n",op2);
        }
        else if(op=='*'){
            printf("MOV BX,%s\n",op2);
            printf("MUL BX\n");
        }
        else if(op=='/'){
            printf("MOV BX,%s\n",op2);
            printf("MOV DX,0\n");
            printf("DIV BX\n");
        }
        printf("MOV %s,AX\n\n",lhs);
    }
    else if(sscanf(s,"%19[^=]=%19s",lhs,op1)==2){
        printf("MOV AX,%s\n",op1);
        printf("MOV %s,AX\n\n",lhs);
    }
    
}

void terminate(){
    printf("MOV AH,4CH\n");
    printf("INT 21H\n");
    printf("END\n");
}

int main(){
    int n;
    char input[500];
    char *statement;

    printf("Enter the number of input statements:");
    scanf("%d",&n);

    printf("Enter the input statements in a line:\n");
    scanf(" %[^\n]",input);

    initialize();

    statement = strtok(input,";");

    for(int i=0;i<n && statement!=NULL;i++){

        generate(statement);
        statement = strtok(NULL,";");
    }

    terminate();
}
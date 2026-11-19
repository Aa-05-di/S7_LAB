#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX_STMT 20
#define MAX_LEN 20

struct Statement{
  char lhs[MAX_LEN],op1[MAX_LEN],op2[MAX_LEN],op;
};

int isNumber(char *s){
    if(*s=='\0'){
        return 0;
    }
    for(int i=0;s[i];i++){
        if(!isdigit((unsigned char)s[i])){
            return 0;
        }
    }
    return 1;
}

void readStatement(struct Statement s[],int n){
    for(int i=0;i<n;i++){
        char str[50];
        scanf("%49s",str);
        sscanf(str,"%19[^=]=%19s",s[i].lhs,s[i].op1);

        char *p = strpbrk(s[i].op1,"+-/*");
        if(p){
            s[i].op = *p;
            *p='\0';
            strcpy(s[i].op2,p+1);
        }
        else{
            s[i].op='\0';
            s[i].op2[0]='\0';
        }
    }
}

void cp(struct Statement s[],int n){
    char value[MAX_STMT][MAX_LEN];
    int known[MAX_STMT] = {0};

    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(known[j]){
                if(strcmp(s[i].op1,s[j].lhs)==0){
                    strcpy(s[i].op1,value[j]);
                }
                if(strcmp(s[i].op2,s[j].lhs)==0){
                    strcpy(s[i].op2,value[j]);
                }
            }
        }

        if(s[i].op=='\0' && isNumber(s[i].op1)){
            known[i]=1;
            strcpy(value[i],s[i].op1);
        }
    
        printf("%s = %s",s[i].lhs,s[i].op1);
        if(s[i].op!='\0'){
            printf(" %c %s",s[i].op,s[i].op2);
        }
        printf("\n");
    }
}

int main(){
    int n;
    struct Statement s[MAX_STMT];
    printf("Enter the number of statements:\n");
    scanf("%d",&n);

    readStatement(s,n);
    cp(s,n);
    return 0;
}
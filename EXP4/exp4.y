%{
#include<stdio.h>
#include<stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER;

%left '+' '-'
%left '*' '/'

%%

expr:
    expr '+' expr
    |expr '-' expr
    |expr '*' expr
    |expr '/' expr
    |'(' expr ')' 
    |NUMBER
    ;

%%

int main(){
    printf("Enter the arithmetic expression:");
    if(yyparse()==0){
        printf("Valid Expression\n");
    }
    return 0;
}

void yyerror(const char *s){
    printf("Invalid Expression\n");
}
%{
#include<stdio.h>
int yylex();
int yyerror(char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

input:expression '\n'
     {
        printf("Result=%d\n",$1);
     }
     ;
    
expression:expression '+' expression {$$=$1+$3;}
          |expression '-' expression {$$=$1-$3;}
          |expression '*' expression {$$=$1*$3;}
          |expression '/' expression
            {
                if($3==0){
                    YYBORT;
                }
                $$=$1/$3;
            }
          |'(' expression ')'
          |NUMBER
            {
                $$=$1;
            }

%%

int main(){
    printf("Enter the expression:\n");
    yyparse();
    return 0;
}
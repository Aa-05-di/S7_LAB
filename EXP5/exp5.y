%{
    #include<stdio.h>
    #include<stdlib.h>

    int yylex(void);
    void yyerror(const char *s);
%}

%union {
    int num;
}

%token <int> NUMBER;
%type <int> expr;
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

program:
    program expr '\n' {printf("Result: %d\n",$2);}
    |
    ;

expr:
    NUMBER {$$=$1;}
    |expr '+' expr {$$=$1+$3;}
    |expr '-' expr {$$=$1-$3;}
    |expr '*' expr {$$=$1*$3;}
    |expr '/' expr {
        if($3==0){
            yyerror("Division by zero\n");
            $$=0;
        }
        else{
            $$=$1/$3;
        }
    }
    |'(' expr ')' {$$=$2;}

%%

void yyerror(const char *s){
    fprintf(stderr,"Error:%s\n",s);
}

int main(void){
        printf("Enter the expression:\n");
        yyparse();
        return 0;
}
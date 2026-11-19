%{
    #include<stdio.h>
    int yylex(void);
    void yyerror(const char *s);
%}

%token NUMBER;
%left '+' '-'
%left '*' '/'

%%

input:expr '\n'
    {
        printf("Result is %d\n",$1);
    }

expr:NUMBER {$$=$1;}
    |expr '+' expr {$$=$1+$3;}
    |expr '-' expr {$$=$1-$3;}
    |expr '*' expr {$$=$1*$3;}
    |expr '/' expr{
        if($3==0){
            YYABORT;
        }
        {$$=$1/$3;}
    }
    |'(' expr ')' {$$=$2;}
%%

int main(){
    printf("Enter the expression:");
    yyparse();

    return 0;
}

void yyerror(const char *s){
    printf("Invalid expression\n"); 
}
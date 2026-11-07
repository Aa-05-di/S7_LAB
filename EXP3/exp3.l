%{
#include<stdio.h>
#include<string.h>
%}

digit [0-9]
letter [a-zA-Z_]

%%
[ \t\n]+ ;
"if"|"else"|"for"|"while"|"break"|"int"|"float"|"char"|"return" {printf("%s is a keyword\n",yytext);}
[a-zA-Z][a-zA-Z0-9]* {printf("%s is an identifier\n",yytext);}
[0-9]+ {printf("%s is a number\n",yytext);}
[0-9]+\.[0-9]+ {printf("%s is a floating number\n",yytext);} 
">="|"<="|"=="|"++"|"&&"|"||"|"--" {printf("%s is an operator\n",yytext);}
[+*%<>=!/\-] {printf("%s is an operator\n",yytext);}
\/\/[^\n]* ;
\/\*([^*]|\*+[^*/])*\*+\/ ;
[(){}\[\];,] {printf("%s is a separator\n",yytext);}
%%

int yywrap(){
    return 1;
}

int main()
{
    yyin = fopen("input.txt", "r");

    if (yyin == NULL)
    {
        printf("Error opening input.txt\n");
        return 1;
    }

    yylex();

    fclose(yyin);
    return 0;
}
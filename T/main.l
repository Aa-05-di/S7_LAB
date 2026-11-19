%{
#include<stdio.h>
#include<ctype.h>
%}

%%
[a-zA-Z]+ {
    for(int i=0; i<yyleng; i++)
    {
        printf("%c", toupper(yytext[i]));
    }
}
%%

int main()
{
    printf("Enter the input: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
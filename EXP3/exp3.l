%{
#include <stdio.h>
extern FILE *yyin;
%}

digit      [0-9]
letter     [a-zA-Z_]
id         {letter}({letter}|{digit})*
number     {digit}+(\.{digit}+)?
keyword    if|else|while|for|do|switch|case|break|continue|return|int|float|double|char|void|long|short|printf|scanf

%%
[ \t\n]+                           ;


"//".*                             ;
"/*"([^*]|\*+[^*/])*\*+"/"         ;

{keyword}                          { printf("%s is a keyword\n", yytext); }


"=="                               { printf("%s is an equality operator\n", yytext); }
"!="                               { printf("%s is a not equal operator\n", yytext); }
"<="                               { printf("%s is a less than or equal operator\n", yytext); }
">="                               { printf("%s is a greater than or equal operator\n", yytext); }
"&&"                               { printf("%s is a logical AND operator\n", yytext); }
"||"                               { printf("%s is a logical OR operator\n", yytext); }
"++"                               { printf("%s is an increment operator\n", yytext); }
"--"                               { printf("%s is a decrement operator\n", yytext); }
"+="                               { printf("%s is an addition assignment operator\n", yytext); }
"-="                               { printf("%s is a subtraction assignment operator\n", yytext); }
"*="                               { printf("%s is a multiplication assignment operator\n", yytext); }
"/="                               { printf("%s is a division assignment operator\n", yytext); }


"+"                                { printf("%s is an arithmetic operator\n", yytext); }
"-"                                { printf("%s is an arithmetic operator\n", yytext); }
"*"                                { printf("%s is an arithmetic operator\n", yytext); }
"/"                                { printf("%s is an arithmetic operator\n", yytext); }
"%"                                { printf("%s is an arithmetic operator\n", yytext); }
"="                                { printf("%s is an assignment operator\n", yytext); }
"<"                                { printf("%s is a less than operator\n", yytext); }
">"                                { printf("%s is a greater than operator\n", yytext); }
"!"                                { printf("%s is a logical NOT operator\n", yytext); }

","                                { printf("%s is a comma\n", yytext); }
";"                                { printf("%s is a semicolon\n", yytext); }
"("                                { printf("%s is a left parenthesis\n", yytext); }
")"                                { printf("%s is a right parenthesis\n", yytext); }
"{"                                { printf("%s is a left brace\n", yytext); }
"}"                                { printf("%s is a right brace\n", yytext); }
"["                                { printf("%s is a left bracket\n", yytext); }
"]"                                { printf("%s is a right bracket\n", yytext); }


{number}                           { printf("%s is a number\n", yytext); }
{id}                               { printf("%s is an identifier\n", yytext); }
.                                  { printf("%s is an invalid token\n", yytext); }
%%

int yywrap()
{
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
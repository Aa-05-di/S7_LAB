%{
    #include<stdio.h>
%}

digit [0-9]
letter [a-zA-Z_]
id {letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?
keywords (if|else|for|while|break|return|continue|exit|switch|while|do|printf|scanf|int|float)
arithmetic [+\-*/%]
relational (<|>|<=|>=|==|!=)
assignment =
special ("("|")"|"{"|"}")
%%
[ \t\n]+    ;
"//".*                             ;
"/*"([^*]|\*+[^*/])*\*+"/"         ;
{keywords} {printf("%s is a keyword\n", yytext);}
{id}        {printf("%s is an identifier\n",yytext);}
{arithmetic}    {printf("%s is an arithmetic operator\n",yytext);}
{relational}    {printf("%s is a relational operator\n",yytext);}
{assignment}    {printf("%s is an assignment operator\n",yytext);}
{number}    {printf("%s is a number\n",yytext);}
{special} { printf("%s is a special symbol\n", yytext); }
.   {printf("Invalid character\n");}
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

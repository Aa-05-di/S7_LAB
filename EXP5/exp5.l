%{
    #include "y.tab.h"
    #include<stdio.h>
    extern int yylval;
%}

%%
[0-9]+(\.[0-9]+)?           {yylval=atoi(yytext); return NUMBER;}
\n                          {return '\n';}
[ \t]+                      ;
.                           {return yytext[0];}
%%

int yywrap(void){
    return 1;
}
%{
#include <stdlib.h>
void yyerror(char *);
#include "y.tab.h"
%}

%%

[0-9]+ {
           yylval = atoi(yytext);
           return INTEGER;
       }

[-+\n] return *yytext;

[ \t]  ; /* pular espaços em branco */

.      yyerror("caractere inválido");

%%

int yywrap(void) {
   return 1;
}

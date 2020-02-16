%{
void yyerror(char *);
#include "y.tab.h"
%}

%%

0 {
     yylval = 0;
     return ZERO;
  }

1 {
     yylval = 1;
     return ONE;
  }

[-+\n] return *yytext;

[ \t]  ; /* pular espaços em branco */

.      yyerror("caractere inválido");

%%

int yywrap(void) {
   return 1;
}

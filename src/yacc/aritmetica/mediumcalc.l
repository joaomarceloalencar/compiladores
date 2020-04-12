%{
   #include <stdlib.h>
   void yyerror(char *);
   #include "y.tab.h"
%}

%%
   /* variáveis */
[a-z]   {
           yylval = *yytext - 'a';
           return VARIABLE;
        }

   /* inteiros */
[0-9]+  {
           yylval = atoi(yytext);
           return INTEGER;
        }
          
   /* operadores */
[-+()=/*\n]   { return *yytext; }

   /* espaços em branco */
[ \t]   ;

   /* o restante é erro */
.   yyerror("caractere inválido.");


%%

int yywrap(void) {
   return 1;
}

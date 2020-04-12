%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}

%token INTEGER

%%

program:
       program expr '\n' { printf("%d\n", $2); }
       |
       ;
expr:
       INTEGER           { 
                            $$ = $1;
                            printf("Transferindo %d de INTEGER para o expr.\n", $1);
                         }
       | expr '+' expr   { 
                            $$ = $1 + $3; 
                            printf("Somando %d e %d dos expr filhos para o expr pai.\n", $1, $3);
                         }
       | expr '-' expr   { 
                            $$ = $1 - $3; 
                            printf("Subtraindo  %d e %d dos expr filhos para o expr pai.\n", $1, $3);
                         }
       ;
%% 

void yyerror(char *s) {
   fprintf(stderr, "%s\n", s);
}

int main(void) {
   yyparse();
   return 0;
}

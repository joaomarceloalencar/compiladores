%{
#include <stdio.h>
#include <ctype.h>

#define YYDEBUG 1

int yylex(void);
int yyerror(char *);
%}

%token NUMBER

%%

command : exp { printf("%d\n", $1); }
        ; /* permite imprimir o resultado */

exp : exp '+' term { $$ = $1 + $3; }
    | exp '-' term { $$ = $1 + $3; }
    | term { $$ = $1; }
    ;
 
term : term '*' factor { $$ = $1 * $3; }
     | factor { $$ = $1 ;} 
     ;

factor : NUMBER { $$ = $1; }
       | '('exp')' { $$ = $2; }
       ;

%%

int main() {
   extern int yydebug;
   yydebug = 1;
   return yyparse();
}

int yylex(void) {
   int c;
   while ((c=getchar()) == ' '); /* elimina espaços em branco */
   if (isdigit(c)) {
      ungetc(c,stdin);
      scanf("%d", &yylval);
      return(NUMBER);
   }
   if (c == '\n') return 0; /* interrompe a análise sintática */
   return c;
}

/* imprimir a mensagem erro */
int yyerror(char *s) {
   fprintf(stderr, "%s\n", s);
   return 0;
}

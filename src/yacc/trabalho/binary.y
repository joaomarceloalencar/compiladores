%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}

%token ONE
%token ZERO

%%

program:
   program number '\n'
   |
   ;

number: 
   sign list { printf("%d\n", $1 * $2); } 
   ;
sign:  
   '+'            { $$ = 1; }
   | '-'          { $$ = -1; }
   |              { $$ = 1; }
   ;
list:
    list bit      { $$ = 2 * $1 + $2; }
    | bit         { $$ = $1; }
    ;
bit:
   ZERO           { $$ = $1; }
   | ONE          { $$ = $1; }
   ;
%%

void yyerror(char *s) {
   fprintf(stderr, "%s\n", s);
}

int main(void) {
   yyparse();
   return 0;
}

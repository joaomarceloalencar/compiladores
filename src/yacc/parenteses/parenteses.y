/* Cabeçalhos a serem incluídos */
%{
#include <stdio.h>
#include <ctype.h>

/* Protótipo das funções explicadas na seção Rotinas Auxiliares. */
int yylex(void);
int yyerror(char *);

%}

/* Tokens.*/
%token LPARAM RPARAM LITTLEA

%%

/* Observe os código entre chaves após cada regra. São as ações. */
A : LPARAM A RPARAM { printf("Fazendo redução por A -> (A).\n"); }
   | LITTLEA        { printf("Fazendo redução por A -> a.\n"); }
   ;

%%

int main(int argc, char *argv[]) {
   /* A função yyparse() ativa o analisador sintático LALR(1). */
   return yyparse();
}

/* Por padrão, yyparse() vai chamar uma função chamada yylex() para a análise léxica.
   Esta função poderia ser criada automaticamente pelo lex. 
   Neste primeiro exemplo, vamos fazê-la manualmente. */
int yylex(void) {
   int c;
   /* Vamos pular os espaços em branco. */
   while ((c = getchar()) == ' ');

   /* Aqui retorna os tokens para cada símbolo. */
   if (c == '(' ) return LPARAM;
   else if (c == ')') return RPARAM;
   else if (c == 'a') return LITTLEA;
   else if (c == '\n') return 0; /* O token de valor 0 finaliza a análise. */
   return c; /* Qualquer outro valor levará a erro. */
} 

int yyerror(char *s) {
   fprintf(stderr, "%s\n", s);
   return 0;
} /* Imprimir uma mensagem de erro. */

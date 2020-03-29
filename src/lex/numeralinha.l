%{
   /* programa Lex para adicionar números
      de linhas a linhas de um texto, e 
      imprimir o novo texto
   */
   #include <stdio.h>
   int lineno = 1;
%}

line .*\n

%%
{line} printf("%d\t%s", lineno++, yytext); 
%%

int yywrap(void) {
   return 1;
}

int main(int argc, char *argv[]) {
   yyin = fopen(argv[1], "r");
   yylex();
   fclose(yyin);
   return 0;
}

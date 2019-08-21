 /* Definições */
%{
   int nchar, nword, nline;
%}
%%
 /* Regras */
\n        { nline++, nchar++; }
[^ \t\n]+ { nword++, nchar += yyleng; }
.         { nchar++; }

%% 
 /* Subrotinas */
int yywrap(void) {
   printf("Terminei.\n");
   return 1;
}

int main(void) {
   yylex();
   printf("%d\t%d\t%d\n", nchar, nword, nline);
   return 0;
}

digito [0-9]
letra [A-Za-z]

%{
   int count;
%}

%%
"{".*"}" { printf("Ignorando comentário.\n"); }
"read"   { printf("Ignorando palavra reservada read.\n"); }
{letra}({letra}|{digito})* {count++;} 
%%

int yywrap(void) {
   return 1;
}

int main(int argc, char *argv[]) {
   yyin = fopen(argv[1], "r");
   yylex();
   printf("Id count: %d\n", count);
   fclose(yyin);
   return 0;
}


digito [0-9]
letra [A-Za-z]

%{

#define ID       100
#define NUMINT   101
#define NUMFLOAT 102

%}

%%

{letra}({letra}|{digito})*  { return ID;}
[1-9][0-9]*                 { return NUM;}
[ \t\n]                     { ; }

%%

int yywrap(void) {
   return 1;
}

int main(int argc, char *argv[]) {
   yyin = fopen(argv[1], "r");
   int token = yylex();
   while (token) {
      if (token == ID) {
         printf("Identificador: %s\n", yytext);
      } else if (token == NUM) {
         printf("Número: %s\n", yytext);
      }
      token = yylex();
   }
   fclose(yyin);
}

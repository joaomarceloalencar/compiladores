digito [0-9]
letra [A-Za-z]
tipo (float|int)
reservada (if|for|while|do|else|return|def)
identificador {letra}({letra}|{digito})*
string (\".*\"|\'.*\')

%{
   #include <stdlib.h>
   #include <string.h>

   typedef struct variavel {
      char nome[100];
   } variavel;

   typedef struct funcao {
      char nome[100];
   } funcao;

   int funcCount = 0;
   funcao funcoes[100];

   int varCount = 0;
   variavel variaveis[100];

   void processarVariavel(char *);
   int variavelExiste(char *);
   void processarFuncao(char *);
   int funcaoExiste(char *);

%}

%%

^[ \t]*\#.*$ { /* printf("Ignorando Linha comentário: %s\n", yytext); */}

{string}     { /* printf("Isto é uma cadeia de caracteres: %s\n", yytext); */}

{reservada} {;}

{identificador}\( { processarFuncao(yytext); } 
 
{identificador} { processarVariavel(yytext); }

.  {;}
\n {;}

%%

int yywrap(void) {
   return 1;
}

void removerUltChar(char *cadeia) {
   int tamanho = strlen(cadeia);
   if ((cadeia[tamanho-1] == ',' ) || (cadeia[tamanho-1] == '(') || (cadeia[tamanho-1] == ';')) {
      cadeia[tamanho-1] = '\0';
   }
}

int funcaoExiste(char *cadeia) {
   int existe = 0;
   for (int i = 0; i < funcCount; i++)
      if (!strcmp(cadeia, funcoes[i].nome))
         existe = 1;
   return existe;
}

void processarFuncao(char *cadeia) {
   removerUltChar(cadeia);
   if (!funcaoExiste(cadeia)) {
      strcpy(funcoes[funcCount].nome, cadeia);
      funcCount++;
   }
   return;
}

int variavelExiste(char *cadeia) {
   int existe = 0;
   for (int i = 0; i < varCount; i++)
      if (!strcmp(cadeia, variaveis[i].nome))
         existe = 1;
   return existe;
}

void processarVariavel(char *cadeia) {
   if (!variavelExiste(cadeia)) {
      strcpy(variaveis[varCount].nome, cadeia);
      varCount++;
   }
   return;
}


int main(int argc, char *argv[]) {
   yyin = fopen(argv[1], "r");
   yylex();
   
   printf("Variáveis:\n");
   for (int i = 0; i < varCount; i++){
      printf(" %s\n", variaveis[i].nome);
   }

   printf("Funções:\n");
   for (int i = 0; i < funcCount; i++){
      printf(" %s\n", funcoes[i].nome);
   }

   fclose(yyin);
   return 0;
}


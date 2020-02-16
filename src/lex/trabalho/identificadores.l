digito [0-9]
letra [A-Za-z]
tipo (float|int)
reservada (if|for|while|do|else|return)
identificador {letra}({letra}|{digito})*

%{
   #include <stdlib.h>
   #include <string.h>

   typedef struct variavel {
      char tipo[10];
      char nome[100];
   } variavel;

   typedef struct funcao {
      char tipo[10];
      char nome[100];
   } funcao;

   int funcCount = 0;
   funcao funcoes[100];

   int varCount = 0;
   variavel variaveis[100];

   void processarVariavelIndividual(char *);
   void processarFuncao(char *);

%}

%%

 /* Definição de Funções */
{tipo}[ \t]+{identificador}[ \t]*\( { processarFuncao(yytext); } 
 
 /* Definição de variáveis - {tipo} {id} */
{tipo}([ \t]+{identificador}) { printf("P:%s\n", yytext); processarVariavelIndividual(yytext); }

 /* Definição de variáveis - {tipo} {id}, {id}, {id}, ... */
{tipo}[ \t]+{identificador},([ \t]*{identificador},?)+; { printf("S:%s\n", yytext); processarVariavelIndividual(yytext); } 

 /* Não imprime o código */
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

void processarFuncao(char *cadeia) {
   const char s[2] = " ";
   char *token;
   token = strtok(cadeia, s);

   char tipo[10];
   strcpy(tipo, token);
    
   while( token != NULL ) {
      token = strtok(NULL, s);
      
      if (token != NULL) {
         strcpy(funcoes[funcCount].tipo, tipo);
         removerUltChar(token);
         strcpy(funcoes[funcCount].nome, token);
         funcCount++;
      }
   }
   return;
}

void processarVariavelIndividual(char *cadeia) {
   const char s[2] = " ";
   char *token;
   token = strtok(cadeia, s);

   char tipo[10];
   strcpy(tipo, token);
    
   while( token != NULL ) {
      token = strtok(NULL, s);
      
      if (token != NULL) {
         strcpy(variaveis[varCount].tipo, tipo);
         removerUltChar(token);
         strcpy(variaveis[varCount].nome, token);
         varCount++;
      }
   }
   return;
}


int main(int argc, char *argv[]) {
   yyin = fopen(argv[1], "r");
   yylex();
   char bufferInt[1000];
   int intCount = 0;
   sprintf(bufferInt, "Variáveis Inteiras:\n ");

   char bufferFloat[1000];
   int floatCount = 0;
   sprintf(bufferFloat, "Variáveis Ponto Flutuante:\n ");

   for (int i = 0; i < varCount; i++) {
       if (!strcmp("int", variaveis[i].tipo)) {
          sprintf(bufferInt, "%s%s ", bufferInt, variaveis[i].nome);
          intCount++;
       }
       if (!strcmp("float", variaveis[i].tipo)) {
          sprintf(bufferFloat, "%s%s ", bufferFloat, variaveis[i].nome);
          floatCount++;
       }
       printf("%s - %s\n", variaveis[i].tipo, variaveis[i].nome);
   }
   sprintf(bufferInt, "%s\nTotal de Variáveis Inteiras: %d\n", bufferInt, intCount);
   printf("%s\n", bufferInt);

   sprintf(bufferFloat, "%s\nTotal de Variáveis Ponto Flutuante: %d\n", bufferFloat, floatCount);
   printf("%s\n", bufferFloat);

   intCount = 0;
   sprintf(bufferInt, "Funções Inteiras:\n ");

   floatCount = 0;
   sprintf(bufferFloat, "Funções Ponto Flutuante:\n ");

   for (int i = 0; i < funcCount; i++) {   
       if (!strcmp("int", funcoes[i].tipo)) {
          sprintf(bufferInt, "%s%s ", bufferInt, funcoes[i].nome);
          intCount++;
       }
       if (!strcmp("float", variaveis[i].tipo)) {
          sprintf(bufferFloat, "%s%s ", bufferFloat, funcoes[i].nome);
          floatCount++;
       }    
   }
   sprintf(bufferInt, "%s\nTotal de Funções Inteiras: %d\n", bufferInt, intCount);
   printf("%s\n", bufferInt);

   sprintf(bufferFloat, "%s\nTotal de Funções Ponto Flutuante: %d\n", bufferFloat, floatCount);
   printf("%s\n", bufferFloat);


   fclose(yyin);
   return 0;
}


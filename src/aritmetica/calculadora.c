/* Calculadora para aritmética de inteiros simples segundo a EBNF:
   <exp>   -> <termo> { <soma> <termo> }
   <soma>  -> + | -
   <termo> -> <fator> { <mult> <fator> }
   <mult>  -> *
   <fator> -> (<exp>) | número

   Linhas de texto fornecidas como entrada de stdin
   Imprime o resultado ou então "Error".
*/

#include <stdio.h>
#include <stdlib.h>

char token; /* variável de marca global */

/* protótipos de funções para ativações recursivas */
int exp(void);
int term(void);
int fator(void);

void error(void) {
   fprintf(stderr, "Erro\n");
   exit(1);
}

void match(char expectedToken) {
   if (token == expectedToken) token = getchar();
   else error();
}

int main(int argc, char *argv[]) {
   int result;
   token = getchar(); /* carrega a marca com o primeiro caractere para verificação à frente */

   result = exp();
   if (token == '\n') /* teste final de linha */
      printf("Resultado = %d\n", result);
   else error(); /* caracteres indevidos na linha */
   return 0;
}

int exp(void) {
   int temp = term();
   while ((token == '+') || (token == '-'))
      switch(token) {
         case '+' : match('+');
	            temp += term();
		    break;
         case '-' : match('-');
	            temp -= term();
		    break;
      }
   return temp;
}

int term(void) {
   int temp = factor();
   while (token == '*') {
      match('*');
      temp *= factor();
   }
   return temp;
}

int factor(void) {
   int temp;
   if (token == '(') {
      match('(');
      temp = exp();
      match(')');
   } else if (isdigit(token)) {
      ungetc(token, stdin);
      scanf("%d", &temp);
      token = getchar();
   }
   else error();
   return temp;
}

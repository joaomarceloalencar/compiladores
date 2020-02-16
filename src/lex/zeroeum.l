 /* Definições */
%%
 /* Regras */

(1*(01|001)?1*)*(0|00)? { printf("Ok\n"); }
.*                      { printf("Not Ok\n"); }  

%% 
 /* Subrotinas */
int yywrap(void) {
   printf("Terminei.\n");
   return 1;
}

int main(void) {
   yylex();
   return 0;
}

/*********************************************/
/* Arquivo: main.c                           */
/* Programa principal para o compilador TINY */
/* Compiladores: princípios e práticas       */
/* Kenneth C. Louden                         */
/*********************************************/

#include "globals.h"

/* ajuste NO_PARSE para TRUE para um compilador que efetue apenas a varredura */
#define NO_PARSE FALSE 

/* ajuste NO_ANALYZE para TRUE para um compilador que efetue apenas a análise sintática */
#define NO_ANALYZE TRUE

/* ajuste NO_CODE para TRUE para um compilador que não gere código */
#define NO_CODE TRUE


#include "util.h"
#if NO_PARSE
   #include "scan.h"
#else
   #include "parse.h"
   #if !NO_ANALYZE
      #include "analyze.h"
      #if !NO_CODE
         #include "cgen.h"
      #endif
   #endif
#endif

/* alocação de variáveis globais */
int lineno = 0;
FILE *source;
FILE *listing;
FILE *code;

/* alocação e ajuste de marcadores de acompanhamento da execução */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = TRUE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

int main(int argc, char *argv[]) {
   TreeNode * syntaxTree;
   char pgm[20]; /*nome do arquivo de código-fonte */
   if (argc != 2) {
      fprintf(stderr, "usage: %s <filename>\n", argv[0]);
      exit(1);
   }
   strcpy(pgm, argv[1]);
   if (strchr(pgm, '.') == NULL)
      strcat(pgm, ".tny");
   source = fopen(pgm, "r");
   if (source == NULL) {
      fprintf(stderr, "File %s not found\n", pgm);
      exit(1);
   }
   listing = stdout; /* envio de listagem para a tela */
   fprintf(listing, "\nTINY COMPILATION: %s\n", pgm);
#if NO_PARSE
   while (getToken() != ENDFILE);
#else
   syntaxTree = parse();
   if (TraceParse) {
      fprintf(listing, "\nSyntax Tree:\n");
      printTree(syntaxTree);
   }
#if !NO_ANALYZE
   if (! Error) {
      fprintf(listing, "\nBuilding Symbol Table...\n");
      buildSymtab(syntaxTree);
      fprintf(listing, "\nChecking Types...\n");
      typeCheck(syntaxTree);
      fprintf(listing, "\nType Checking Finished\n");
   }
#if !NO_CODE
   if (! Error) {
      char *codefile;
      int fnlen = strcspn(pgm, ".");
      codefile = (char *) calloc(fnlen + 4, sizeof(char));
      strncpy(codefile, pgm, fnlen);
      strcat(codefile, ".tm");
      code = fopen(codefile, "w");
      if (code == NULL) {
         printf("Unable to open %s\n", codefile);
         exit(1);
      }
      codeGen(syntaxTree, codefile);
      fclose(code);
   }
#endif
#endif
#endif
   return 0;
}

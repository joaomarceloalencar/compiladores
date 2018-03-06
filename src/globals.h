/****************************************************/
/* Arquivo: globals.h                               */
/* Tipos e variáveis globais para o compilador TINY */
/* devem vir antes dos outros arquivos include      */
/* Compiladores: princípios e práticas              */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = quantidade de palavras reservadas */
#define MAXRESERVED 8

typedef enum {
   /* Marcas de Controle */
   ENDFILE, ERROR,
   /* Palavras reservadas */
   IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
   /* Marcas Multicaracteres */
   ID, NUM,
   /* Símbolos especiais */
   ASSIGN, EQ, LT, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, SEMI
} TokenType;

extern FILE *source;  /* arquivo texto de código fonte */
extern FILE *listing; /* arquivo texto da listagem de saída */
extern FILE *code;    /* arquivo texto de código para o simulador TM*/

extern int lineno;    /* enumeração das linhas da fonta da listagem */

/**********************************************************/
/******* Árvore sintática para a análise sintática ********/
/**********************************************************/

typedef enum {StmtK, ExpK} NodeKind;
typedef enum {IfK, RepeatK, AssignK, ReadK, WriteK} StmtKind;
typedef enum {OpK, ConstK, IdK} ExpKind;

/* ExpType é usada para verificação de tipos */
typedef enum {Void, Integer, Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode {
   struct treenode *children[MAXCHILDREN];
   struct treeNode *sibling;
   int lineno;
   NodeKind nodekind;
   union { StmtKind stmt, ExpKind exp; } kind;
   union {
      TokenType op;
      int val;
      char *name;
   } attr;
   ExpType type; /* para verificação de tipos de expressões */
} TreeNode;

/***********************************************************/
/******* Marcadores para acompanhamento de execução ********/
/***********************************************************/

/* EchoSource = TRUE ecoa o programa-fonte no arquivo de listagem com enumeração de linhas durante a análise sintática */
extern int EchoSource;

/* TraceScan = TRUE imprime informações de marcadores no arquivo de listagem quando cada marcado é reconhecido pelo sistema de varredura */
extern int TraceScan;

/* TraceParse = TRUE imprime a árvore sintática no arquivo de listagem em forma linearizada (com identificadores para os filhos) */
extern int TraceParse;

/* TraceAnalyze = TRUE coloca no arquivo de listagem as inserções e buscas na tabela de símbolos */
extern int TraceAnalyze;

/* TraceCode = TRUE escreve os comentátios no arquivo de código TM à medida que o código é gerado */
extern int TraceCode;

/* Error = TRUE impede novas passadas se ocorrer um error */
extern int Error;
#endif

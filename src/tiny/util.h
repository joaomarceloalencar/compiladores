/****************************************************/
/* Arquivo: util.h                                  */
/* Funções auxiliares para o compílador TINY        */
/* Compiladores: princípios e práticas              */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/* Procedimento printToken imprime um marcador e seu lexema no arquivo de listagem */
void printToken(TokenType, const char*);

/* Função newStmtNode cria um novo nó de declaração ara a construção da árvore sintática */
TreeNode *newStmtNode(StmtKind);

/* Função newExpNode cria um novo nó de expressão ara a construção da árvore sintática */
TreeNode *newExpNode(ExpKind);

/* Função copyString aloca e cria nova cópia de uma cadeia existente */
char *copyString(char *);

/* procedimento printTree imprime um árvore sintática no arquivo de listagem usando tabulação para indicar subárvores */
void printTree(TreeNode *);

#endif

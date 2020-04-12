/***************************************************************/
/* Arquivo: util.c                                             */
/* Implementações de cfnções auxiliares para o compílador TINY */
/* Compiladores: princípios e práticas                         */
/* Kenneth C. Louden                                           */
/***************************************************************/

#include "globals.h"
#include "util.h"

/* Procedimento printToken imprime um marcador e seu lexema no arquivo de listagem */
void printToken(TokenType token, const char* tokenString) {
   switch(token) {
      case IF:
      case THEN:
      case ELSE:
      case END:
      case REPEAT:
      case UNTIL:
      case READ:
      case WRITE:
         fprintf(listing, "reserved word: %s\n", tokenString);
	 break;
      case ASSIGN: fprintf(listing, ":=\n"); break;
      case LT: fprintf(listing, "<\n"); break;
      case EQ: fprintf(listing, "=\n"); break;
      case LPAREN: fprintf(listing, "(\n"); break;
      case RPAREN: fprintf(listing, ")\n"); break;
      case SEMI: fprintf(listing, ";\n"); break;
      case PLUS: fprintf(listing, "+\n"); break;
      case MINUS: fprintf(listing, "-\n"); break;
      case TIMES: fprintf(listing, "*\n"); break;
      case OVER: fprintf(listing, "/\n"); break;
      case ENDFILE: fprintf(listing, "EOF\n"); break;
      case NUM: fprintf(listing, "NUM, val=%s\n", tokenString); break;
      case ID: fprintf(listing, "ID, name=%s\n", tokenString); break;
      case ERROR: fprintf(listing, "ERROR: %s\n", tokenString); break;
      default: /* nunca deveria acontecer */
         fprintf(listing, "Unknown token: %d\n", token);
   }
}

/* Função newStmtNode cria um novo nó de declaração ara a construção da árvore sintática */
TreeNode *newStmtNode(StmtKind kind) {
   TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
   int i;
   if (t == NULL)
      fprintf(listing, "Out of Memory error at line %d\n", lineno);
   else {
      for (i = 0; i< MAXCHILDREN; ++i) t->child[i] = NULL;
      t->sibling = NULL;
      t->nodekind = StmtK;
      t->kind.stmt = kind;
      t->lineno = lineno;
   }
   return t;
}

/* Função newExpNode cria um novo nó de expressão ara a construção da árvore sintática */
TreeNode *newExpNode(ExpKind kind) {
   TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
   int i;
   if (t == NULL)
      fprintf(listing, "Out of Memory error at line %d\n", lineno);
   else { 
      for (i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
      t->sibling = NULL;
      t->nodekind = ExpK;
      t->kind.exp = kind;
      t->lineno = lineno;
      t->type = Void;
   }
   return t;
}

/* Função copyString aloca e cria nova cópia de uma cadeia existente */
char *copyString(char *s) {
   int n;
   char *t;
   if (s == NULL) return NULL;
   n = strlen(s) + 1;
   t = malloc(n);
   if (t == NULL)
      fprintf(listing, "Out of memory error ar line %d\n", lineno);
   else strcpy(t,s);
   return t;
}

/* Variável indentno usada por printTree para armazenar a quantidade corrente de espaços para tabulação */
static int indentno = 0;

/* Macros para aumentar/diminuir a tabulação */
#define INDENT indentno += 2
#define UNINDENT indentno -= 2

/* printSpaces tabiula por espaços de impressão */
static void printSpaces(void) {
   int i;
   for (i = 0; i < indentno; i++) {
      fprintf(listing, " ");
   }
}

/* procedimento printTree imprime um árvore sintática no arquivo de listagem usando tabulação para indicar subárvores */
void printTree(TreeNode * tree) {
   int i;
   INDENT;
   while (tree != NULL) {
      printSpaces();
      if (tree->nodekind == StmtK) {
         switch (tree->kind.stmt) {
	    case IfK:
	       fprintf(listing, "If\n");
	       break;
	    case RepeatK:
	       fprintf(listing, "Repeat\n");
	       break;
	    case AssignK:
	       fprintf(listing, "Assign to: %s\n", tree->attr.name);
	       break;
	    case ReadK:
	       fprintf(listing, "Read: %s\n", tree->attr.name);
	       break;
	    case WriteK:
	       fprintf(listing, "Write\n");
	       break;
	    default:
	       fprintf(listing, "Unknown ExpNode kind\n");
	       break;
	 }
      } else if (tree->nodekind == ExpK ) {
         switch (tree->kind.exp) {
	    case OpK:
	       fprintf(listing, "Op: ");
	       printToken(tree->attr.op, "\0");
	       break;
	    case ConstK:
	       fprintf(listing, "const: %d\n", tree->attr.val);
	       break;
	    case IdK:
	       fprintf(listing, "Id: %s\n", tree->attr.name);
	       break;
            default:
	       fprintf(listing, "Unknown ExpNode kind\n");
	       break;
	 }

      } else fprintf(listing, "Unknown node kind\n");
      for (i = 0; i < MAXCHILDREN; i++)
         printTree(tree->child[i]);
      tree = tree -> sibling;
   }
   UNINDENT;
}


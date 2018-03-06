/***************************************************************/
/* Arquivo: util.c                                             */
/* Implementações de cfnções auxiliares para o compílador TINY */
/* Compiladores: princípios e práticas                         */
/* Kenneth C. Louden                                           */
/***************************************************************/

/* Procedimento printToken imprime um marcador e seu lexema no arquivo de listagem */
void printToken(TokenType, const char*) {
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
TreeNode *newStmtNode(StmtKind) {
   TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
   int i;
   if (t == NULL)
      fprintf(listing, "Out of Memory error at line %d\n", lineno);
   else {
      for (i = 0; i< MAXCHILDREN ++i) t->child[i] = NULL;
      t->sibling = NULL;
      t->nodekind = StmtK;
      t->kind.stmt = kind;
      t->lineno = lineno;
   }
   return t;
}

/* Função newExpNode cria um novo nó de expressão ara a construção da árvore sintática */
TreeNode *newExpNode(ExpKind) {
   TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
   int i;
   if (t == NULL)
      fprintf(listing, "Out of Memory error at line %d\n", lineno);
   else { 
      for (i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
      t->sibling = NULL;
      t->nodeKind = ExpK;
      t->kind.exp = kind;
      t->lineno = lineno;
      t->type = Void;
   }
   return t;
}

/* Função copyString aloca e cria nova cópia de uma cadeia existente */
char *copyString(char *) {
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

/* procedimento printTree imprime um árvore sintática no arquivo de listagem usando tabulação para indicar subárvores */
void printTree(TreeNode *);


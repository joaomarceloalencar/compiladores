/********************************************/
/* Arquivo: tiny.y                          */
/* Arquivo de especificação TINY Yacc/Bison */
/* Compiladores: Princípios e Práticas      */ 
/* Kenneth C. Louden                        */
/********************************************/

%{
#define YYPARSER

#include "globals.h"
#include "util.h"
#include "scan.h"

#define YYSTYPE TreeNode *
static char *savedName;     /* para uso em atribuições */
static int savedLineNo;     /* idem */
static TreeNode *savedTree; /* armazena árvore sintática para retorno posterior */

%}

%token IF THEN ELSE END REPEAT UNTIL READ WRITE
%token ID NUM
%token ASSIGN EQ LT PLUS MINUS TIMES OVER LPAREN RPAREN SEMI
%token ERROR

%%                          /* Gramática para TINY */

program         : stmt_seq { savedTree = $1; }
                ;

stmt_seq        : stmt_seq SEMI stmt { 
                    YYSTYPE t = $1;
                    if (t != NULL) {
                        while (t->sibling != NULL)
                            t = t->sibling;
                        t->sibling = $3;
                        $$ = $1;
                    } else {
                        $$ = $3;
                    }
                }
                | stmt { $$ = $1; }
                ;

stmt            : if_stmt { $$ = $1; }
                | repeat_stmt { $$ = $1; }
                | assign_stmt { $$ = $1; }
                | read_stmt { $$ = $1; }
                | write_stmt { $$ = $1; }
                | error { $$ = $1; }
                ;

if_stmt         : IF exp THEN stmt_seq END {
                    $$ = newStmtNode(IfK);
                    $$->child[0] = $2;
                    $$->child[1] = $4;
                }
                | IF exp THEN stmt_seq ELSE stmt_seq END {
                    $$ = newStmtNode(IfK);
                    $$->child[0] = $2;
                    $$->child[1] = $4;
                    $$->child[2] = $6;
                }
                ;

repeat_stmt     : REPEAT stmt_seq UNTIL exp {
                    $$ = newStmtNode(RepeatK);
                    $$->child[0] = $2;
                    $$->child[1] = $4;
                }
                ;

assign_stmt     : ID {
                    savedName = copyString(tokenString);
                    savedLineNo = lineno;
                } ASSIGN exp {
                    $$ = newStmtNode(AssignK);
                    $$->child[0] = $4;
                    $$->attr.name = savedName;
                    $$->lineno = savedLineNo;
                }
                ;

read_stmt       : READ ID {
                    $$ = newStmtNode(ReadK);
                    $$->attr.name = copyString(tokenString);
                }
                ;

write_stmt      : WRITE ID {
                    $$ = newStmtNode(WriteK);
                    $$->child[0] = $2;
                }
                ;
            
exp             : simple_exp LT simple_exp {
                    $$ = newExpNode(OpK);
                    $$->child[0] = $1;
                    $$->child[1] = $3;
                    $$->attr.op = LT;
                }
                | simple_exp EQ simple_exp {
                    $$ = newExpNode(OpK);
                    $$->child[0] = $1;
                    $$->child[1] = $3;
                    $$->attr.op = EQ;
                }
                | simple_exp { $$ = $1; }
                ;

simple_exp      : simple_exp PLUS term {
                    $$ = newExpNode(OpK);
                    $$->child[0] = $1;
                    $$->child[1] = $3;
                    $$->attr.op = PLUS;
                }
                | simple_exp MINUS term {
                    $$ = newExpNode(OpK);
                    $$->child[0] = $1;
                    $$->child[1] = $3;
                    $$->attr.op = MINUS;
                }
                | term { $$ = $1; }
                ;

term            : term TIMES factor {
                    $$ = newExpNode(OpK);
                    $$->child[0] = $1;
                    $$->child[1] = $3;
                    $$->attr.op = TIMES;
                }
                | simple_exp OVER term {
                    $$ = newExpNode(OpK);
                    $$->child[0] = $1;
                    $$->child[1] = $3;
                    $$->attr.op = OVER;
                }
                | factor { $$ = $1; }
                ;

factor          : LPAREN exp RPAREN { $$ = $2; } 
                | NUM {
                    $$ = newExpNode(ConstK);
                    $$->attr.val = atoi(tokenString);
                }
                | ID {
                    $$ = newExpNode(IdK);
                    $$->attr.name = copyString(tokenString);
                }
                | error { $$ = NULL; }
                ;

%%

int yyerror(char *message) {
    fprintf(listing, "Erro de sintaxe na linha %d: %s\n", lineno, message);
    fprintf(listing, "Token atual: ");
    printToken(yychar, tokenString);
    Error = TRUE;
    return 0;
}

/* yylex ativa getToken para tornar a saída Yacc 
 * compatível com versões anteriores do
 * sistema de varredura TINY

int yylex(void) {
    return getToken();
}
*/

TreeNode *parse(void) {
    yyparse();
    return savedTree;
}
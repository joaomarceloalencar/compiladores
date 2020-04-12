/********************************************/
/* Arquivo: tiny.l                          */
/* Específicação Lex para TINY              */
/* Compiladores: Princípios e Práticas      */ 
/* Kenneth C. Louden                        */
/********************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"

/* lexema do identificador ou palavra reservada */
char tokenString[MAXTOKENLEN + 1];
%}

digit      [0-9]
number     {digit}+
letter     [a-zA-Z]
identifier {letter}+
newline    \newline
whitespace [ \t]*

%%

"if"          { return IF; }
"then"        { return THEN; }
"else"        { return ELSE; }
"end"         { return END; }
"repeat"      { return REPEAT; }
"until"       { return UNTIL; }
"read"        { return READ; }
"write"       { return WRITE; }

":="          { return ASSIGN; }
"="           { return EQ; }
"<"           { return LT; }
"+"           { return PLUS; }
"-"           { return MINUS; }
"*"           { return TIMES; }
"/"           { return OVER; }
"("           { return LPAREN; }
")"           { return RPAREN; }
";"           { return SEMI; }

{number}      { return NUM; }
{identifier}  { return NUM; }
{newline}     { lineno++; }
{whitespace}  { /* pular espaços em branco */ }

"{"           {
                char c;
                do {
                    c = input();
                    if (c == '\n') lineno++;
                } while (c != '}');
              }
.*            { return ERROR; }

%%

int yywrap(void) {
   return 1;
}

TokenType getToken(void) {
    static int firstTime = TRUE;
    TokenType currentToken;
    if (firstTime) {
        firstTime = FALSE;
        lineno++;
        yyin = source;
        yyout = listing;
    }
    currentToken = yylex();
    strncpy(tokenString, yytext, MAXTOKENLEN);
    if (TraceScan) {
        fprintf(listing, "\t%d:", lineno);
        printToken(currentToken, tokenString);
    }
    return currentToken;
}
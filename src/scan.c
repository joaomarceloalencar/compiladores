/****************************************************************/
/* Arquivo: scan.c                                              */
/* Implementação do sistema de varredura para o compilador TINY */
/* Compiladores: princípios e práticas                          */
/* Kenneth C. Louden                                            */
/****************************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"

/* estados do DFA de varredura */
typedef enum {
   START, INASSIGN, INCOMMENT, INNUM, INID, DONE
} StateType;

/* lexema do identificador ou palavra reservada. */
char tokenString[MAXTOKENLEN + 1];

/* BUFLEN = tamanho do repositório de entrada para linhas do código-fonte */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* preserva a linha corrente */
static int linepos = 0;      /* posição corrente em lineBuf */
static int bufsize = 0;      /* tamanho corrente da cadeia do repositório */

/* getNextChar captura o caractere seguinte diferente de espaço em branco em lineBuf, e lê uma nova linha se linebuf tiver sido totalmente usado */
static char getNextChar(void) {
   if (!(linepos < bufsize)) {
      lineno ++;
      if (fgets(lineBuf, BUFLEN - 1, source) {
         if (EchoSource) fprintf(listing, "%4d: %s", lineno, lineBuf);
	 bufsize = strlen(lineBuf);
	 linepos = 0;
	 return lineBuf[linepos++];
      }
      else return EOF
   }
   else return lineBuf[linepos++];
}

/* ungetNextChar retrocede um caractere em lineBuf */
static void ungetNextChar(void) {
   linepos --;
}

/* tabela de verificação de palavras reservadas */
static struct {
  char *str;
  TokenType tok;
} reservedWords[MAXRESERVED] = {{"if", IF}, {"then", THEN}, {"else", ELSE}, {"end", END}, 
                                {"repeat", REPEAT}, {"until", UNTIL}, {"read", READ}, {"write", WRITE}};

/* busca de um identificador para ver se é uma palavra reservada, usa busca linear */
static TokenType reservedLookup (char *s) {
   int i;
   for (i = 0;  i < MAXRESERVED; i++)
      if (!strcmp(s, reservedWords[i].str))
         return reservedWords[i].tok;
   return ID;
}

/******************************/
/* Função básica de varredura */
/******************************/
/* função getToken retorna o marcador seguinte no arquivo-fonte */
TokenType getToken(void) {
   /* índice para armazenar em tokenString */
   int tokenStringIndex = 0;

   /* preserva o marcador corrente para o retorno */
   TokenType currentToken;

   /* estado corrente - sempre inicia em START */
   StateType state = START;

   /* marca para indicar gravação em tokenString */
   int save;
 
   while (state != DONE) {
      char c = getNextChar();
      save = TRUE;
      switch (state) {
         case START:
	    if (isdigit(c))
	       state = INNUM;
	    else if (isalpha(c))
	       state = INID;
	    else if (c == ':')
	       state = INASSIGN;
	    else if ((c == ' ') || (c == '\t') || (c == '\n'))
	       save = FALSE;
	    else if (c == '{') {
	       save = FALSE;
	       state = INCOMMENT;
	    } else {
	       state = DONE;
	       switch (c) {
	          case EOF:
		     save = FALSE;
		     currentToken = ENDFILE;
		     break;
		  case '=' :
		     currentToken = EQ;
		     break;
		  case '<' :
		     currentToken = LT;
		     break;
	          case '+' :
		     currentToken = PLUS;
		     break;
		  case '-' :
		     currentToken = MINUS:
		     break;
		  case '*' :
		     currentToken = TIMES;
		     break;
		  case '/' :
		     currentToken = OVER:
		     break;
	          case '(' :
		     currentToken = LPAREN
		     break;
		  case ')' :
		     currentToken = RPAREN;
		     break;
		  case ';':
		     currentToken = SEMI;
		     break;
                  default:
		     currentToken = ERROR;
		     break;
	       }
	    }
	    break;
         case INCOMMENT:
	    save = FALSE;
	    if (c == '}') state = START;
	    break;
         case INASSIGN:
	    state = DONE;
	    if (c == '=') 
	       currentToken = ASSIGN;
	    else {
	       /* volta para a entrada */
	       ungetNextChar();
	       save = FALSE;
	       currentToken = ERROR;
	    }
	    break;
         case INNUM:
	    if (!isdigit(c)) {
	       /* volta para entrada */
	       ungetNextChar();
	       save = FALSE;
	       state = DONE;
	       currentToken = NUM;
	    }
	    break;
         case INID:
	    if (!isalpha(c)) {
               /* volta para entrada */
	       ungetNextChar();
	       save = FALSE;
	       state = DONE;
	       currentToken = ID;
	    }
	    break;
         case DONE:
	 default: /* nunca deveria acontecer */
	    fprintf(listing, "Scanner Bug: state = %d\n", state);
	    state = DONE;
	    currentToken = ERROR;
	    break;
      }
      if ((save) && (tokenStringIndex <= MAXTOKENLEN))
         tokenString[tokenStringIndex++] = c;
      if (state == DONE) {
         tokenString[tokenStringIndex] = '\0';
	 if (currentToken == ID)
	    currentToken = reservedLookup(tokenString);
      }
   }
   if (TraceScan) {
      fprintf(listing, "\t%d:", lineno);
      printToken(currentToken, tokenString);
   }
   return currentToken;
} /* termina getToken */


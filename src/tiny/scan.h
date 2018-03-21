/************************************************************/
/* Arquivo: scan.h                                          */
/* Interface do sistema de varredura para o compilador TINY */
/* Compiladores: princípios e práticas                      */
/* Kenneth C. Louden                                        */
/************************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_

/* MAXTOKENLEN é o tamanho de um marcador */
#define MAXTOKENLEN 40

/* matriz tokenString armazena o lexema de cada marcador */
extern char tokenString[MAXTOKENLEN + 1];

/* função getToken retorna o marcador seguinte no arquivo-fonte */
TokenType getToken(void);

#endif

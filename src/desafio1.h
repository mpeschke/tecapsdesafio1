#ifndef CABECALHO_DESAFIO1_H_INCLUDED
#define CABECALHO_DESAFIO1_H_INCLUDED

#define BOOL int
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>

/*
 * Analisadores Léxicos (analisam uma sentença para validar
 * a sintaxe dos comandos 'add', 'del', 'info', 'query' e
 * '000').
*/
BOOL addcommandlexicalanalyser(const char *const sentence);

BOOL delcommandlexicalanalyser(const char *const sentence);

BOOL infocommandlexicalanalyser(const char *const sentence);

BOOL querycommandlexicalanalyser(const char *const sentence);

BOOL terminatecommandlexicalanalyser(const char *const sentence);

void iniciaCRUD(void);

#endif

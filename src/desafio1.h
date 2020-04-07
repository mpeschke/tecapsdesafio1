#ifndef CABECALHO_DESAFIO1_H_INCLUDED
#define CABECALHO_DESAFIO1_H_INCLUDED

#define BOOL int
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>

#define INDIVIDUOMAXID 3
#define INDIVIDUOMAXFIRSTNAME 50
#define INDIVIDUOMAXLASTNAME 50
#define INDIVIDUOMAXBIRTHDAY 10
#define INDIVIDUOMAXPHONE 16

struct Individuo {
    char paramId[INDIVIDUOMAXID];
    char firstName[INDIVIDUOMAXFIRSTNAME];
    char lastName[INDIVIDUOMAXLASTNAME];
    char birthday[INDIVIDUOMAXBIRTHDAY];
    char phone[INDIVIDUOMAXPHONE];
} typedef stIndividuo;

struct Query {
    char fn[INDIVIDUOMAXFIRSTNAME];
    char ln[INDIVIDUOMAXLASTNAME];
    char bd[INDIVIDUOMAXBIRTHDAY];
    char pn[INDIVIDUOMAXPHONE];
} typedef stQuery;

/*
 * Analisadores Léxicos (analisam uma sentença para validar
 * a sintaxe dos comandos 'add', 'del', 'info', 'query' e
 * '000').
*/
BOOL addcommandlexicalanalyser(const char *const sentence);

BOOL delcommandlexicalanalyser(const char *const sentence);

BOOL infocommandlexicalanalyser(const char *const sentence);

BOOL querycommandlexicalanalyser(const char *const sentence, stQuery* pqry);

BOOL terminatecommandlexicalanalyser(const char *const sentence);

void iniciaCRUD(void);

#endif

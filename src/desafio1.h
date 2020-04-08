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
    char paramId[INDIVIDUOMAXID+1];
    char firstName[INDIVIDUOMAXFIRSTNAME+1];
    char lastName[INDIVIDUOMAXLASTNAME+1];
    char birthday[INDIVIDUOMAXBIRTHDAY+1];
    char phone[INDIVIDUOMAXPHONE+1];
} typedef stIndividuo;

struct Query {
    char fn[INDIVIDUOMAXFIRSTNAME+1];
    char ln[INDIVIDUOMAXLASTNAME+1];
    char bd[INDIVIDUOMAXBIRTHDAY+1];
    char pn[INDIVIDUOMAXPHONE+1];
} typedef stQuery;

/*
 * Analisadores Léxicos (analisam uma sentença para validar
 * a sintaxe dos comandos 'add', 'del', 'info', 'query' e
 * '000').
*/
BOOL addcommandlexicalanalyser(const char *const sentence, stIndividuo* pindividuo);

BOOL delcommandlexicalanalyser(const char *const sentence, stIndividuo* pindividuo);

BOOL infocommandlexicalanalyser(const char *const sentence, stIndividuo* pindividuo);

BOOL querycommandlexicalanalyser(const char *const sentence, stQuery* pqry);

BOOL terminatecommandlexicalanalyser(const char *const sentence);

void addcommand(const stIndividuo *const pindividuo);

BOOL terminatecommand(void);

void infocommand(const stIndividuo *const pindividuo);

void querycommand(const stQuery *const pquery);

void iniciaCRUD(void);

#endif

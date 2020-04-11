#ifndef CABECALHO_DESAFIO1_H_INCLUDED
#define CABECALHO_DESAFIO1_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Não há tipo booleano em C, portanto
// vamos criar um para facilitar a leitura
// de operações booleanas no código:
#define BOOL int
#define TRUE 1
#define FALSE 0

#define INDIVIDUOMAXID 3
#define INDIVIDUOMAXFIRSTNAME 50
#define INDIVIDUOMAXLASTNAME 50
#define INDIVIDUOMAXBIRTHDAY 10
#define INDIVIDUOMAXPHONE 16
// Indicando aqui qual o valor do maior tamanho dos parâmetros listados acima.
#define LARGESTINDIVIDUOPARAMSIZE 50

/*
 * Estrutura para organizar as informações de um indivíduo.
 *
*/
struct Individuo {
    char paramId[INDIVIDUOMAXID+1];
    char firstName[INDIVIDUOMAXFIRSTNAME+1];
    char lastName[INDIVIDUOMAXLASTNAME+1];
    char birthday[INDIVIDUOMAXBIRTHDAY+1];
    char phone[INDIVIDUOMAXPHONE+1];
} typedef stIndividuo;

/*
 * Estrutura para organizar os parâmetros de busca ('query').
 *
*/
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

/*
 * Os comandos do sistema ('add', 'del', 'info', 'query' e
 * '000').
*/
void addcommand(const stIndividuo *const pindividuo);

void infocommand(const stIndividuo *const pindividuo);

void querycommand(const stQuery *const pquery);

BOOL terminatecommand(void);

/*
 * Inicia a captura dos comandos digitados pelo usuário.
 *
*/
void iniciaCRUD(void);

#endif

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
// Determina aqui qual o valor do maior tamanho dos parâmetros listados acima.
#define LARGESTPARAMSIZE 50

#define MAXDATABASESIZE 100

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

stIndividuo database[MAXDATABASESIZE];

// Exemplo de comando 'add': 'add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190'
// 'add' = 3, 'id' = 3(máximo de 100), 'firstname' = 7(máximo de 100), 'lastname' = 10(máximo de 100),
// 'birthday' = 10, 'phone' = 16, espaços = 5.
// Máximo comprimento da string: 237
static const int MAXADDSENTENCESIZE = 237;
// Exemplo de comando 'del': 'del 123'
// 'del' = 3, 'id' = 3(mínimo de 1, máximo de 3), espaços = 1.
// Máximo comprimento da string: 7
// Mínimo comprimento da string: 5
static const int MAXDELSENTENCESIZE = 7;
static const int MINDELSENTENCESIZE = 5;
// Exemplo de comando 'info': 'info 123'
// 'info' = 4, 'id' = 3(máximo de 3), espaços = 1.
// Máximo comprimento da string: 8
static const int MAXINFOSENTENCESIZE = 8;
static const int MININFOSENTENCESIZE = 6;
// Exemplo de comando 'query': 'query fn:João ln:Ninguém 123 bd:00/00/0000 pn:+00-00-0000-0000'
// 'query' = 5, 'fn:FIRSTNAME' = 3 ('fn:') + (tamanho máximo de primeiro nome: 50),
// 'ln:LASTNAME' = 3 ('ln:') + (tamanho máximo de sobrenome: 50),
// 'bd:00/00/0000' = 3 ('bd:') + (tamanho máximo de birthday: 10),
// 'pn:+00-00-0000-0000' = 3 ('pn:') + (tamanho máximo de phone: 16), espaços = 5.
// Máximo comprimento da string: 148
// 'xx:'
#define QUERYPARAMIDSIZE 3
#define MAXQUERYFNSIZE (QUERYPARAMIDSIZE+INDIVIDUOMAXLASTNAME)
#define MAXQUERYLNSIZE (QUERYPARAMIDSIZE+INDIVIDUOMAXLASTNAME)
#define MAXQUERYBDSIZE (QUERYPARAMIDSIZE+INDIVIDUOMAXBIRTHDAY)
#define MAXQUERYPNSIZE (QUERYPARAMIDSIZE+INDIVIDUOMAXPHONE)
#define MAXQUERYSENTENCESIZE (5 + MAXQUERYFNSIZE + MAXQUERYLNSIZE + MAXQUERYBDSIZE + MAXQUERYPNSIZE)
static const char* QUERYFN = "fn:";
static const char* QUERYLN = "ln:";
static const char* QUERYBD = "bd:";
static const char* QUERYPN = "pn:";
#define MINQUERYSENTENCESIZE (5 + 1 + QUERYPARAMIDSIZE + 1)

static const char SENTENCETOKENSEPARATOR = ' ';

/*
 * Enumeração: lista todos os tipos possíveis de comandos do sistema.
 * Obs: o comando 'invalid', implementado nesse sistema,
 * apenas executa uma regra do exercício: não imprime nada, pois o
 * programa não conseguiu fazer o parsing do comando (comando incorreto
 * ou não identificado).
*/
static const int NUMOFCOMMANDS = 5;
enum systemcommands {invalid, add, del, info, query, terminate};

const char *const getcommanddescription(const enum systemcommands command);

BOOL validatetokenaddverb(const char *const verb);

BOOL validatetokenaddcommandidparam(const char *const idparam);

BOOL validatetokenaddcommandfirstnameparam(const char *const firstnameparam);

BOOL validatetokenaddcommandlastnameparam(const char *const lastnameparam);

BOOL validatetokenaddcommandbirthdayparam(const char *const birthdayparam);

BOOL validatetokenaddcommandphoneparam(const char *const phoneparam);

BOOL addcommandlexicalanalyser(const char *const sentence);

BOOL delcommandlexicalanalyser(const char *const sentence);

BOOL infocommandlexicalanalyser(const char *const sentence);

BOOL querycommandlexicalanalyser(const char *const sentence);

enum systemcommands commandparser(const char* candidate);

#endif

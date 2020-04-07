#include <stdlib.h>
#include "desafio1.h"

// Determina aqui qual o valor do maior tamanho dos parâmetros listados acima.
#define LARGESTPARAMSIZE 50

#define MAXDATABASESIZE 100

stIndividuo database[MAXDATABASESIZE];

// Exemplo de comando 'add': 'add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190'
// 'add' = 3, 'id' = 3(máximo de 3), 'firstname' = 7(máximo de 50), 'lastname' = 10(máximo de 50),
// 'birthday' = 10, 'phone' = 16, espaços = 5.
// Máximo comprimento da string: 137
static const int MAXADDSENTENCESIZE = 137;
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
// Exemplo de comando 'terminate': '000' (máximo de 3 caracteres).
#define TERMINATEPARAMIDSIZE 3

// Para auxiliar o programa a utilizar o maior buffer disponível
// para interpretar lexicamente os comandos, definimos qual é o maior
// buffer dos comandos implementados aqui:
#define MAXSENTENCESIZE MAXQUERYSENTENCESIZE

static const char SENTENCETOKENSEPARATOR = ' ';

static const int ADDVERBDESCRIPTIONPOSITION = 0;
static const int DELCOMMANDDESCRIPTIONPOSITION = 1;
static const int INFOCOMMANDDESCRIPTIONPOSITION = 2;
static const int QUERYCOMMANDDESCRIPTIONPOSITION = 3;
static const int TERMINATECOMMANDDESCRIPTIONPOSITION = 4;

/*
 * Array: descrição de texto dos possíveis comandos implementados no sistema.
*/
const char commandinitializers[5][8] =
{
    "add ",
    "del ",
    "info ",
    "query ",
    "000"
};

const char commandverbs[5][10] =
{
    "add",
    "del",
    "info",
    "query",
    "000"
};

/*
 * Funções que compõem um analisador léxico: uma 'sentença' (sentence) é composta por palavras
 * (genericamente, 'tokens'). Cada token é analisado para identificar seu sentido. Quem
 * no final faz a análise para entender o 'significado' da sentença, no contexto dos tokens
 * econtrados, é o analisador léxico (lexical analyser).
 */

int advancetonexttoken(const char *const sentence, const int *const pinitialposition, const int *const psentencesize)
{
    // Para procurar pelo próximo token, deve estar apontando para um separador de tokens.
    // Se já estiver num caracter válido para token, retorna essa posição como o início de
    // um token válido.
    int i = *pinitialposition;

    while((i < *psentencesize) && (sentence[i] == SENTENCETOKENSEPARATOR))
        i++;

    return i;
}

BOOL getsentencetoken(const int* const  pposicaoleiturainicial,
                      int*              pposicaoleiturafinal,
                      const char* const sentence,
                      const int* const  pmaxsizesentence,
                      char*             token,
                      const int* const  pmaxsizetoken)
{
    // Limpa todo o buffer provido para receber o token.
    memset((void*)token, '\0', *pmaxsizetoken);

    int i = 0;
    int j = -1;
    *pposicaoleiturafinal = *pposicaoleiturainicial;
    for(i = *pposicaoleiturainicial; i < *pmaxsizesentence; i++)
    {
        if(sentence[i] != SENTENCETOKENSEPARATOR)
        {
            // O buffer do token tem um tamanho limitado, não necessariamente igual
            // ao buffer da sentença.
            if(j+1 < *pmaxsizetoken)
            {
                *token = sentence[i];
                token++;
            }
            j++;
        }
        else
            break;
    }

    *pposicaoleiturafinal = *pposicaoleiturainicial + j;
    return (j != -1);
}

BOOL validatetokenaddverb(const char *const verb)
{
    if(strcmp(commandverbs[ADDVERBDESCRIPTIONPOSITION], verb) == 0)
        return TRUE;
    else
        return FALSE;
}

BOOL validatetokenaddcommandidparam(const char *const idparam)
{
    int length = strlen(idparam);
    return (length > 0 && length <= INDIVIDUOMAXID);
}

BOOL validatetokenaddcommandfirstnameparam(const char *const firstnameparam)
{return (strlen(firstnameparam) <= INDIVIDUOMAXFIRSTNAME);}

BOOL validatetokenaddcommandlastnameparam(const char *const lastnameparam)
{return (strlen(lastnameparam) <= INDIVIDUOMAXLASTNAME);}

BOOL validatetokenaddcommandbirthdayparam(const char *const birthdayparam)
{return (strlen(birthdayparam) == INDIVIDUOMAXBIRTHDAY);}

BOOL validatetokenaddcommandphoneparam(const char *const phoneparam)
{return (strlen(phoneparam) == INDIVIDUOMAXPHONE);}

BOOL validatetokendelverb(const char *const verb)
{
    if(strcmp(commandverbs[DELCOMMANDDESCRIPTIONPOSITION], verb) == 0)
        return TRUE;
    else
        return FALSE;
}

BOOL validatetokendelcommandidparam(const char *const idparam)
{return validatetokenaddcommandidparam(idparam);}

BOOL validatetokeninfoverb(const char *const verb)
{
    if(strcmp(commandverbs[INFOCOMMANDDESCRIPTIONPOSITION], verb) == 0)
        return TRUE;
    else
        return FALSE;
}

BOOL validatetokeninfocommandidparam(const char *const idparam)
{return validatetokenaddcommandidparam(idparam);}

BOOL validatetokenqueryverb(const char *const verb)
{
    if(strcmp(commandverbs[QUERYCOMMANDDESCRIPTIONPOSITION], verb) == 0)
        return TRUE;
    else
        return FALSE;
}

BOOL validatetokenterminateverb(const char *const verb)
{
    if(strcmp(commandverbs[TERMINATECOMMANDDESCRIPTIONPOSITION], verb) == 0)
        return TRUE;
    else
        return FALSE;
}

BOOL validatetokenqueryparam(const char *const param, stQuery* pQry)
{
    int size = strlen(param);

    if(size <= QUERYPARAMIDSIZE) // O parâmetro deve conter pelo menos o identificador de busca 'xx:' e 1 caracter de busca.
        return FALSE;

    char paramtype[QUERYPARAMIDSIZE] = {'\0'};
    strncpy(paramtype, param, QUERYPARAMIDSIZE);

    // Query do primeiro nome.
    if (strcmp(paramtype, QUERYFN) == 0)
    {
        // Uma validação anterior já preencheu o primeiro nome - significa que há duplicidade de parâmetros.
        if(strlen(pQry->fn) != 0)
            return FALSE;

        // Valida o tamanho máximo do valor desse parâmetro de primeiro nome.
        if(strlen(param) > (MAXQUERYFNSIZE))
            return FALSE;

        for(int i = (QUERYPARAMIDSIZE); i < size; i++)
            pQry->fn[i-QUERYPARAMIDSIZE] = param[i];
        return TRUE;
    }

    // Query do último nome.
    if (strcmp(paramtype, QUERYLN) == 0)
    {
        // Uma validação anterior já preencheu o sobrenome - significa que há duplicidade de parâmetros.
        if(strlen(pQry->ln) != 0)
            return FALSE;

        // Valida o tamanho máximo do valor desse parâmetro de sobrenome.
        if(strlen(param) > (MAXQUERYLNSIZE))
            return FALSE;

        for(int i = (QUERYPARAMIDSIZE); i < size; i++)
            pQry->ln[i-QUERYPARAMIDSIZE] = param[i];
        return TRUE;
    }

    // Query do aniversário.
    if (strcmp(paramtype, QUERYBD) == 0)
    {
        // Uma validação anterior já preencheu o aniversário - significa que há duplicidade de parâmetros.
        if(strlen(pQry->bd) != 0)
            return FALSE;

        // Valida o tamanho esperado do valor desse parâmetro de aniversário.
        if(strlen(param) != (MAXQUERYBDSIZE))
            return FALSE;

        for(int i = (QUERYPARAMIDSIZE); i < size; i++)
            pQry->bd[i-QUERYPARAMIDSIZE] = param[i];
        return TRUE;
    }

    // Query do telefone.
    if (strcmp(paramtype, QUERYPN) == 0)
    {
        // Uma validação anterior já preencheu o telefone - significa que há duplicidade de parâmetros.
        if(strlen(pQry->pn) != 0)
            return FALSE;

        // Valida o tamanho esperado do valor desse parâmetro de telefone.
        if(strlen(param) != (MAXQUERYPNSIZE))
            return FALSE;

        for(int i = (QUERYPARAMIDSIZE); i < size; i++)
            pQry->pn[i-QUERYPARAMIDSIZE] = param[i];
        return TRUE;
    }

    // Não foi encontrada nenhuma query válida.
    return FALSE;
}

BOOL addcommandlexicalanalyser(const char *const sentence)
{
    int sentencesize = strlen(sentence);
    if (sentencesize > MAXADDSENTENCESIZE)
        return FALSE;

    char tokenbuffer[MAXADDSENTENCESIZE];

    int tokeninitialpos = 0;
    int tokenfinalpos = tokeninitialpos;

    tokeninitialpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddverb(tokenbuffer))
        return FALSE;

    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandidparam(tokenbuffer))
        return FALSE;

    stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
    strcpy(individuo.paramId, tokenbuffer);

    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandfirstnameparam(tokenbuffer))
        return FALSE;

    strcpy(individuo.firstName, tokenbuffer);

    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandlastnameparam(tokenbuffer))
        return FALSE;

    strcpy(individuo.lastName, tokenbuffer);

    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandbirthdayparam(tokenbuffer))
        return FALSE;

    strcpy(individuo.birthday, tokenbuffer);

    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandphoneparam(tokenbuffer))
        return FALSE;

    strcpy(individuo.phone, tokenbuffer);

    // Se encontrar outros tokens inesperados, com ou sem valor sintático, invalida o comando add.
    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    return TRUE;
}

BOOL delcommandlexicalanalyser(const char *const sentence)
{
    int sentencesize = strlen(sentence);
    if (sentencesize < MINDELSENTENCESIZE)
        return FALSE;

    char tokenbuffer[MAXDELSENTENCESIZE];

    int tokeninitialpos = 0;
    int tokenfinalpos = tokeninitialpos;

    tokeninitialpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXDELSENTENCESIZE))
        return FALSE;

    if(!validatetokendelverb(tokenbuffer))
        return FALSE;

    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXDELSENTENCESIZE))
        return FALSE;

    if(!validatetokendelcommandidparam(tokenbuffer))
        return FALSE;

    stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
    strcpy(individuo.paramId, tokenbuffer);

    // Se encontrar outros tokens inesperados, com ou sem valor sintático, invalida o comando del.
    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXDELSENTENCESIZE))
        return FALSE;

    return TRUE;
}

BOOL infocommandlexicalanalyser(const char *const sentence, stIndividuo* pindividuo)
{
    int sentencesize = strlen(sentence);
    if (sentencesize < MININFOSENTENCESIZE)
        return FALSE;

    char tokenbuffer[MAXINFOSENTENCESIZE];

    int tokeninitialpos = 0;
    int tokenfinalpos = tokeninitialpos;

    tokeninitialpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXINFOSENTENCESIZE))
        return FALSE;

    if(!validatetokeninfoverb(tokenbuffer))
        return FALSE;

    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXINFOSENTENCESIZE))
        return FALSE;

    if(!validatetokeninfocommandidparam(tokenbuffer))
        return FALSE;

    strcpy(pindividuo->paramId, tokenbuffer);

    // Se encontrar outros tokens inesperados, com ou sem valor sintático, invalida o comando info.
    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXINFOSENTENCESIZE))
        return FALSE;

    return TRUE;
}

BOOL querycommandlexicalanalyser(const char *const sentence, stQuery* pqry)
{
    static const int maxquerysentencesize = MAXQUERYSENTENCESIZE;
    int sentencesize = strlen(sentence);
    if (sentencesize < MINQUERYSENTENCESIZE)
        return FALSE;

    if (sentencesize > MAXQUERYSENTENCESIZE)
        return FALSE;

    char tokenbuffer[MAXQUERYSENTENCESIZE];

    int tokeninitialpos = 0;
    int tokenfinalpos = tokeninitialpos;

    tokeninitialpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &maxquerysentencesize))
        return FALSE;

    if(!validatetokenqueryverb(tokenbuffer))
        return FALSE;

    BOOL error = FALSE;

    do
    {
        tokeninitialpos = ++tokenfinalpos;
        tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
        if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &maxquerysentencesize))
            break;
        else if(!validatetokenqueryparam(tokenbuffer, pqry))
            error = TRUE;
    }while (!error);

    if(error)
        return FALSE;

    // Se encontrar outros tokens inesperados, com ou sem valor sintático, invalida o comando info.
    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &maxquerysentencesize))
        return FALSE;

    return TRUE;
}

BOOL terminatecommandlexicalanalyser(const char *const sentence)
{
    static const int terminatesentencesize = TERMINATEPARAMIDSIZE;
    int sentencesize = strlen(sentence);
    if (sentencesize < TERMINATEPARAMIDSIZE)
        return FALSE;

    char tokenbuffer[TERMINATEPARAMIDSIZE];

    int tokeninitialpos = 0;
    int tokenfinalpos = tokeninitialpos;

    tokeninitialpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &terminatesentencesize))
        return FALSE;

    if(!validatetokenterminateverb(tokenbuffer))
        return FALSE;

    // Se encontrar outros tokens inesperados, com ou sem valor sintático, invalida o comando terminate.
    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &terminatesentencesize))
        return FALSE;

    return TRUE;
}

BOOL terminatecommand(void)
{return TRUE;}

void iniciaCRUD(void)
{
    BOOL terminate = FALSE;

    while(!terminate)
    {
        char BUFF[MAXSENTENCESIZE] = {'\0'};
        fgets(BUFF, MAXSENTENCESIZE, stdin);
        stQuery qry = { .fn = {'\0'}, .ln = {'\0'}, .bd = {'\0'}, .pn = {'\0'}};
        stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};

        if(addcommandlexicalanalyser(BUFF))
            break;
        else if (delcommandlexicalanalyser(BUFF))
            break;
        else if (infocommandlexicalanalyser(BUFF, &individuo))
            break;
        else if (querycommandlexicalanalyser(BUFF, &qry))
            break;
        else if (terminatecommandlexicalanalyser(BUFF))
            terminate = terminatecommand();
    }
}

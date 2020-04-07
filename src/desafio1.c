#include <stdlib.h>
#include "desafio1.h"

static const int ADDVERBDESCRIPTIONPOSITION = 1;
static const int DELCOMMANDDESCRIPTIONPOSITION = 2;
static const int INFOCOMMANDDESCRIPTIONPOSITION = 3;
static const int QUERYCOMMANDDESCRIPTIONPOSITION = 4;
static const int TERMINATECOMMANDDESCRIPTIONPOSITION = 5;

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

const char commandverbs[6][10] =
{
    "invalid",
    "add",
    "del",
    "info",
    "query",
    "terminate"
};

const char *const getcommanddescription(const enum systemcommands command)
{
    if((command < invalid) || (command > terminate))
        return commandverbs[0];

    return commandverbs[command];
}

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

BOOL getsentencetoken(const int* const pposicaoleiturainicial,
                      int* pposicaoleiturafinal,
                      const char* const sentence,
                      const int* const pmaxsizesentence,
                      char* token,
                      const int* const pmaxsizetoken)
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
            *token = sentence[i];
            token++;
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

BOOL infocommandlexicalanalyser(const char *const sentence)
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

    stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
    strcpy(individuo.paramId, tokenbuffer);

    // Se encontrar outros tokens inesperados, com ou sem valor sintático, invalida o comando info.
    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXINFOSENTENCESIZE))
        return FALSE;

    return TRUE;
}

BOOL querycommandlexicalanalyser(const char *const sentence)
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
    stQuery qry = { .fn = {'\0'}, .ln = {'\0'}, .bd = {'\0'}, .pn = {'\0'}};
    do
    {
        tokeninitialpos = ++tokenfinalpos;
        tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
        if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &maxquerysentencesize))
            break;
        else if(!validatetokenqueryparam(tokenbuffer, &qry))
            error = TRUE;
    }while (!error);

    if(error)
        return FALSE;

    // Se encontrar outros tokens inesperados, com ou sem valor sintático, invalida o comando info.
    tokeninitialpos = ++tokenfinalpos;
    tokeninitialpos = tokenfinalpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXINFOSENTENCESIZE))
        return FALSE;

    return TRUE;
}

enum systemcommands commandparser(const char* candidate)
{
    for(enum systemcommands commanditem = add; commanditem <= NUMOFCOMMANDS; commanditem++)
        if (strcmp(candidate, commandinitializers[commanditem-1]) == 0)
            return commanditem;

    return invalid;
}

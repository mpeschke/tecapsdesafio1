/*
* Desafio 1
* Matheus Peschke de Azevedo - RA: 20396209
* Gustavo Caldas de Souza - RA: 21352329
*/
#include "desafio1.h"

/*
 *
 ***************************** DATABASE*******************************************************
 *
 * Número aleatório máximo definido. Como a APS foi publicada
 * antes da aula de alocação dinâmica de memória,
 * vamos limitar a memória de stack a 100 registros máximos.
*/
#define MAXDATABASESIZE 100

// O intervalo dos registros (stIndividuo) vai de 0 a 99 (MAXDATABASE, zero based index).
// Vamos considerar -1 como 'fora do intervalo', ou 'não encontrado'.
#define RECORDNOTFOUNDDATABASEINDEX -1

// 'Banco de dados' de indivíduos.
stIndividuo database[MAXDATABASESIZE];

// Localiza um registro buscando pelo seu 'índice' paramId.
int searchdatabaserecord(const stIndividuo *const pindividuo)
{
    for(unsigned long i = 0; i < MAXDATABASESIZE; i++)
        if(strcmp(pindividuo->paramId, database[i].paramId) == 0)
            return i;

    return RECORDNOTFOUNDDATABASEINDEX;
}

// Algoritmo clássico de ordenamento (sorting), usando um elemento
// temporário para fazer uma troca de elementos. Essa função ordena
// todos os indivíduos no banco de dados por ID, em ordem crescente.
void sortdatabase(void)
{
    for (int i = 0; i < MAXDATABASESIZE; ++i)
        for (int j = 0; j < MAXDATABASESIZE; j++)
        {
            // Em ordem crescente
            if (atoi(database[i].paramId) < atoi(database[j].paramId))
            {
                stIndividuo tmp = database[i];
                database[i] = database[j];
                database[j] = tmp;
            }
        }
}

/*
 *
 *********************ANALISADOR LÉXICO (TOKENIZADOR)*****************************************
 *
 * Definições que fazem parte de um analisador léxico:
 *
 * 'sentença' = a linha de comando com todos os seus parâmetros
 * 'token' = um item que esteja separados dos outros por um ou mais espaços.
 * 'verbo' = o primeiro token, que identifica o tipo de comando
 * 'parâmetro' = todos os outros tokens, após o token de verbo.
 *
 * Exemplo:
 *
 * add               123               Igor               Borges               25/12/1990               +55-11-2222-3333
 * ^                 ^                 ^                  ^                    ^                        ^
 * |                 |                 |                  |                    |                        |
 * token (verbo)     token (parâmetro) token (parâmetro)  token (parâmetro)    token (parâmetro)        token (parâmetro)
*/
static const char SENTENCETOKENSEPARATOR = ' ';

// Array: descrição de texto dos possíveis verbos de comando.
const char commandverbs[5][10] =
{
    "add",
    "del",
    "info",
    "query",
    "000"
};
static const int DESCRPOSVERBADD = 0;
static const int DESCRPOSVERBDEL = 1;
static const int DESCRPOSITIONVERBINFO = 2;
static const int DESCRPOSVERBQUERY = 3;
static const int DESCRPOSVERBTERMINATE = 4;

/* A partir do cursor inicial fornecido, avança até encontrar o próximo token.
 *
 * Exemplo:
 *          10        20        30        40        50        60        70        80        90        100       110
 *          |         |         |         |         |         |         |         |         |         |         |
 * 123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
 * add  ^            123               Igor               Borges               25/12/1990               +55-11-2222-3333
 * ^    |            ^                 ^                  ^                    ^                        ^
 * |    |            |                 |                  |                    |                        |
 * token|(verbo)     token (parâmetro) token (parâmetro)  token (parâmetro)    token (parâmetro)        token (parâmetro)
 *      |            |
 *      *pinitialposition = 6.
 *                   |
 *                   função retorna posição do próximo token, '123' = 19.
*/
int advancetonexttoken(const char *const    sentence,
                       const int *const     pinitialposition,
                       const int *const     psentencesize)
{
    // Para procurar pelo próximo token, deve estar apontando para um separador de tokens.
    // Se já estiver num caracter válido para token, retorna essa posição como o início de
    // um token válido.
    int i = *pinitialposition;

    while((i < *psentencesize) && (sentence[i] == SENTENCETOKENSEPARATOR))
        i++;

    return i;
}

/* Copia o token para um buffer, identificando também onde termina esse token na sentença.
 *
 * Exemplo:
 *          10        20        30        40        50        60        70        80        90        100       110
 *          |         |         |         |         |         |         |         |         |         |         |
 * 123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
 * add  ^            123               Igor               Borges               25/12/1990               +55-11-2222-3333
 * ^    |              ^               ^                  ^                    ^                        ^
 * |    |              |               |                  |                    |                        |
 * token|(verbo)     token (parâmetro) token (parâmetro)  token (parâmetro)    token (parâmetro)        token (parâmetro)
 *      |              |
 *      *pposicaoleiturainicial = 6.
 *                     |
 *                     *pposicaoleiturafinal = 21.
 *                   token = '123'
*/
BOOL getsentencetoken(const int* const  pposicaoleiturainicial,
                      int*              pposicaoleiturafinal,
                      const char* const sentence,
                      const int* const  pmaxsizesentence,
                      char*             token,
                      const int* const  pmaxsizetoken)
{
    // Limpa o buffer para receber um novo token.
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

/* Combina 'advancetonexttoken' e 'getsentencetoken' para facilitar a sequência de leitura
 * consecutiva dos tokens numa mesma sentença.
 * Copia o token para um buffer, identificando também onde termina esse token na sentença.
 *
 * Exemplo:
 *          10        20        30        40        50        60        70        80        90        100       110
 *          |         |         |         |         |         |         |         |         |         |         |
 * 123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
 * add  ^            123               Igor               Borges               25/12/1990               +55-11-2222-3333
 * ^    |            ^ ^               ^                  ^                    ^                        ^
 * |    |            | |               |                  |                    |                        |
 * token|(verbo)     token (parâmetro) token (parâmetro)  token (parâmetro)    token (parâmetro)        token (parâmetro)
 *      |            | |
 *      *pposicaoleiturainicial = 6.
 *                   |
 *                   *pposicaoleiturainicial = 19.
 *                     |
 *                     *pposicaoleiturafinal = 21.
 *                   token = '123'
*/
BOOL getnextsentencetoken(int* const        pposicaoleiturainicial,
                          int*              pposicaoleiturafinal,
                          const char* const sentence,
                          const int* const  pmaxsizesentence,
                          char*             token,
                          const int* const  pmaxsizetoken)
{
    const int sentencesize = strlen(sentence);

    *pposicaoleiturainicial = ++(*pposicaoleiturafinal);
    *pposicaoleiturainicial = *pposicaoleiturafinal = advancetonexttoken(sentence, pposicaoleiturainicial, &sentencesize);
    return getsentencetoken(pposicaoleiturainicial, pposicaoleiturafinal, sentence, pmaxsizesentence, token, pmaxsizetoken);
}

/*
 *
 *********************ANALISADOR LÉXICO (COMANDO 'ADD')***************************************
 *
*/
static const int MAXADDSENTENCESIZE = 137;

BOOL validatetokenaddverb(const char *const verb)
{return (strcmp(commandverbs[DESCRPOSVERBADD], verb) == 0);}

/*
 * Contornando o clássico problema de conversão léxica de string
 * para números. A função atoi() é bem conhecida por inúmeras falhas,
 * sendo a mais infame o retorno do mesmo número '0' quando a string
 * é igual a '0' ou 'SHIT', por exemplo.
 * Para evitar isso, utilizamos 'strtol', que provê um mecanismo
 * sólido para identificar falha ou sucesso na conversão léxica.
*/
BOOL validatetokenaddcommandidparam(const char *const idparam)
{
    char *eptr;
    int length = strlen(idparam);
    errno = 0;
    strtol(idparam, &eptr, 10); // Número de base 10.
    // Testa somente EINVAL (erro de conversão), e não ERANGE (erro de intervalo)
    // porque o buffer é pequeno demais para ter números muito grandes.
    BOOL conversiontonum = (errno != EINVAL) && (idparam != eptr);

    return ((length > 0) && (length <= INDIVIDUOMAXID) && conversiontonum);
}

BOOL validatetokenaddcommandfirstnameparam(const char *const firstnameparam)
{return (strlen(firstnameparam) <= INDIVIDUOMAXFIRSTNAME);}

BOOL validatetokenaddcommandlastnameparam(const char *const lastnameparam)
{return (strlen(lastnameparam) <= INDIVIDUOMAXLASTNAME);}

BOOL validatetokenaddcommandbirthdayparam(const char *const birthdayparam)
{return (strlen(birthdayparam) == INDIVIDUOMAXBIRTHDAY);}

BOOL validatetokenaddcommandphoneparam(const char *const phoneparam)
{return (strlen(phoneparam) == INDIVIDUOMAXPHONE);}

/*
* Dada a peculiaridade incomum do enunciado do exercício, no qual é possível
* identificar a existência de um indivíduo já cadastrado pelo seu ID através
* de um comando 'add' lexicamente INCORRETO:
*
* 'add 123 Joao Souza 11/10/2000 103-99'
*                                ^
*                                |
*                                token de telefone inválido
*
* temos que utilizar um analisador léxico customizado para esse cenário.
*/
BOOL addcommandlexicalanalyser_idonly(const char *const sentence, stIndividuo* pindividuo)
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

    if(!getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &MAXADDSENTENCESIZE, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    BOOL valid = validatetokenaddcommandidparam(tokenbuffer);

    if(valid)
        strcpy(pindividuo->paramId, tokenbuffer);

    return valid;
}

/*
* Exemplo de comando 'add': 'add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190'
* 'add' = 3, 'id' = 3(máximo de 3), 'firstname' = 7(máximo de 50), 'lastname' = 10(máximo de 50),
* 'birthday' = 10, 'phone' = 16, espaços = 5.
* Máximo comprimento da string: 3 + 3 + 50 + 50 + 10 + 16 + 5 = 137
*
* IMPORTANTE:
*
* Embora os exemplos de comandos no enunciado do desafio possibilitem inferir
* tipo, formato e tamanho de ID, aniversário e telefone, não há menção a tamanho máximo
* de nome e sobrenome. Dessa forma, para evitar problemas de buffers muito longos,
* vamos impor um limite de 50 caracteres para nome e sobrenome.
*
* Assume-se também, pelo enunciado, que o ID é numérico, de 000 a 999.
* O sistema vai armazenar '0', '00' e '000' como válidos e distintos.
*/
BOOL addcommandlexicalanalyser(const char *const sentence, stIndividuo* pindividuo)
{
    int sentencesize = strlen(sentence);
    if (sentencesize > MAXADDSENTENCESIZE)
        return FALSE;

    char tokenbuffer[MAXADDSENTENCESIZE];

    int tokeninitialpos = 0;
    int tokenfinalpos = tokeninitialpos;

    // Primeiro token deve ser o verbo do comando 'add'.
    tokeninitialpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddverb(tokenbuffer))
        return FALSE;

    // Próximo token deve ser o ID do indivíduo.
    if(!getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &MAXADDSENTENCESIZE, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandidparam(tokenbuffer))
        return FALSE;

    strcpy(pindividuo->paramId, tokenbuffer);

    // Próximo token deve ser o nome do indivíduo.
    if(!getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &MAXADDSENTENCESIZE, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandfirstnameparam(tokenbuffer))
        return FALSE;

    strcpy(pindividuo->firstName, tokenbuffer);

    // Próximo token deve ser o sobrenome do indivíduo.
    if(!getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &MAXADDSENTENCESIZE, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandlastnameparam(tokenbuffer))
        return FALSE;

    strcpy(pindividuo->lastName, tokenbuffer);

    // Próximo token deve ser o aniversário do indivíduo.
    if(!getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &MAXADDSENTENCESIZE, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandbirthdayparam(tokenbuffer))
        return FALSE;

    strcpy(pindividuo->birthday, tokenbuffer);

    // Próximo e último token deve ser o telefone do indivíduo.
    if(!getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &MAXADDSENTENCESIZE, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    if(!validatetokenaddcommandphoneparam(tokenbuffer))
        return FALSE;

    strcpy(pindividuo->phone, tokenbuffer);

    // Não pode haver mais tokens. Se encontrados, com ou sem valor léxico, a sentença é considerada inválida.
    if(getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXADDSENTENCESIZE))
        return FALSE;

    return TRUE;
}

/*
 *
 *********************ANALISADOR LÉXICO (COMANDO 'DEL')***************************************
 *
 * Exemplo de comando 'del': 'del 123'
 * 'del' = 3, 'id' = 3(mínimo de 1, máximo de 3), espaços = 1.
 * Máximo comprimento da string: 3 + 3 + 1 = 7
 * Mínimo comprimento da string: 3 + 1 + 1 = 5
*/
static const int MAXDELSENTENCESIZE = 7;
static const int MINDELSENTENCESIZE = 5;

BOOL validatetokendelcommandidparam(const char *const idparam)
{return validatetokenaddcommandidparam(idparam);}

BOOL validatetokendelverb(const char *const verb)
{return (strcmp(commandverbs[DESCRPOSVERBDEL], verb) == 0);}

BOOL delcommandlexicalanalyser(const char *const sentence, stIndividuo* pindividuo)
{
    int sentencesize = strlen(sentence);
    if (sentencesize < MINDELSENTENCESIZE)
        return FALSE;

    char tokenbuffer[MAXDELSENTENCESIZE];

    int tokeninitialpos = 0;
    int tokenfinalpos = tokeninitialpos;

    // Primeiro token deve ser o verbo do comando 'del'.
    tokeninitialpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXDELSENTENCESIZE))
        return FALSE;

    if(!validatetokendelverb(tokenbuffer))
        return FALSE;

    // Próximo token deve ser o ID do indivíduo.
    if(!getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXDELSENTENCESIZE))
        return FALSE;

    if(!validatetokendelcommandidparam(tokenbuffer))
        return FALSE;

    strcpy(pindividuo->paramId, tokenbuffer);

    // Não pode haver mais tokens. Se encontrados, com ou sem valor léxico, a sentença é considerada inválida.
    if(getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXDELSENTENCESIZE))
        return FALSE;

    return TRUE;
}

/*
 *
 *********************ANALISADOR LÉXICO (COMANDO 'INFO')**************************************
 *
 * Exemplo de comando 'info': 'info 123'
 * 'info' = 4, 'id' = 3(máximo de 3), espaços = 1.
 * Máximo comprimento da string: 4 + 3 + 1 = 8
*/
static const int MAXINFOSENTENCESIZE = 8;
static const int MININFOSENTENCESIZE = 6;

BOOL validatetokeninfoverb(const char *const verb)
{return (strcmp(commandverbs[DESCRPOSITIONVERBINFO], verb) == 0);}

BOOL validatetokeninfocommandidparam(const char *const idparam)
{return validatetokenaddcommandidparam(idparam);}

BOOL infocommandlexicalanalyser(const char *const sentence, stIndividuo* pindividuo)
{
    int sentencesize = strlen(sentence);
    if (sentencesize < MININFOSENTENCESIZE)
        return FALSE;

    char tokenbuffer[MAXINFOSENTENCESIZE];

    int tokeninitialpos = 0;
    int tokenfinalpos = tokeninitialpos;

    // Primeiro token deve ser o verbo do comando 'info'.
    tokeninitialpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXINFOSENTENCESIZE))
        return FALSE;

    if(!validatetokeninfoverb(tokenbuffer))
        return FALSE;

    // Próximo token deve ser o ID do indivíduo.
    if(!getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXINFOSENTENCESIZE))
        return FALSE;

    if(!validatetokeninfocommandidparam(tokenbuffer))
        return FALSE;

    strcpy(pindividuo->paramId, tokenbuffer);

    // Não pode haver mais tokens. Se encontrados, com ou sem valor léxico, a sentença é considerada inválida.
    if(getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &MAXINFOSENTENCESIZE))
        return FALSE;

    return TRUE;
}

/*
 *
 *********************ANALISADOR LÉXICO (COMANDO 'QUERY')*************************************
 *
 * Exemplo de comando 'query': 'query fn:João ln:Ninguém 123 bd:00/00/0000 pn:+00-00-0000-0000'
 * 'query' = 5, 'fn:FIRSTNAME' = 3 ('fn:') + (tamanho máximo de primeiro nome: 50),
 * 'ln:LASTNAME' = 3 ('ln:') + (tamanho máximo de sobrenome: 50),
 * 'bd:00/00/0000' = 3 ('bd:') + (tamanho máximo de birthday: 10),
 * 'pn:+00-00-0000-0000' = 3 ('pn:') + (tamanho máximo de phone: 16), espaços = 5.
 * Máximo comprimento da string: 5 + 3 + 50 + 3 + 50 + 3 + 10 + 3 + 10 + 3 + 16 + 5 = 148
*/
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
// Mínimo comprimento da string: 5 + 1 + 3 + 1 = 10
#define MINQUERYSENTENCESIZE (5 + 1 + QUERYPARAMIDSIZE + 1)

// Para auxiliar o programa a utilizar o maior buffer disponível
// para interpretar lexicamente as sentenças, definimos qual é o maior
// buffer dos comandos implementados até aqui:
#define MAXSENTENCESIZE MAXQUERYSENTENCESIZE

BOOL validatetokenqueryverb(const char *const verb)
{return (strcmp(commandverbs[DESCRPOSVERBQUERY], verb) == 0);}

// Valida o token e copia para o campo de parâmetro.
BOOL validatetokenqueryparamrules(const char *const token, char *const queryparam, const unsigned long maxqueryparamsize)
{
    int size = strlen(token);

    // Uma validação anterior já preencheu esse parâmetro - 2 ou mais tokens têm o mesmo significado léxico (ambiguidade).
    if(strlen(queryparam) != 0)
        return FALSE;

    // Valida o tamanho máximo do token.
    if(strlen(token) > (maxqueryparamsize))
        return FALSE;

    // Copia o conteúdo do token para o parâmetro.
    for(int i = (QUERYPARAMIDSIZE); i < size; i++)
        queryparam[i-QUERYPARAMIDSIZE] = token[i];
    return TRUE;
}

BOOL validatetokenqueryparam(const char *const token, stQuery* pQry)
{
    int size = strlen(token);

    // O parâmetro deve ter no mínimo o identificador de busca 'xx:' e 1 caracter de busca.
    if(size <= QUERYPARAMIDSIZE)
        return FALSE;

    char paramtype[QUERYPARAMIDSIZE] = {'\0'};
    strncpy(paramtype, token, QUERYPARAMIDSIZE);

    // Query do primeiro nome.
    if (strcmp(paramtype, QUERYFN) == 0)
        return validatetokenqueryparamrules(token, pQry->fn, MAXQUERYLNSIZE);

    // Query do último nome.
    if (strcmp(paramtype, QUERYLN) == 0)
        return validatetokenqueryparamrules(token, pQry->ln, MAXQUERYLNSIZE);

    // Query do aniversário.
    if (strcmp(paramtype, QUERYBD) == 0)
        return validatetokenqueryparamrules(token, pQry->bd, MAXQUERYBDSIZE);

    // Query do telefone.
    if (strcmp(paramtype, QUERYPN) == 0)
        return validatetokenqueryparamrules(token, pQry->pn, MAXQUERYPNSIZE);

    // Não foi encontrada nenhuma query válida.
    return FALSE;
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

    // Primeiro token deve ser o verbo do comando 'query'.
    tokeninitialpos = advancetonexttoken(sentence, &tokeninitialpos, &sentencesize);
    if(!getsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &maxquerysentencesize))
        return FALSE;

    if(!validatetokenqueryverb(tokenbuffer))
        return FALSE;

    BOOL error = FALSE;

    // Ao contrário dos outros comando, 'query' não requer um sequência de
    // seus parâmetros. Portanto, utilizaremos uma instância de stIndividuo
    // para validar os parâmetros do comando (sentido léxico, ambiguidade, etc).
    do
    {
        if(!getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &maxquerysentencesize))
            break;
        else if(!validatetokenqueryparam(tokenbuffer, pqry))
            error = TRUE;
    }while (!error);

    if(error)
        return FALSE;

    // Não pode haver mais tokens. Se encontrados, com ou sem valor léxico, a sentença é considerada inválida.
    if(getnextsentencetoken(&tokeninitialpos, &tokenfinalpos, sentence, &sentencesize, tokenbuffer, &maxquerysentencesize))
        return FALSE;

    return TRUE;
}

/*
 *
 *********************ANALISADOR LÉXICO (COMANDO 'TERMINATE')*********************************
 *
*/
// Exemplo de comando 'terminate': '000' (máximo de 3 caracteres).
#define TERMINATEPARAMIDSIZE 3

BOOL validatetokenterminateverb(const char *const verb)
{return (strcmp(commandverbs[DESCRPOSVERBTERMINATE], verb) == 0);}

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

/*
 *
 ***************************************(COMANDO 'ADD')***************************************
 *
*/
void addcommand(const stIndividuo *const pindividuo)
{
    BOOL found = FALSE;
    for(unsigned long i = 0; i < MAXDATABASESIZE; i++)
    {
        if(strcmp(pindividuo->paramId, database[i].paramId) == 0)
        {
            found = TRUE;
            break;
        }
    }

    if(found)
        printf("ID %s ja cadastrado\n", pindividuo->paramId);
    else
        for(unsigned long i = 0; i < MAXDATABASESIZE; i++)
            if(strlen(database[i].paramId) == 0)
            {
                strcpy(database[i].phone, pindividuo->phone);
                strcpy(database[i].paramId, pindividuo->paramId);
                strcpy(database[i].birthday, pindividuo->birthday);
                strcpy(database[i].firstName, pindividuo->firstName);
                strcpy(database[i].lastName, pindividuo->lastName);
                break;
            }
}

/*
 *
 ***************************************(COMANDO 'DEL')***************************************
 *
*/
void delcommand(const stIndividuo *const pindividuo)
{
    BOOL found = FALSE;
    for(unsigned long i = 0; i < MAXDATABASESIZE; i++)
    {
        if(strcmp(pindividuo->paramId, database[i].paramId) == 0)
        {
            found = TRUE;
            strcpy(database[i].phone, "");
            strcpy(database[i].paramId, "");
            strcpy(database[i].birthday, "");
            strcpy(database[i].firstName, "");
            strcpy(database[i].lastName, "");
            break;
        }
    }

    if(!found)
        printf("ID %s nao existente.\n", pindividuo->paramId);
}

/*
 *
 ***************************************(COMANDO 'INFO')**************************************
 *
*/
void infocommand(const stIndividuo *const pindividuo)
{
    BOOL found = FALSE;
    for(unsigned long i = 0; i < MAXDATABASESIZE; i++)
    {
        if(strcmp(pindividuo->paramId, database[i].paramId) == 0)
        {
            printf("%s %s %s %s\n",
                   database[i].firstName,
                   database[i].lastName,
                   database[i].birthday,
                   database[i].phone);
            found = TRUE;
            break;
        }
    }

    if(!found)
        printf("ID %s nao existente\n", pindividuo->paramId);
}

/*
 *
 ***************************************(COMANDO 'QUERY')*************************************
 *
*/
void querycommand(const stQuery *const pquery)
{
    // Antes de executar a busca, ordena o banco de dados - assim o resultado sempre
    // sairá ordenado.
    sortdatabase();

    BOOL match = FALSE;
    BOOL searchbd = strlen(pquery->bd);
    BOOL searchfn = strlen(pquery->fn);
    BOOL searchln = strlen(pquery->ln);
    BOOL searchpn = strlen(pquery->pn);
    for(unsigned long i = 0; i < MAXDATABASESIZE; i++)
    {
        match = TRUE;
        if(searchbd)
            match &= (strcmp(pquery->bd, database[i].birthday) == 0);
        if(searchfn)
            match &= (strcmp(pquery->fn, database[i].firstName) == 0);
        if(searchln)
            match &= (strcmp(pquery->ln, database[i].lastName) == 0);
        if(searchpn)
            match &= (strcmp(pquery->pn, database[i].phone) == 0);
        if(match)
            printf("%s ", database[i].paramId);
    }

    printf("\n");
}

/*
 *
 ***************************************(COMANDO 'TERMINATE')*********************************
 *
*/
BOOL terminatecommand(void)
{return TRUE;}

/*
 * fgets, ao contrário da função (insegura) scanf, inclui
 * os caracteres terminadores de linha (\n no Linux, \r\n no Windows).
 * Essa função coloca um caracter nulo na primeira instância desses
 * caracteres terminadores, garantindo um buffer contendo apenas
 * o token da sentença.
*/
void zero_fgets_trailchars(char* buff)
{buff[strcspn(buff, "\r\n")] = 0;}

/*
 *
 ***************************************CRUD ENGINE*******************************************
 *
*/
void iniciaCRUD(void)
{
    BOOL terminate = FALSE;

    while(!terminate)
    {
        char BUFF[MAXSENTENCESIZE] = {'\0'};
        stQuery qry = {
            .fn = {'\0'},
            .ln = {'\0'},
            .bd = {'\0'},
            .pn = {'\0'}
        };
        stIndividuo individuo = {
            .paramId = "",
            .firstName = "",
            .lastName = "",
            .birthday = "",
            .phone = ""
        };

        fgets(BUFF, MAXSENTENCESIZE, stdin);
        zero_fgets_trailchars(BUFF);

        if(addcommandlexicalanalyser_idonly(BUFF, &individuo))
            if(searchdatabaserecord(&individuo) == RECORDNOTFOUNDDATABASEINDEX)
            {
                if(addcommandlexicalanalyser(BUFF, &individuo))
                    addcommand(&individuo);
            }
            else
                addcommand(&individuo);
        else if (delcommandlexicalanalyser(BUFF, &individuo))
            delcommand(&individuo);
        else if (infocommandlexicalanalyser(BUFF, &individuo))
            infocommand(&individuo);
        else if (querycommandlexicalanalyser(BUFF, &qry))
            querycommand(&qry);
        else if (terminatecommandlexicalanalyser(BUFF))
            terminate = terminatecommand();
    }
}

// li e concordo com os termos da aps

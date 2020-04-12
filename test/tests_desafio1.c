/*
* Desafio 1
* Matheus Peschke de Azevedo - RA: 20396209
* Gustavo Caldas de Souza - RA: 21352329
*/
#include "tests_desafio1.h"

void test_unittests_desafio_1(const int lexicalanalyser, const char* sentence)
{
    stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
    stQuery qry = { .fn = {'\0'}, .ln = {'\0'}, .bd = {'\0'}, .pn = {'\0'}};

    switch(lexicalanalyser)
    {
        case 0:// Testa cenário válido para o analisador léxico 'addcommandlexicalanalyser'
        {
            BOOL ret = addcommandlexicalanalyser(sentence, &individuo);
            printf("Valor esperado: TRUE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        case 1:// Testa cenário válido para o analisador léxico 'delcommandlexicalanalyser'
        {
            BOOL ret = delcommandlexicalanalyser(sentence, &individuo);
            printf("Valor esperado: TRUE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        case 2:// Testa cenário válido para o analisador léxico 'infocommandlexicalanalyser'
        {
            BOOL ret = infocommandlexicalanalyser(sentence, &individuo);
            printf("Valor esperado: TRUE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        case 3:// Testa cenário válido para o analisador léxico 'querycommandlexicalanalyser'
        {
            BOOL ret = querycommandlexicalanalyser(sentence, &qry);
            printf("Valor esperado: TRUE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        case 4:// Testa cenário válido para o analisador léxico 'terminatecommandlexicalanalyser'
        {
            BOOL ret = terminatecommandlexicalanalyser(sentence);
            printf("Valor esperado: TRUE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        case 5:// Testa cenário INválido para o analisador léxico 'addcommandlexicalanalyser'
        {
            BOOL ret = addcommandlexicalanalyser(sentence, &individuo);
            printf("Valor esperado: FALSE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        case 6:// Testa cenário INválido para o analisador léxico 'delcommandlexicalanalyser'
        {
            BOOL ret = delcommandlexicalanalyser(sentence, &individuo);
            printf("Valor esperado: FALSE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        case 7:// Testa cenário INválido para o analisador léxico 'infocommandlexicalanalyser'
        {
            BOOL ret = infocommandlexicalanalyser(sentence, &individuo);
            printf("Valor esperado: FALSE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        case 8:// Testa cenário INválido para o analisador léxico 'querycommandlexicalanalyser'
        {
            BOOL ret = querycommandlexicalanalyser(sentence, &qry);
            printf("Valor esperado: FALSE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        case 9:// Testa cenário INválido para o analisador léxico 'terminatecommandlexicalanalyser'
        {
            BOOL ret = terminatecommandlexicalanalyser(sentence);
            printf("Valor esperado: FALSE. Valor retornado: %s.",
                   ret == TRUE ? "TRUE" : "FALSE");
            break;
        }
        default:
            break;
    };
}

int main(int argc, char* argv[])
{
    test_unittests_desafio_1(atoi(argv[1]), argv[2]);

    return 0;
}

// li e concordo com os termos da aps

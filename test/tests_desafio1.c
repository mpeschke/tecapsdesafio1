#include <stdio.h>
#include "desafio1.h"
#include "tests_desafio1.h"

void test_unittests_desafio_1(void)
{
    int testcounter = 0;
    int failed = 0;
    int passed = 0;

    // Testa cenários para os quais o analisador sintático 'addcommandlexicalanalyser' deve
    // validar a sentença como CORRETA (TRUE).
    for(int i = 0; i < 12; i++)
    {
        stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
        BOOL ret = addcommandlexicalanalyser(add_syntaticanalyser_valid_testcases[i], &individuo);
        printf("%s: Valor esperado: TRUE. Valor retornado: %s. Analisador sintático 'add' para a sentença '%s'.\n",
               ret == TRUE ? "PASSED" : "FAILED",
               ret == TRUE ? "TRUE" : "FALSE",
               add_syntaticanalyser_valid_testcases[i]);
        if(ret)
            passed++;
        else
            failed++;
        testcounter++;
    }

    // Testa cenários para os quais o analisador sintático 'delcommandlexicalanalyser' deve
    // validar a sentença como CORRETA (TRUE).
    printf("\n");
    for(int i = 0; i < 15; i++)
    {
        stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
        BOOL ret = delcommandlexicalanalyser(del_syntaticanalyser_valid_testcases[i], &individuo);
        printf("%s: Valor esperado: TRUE. Valor retornado: %s. Analisador sintático 'del' para a sentença '%s'.\n",
               ret == TRUE ? "PASSED" : "FAILED",
               ret == TRUE ? "TRUE" : "FALSE",
               del_syntaticanalyser_valid_testcases[i]);
        if(ret)
            passed++;
        else
            failed++;
        testcounter++;
    }

    // Testa cenários para os quais o analisador sintático 'infocommandlexicalanalyser' deve
    // validar a sentença como CORRETA (TRUE).
    printf("\n");
    for(int i = 0; i < 15; i++)
    {
        stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
        BOOL ret = infocommandlexicalanalyser(info_syntaticanalyser_valid_testcases[i], &individuo);
        printf("%s: Valor esperado: TRUE. Valor retornado: %s. Analisador sintático 'info' para a sentença '%s'.\n",
               ret == TRUE ? "PASSED" : "FAILED",
               ret == TRUE ? "TRUE" : "FALSE",
               info_syntaticanalyser_valid_testcases[i]);
        if(ret)
            passed++;
        else
            failed++;
        testcounter++;
    }

    // Testa cenários para os quais o analisador sintático 'querycommandlexicalanalyser' deve
    // validar a sentença como CORRETA (TRUE).
    printf("\n");
    for(int i = 0; i < 58; i++)
    {
        stQuery qry = { .fn = {'\0'}, .ln = {'\0'}, .bd = {'\0'}, .pn = {'\0'}};
        BOOL ret = querycommandlexicalanalyser(query_syntaticanalyser_valid_testcases[i], &qry);
        printf("%s: Valor esperado: TRUE. Valor retornado: %s. Analisador sintático 'query' para a sentença '%s'.\n",
               ret == TRUE ? "PASSED" : "FAILED",
               ret == TRUE ? "TRUE" : "FALSE",
               query_syntaticanalyser_valid_testcases[i]);
        if(ret)
            passed++;
        else
            failed++;
        testcounter++;
    }

    // Testa cenários para os quais o analisador sintático 'terminatecommandlexicalanalyser' deve
    // validar a sentença como CORRETA (TRUE).
    printf("\n");
    for(int i = 0; i < 5; i++)
    {
        BOOL ret = terminatecommandlexicalanalyser(terminate_syntaticanalyser_valid_testcases[i]);
        printf("%s: Valor esperado: TRUE. Valor retornado: %s. Analisador sintático 'terminate' para a sentença '%s'.\n",
               ret == TRUE ? "PASSED" : "FAILED",
               ret == TRUE ? "TRUE" : "FALSE",
               terminate_syntaticanalyser_valid_testcases[i]);
        if(ret)
            passed++;
        else
            failed++;
        testcounter++;
    }

    // Testa cenários para os quais o analisador sintático 'addcommandlexicalanalyser' deve
    // validar a sentença como INCORRETA (FALSE).
    printf("\n");
    for(int i = 0; i < 27; i++)
    {
        stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
        BOOL ret = addcommandlexicalanalyser(add_syntaticanalyser_invalid_testcases[i], &individuo);
        printf("%s: Valor esperado: FALSE. Valor retornado: %s. Analisador sintático 'add' para a sentença '%s'.\n",
               ret == TRUE ? "FAILED" : "PASSED",
               ret == TRUE ? "TRUE" : "FALSE",
               add_syntaticanalyser_invalid_testcases[i]);
        if(ret)
            failed++;
        else
            passed++;
        testcounter++;
    }

    // Testa cenários para os quais o analisador sintático 'delcommandlexicalanalyser' deve
    // validar a sentença como INCORRETA (FALSE).
    printf("\n");
    for(int i = 0; i < 25; i++)
    {
        stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
        BOOL ret = delcommandlexicalanalyser(del_syntaticanalyser_invalid_testcases[i], &individuo);
        printf("%s: Valor esperado: FALSE. Valor retornado: %s. Analisador sintático 'del' para a sentença '%s'.\n",
               ret == TRUE ? "FAILED" : "PASSED",
               ret == TRUE ? "TRUE" : "FALSE",
               del_syntaticanalyser_invalid_testcases[i]);
        if(ret)
            failed++;
        else
            passed++;
        testcounter++;
    }

    // Testa cenários para os quais o analisador sintático 'infocommandlexicalanalyser' deve
    // validar a sentença como INCORRETA (FALSE).
    printf("\n");
    for(int i = 0; i < 34; i++)
    {
        stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
        BOOL ret = infocommandlexicalanalyser(info_syntaticanalyser_invalid_testcases[i], &individuo);
        printf("%s: Valor esperado: FALSE. Valor retornado: %s. Analisador sintático 'info' para a sentença '%s'.\n",
               ret == TRUE ? "FAILED" : "PASSED",
               ret == TRUE ? "TRUE" : "FALSE",
               info_syntaticanalyser_invalid_testcases[i]);
        if(ret)
            failed++;
        else
            passed++;
        testcounter++;
    }

    // Testa cenários para os quais o analisador sintático 'querycommandlexicalanalyser' deve
    // validar a sentença como INCORRETA (FALSE).
    printf("\n");
    for(int i = 0; i < 69; i++)
    {
        stQuery qry = { .fn = {'\0'}, .ln = {'\0'}, .bd = {'\0'}, .pn = {'\0'}};
        BOOL ret = querycommandlexicalanalyser(query_syntaticanalyser_invalid_testcases[i], &qry);
        printf("%s: Valor esperado: FALSE. Valor retornado: %s. Analisador sintático 'query' para a sentença '%s'.\n",
               ret == TRUE ? "FAILED" : "PASSED",
               ret == TRUE ? "TRUE" : "FALSE",
               query_syntaticanalyser_invalid_testcases[i]);
        if(ret)
            failed++;
        else
            passed++;
        testcounter++;
    }

    // Testa cenários para os quais o analisador sintático 'terminatecommandlexicalanalyser' deve
    // validar a sentença como INCORRETA (FALSE).
    printf("\n");
    for(int i = 0; i < 10; i++)
    {
        BOOL ret = terminatecommandlexicalanalyser(terminate_syntaticanalyser_invalid_testcases[i]);
        printf("%s: Valor esperado: FALSE. Valor retornado: %s. Analisador sintático 'terminate' para a sentença '%s'.\n",
               ret == TRUE ? "FAILED" : "PASSED",
               ret == TRUE ? "TRUE" : "FALSE",
               terminate_syntaticanalyser_invalid_testcases[i]);
        if(ret)
            failed++;
        else
            passed++;
        testcounter++;
    }

    // Testa cenários onde o comando 'addcommandlexicalanalyser' deve
    // com sucesso criar um novo indivíduo.
    printf("\n");
    for(int i = 0; i < 12; i++)
    {
        stIndividuo individuo = { .paramId = "", .firstName = "", .lastName = "", .birthday = "", .phone = ""};
        addcommandlexicalanalyser(add_syntaticanalyser_valid_testcases[i], &individuo);
        addcommand(&individuo);
    }

    printf("\n\nTestes realizados: %d. (PASSED: %d, FAILED: %d)\n", testcounter, passed, failed);
}

int main()
{
    test_unittests_desafio_1();

    return 0;
}

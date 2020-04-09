#ifndef CABECALHO_TESTS_DESAFIO1_H_INCLUDED
#define CABECALHO_TESTS_DESAFIO1_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include "desafio1.h"

static const char add_syntaticanalyser_valid_testcases[12][66] =
{
    "add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190",
    "     add 124 Roberto Nascimento 01/01/1960 +55-21-0190-0190",
    "add       125 Roberto Nascimento 01/01/1960 +55-21-0190-0190",
    "add 1    Roberto Nascimento 01/01/1960 +55-21-0190-0190",
    "add 2 Roberto     Nascimento 01/01/1960 +55-21-0190-0190",
    "add 3 Roberto Nascimento      01/01/1960 +55-21-0190-0190",
    "add 4 Roberto Nascimento 01/01/1960       +55-21-0190-0190",
    "add 5 Roberto Nascimento 01/01/1960 +55-21-0190-0190     ",
    "      add 6 Roberto Nascimento 01/01/1960 +55-21-0190-0190    ",
    "add 7 Gustavo Gustavo 01/01/1960 +55-21-0190-0190",
    "add 8 Marcelo Marcelo AA/BB/CCCC +55-21-0190-0190",
    "add 9 Marcelo Marcelo 01/01/1960 +XX-WW-YYYY-ZZZZ"
};

static const char del_syntaticanalyser_valid_testcases[15][10] =
{
    "del 1",
    "del 0",
    "del 00",
    "del 000",
    " del 1",
    "del 1 ",
    " del 1 ",
    "del 12",
    " del 12",
    "del 12 ",
    " del 12 ",
    "del 123",
    " del 123",
    "del 123 ",
    " del 123 "
};

static const char info_syntaticanalyser_valid_testcases[15][11] =
{
    "info 1",
    "info 0",
    "info 00",
    "info 000",
    " info 1",
    "info 1 ",
    " info 1 ",
    "info 12",
    " info 12",
    "info 12 ",
    " info 12 ",
    "info 123",
    " info 123",
    "info 123 ",
    " info 123 "
};

static const char query_syntaticanalyser_valid_testcases[58][56] =
{
    "query fn:r",
    "query ln:n",
    " query ln:n",
    "query ln:n  ",
    " query ln:n  ",
    " query             ln:n  ",
    "query fn:Roberto",
    "query ln:Nascimento",
    "query bd:01/01/1960",
    "query pn:+55-21-0190-0190",
    " query pn:+55-21-0190-0190",
    "query pn:+55-21-0190-0190 ",
    " query pn:+55-21-0190-0190 ",
    " query             pn:+55-21-0190-0190 ",
    "query fn:Roberto ln:Nascimento",
    "query fn:Roberto bd:01/01/1960",
    "query fn:Roberto pn:+55-21-0190-0190",
    " query fn:Roberto pn:+55-21-0190-0190",
    "query fn:Roberto pn:+55-21-0190-0190 ",
    " query fn:Roberto pn:+55-21-0190-0190 ",
    " query fn:Roberto    pn:+55-21-0190-0190 ",
    "query ln:Nascimento fn:Roberto",
    "query ln:Nascimento bd:01/01/1960",
    "query ln:Nascimento pn:+55-21-0190-0190",
    " query ln:Nascimento pn:+55-21-0190-0190",
    "query ln:Nascimento pn:+55-21-0190-0190 ",
    " query ln:Nascimento pn:+55-21-0190-0190 ",
    " query ln:Nascimento      pn:+55-21-0190-0190 ",
    "query bd:01/01/1960 fn:Roberto",
    "query bd:01/01/1960 ln:Nascimento pn:+55-21-0190-0190",
    "query bd:01/01/1960 pn:+55-21-0190-0190",
    " query bd:01/01/1960 pn:+55-21-0190-0190",
    "query bd:01/01/1960 pn:+55-21-0190-0190 ",
    " query bd:01/01/1960 pn:+55-21-0190-0190 ",
    " query bd:01/01/1960      pn:+55-21-0190-0190 ",
    "query pn:+55-21-0190-0190 fn:Roberto",
    "query pn:+55-21-0190-0190 ln:Nascimento",
    "query pn:+55-21-0190-0190 bd:01/01/1960",
    " query pn:+55-21-0190-0190 bd:01/01/1960",
    "query pn:+55-21-0190-0190 bd:01/01/1960 ",
    " query pn:+55-21-0190-0190 bd:01/01/1960 ",
    " query    pn:+55-21-0190-0190    bd:01/01/1960 ",
    "query fn:Roberto ln:Nascimento bd:01/01/1960",
    "query fn:Roberto ln:Nascimento pn:+55-21-0190-0190",
    "query fn:Roberto pn:+55-21-0190-0190 ln:Nascimento",
    "query fn:Roberto bd:01/01/1960 ln:Nascimento",
    " query fn:Roberto bd:01/01/1960 ln:Nascimento",
    " query fn:Roberto bd:01/01/1960 ln:Nascimento ",
    "query fn:Roberto bd:01/01/1960 ln:Nascimento ",
    "query fn:Roberto    bd:01/01/1960     ln:Nascimento ",
    "query ln:Nascimento fn:Roberto bd:01/01/1960",
    "query ln:Nascimento fn:Roberto pn:+55-21-0190-0190",
    "query ln:Nascimento pn:+55-21-0190-0190 fn:Roberto",
    "query ln:Nascimento bd:01/01/1960 fn:Roberto",
    " query ln:Nascimento bd:01/01/1960 fn:Roberto",
    "query ln:Nascimento bd:01/01/1960 fn:Roberto ",
    " query ln:Nascimento bd:01/01/1960 fn:Roberto ",
    " query    ln:Nascimento    bd:01/01/1960    fn:Roberto "
};

static const char terminate_syntaticanalyser_valid_testcases[5][12] =
{
    "000",
    " 000",
    "000 ",
    " 000 ",
    "    000    "
};

static const char add_syntaticanalyser_invalid_testcases[27][67] =
{
    "",
    "                                             ",
    " ESSE NÃO É UM COMANDO ADD VÁLIDO            ",
    "ADD Carlos Irineu 99/88/9999 +00-00-0000-0000 444",
    "AdD Carlos Irineu 99/88/9999 +00-00-0000-0000 444",
    "Add Carlos Irineu 99/88/9999 +00-00-0000-0000 444",
    "aDd Carlos Irineu 99/88/9999 +00-00-0000-0000 444",
    "adD Carlos Irineu 99/88/9999 +00-00-0000-0000 444",
    "aDD Carlos Irineu 99/88/9999 +00-00-0000-0000 444",
    "add",
    "add A João Silva 01/02/2020 +51-33-9999-9988",
    "add BBB Carlos Irineu 99/88/9999 +00-00-0000-0000",
    "add Carlos Irineu 99/88/9999 +00-00-0000-0000 444",
    "444 Carlos Irineu 99/88/9999 +00-00-0000-0000",
    "add Gustavo Gustavo 01/01/1960 +55-21-0190-0190",
    "add  Marcelo Marcelo 01/01/1960 +55-21-0190-0190",
    "add 1 Marcelo 01/01/1960 +55-21-0190-0190",
    "add 1 01/01/1960 +55-21-0190-0190",
    "add 1 +55-21-0190-0190",
    "add 1 Marcelo Marcelo +55-21-0190-0190",
    "add 1 Marcelo Marcelo       +55-21-0190-0190",
    "add 1 Marcelo Marcelo 01/01/1960",
    "add 1 Marcelo Marcelo 01/0/1960 +55-21-0190-0190",
    "add 1 Marcelo Marcelo 01/000/1960 +55-21-0190-0190",
    "add 1 Marcelo Marcelo 01/01/1960 +55000-21-0190-0190",
    "add 1 Marcelo Marcelo 01/00/1960 +55-21-01 90-0190",
    "add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190 outro param"
};

static const char del_syntaticanalyser_invalid_testcases[25][96] =
{
    "",
    "   ",
    "del ",
    " del",
    "del",
    "123 del",
    "del a",
    "del ab",
    "del abc",
    "dell 123",
    "deel 123",
    "DEL 123",
    "DEl 123",
    "Del 123",
    "DeL 123",
    "del:123",
    "del 1234",
    " del 1234",
    " del     1234",
    " del     1234  ",
    "del 1 aproveita e add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190",
    "del 12 aproveita e add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190",
    "del 123 aproveita e add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190",
    "del ABC aproveita e add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190",
    "del ABC aproveita del 123 junto e também add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190"
};

static const char info_syntaticanalyser_invalid_testcases[34][96] =
{
    "",
    "   ",
    "info ",
    " info",
    "info",
    "info A",
    "info AB",
    "info ABC",
    "info  A",
    "info  AB",
    "info  ABC",
    "info  A ",
    "info  AB ",
    "info  ABC ",
    " info  A",
    " info  AB",
    " info  ABC",
    "   info     ABC    ",
    "123 info",
    "infoo 123",
    "iinfo 123",
    "INFO 123",
    "Info 123",
    "INfo 123",
    "INFo 123",
    "INfO 123",
    "InFO 123",
    "info:123",
    "info 1234",
    " info 1234",
    " info     1234",
    " info     1234  ",
    "info ABC aproveita e add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190",
    "del ABC aproveita del 123 junto e também add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190"
};

static const char query_syntaticanalyser_invalid_testcases[69][59] =
{
    "",
    "    ",
    "query ",
    " query ",
    "query",
    "query ln:",
    "query ln: ",
    "ln:n query",
    "QUERY ln:n",
    "Query ln:n",
    "QUery ln:n",
    "QUEry ln:n",
    "QUERy ln:n",
    "query fn:Rob erto",
    "query ln:Nas cimento",
    "query bd:01/01/1 960",
    "query pn:+55- 21-0190 -0190",
    " query pn:+ 55-21-0190-0190",
    "query pn:+ 55-21-0190-0190 ",
    " query pn:+55-21-0190-019 0 ",
    " query             pn:+55 -21-0190-0190 ",
    "query fn:Robe rto ln:Nascim ento",
    "query fn:Rob erto bd:01/01/ 1960",
    "query fn:Ro berto pn:+55-21-019 0-0190",
    " query fn:R oberto pn:+55-21- 0190-0190",
    "query fn:Ro berto pn:+55-21 -0190-0190 ",
    " query fn:Rob erto pn:+55-21-01 90-0190 ",
    " query fn:Robe rto    pn:+55-21-0190 -0190 ",
    "query ln:Nasc imento fn:Rob erto",
    "query ln:Nasci mento bd:01/01/ 1960",
    "query ln:Nasc imento pn:+55-21-019 -0190",
    " query ln:Nas to pn:+55-21-0 0190",
    "query ln:Nas mento pn:+55-21 -0190-0190 ",
    " query ln:Nas ento pn:+55-21- 0190 ",
    " query ln:Nas mento      pn:+55 90-0190 ",
    "query bd:01/ /1960 fn:Ro rto",
    "query bd:01/ /1960 ln:Nasc nto bd:0 /1960",
    "query bd:01 1/1960 pn:+55- 90-0190",
    " query bd:0 /1960 pn:+55-21- 0190",
    "query bd:01/ 960 pn:+55-21-0 0190 ",
    " query bd:01/0 0 pn:+55-21 -0190 ",
    " query bd:01 1960      pn:+55-2 90-0190 ",
    "query pn:+55 190-0190 fn:R to",
    "query pn:+55-2 0-0190 ln:Nas ento",
    "query pn:+5 1-0190-0190 bd: 01/1960",
    " query pn:+55- 0-0190 bd:01/ 1960",
    "query pn:+55- 190-0190 bd:01/0 60 ",
    " query pn:+55- 90-0190 bd:01/0 1960 ",
    " query    pn:+55-21- 190    bd:01 1960 ",
    "query fn:Ro to ln:Nasc ento bd:01/ 960",
    "query fn:Ro to ln:Nascim nto pn:+55-21 90-0190",
    "query fn:Robe o pn:+55-2 90-0190 ln:Na mento",
    "query fn:Ro o bd:01/ 60 ln:Nasc nto",
    " query fn:Ro to bd:01/0 960 ln:Nasci nto",
    " query fn:Rob to bd:01/ 1960 ln:Nas mento ",
    "query fn:Rob rto bd:01/01  ln:Na nto ",
    "query fn:Ro to    bd:01/0 1960     ln:Nas ento ",
    "query ln:Nasc ento fn:Robe to bd:01/0 60",
    "query ln:Nas ento fn:Ro rto pn:+55-21- -0190",
    "query ln:Nas ento pn:+55-2 190-0190 fn:Ro o",
    "query ln:Nasc ento bd:01/01/1960 fn:Roberto",
    " query ln:Nascimento bd:0 1/1960 fn:Roberto",
    "query ln:Nascimento bd:01/0 1960 fn:Roberto ",
    " query ln:Nascimento bd:01/01/1960 fn:Robe rto ",
    " query    ln:Nasc ento    bd:01/01/1960    fn:Roberto ",
    "query fn:Roberto ln:Nascimento bd:01/01/1960 fn:Roberto",
    "query fn:Roberto ln:Nascimento bd:01/01/1960 ln:Nascime",
    "query bd:01/01/1960 ln:Nascnto bd:01/01/1960 ln:Nascime",
    "query pn:+55-21-4444-0190 bd:01/01/1960 pn:+55-21-4444-0190"
};

static const char terminate_syntaticanalyser_invalid_testcases[10][23] =
{
    "",
    "   ",
    "000 termina aí",
    "OOO",
    "001",
    "0",
    "00",
    "000 000",
    "000 001",
    "000 DAVE, JUST WHAT..."
};

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

#endif

/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:parser.c
*/


#include "parserDef.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define table_row 60
int flag_eps;
nodecount = 0;

// returns firsts set of given token
int* getFirsts(char * input){

    char* line;
    line = (char*) malloc(sizeof(char)*100);
    char * token;
    size_t len = 0;
    int count = 0;
    ssize_t read;


    int firsts[25];

    FILE *fp = fopen("firsts.txt", "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        line[read - 1] = '\0';

        char* temp;
        temp = (char*) malloc(200*sizeof(char));

        strcpy(temp, line);


        token = strtok(temp, " ");
        if( token != NULL && strcmp(token, input) == 0){
            while(token!=NULL){
                token = strtok(NULL, " ");
                if(token==NULL){
                    break;
                }
                firsts[count++] = getColumnIndex(token);
            }
            break;
        }
    }

    firsts[count] = -1;

    fclose(fp);
    return firsts;
}

// returns firsts set of given set of tokens
int* first(char * input){
    int firsts[1000];
    int* current;
    int count = 0;
    char * token;
    char* save;

    char* temp;
    temp = (char*) malloc(200*sizeof(char));

    strcpy(temp, input);

    token = strtok_r(temp, " ", &save);

    char* token_copy;
    token_copy = (char*) malloc(200*sizeof(char));

    int epislonFound = 1;
    while(token!=NULL && epislonFound == 1){
        // printf("%s\n", token);
        epislonFound = 0;

        strcpy(token_copy, token);

        current = getFirsts(token_copy);
        int i = 0;
        while(current[i]!=-1){
            if(current[i] == 57) {
                epislonFound = 1;
            }
            firsts[count++] = current[i++];
        }
        token = strtok_r(NULL, " ", &save);

    }
    firsts[count] = -1;
    return firsts;
}

// returns follow set of given token
int* getFollows(char * input){

    char * line = NULL;
    char * token;
    size_t len = 0;
    int count = 0;
    ssize_t read;

    int follows[25];

    FILE *fp = fopen("follows.txt", "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        line[read - 1] = '\0';

        char* temp;
        temp = (char*) malloc(200*sizeof(char));

        strcpy(temp, line);

        token = strtok(temp, " ");

        if( token != NULL && strcmp(token, input) == 0){
            while(token!=NULL){
                token = strtok(NULL, " ");
                if(token==NULL){
                    break;
                }
                follows[count++] = getColumnIndex(token);
            }
            break;
        }
    }

    follows[count] = -1;

    fclose(fp);
    return follows;
}

int* follow(char * input){
    int firsts[1000];
    int* current;
    int count = 0;
    char * token;

    char* temp;
    temp = (char*) malloc(200*sizeof(char));

    strcpy(temp, input);

    token = strtok(temp, " ");

    int epislonFound = 0;
    while(token!=NULL && epislonFound == 1){
        epislonFound = 1;
        current = getFollows(token);
        int i = 0;
        while(current[i]!=-1){
            if(current[i] == 57) {
                epislonFound = 1;
            }
            firsts[count++] = current[i++];
        }
        token = strtok(NULL, " ");

    }
    firsts[count] = -1;
    return firsts;
}

// return id for token (non-terminals)
int getRowIndex(char* s)
{
    if(strcmp(s, "program") == 0) { return 100; }
    if(strcmp(s, "mainFunction") == 0) { return 101; }
    if(strcmp(s, "otherFunctions") == 0) { return 102; }
    if(strcmp(s, "function") == 0) { return 103; }
    if(strcmp(s, "input_par") == 0) { return 104; }
    if(strcmp(s, "output_par") == 0) { return 105; }
    if(strcmp(s, "parameter_list") == 0) { return 106; }
    if(strcmp(s, "dataType") == 0) { return 107; }
    if(strcmp(s, "primitiveDatatype") == 0) { return 108; }
    if(strcmp(s, "constructedDatatype") == 0) { return 109; }
    if(strcmp(s, "remaining_list") == 0) { return 110; }
    if(strcmp(s, "stmts") == 0) { return 111; }
    if(strcmp(s, "typeDefinitions") == 0) { return 112; }
    if(strcmp(s, "typeDefinition") == 0) { return 113; }
    if(strcmp(s, "fieldDefinitions") == 0) { return 114; }
    if(strcmp(s, "fieldDefinition") == 0) { return 115; }
    if(strcmp(s, "moreFields") == 0) { return 116; }
    if(strcmp(s, "declarations") == 0) { return 117; }
    if(strcmp(s, "declaration") == 0) { return 118; }
    if(strcmp(s, "global_or_not") == 0) { return 119; }
    if(strcmp(s, "otherStmts") == 0) { return 120; }
    if(strcmp(s, "stmt") == 0) { return 121; }
    if(strcmp(s, "assignmentStmt") == 0) { return 122; }
    if(strcmp(s, "singleOrRecId") == 0) { return 123; }
    if(strcmp(s, "funCallStmt") == 0) { return 124; }
    if(strcmp(s, "outputParameters") == 0) { return 125; }
    if(strcmp(s, "inputParameters") == 0) { return 126; }
    if(strcmp(s, "iterativeStmt") == 0) { return 127; }
    if(strcmp(s, "conditionalStmt") == 0) { return 128; }
    if(strcmp(s, "elsePart") == 0) { return 129; }
    if(strcmp(s, "ioStmt") == 0) { return 130; }
    if(strcmp(s, "allVar") == 0) { return 131; }
    if(strcmp(s, "arithmeticExpression") == 0) { return 132; }
    if(strcmp(s, "expPrime") == 0) { return 133; }
    if(strcmp(s, "term") == 0) { return 134; }
    if(strcmp(s, "termPrime") == 0) { return 135; }
    if(strcmp(s, "factor") == 0) { return 136; }
    if(strcmp(s, "highPrecedenceOperators") == 0) { return 137; }
    if(strcmp(s, "lowPrecedenceOperators") == 0) { return 138; }
    if(strcmp(s, "all") == 0) { return 139; }
    if(strcmp(s, "temp") == 0) { return 140; }
    if(strcmp(s, "booleanExpression") == 0) { return 141; }
    if(strcmp(s, "var") == 0) { return 142; }
    if(strcmp(s, "logicalOp") == 0) { return 143; }
    if(strcmp(s, "relationalOp") == 0) { return 144; }
    if(strcmp(s, "returnStmt") == 0) { return 145; }
    if(strcmp(s, "optionalReturn") == 0) { return 146; }
    if(strcmp(s, "idList") == 0) { return 147; }
    if(strcmp(s, "more_ids") == 0) { return 148; }
    if(strcmp(s, "new24") == 0) { return 149; }
    if(strcmp(s, "newVar") == 0) { return 150; }
}

// returns token name for given id
char* getCorrespondingToken(int f){
	char * token = malloc(100);
    switch(f){
        case 1: strcpy(token, "TK_ASSIGNOP");
			break;
        case 2: strcpy(token, "TK_COMMENT");
			break;
        case 3: strcpy(token, "TK_FIELDID");
			break;
        case 4: strcpy(token, "TK_ID");
			break;
        case 5: strcpy(token, "TK_NUM");
			break;
        case 6: strcpy(token, "TK_RNUM");
			break;
        case 7: strcpy(token, "TK_FUNID");
			break;
        case 8: strcpy(token, "TK_RECORDID");
			break;
        case 9: strcpy(token, "TK_WITH");
			break;
        case 10: strcpy(token, "TK_PARAMETERS");
			break;
        case 11: strcpy(token, "TK_END");
			break;
        case 12: strcpy(token, "TK_WHILE");
			break;
        case 13: strcpy(token, "TK_INT");
			break;
        case 14: strcpy(token, "TK_REAL");
			break;
        case 15: strcpy(token, "TK_TYPE");
			break;
        case 16: strcpy(token, "TK_MAIN");
			break;
        case 17: strcpy(token, "TK_GLOBAL");
			break;
        case 18: strcpy(token, "TK_PARAMETER");
			break;
        case 19: strcpy(token, "TK_LIST");
			break;
        case 20: strcpy(token, "TK_SQL");
			break;
        case 21: strcpy(token, "TK_SQR");
			break;
        case 22: strcpy(token, "TK_INPUT");
			break;
        case 23: strcpy(token, "TK_OUTPUT");
			break;
        case 24: strcpy(token, "TK_INT");
			break;
        case 25: strcpy(token, "TK_REAL");
			break;
        case 26: strcpy(token, "TK_SEM");
			break;
        case 27: strcpy(token, "TK_COLON");
			break;
        case 28: strcpy(token, "TK_DOT");
			break;
        case 29: strcpy(token, "TK_ENDWHILE");
			break;
        case 30: strcpy(token, "TK_OP");
			break;
        case 31: strcpy(token, "TK_CL");
			break;
        case 32: strcpy(token, "TK_IF");
			break;
        case 33: strcpy(token, "TK_THEN");
			break;
        case 34: strcpy(token, "TK_ENDIF");
			break;
        case 35: strcpy(token, "TK_READ");
			break;
        case 36: strcpy(token, "TK_WRITE");
			break;
        case 37: strcpy(token, "TK_RETURN");
			break;
        case 38: strcpy(token, "TK_PLUS");
			break;
        case 39: strcpy(token, "TK_MINUS");
			break;
        case 40: strcpy(token, "TK_MUL");
			break;
        case 41: strcpy(token, "TK_DIV");
			break;
        case 42: strcpy(token, "TK_CALL");
			break;
        case 43: strcpy(token, "TK_RECORD");
			break;
        case 44: strcpy(token, "TK_ENDRECORD");
			break;
        case 45: strcpy(token, "TK_ELSE");
			break;
        case 46: strcpy(token, "TK_AND");
			break;
        case 47: strcpy(token, "TK_OR");
			break;
        case 48: strcpy(token, "TK_NOT");
			break;
        case 49: strcpy(token, "TK_LT");
			break;
        case 50: strcpy(token, "TK_LE");
			break;
        case 51: strcpy(token, "TK_EQ");
			break;
        case 52: strcpy(token, "TK_GT");
			break;
        case 53: strcpy(token, "TK_GE");
			break;
        case 54: strcpy(token, "TK_NE");
			break;
        case 55: strcpy(token, "$");
			break;
        case 56: strcpy(token, "TK_COMMA");
			break;
        case 57: strcpy(token, "eps");
			break;

        // non-terminals below!

        case 100: strcpy(token, "program");
			break;
        case 101: strcpy(token, "mainFunction");
			break;
        case 102: strcpy(token, "otherFunctions");
			break;
        case 103: strcpy(token, "function");
			break;
        case 104: strcpy(token, "input_par");
			break;
        case 105: strcpy(token, "output_par");
			break;
        case 106: strcpy(token, "parameter_list");
			break;
        case 107: strcpy(token, "dataType");
			break;
        case 108: strcpy(token, "primitiveDatatype");
			break;
        case 109: strcpy(token, "constructedDatatype");
			break;
        case 110: strcpy(token, "remaining_list");
			break;
        case 111: strcpy(token, "stmts");
			break;
        case 112: strcpy(token, "typeDefinitions");
			break;
        case 113: strcpy(token, "typeDefinition");
			break;
        case 114: strcpy(token, "fieldDefinitions");
			break;
        case 115: strcpy(token, "fieldDefinition");
			break;
        case 116: strcpy(token, "moreFields");
			break;
        case 117: strcpy(token, "declarations");
			break;
        case 118: strcpy(token, "declaration");
			break;
        case 119: strcpy(token, "global_or_not");
			break;
        case 120: strcpy(token, "otherStmts");
			break;
        case 121: strcpy(token, "stmt");
			break;
        case 122: strcpy(token, "assignmentStmt");
			break;
        case 123: strcpy(token, "singleOrRecId");
			break;
        case 124: strcpy(token, "funCallStmt");
			break;
        case 125: strcpy(token, "outputParameters");
			break;
        case 126: strcpy(token, "inputParameters");
			break;
        case 127: strcpy(token, "iterativeStmt");
			break;
        case 128: strcpy(token, "conditionalStmt");
			break;
        case 129: strcpy(token, "elsePart");
			break;
        case 130: strcpy(token, "ioStmt");
			break;
        case 131: strcpy(token, "allVar");
			break;
        case 132: strcpy(token, "arithmeticExpression");
			break;
        case 133: strcpy(token, "expPrime");
			break;
        case 134: strcpy(token, "term");
			break;
        case 135: strcpy(token, "termPrime");
			break;
        case 136: strcpy(token, "factor");
			break;
        case 137: strcpy(token, "highPrecedenceOperators");
			break;
        case 138: strcpy(token, "lowPrecedenceOperators");
			break;
        case 139: strcpy(token, "all");
			break;
        case 140: strcpy(token, "temp");
			break;
        case 141: strcpy(token, "booleanExpression");
			break;
        case 142: strcpy(token, "var");
			break;
        case 143: strcpy(token, "logicalOp");
			break;
        case 144: strcpy(token, "relationalOp");
			break;
        case 145: strcpy(token, "returnStmt");
			break;
        case 146: strcpy(token, "optionalReturn");
			break;
        case 147: strcpy(token, "idList");
			break;
        case 148: strcpy(token, "more_ids");
			break;
        case 149: strcpy(token, "new24");
			break;
        case 150: strcpy(token, "newVar");
			break;
        default:
                {
                    char buf[12];
                    sprintf(buf, "Nothing", f);
                    return buf;
                }
    }
    return token;
}
// returns token id for terminals
int getColumnIndex(char* s)
{
    if(strcmp(s, "TK_AND") == 0) { return 46; }
    if(strcmp(s, "TK_ASSIGNOP") == 0) { return 1; }
    if(strcmp(s, "TK_CALL") == 0) { return 42; }
    if(strcmp(s, "TK_CL") == 0) { return 31; }
    if(strcmp(s, "TK_COLON") == 0) { return 27; }
    if(strcmp(s, "TK_COMMA") == 0) { return 56; }
    if(strcmp(s, "TK_DIV") == 0) { return 41; }
    if(strcmp(s, "TK_DOT") == 0) { return 28; }
    if(strcmp(s, "TK_ELSE") == 0) { return 45; }
    if(strcmp(s, "TK_END") == 0) { return 11; }
    if(strcmp(s, "TK_ENDIF") == 0) { return 34; }
    if(strcmp(s, "TK_ENDRECORD") == 0) { return 44; }
    if(strcmp(s, "TK_ENDWHILE") == 0) { return 29; }
    if(strcmp(s, "TK_EQ") == 0) { return 51; }
    if(strcmp(s, "TK_FIELDID") == 0) { return 3; }
    if(strcmp(s, "TK_FUNID") == 0) { return 7; }
    if(strcmp(s, "TK_GE") == 0) { return 53; }
    if(strcmp(s, "TK_GLOBAL") == 0) { return 17; }
    if(strcmp(s, "TK_GT") == 0) { return 52; }
    if(strcmp(s, "TK_ID") == 0) { return 4; }
    if(strcmp(s, "TK_IF") == 0) { return 32; }
    if(strcmp(s, "TK_INPUT") == 0) { return 22; }
    if(strcmp(s, "TK_INT") == 0) { return 13; }
    if(strcmp(s, "TK_LE") == 0) { return 50; }
    if(strcmp(s, "TK_LIST") == 0) { return 19; }
    if(strcmp(s, "TK_LT") == 0) { return 49; }
    if(strcmp(s, "TK_MAIN") == 0) { return 16; }
    if(strcmp(s, "TK_MINUS") == 0) { return 39; }
    if(strcmp(s, "TK_MUL") == 0) { return 40; }
    if(strcmp(s, "TK_NE") == 0) { return 54; }
    if(strcmp(s, "TK_NOT") == 0) { return 48; }
    if(strcmp(s, "TK_NUM") == 0) { return 5; }
    if(strcmp(s, "TK_OP") == 0) { return 30; }
    if(strcmp(s, "TK_OR") == 0) { return 47; }
    if(strcmp(s, "TK_OUTPUT") == 0) { return 23; }
    if(strcmp(s, "TK_PARAMETER") == 0) { return 18; }
    if(strcmp(s, "TK_PARAMETERS") == 0) { return 10; }
    if(strcmp(s, "TK_PLUS") == 0) { return 38; }
    if(strcmp(s, "TK_READ") == 0) { return 35; }
    if(strcmp(s, "TK_REAL") == 0) { return 14; }
    if(strcmp(s, "TK_RECORD") == 0) { return 43; }
    if(strcmp(s, "TK_RECORDID") == 0) { return 8; }
    if(strcmp(s, "TK_RETURN") == 0) { return 37; }
    if(strcmp(s, "TK_RNUM") == 0) { return 6; }
    if(strcmp(s, "TK_SEM") == 0) { return 26; }
    if(strcmp(s, "TK_SQL") == 0) { return 20; }
    if(strcmp(s, "TK_SQR") == 0) { return 21; }
    if(strcmp(s, "TK_THEN") == 0) { return 33; }
    if(strcmp(s, "TK_TYPE") == 0) { return 15; }
    if(strcmp(s, "TK_WHILE") == 0) { return 12; }
    if(strcmp(s, "TK_WITH") == 0) { return 9; }
    if(strcmp(s, "TK_WRITE") == 0) { return 36; }
    if(strcmp(s, "eps") == 0 ) {return 57;}
    if(strcmp(s, "$") == 0) { return 55; }
    return -90;
}

// combines fn's for terminals and non-terminals
int getIndex(char* tok)
{
    int ret = getColumnIndex(tok);

    if (ret == -90)
        ret = getRowIndex(tok);

    return ret;
}

// initializing parsing table to rule no -1
// -1 indicates *no rule present*
void initializeTable(table T)
{
    int i = 0;
    int j = 0;

    for (i = 0;i<table_row;i++)
    {
        for (j = 0;j<table_row;j++)
            T[i][j] = -1;
    }
}

// default rule number -1
void createParseTable(FILE* G, table T)
{
    initializeTable(T);

    int terminals = 0;
    int nonTerminals = 0;

    char readString[100];

    char LHSString[25];

    char* restOfRule;
    size_t len = 0;

    int LHS;

    int* toBeMarked;

    int ruleNo = 0;
    int counter;

    int flag = 0;


    while(!feof(G))
    {
        flag = 0;

        fscanf(G, "%s", readString);

        // incrementing each time
        ruleNo++;

        strcpy(LHSString, readString);
        LHS = getRowIndex(readString);

        fscanf(G, "%s", readString);
        if (strcmp(readString, "===>") != 0)
            printf("ERROR !!! :(");

        int read = getline(&restOfRule, &len, G);
        restOfRule[read - 1] = '\0';

        toBeMarked = first(restOfRule);

        counter = 0;

        while(toBeMarked[counter] != -1)
        {
            // printf("%d\n", toBeMarked[counter]);
            if(toBeMarked[counter] == 57)
            {
                flag = 1;
                counter++;
                continue;
            }
            T[LHS % 100][toBeMarked[counter] % 100] = ruleNo;
            counter++;
        }

        if (flag == 1)
        {
            toBeMarked = getFollows(LHSString);

            counter = 0;
            while(toBeMarked[counter] != -1)
            {
                // printf("%d\n", toBeMarked[counter]);
                // in case of $
                if(toBeMarked[counter] == 55)
                {
                    counter++;
                    continue;
                }
                T[LHS % 100][toBeMarked[counter]] = ruleNo;
                counter++;
            }
        }
    }
}

// does the actual parsing using the table and source file
parseTree parseInputSourceCode(char *testcaseFile, table T)
{
    // initialize file pointer
    FILE *fp;
    fp = fopen(testcaseFile, "rb");

    if (fp == NULL) {
        perror("Error");
    }

    // initialize buffer
    buffer b;
    buffersize bufsize = 25;

    lineNo = 1;

    b = (buffer) malloc(sizeof(char)*bufsize);

    memset(b, 0, sizeof(b));

    // initialize stack
    stack* head = (stack*) malloc(sizeof(stack));
    head->next = NULL;

    // initialize parseTree
    parseTree ptree = (parseTree) malloc(sizeof(struct tree));
    ptree->id = 100;
    ptree->firstKid = NULL;
    ptree->siblings = NULL;
    ptree->lexeme = (char*) malloc(sizeof(char)*25);
    strcpy(ptree->lexeme, "program");

    parseTree curr = ptree;

    // push "dollar" or -47 to indicate the end of the stack
    head = push(head, -47);
    // push "program" to start parsing
    head = push(head, 100);

    tokenInfo token;
    int ruleNum;
    int popVal;

    stack popped;

    token = getNextToken(fp, b, bufsize);
    while (token.id == 2)
    {
        state = 1;
        token = getNextToken(fp , b, bufsize);
    }

    while(1)
    {
        state = 1;

        popped = pop(head);

        popVal = popped.data;
        head = popped.next;

        // if $ is popped
        if(popVal == -47 && token.id == 55)
        {
            fclose(fp);
            return curr;
        }

        while (popVal < 100) {
            if (popVal == 57)
            {
                popped = pop(head);

                popVal = popped.data;
                head = popped.next;

                strcpy(curr->lexeme, "");
                curr->lineNo = token.lineNo;
                while (curr->siblings == NULL)
                    curr = curr->parent;

                curr = curr->siblings;
                continue;
            }

            if (popVal != token.id)
            {
                if(popVal == -47 && token.id == 55)
                {
                    fclose(fp);
                    return ptree;
                }
                else if(token.id == 55)
                {   error_in_parsing = 1;
                    printf("ERROR_4: Input is consumed while it is expected to have token <%s> at line number <%d>\n", getCorrespondingToken(popVal), token.lineNo);
                    fclose(fp);
                    return ptree;
                }
                else {
                    error_in_parsing = 1;
                    printf("ERROR_5: The token <%s> for lexeme<%s> does not match at line <%d>. The expected token here is <%s>\n",
                       getCorrespondingToken(token.id), token.name, token.lineNo, getCorrespondingToken(popVal));

                    popped = pop(head);

                    popVal = popped.data;
                    head = popped.next;

                    while (curr->siblings == NULL)
                        curr = curr->parent;

                    curr = curr->siblings;

                    if (popVal > 100 && T[popVal % 100][token.id] != -1)
                        continue;

                    if (popVal != token.id)
                    {
                        token = getNextToken(fp, b, bufsize);
                        while (token.id == 2)
                            token = getNextToken(fp , b, bufsize);

                        if (popVal != token.id)
                        {
                            while(token.id != 55)
                                token = getNextToken(fp, b, bufsize);

                            error_in_parsing = 1;
                            printf("ERROR_4: Input is consumed while it is expected to have token <%s> at line number <%d>\n", getCorrespondingToken(popVal), token.lineNo);

                            fclose(fp);
                            return ptree;
                        }

                        continue;
                    }
                }
            }
            else
            {
                popped = pop(head);

                popVal = popped.data;
                head = popped.next;

                strcpy(curr->lexeme, token.name);
                curr->lineNo = token.lineNo;

                while (curr->siblings == NULL)
                    curr = curr->parent;

                curr = curr->siblings;

                state = 1;

                token = getNextToken(fp, b, bufsize);
                while (token.id == 2)
                    token = getNextToken(fp , b, bufsize);
            }
        }

        ruleNum = T[popVal % 100][token.id];

        if (ruleNum == -1)
        {   error_in_parsing = 1;
            int* ans = getFirsts(getCorrespondingToken(popVal));
            printf("ERROR_5: The token <%s> for lexeme<%s> does not match at line <%d>. The expected token here is <%s>\n",
                       getCorrespondingToken(token.id), token.name, token.lineNo, getCorrespondingToken(*ans));

            popped = pop(head);

            popVal = popped.data;
            head = popped.next;

            while (curr->siblings == NULL)
                curr = curr->parent;

            curr = curr->siblings;

            if (popVal > 100 && T[popVal % 100][token.id] != -1)
                continue;

            if (popVal != token.id)
            {
                token = getNextToken(fp, b, bufsize);
                while (token.id == 2)
                    token = getNextToken(fp , b, bufsize);

                if (popVal != token.id)
                {
                    while(token.id != 55)
                        token = getNextToken(fp, b, bufsize);
                    error_in_parsing = 1;
                    printf("ERROR_4: Input is consumed while it is expected to have token <%s> at line number <%d>\n", getCorrespondingToken(popVal), token.lineNo);

                    fclose(fp);

                    return ptree;
                }

                continue;
            }
        }

        head = push_ints(head, getRuleRHSrev(ruleNum), curr);

        curr = curr->firstKid;
    }
}

// helper fn for tree printing (does the acutal printing)
int printParseTree_r(parseTree curr, FILE* f, int * size, int print)
{
    if (curr == NULL)
        return;


    if(curr->firstKid != NULL)
    {

        printParseTree_r(curr->firstKid, f, size, print);

        char* value = (char*) malloc(sizeof(char)*20);
        strcpy(value, "");

        if(print != -1)
	        fprintf(f, "\n %20s %15d %15s %15s %20s %15s %15s", curr->lexeme, curr->lineNo,
	                getCorrespondingToken(curr->id), value, getCorrespondingToken(curr->parent->id),
	                curr->firstKid == NULL?"yes": "no", getCorrespondingToken(curr->id));

        *size  = *size + 1;

    }
    else
    {
        char* value = (char*) malloc(sizeof(char)*20);
        strcpy(value, "");
        if (curr->id == 5 || curr->id == 6)
            strcpy(value, curr->lexeme);

        if(print != -1)
	        fprintf(f, "\n %20s %15d %15s %15s %20s %15s %15s", curr->lexeme, curr->lineNo,
	                getCorrespondingToken(curr->id), value, getCorrespondingToken(curr->parent->id),
	                curr->firstKid == NULL?"yes": "no", getCorrespondingToken(curr->id));


        *size  = *size + 1;



    }
    parseTree prev = curr;
    curr = curr->siblings;

    if(curr != NULL)
    {
        printParseTree_r(curr, f, size, print);
    }

}

// prints parse tree to given out file
void printParseTree(parseTree  curr, char* outfile)
{
    FILE* f = fopen(outfile, "w");
    int size = 0;
    printParseTree_r(curr, f, &size, 1);
    fclose(f);

}

// returns RHS of given rule as an int array
int* getRuleRHSrev(int rule)
{
    int* ret;
    ret = (int*) malloc(sizeof(int)*8);

    int i;

    for(i = 0; i<8 ;i++)
        ret[i] = 1000;

    char* temp;
    temp = (char*) malloc(200*sizeof(char));

    strcpy(temp, GRule[rule]);
    char* toks = strtok(temp, " ");

    int counter = 0;

    while(toks != NULL)
    {
        ret[counter] = getIndex(toks);
        counter++;
        toks = strtok(NULL, " ");
    }

    return ret;
}

// add stack methods

// push to stack
stack* push(stack* head, int val)
{
    // Allocate new space
    stack* new = (stack*) malloc(sizeof(stack));
    new->data = val;
    new->next = head;
    // head = new;

    return new;
}

// push multiple ints, updates tree ptr too
stack* push_ints(stack* head, int* ints, parseTree curr)
{
    int counter = 0;

    parseTree new = (parseTree) malloc(sizeof(*curr));

    new->id = ints[0];
    new->siblings = NULL;
    new->parent = curr;
    new->firstKid = NULL;
    new->lexeme = (char*) malloc(sizeof(char)*25);
    memset(new->lexeme, '\0', 25);
    curr->firstKid = new;

    counter++;

    parseTree prev = new;
    while(ints[counter] != 1000 && counter < 8)
    {
        if(ints[counter] == 57)
            flag_eps = 1;

        parseTree temp = (parseTree) malloc(sizeof(*curr));
        temp->id = ints[counter];
        temp->siblings = NULL;
        temp->firstKid = NULL;
        temp->parent = curr;
        temp->lexeme = (char*) malloc(sizeof(char)*25);
        memset(temp->lexeme, '\0', 25);
        prev->siblings = temp;
        prev = temp;
        counter++;
    }

    counter--;

    while (counter >= 0)
    {
        if(ints[counter] == 1000)
        {
            counter--;
            continue;
        }

        head = push(head, ints[counter]);
        counter--;
    }

    return head;
}

// pop from stack
stack pop(stack* head)
{
    stack* temp;
    temp = head;

    int outVal = temp->data;

    head = temp->next;

    free(temp);

    stack ret;
    ret.data = outVal;
    ret.next = head;
    return ret;
}

// array of grammar rules used for parsing
char GRule[95][100] = {
    "",
    "otherFunctions mainFunction",
    "TK_MAIN stmts TK_END",
    "function otherFunctions",
    "eps",
    "TK_FUNID input_par output_par TK_SEM stmts TK_END",
    "TK_INPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR",
    "TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR",
    "eps",
    "dataType TK_ID remaining_list",
    "primitiveDatatype",
    "constructedDatatype",
    "TK_INT",
    "TK_REAL",
    "TK_RECORD TK_RECORDID",
    "TK_COMMA parameter_list",
    "eps",
    "typeDefinitions declarations otherStmts returnStmt",
    "typeDefinition typeDefinitions",
    "eps",
    "TK_RECORD TK_RECORDID fieldDefinitions TK_ENDRECORD TK_SEM",
    "fieldDefinition fieldDefinition moreFields",
    "TK_TYPE primitiveDatatype TK_COLON TK_FIELDID TK_SEM",
    "fieldDefinition moreFields",
    "eps",
    "declaration declarations",
    "eps",
    "TK_TYPE dataType TK_COLON TK_ID global_or_not TK_SEM",
    "TK_COLON TK_GLOBAL",
    "eps",
    "stmt otherStmts",
    "eps",
    "assignmentStmt",
    "iterativeStmt",
    "conditionalStmt",
    "ioStmt",
    "funCallStmt",
    "singleOrRecId TK_ASSIGNOP arithmeticExpression TK_SEM",
    "TK_ID new24",
    "TK_DOT TK_FIELDID",
    "eps",
    "outputParameters TK_CALL TK_FUNID TK_WITH TK_PARAMETERS inputParameters TK_SEM",
    "TK_SQL idList TK_SQR TK_ASSIGNOP",
    "eps",
    "TK_SQL idList TK_SQR",
    "TK_WHILE TK_OP booleanExpression TK_CL stmt otherStmts TK_ENDWHILE",
    "TK_IF TK_OP booleanExpression TK_CL TK_THEN stmt otherStmts elsePart",
    "TK_ELSE stmt otherStmts TK_ENDIF",
    "TK_ENDIF",
    "TK_READ TK_OP singleOrRecId TK_CL TK_SEM",
    "TK_WRITE TK_OP allVar TK_CL TK_SEM",
    "TK_ID newVar",
    "TK_NUM",
    "TK_RNUM",
    "TK_DOT TK_FIELDID",
    "eps",
    "term expPrime",
    "lowPrecedenceOperators term expPrime",
    "eps",
    "factor termPrime",
    "highPrecedenceOperators factor termPrime",
    "eps",
    "TK_OP arithmeticExpression TK_CL",
    "all",
    "TK_MUL",
    "TK_DIV",
    "TK_PLUS",
    "TK_MINUS",
    "TK_NUM",
    "TK_RNUM",
    "TK_ID temp",
    "TK_DOT TK_FIELDID",
    "eps",
    "TK_OP booleanExpression TK_CL logicalOp TK_OP booleanExpression TK_CL",
    "var relationalOp var",
    "TK_NOT TK_OP booleanExpression TK_CL",
    "TK_ID",
    "TK_NUM",
    "TK_RNUM",
    "TK_AND",
    "TK_OR",
    "TK_LT",
    "TK_LE",
    "TK_EQ",
    "TK_GT",
    "TK_GE",
    "TK_NE",
    "TK_RETURN optionalReturn TK_SEM",
    "TK_SQL idList TK_SQR",
    "eps",
    "TK_ID more_ids",
    "TK_COMMA idList",
    "eps",
};

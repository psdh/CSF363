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
    switch(f){
        case 1: return "TK_ASSIGNOP";
        case 2: return "TK_COMMENT";
        case 3: return "TK_FIELDID";
        case 4: return "TK_ID";
        case 5: return "TK_NUM";
        case 6: return "TK_RNUM";
        case 7: return "TK_FUNID";
        case 8: return "TK_RECORDID";
        case 9: return "TK_WITH";
        case 10: return "TK_PARAMETERS";
        case 11: return "TK_END";
        case 12: return "TK_WHILE";
        case 13: return "TK_INT";
        case 14: return "TK_REAL";
        case 15: return "TK_TYPE";
        case 16: return "TK_MAIN";
        case 17: return "TK_GLOBAL";
        case 18: return "TK_PARAMETER";
        case 19: return "TK_LIST";
        case 20: return "TK_SQL";
        case 21: return "TK_SQR";
        case 22: return "TK_INPUT";
        case 23: return "TK_OUTPUT";
        case 24: return "TK_INT";
        case 25: return "TK_REAL";
        case 26: return "TK_SEM";
        case 27: return "TK_COLON";
        case 28: return "TK_DOT";
        case 29: return "TK_ENDWHILE";
        case 30: return "TK_OP";
        case 31: return "TK_CL";
        case 32: return "TK_IF";
        case 33: return "TK_THEN";
        case 34: return "TK_ENDIF";
        case 35: return "TK_READ";
        case 36: return "TK_WRITE";
        case 37: return "TK_RETURN";
        case 38: return "TK_PLUS";
        case 39: return "TK_MINUS";
        case 40: return "TK_MUL";
        case 41: return "TK_DIV";
        case 42: return "TK_CALL";
        case 43: return "TK_RECORD";
        case 44: return "TK_ENDRECORD";
        case 45: return "TK_ELSE";
        case 46: return "TK_AND";
        case 47: return "TK_OR";
        case 48: return "TK_NOT";
        case 49: return "TK_LT";
        case 50: return "TK_LE";
        case 51: return "TK_EQ";
        case 52: return "TK_GT";
        case 53: return "TK_GE";
        case 54: return "TK_NE";
        case 55: return "$";
        case 56: return "TK_COMMA";
        case 57: return "eps";

        // non-terminals below!

        case 100: return "program";
        case 101: return "mainFunction";
        case 102: return "otherFunctions";
        case 103: return "function";
        case 104: return "input_par";
        case 105: return "output_par";
        case 106: return "parameter_list";
        case 107: return "dataType";
        case 108: return "primitiveDatatype";
        case 109: return "constructedDatatype";
        case 110: return "remaining_list";
        case 111: return "stmts";
        case 112: return "typeDefinitions";
        case 113: return "typeDefinition";
        case 114: return "fieldDefinitions";
        case 115: return "fieldDefinition";
        case 116: return "moreFields";
        case 117: return "declarations";
        case 118: return "declaration";
        case 119: return "global_or_not";
        case 120: return "otherStmts";
        case 121: return "stmt";
        case 122: return "assignmentStmt";
        case 123: return "singleOrRecId";
        case 124: return "funCallStmt";
        case 125: return "outputParameters";
        case 126: return "inputParameters";
        case 127: return "iterativeStmt";
        case 128: return "conditionalStmt";
        case 129: return "elsePart";
        case 130: return "ioStmt";
        case 131: return "allVar";
        case 132: return "arithmeticExpression";
        case 133: return "expPrime";
        case 134: return "term";
        case 135: return "termPrime";
        case 136: return "factor";
        case 137: return "highPrecedenceOperators";
        case 138: return "lowPrecedenceOperators";
        case 139: return "all";
        case 140: return "temp";
        case 141: return "booleanExpression";
        case 142: return "var";
        case 143: return "logicalOp";
        case 144: return "relationalOp";
        case 145: return "returnStmt";
        case 146: return "optionalReturn";
        case 147: return "idList";
        case 148: return "more_ids";
        case 149: return "new24";
        case 150: return "newVar";
        default:
                {
                    char buf[12];
                    sprintf(buf, "Nothing", f);
                    return buf;
                }
    }
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
                {
                    printf("ERROR_4: Input is consumed while it is expected to have token <%s> at line number <%d>\n", getCorrespondingToken(popVal), token.lineNo);
                    fclose(fp);
                    return ptree;
                }
                else {
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
        {
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

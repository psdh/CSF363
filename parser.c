// filename: parser.c
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

#include "parserDef.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>

#define table_row 60
int flag_eps;

int* getFirsts(char * input){

    char* line;
    line = (char*) malloc(sizeof(char)*100);
    char * token;
    size_t len = 0;
    int count = 0;
    ssize_t read;


    int firsts[25];

    FILE *fp = fopen("first", "r");
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
        printf("%s\n", token);
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

int* getFollows(char * input){

    char * line = NULL;
    char * token;
    size_t len = 0;
    int count = 0;
    ssize_t read;

    int follows[25];

    FILE *fp = fopen("follow", "r");
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


int getRowIndex(char* s)
{
    if(strcmp(s, "program") == 0)
        return 100;
    if(strcmp(s, "mainFunction") == 0)
        return 101;

    if(strcmp(s, "otherFunctions") == 0)
        return 102;

    if(strcmp(s, "function") == 0)
        return 103;

    if(strcmp(s, "input_par") == 0)
        return 104;

    if(strcmp(s, "output_par") == 0)
        return 105;

    if(strcmp(s, "parameter_list") == 0)
        return 106;

    if(strcmp(s, "dataType") == 0)
        return 107;

    if(strcmp(s, "primitiveDatatype") == 0)
        return 108;

    if(strcmp(s, "constructedDatatype") == 0)
        return 109;

    if(strcmp(s, "remaining_list") == 0)
        return 110;

    if(strcmp(s, "stmts") == 0)
        return 111;

    if(strcmp(s, "typeDefinitions") == 0)
        return 112;

    if(strcmp(s, "typeDefinition") == 0)
        return 113;

    if(strcmp(s, "fieldDefinitions") == 0)
        return 114;

    if(strcmp(s, "fieldDefinition") == 0)
        return 115;

    if(strcmp(s, "moreFields") == 0)
        return 116;

    if(strcmp(s, "declarations") == 0)
        return 117;

    if(strcmp(s, "declaration") == 0)
        return 118;

    if(strcmp(s, "global_or_not") == 0)
        return 119;

    if(strcmp(s, "otherStmts") == 0)
        return 120;

    if(strcmp(s, "stmt") == 0)
        return 121;

    if(strcmp(s, "assignmentStmt") == 0)
        return 122;

    if(strcmp(s, "singleOrRecId") == 0)
        return 123;

    if(strcmp(s, "funCallStmt") == 0)
        return 124;

    if(strcmp(s, "outputParameters") == 0)
        return 125;

    if(strcmp(s, "inputParameters") == 0)
        return 126;

    if(strcmp(s, "iterativeStmt") == 0)
        return 127;

    if(strcmp(s, "conditionalStmt") == 0)
        return 128;

    if(strcmp(s, "elsePart") == 0)
        return 129;

    if(strcmp(s, "ioStmt") == 0)
        return 130;

    if(strcmp(s, "allVar") == 0)
        return 131;

    if(strcmp(s, "arithmeticExpression") == 0)
        return 132;

    if(strcmp(s, "expPrime") == 0)
        return 133;

    if(strcmp(s, "term") == 0)
        return 134;

    if(strcmp(s, "termPrime") == 0)
        return 135;

    if(strcmp(s, "factor") == 0)
        return 136;

    if(strcmp(s, "highPrecedenceOperators") == 0)
        return 137;

    if(strcmp(s, "lowPrecedenceOperators") == 0)
        return 138;

    if(strcmp(s, "all") == 0)
        return 139;

    if(strcmp(s, "temp") == 0)
        return 140;

    if(strcmp(s, "booleanExpression") == 0)
        return 141;

    if(strcmp(s, "var") == 0)
        return 142;

    if(strcmp(s, "logicalOp") == 0)
        return 143;

    if(strcmp(s, "relationalOp") == 0)
        return 144;
    if(strcmp(s, "returnStmt") == 0)
    	return 145;

    if(strcmp(s, "optionalReturn") == 0)
    	return 146;

    if(strcmp(s, "idList") == 0)
    	return 147;
    if(strcmp(s, "more_ids") == 0)
        return 148;
    if(strcmp(s, "new24") == 0)
        return 149;
    if(strcmp(s, "newVar") == 0)
        return 150;
}


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
        default: return "NOTHING";
    }
}

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

int getIndex(char* tok)
{
    int ret = getColumnIndex(tok);

    if (ret == -90)
        ret = getRowIndex(tok);

    return ret;
}

// initializing parsing table to rule no 1000
// 1000 indicates *no rule*
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

    printf("\n\n%d\n\n", token.lineNo);
    // parsing now!
    while(1)
    {
        state = 1;

        popped = pop(head);

        popVal = popped.data;
        head = popped.next;

        // if $ is popped
        if(popVal == -47)
        {
            // some error report here!
        }

        while (popVal < 100) {
            if (popVal == 57)
            {
                popped = pop(head);

                popVal = popped.data;
                head = popped.next;

                while (curr->siblings == NULL)
                    curr = curr->parent;

                curr = curr->siblings;
                continue;
            }

            if (popVal != token.id)
            {
                printf("ERROR: popped value should be same as token");
                printf("popVal: %d, token.id: %d and name: %sn", popVal, token.id, token.name);

                exit(0);
            }
            else
            {
                popped = pop(head);

                popVal = popped.data;
                head = popped.next;

                while (curr->siblings == NULL)
                    curr = curr->parent;

                curr = curr->siblings;

                state = 1;
                token = getNextToken(fp, b, bufsize);
                while (token.id == 2)
                    token = getNextToken(fp , b, bufsize);
                printf("\n\n%d\n\n", token.lineNo);
            }
        }

        ruleNum = T[popVal % 100][token.id];

        if (ruleNum == -1)
        {
            printf("rule not found");
            printf("popVal: %d, token.id: %d and name: %sn", popVal, token.id, token.name);
            exit(0);
        }

        head = push_ints(head, getRuleRHSrev(ruleNum), curr);

        curr = curr->firstKid;

        printf("\n\n\n");
        printParseTree(ptree);
    }
}

void printParseTree(parseTree  curr)
{
    // print for debugging!!

    if (curr == NULL)
        return;


    if(curr->firstKid != NULL)
    {
        printf("\ngoing to first kid with id: %d %d\n\n", curr->firstKid->id, curr->id);
        printParseTree(curr->firstKid);
    }
    else
        printf("\n id: %d, name: %s parent id: %d", curr->id, getCorrespondingToken(curr->id), curr->parent->id);

    parseTree prev = curr;
    curr = curr->siblings;

    if(curr != NULL)
    {
        printf("\ngoing to siblings with id: %d %d\n\n", curr->id, prev->id);
        return printParseTree(curr);
    }
}

parseTree next(parseTree curr)
{
    if(curr->siblings == NULL)
        return curr->parent;
    else
        return curr->siblings;
}

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

stack* push(stack* head, int val)
{
    // Allocate new space
    stack* new = (stack*) malloc(sizeof(stack));
    new->data = val;
    new->next = head;
    // head = new;

    return new;
}

stack* push_ints(stack* head, int* ints, parseTree curr)
{
    int counter = 0;

    parseTree new = (parseTree) malloc(sizeof(*curr));

    new->id = ints[0];
    new->siblings = NULL;
    new->parent = curr;
    new->firstKid = NULL;
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

int main()
{
    printf("Now We will parse!!! :D");

    FILE* fp;

    fp = fopen("grammar", "r");

    table doNow = (int **) malloc(table_row * sizeof(int *));

    int i = 0;

    for (i=0; i<table_row; i++)
         doNow[i] = (int *) malloc(table_row * sizeof(int));

    createParseTable(fp, doNow);

    int j = 0;

    for (i = 0;i<table_row;i++)
    {
        for(j=0;j<table_row;j++)
            printf(" %d ", doNow[i][j]);

        printf("\n");
    }
    fclose(fp);

    printf("\nCreated Parsing Table\n");


    parseTree n;
    char filename[] = "testcases/testcase3.txt";

    n = parseInputSourceCode(filename, doNow);

    printf("chal gaya\n");
    return 0;
}

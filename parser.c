// filename: lexer.c
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

#include "parserDef.h"
#include "lexer.h"

typedef char[20] string;

typedef string[] rule;

int getRowIndex()
{
    if(strcmp(s, "program") == 0)
        return 0;
    if(strcmp(s, "mainFunction") == 0)
        return 1;

    if(strcmp(s, "otherFunctions") == 0)
        return 2;

    if(strcmp(s, "function") == 0)
        return 3;

    if(strcmp(s, "input_par") == 0)
        return 4;

    if(strcmp(s, "output_par") == 0)
        return 5;

    if(strcmp(s, "parameter_list") == 0)
        return 6;

    if(strcmp(s, "dataType") == 0)
        return 7;

    if(strcmp(s, "primitiveDatatype") == 0)
        return 8;

    if(strcmp(s, "constructedDatatype") == 0)
        return 9;

    if(strcmp(s, "remaining_list") == 0)
        return 10;

    if(strcmp(s, "stmts") == 0)
        return 11;

    if(strcmp(s, "typeDefinitions") == 0)
        return 12;

    if(strcmp(s, "typeDefinition") == 0)
        return 13;

    if(strcmp(s, "fieldDefinitions") == 0)
        return 14;

    if(strcmp(s, "fieldDefinition") == 0)
        return 15;

    if(strcmp(s, "moreFields") == 0)
        return 16;

    if(strcmp(s, "declarations") == 0)
        return 17;

    if(strcmp(s, "declaration") == 0)
        return 18;

    if(strcmp(s, "global_or_not") == 0)
        return 19;

    if(strcmp(s, "otherStmts") == 0)
        return 20;

    if(strcmp(s, "stmt") == 0)
        return 21;

    if(strcmp(s, "assignmentStmt") == 0)
        return 22;

    if(strcmp(s, "singleOrRecId") == 0)
        return 23;

    if(strcmp(s, "funCallStmt") == 0)
        return 24;

    if(strcmp(s, "outputParameters") == 0)
        return 25;

    if(strcmp(s, "inputParameters") == 0)

    if(strcmp(s, "iterativeStmt") == 0)

    if(strcmp(s, "conditionalStmt") == 0)

    if(strcmp(s, "elsePart") == 0)

    if(strcmp(s, "ioStmt") == 0)

    if(strcmp(s, "allVar") == 0)

    if(strcmp(s, "arithmeticExpression") == 0)

    if(strcmp(s, "expPrime") == 0)

    if(strcmp(s, "term") == 0)

    if(strcmp(s, "termPrime") == 0)

    if(strcmp(s, "factor") == 0)

    if(strcmp(s, "highPrecedenceOperator") == 0)

    if(strcmp(s, "lowPrecedenceOperators") == 0)

    if(strcmp(s, "all") == 0)

    if(strcmp(s, "temp") == 0)

    if(strcmp(s, "booleanExpression") == 0)

    if(strcmp(s, "var") == 0)

    if(strcmp(s, "logicalOp") == 0)

    if(strcmp(s, "relationalOp") == 0)

    if(strcmp(s, "returnStmt") == 0)

    if(strcmp(s, "optionalReturn") == 0)

    if(strcmp(s, "idList") == 0)

    if(strcmp(s, "more_ids") == 0)
        return

}

int getColumnIndex()
{

}

typedef enum ruleState
{
    LHS,
    RHS
};

void createParseTable(FILE* G, table T)
{
    // Assuming that we have one grammar rule in one line
    // read until RULE_END and process rule, increment the number of terminals and non-terminals

    int terminals = 0;
    int nonTerminals = 0;

    char s[25], readString[25];

    while(!feof(G))
    {
        s = "";
        readString = "";
        RHString = "";
        fscanf(G, "%s", readString);

        ruleState state = LHS;

        while(1)
        {
            if(state == LHS)
            {
                strcpy(LHString, readString);
                state = RHS;
            }
            else
            {
                // decide to add a new state for ===> or remove it entirely
                // from the grammar
                if (strcmp(readString, "===>") != 0)
                {
                    if(strcmp(readString, "RULE_END") == 0)
                    {
                        printf("adding rule: %s at index: %d", RHString, ind);

                        markFirst(T, getRowIndex(LHString), )
                    }

                    strcat(RHString, " ");
                    sprintf(readString, "%d", getRowIndex(readString));
                    strcat(RHString, readString);
                }
                else
                {
                    fscanf(G, "%s", readString);
                    strcpy(first, readString);
                }
            }

            fscanf(G, "%s", readString);
        }
    }

}

parseTree parseInputSourceCode(char *testcaseFile, table T)
{
    FILE *fp;
    fp = fopen(testcaseFile, 'rb');

    buffer[2] b;
    buffersize bufsize = 100;

    b[0] = (char*) malloc(sizeof(char)*bufsize);
    b[1] = (char*) malloc(sizeof(char)*bufsize);

    int count = 0;
    fp = getStream(fp, b[count % 2], bufsize);

}

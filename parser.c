// filename: lexer.c
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

#include "parserDef.h"
#include "lexer.h"

typedef char[20] string;

typedef string[] rule;

int getRowIndex(char* s)
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
        return 18;

    if(strcmp(s, "iterativeStmt") == 0)
        return 18;

    if(strcmp(s, "conditionalStmt") == 0)
        return 18;

    if(strcmp(s, "elsePart") == 0)
        return 18;

    if(strcmp(s, "ioStmt") == 0)
        return 18;

    if(strcmp(s, "allVar") == 0)
        return 18;

    if(strcmp(s, "arithmeticExpression") == 0)
        return 18;

    if(strcmp(s, "expPrime") == 0)
        return 18;

    if(strcmp(s, "term") == 0)
        return 18;

    if(strcmp(s, "termPrime") == 0)
        return 18;

    if(strcmp(s, "factor") == 0)
        return 18;

    if(strcmp(s, "highPrecedenceOperators") == 0)
        return 18;

    if(strcmp(s, "lowPrecedenceOperators") == 0)
        return 18;

    if(strcmp(s, "all") == 0)
        return 18;

    if(strcmp(s, "temp") == 0)
        return 18;

    if(strcmp(s, "booleanExpression") == 0)
        return 18;

    if(strcmp(s, "var") == 0)
        return 18;

    if(strcmp(s, "logicalOp") == 0)
        return 18;

    if(strcmp(s, "relationalOp") == 0)
        return 18;
    if(strcmp(s, "returnStmt") == 0)

    if(strcmp(s, "optionalReturn") == 0)

    if(strcmp(s, "idList") == 0)

    if(strcmp(s, "more_ids") == 0)
        return

}

int getColumnIndex(char* s)
{
    if(strcmp(s, "TK_AND") == 0) { return 100; }
    if(strcmp(s, "TK_ASSIGNOP") == 0) { return 101; }
    if(strcmp(s, "TK_CALL") == 0) { return 102; }
    if(strcmp(s, "TK_CL") == 0) { return 103; }
    if(strcmp(s, "TK_COLON") == 0) { return 104; }
    if(strcmp(s, "TK_COMMA") == 0) { return 105; }
    if(strcmp(s, "TK_DIV") == 0) { return 106; }
    if(strcmp(s, "TK_DOT") == 0) { return 107; }
    if(strcmp(s, "TK_ELSE") == 0) { return 108; }
    if(strcmp(s, "TK_END") == 0) { return 109; }
    if(strcmp(s, "TK_ENDIF") == 0) { return 110; }
    if(strcmp(s, "TK_ENDRECORD") == 0) { return 111; }
    if(strcmp(s, "TK_ENDWHILE") == 0) { return 112; }
    if(strcmp(s, "TK_EQ") == 0) { return 113; }
    if(strcmp(s, "TK_FIELDID") == 0) { return 114; }
    if(strcmp(s, "TK_FUNID") == 0) { return 115; }
    if(strcmp(s, "TK_GE") == 0) { return 116; }
    if(strcmp(s, "TK_GLOBAL") == 0) { return 117; }
    if(strcmp(s, "TK_GT") == 0) { return 118; }
    if(strcmp(s, "TK_ID") == 0) { return 119; }
    if(strcmp(s, "TK_IF") == 0) { return 120; }
    if(strcmp(s, "TK_INPUT") == 0) { return 121; }
    if(strcmp(s, "TK_INT") == 0) { return 122; }
    if(strcmp(s, "TK_LE") == 0) { return 123; }
    if(strcmp(s, "TK_LIST") == 0) { return 124; }
    if(strcmp(s, "TK_LT") == 0) { return 125; }
    if(strcmp(s, "TK_MAIN") == 0) { return 126; }
    if(strcmp(s, "TK_MINUS") == 0) { return 127; }
    if(strcmp(s, "TK_MUL") == 0) { return 128; }
    if(strcmp(s, "TK_NE") == 0) { return 129; }
    if(strcmp(s, "TK_NOT") == 0) { return 130; }
    if(strcmp(s, "TK_NUM") == 0) { return 131; }
    if(strcmp(s, "TK_OP") == 0) { return 132; }
    if(strcmp(s, "TK_OR") == 0) { return 133; }
    if(strcmp(s, "TK_OUTPUT") == 0) { return 134; }
    if(strcmp(s, "TK_PARAMETER") == 0) { return 135; }
    if(strcmp(s, "TK_PARAMETERS") == 0) { return 136; }
    if(strcmp(s, "TK_PLUS") == 0) { return 137; }
    if(strcmp(s, "TK_READ") == 0) { return 138; }
    if(strcmp(s, "TK_REAL") == 0) { return 139; }
    if(strcmp(s, "TK_RECORD") == 0) { return 140; }
    if(strcmp(s, "TK_RECORDID") == 0) { return 141; }
    if(strcmp(s, "TK_RETURN") == 0) { return 141; }
    if(strcmp(s, "TK_RNUM") == 0) { return 142; }
    if(strcmp(s, "TK_SEM") == 0) { return 143; }
    if(strcmp(s, "TK_SQL") == 0) { return 144; }
    if(strcmp(s, "TK_SQR") == 0) { return 145; }
    if(strcmp(s, "TK_THEN") == 0) { return 146; }
    if(strcmp(s, "TK_TYPE") == 0) { return 147; }
    if(strcmp(s, "TK_WHILE") == 0) { return 148; }
    if(strcmp(s, "TK_WITH") == 0) { return 149; }
    if(strcmp(s, "TK_WRITE") == 0) { return 150; }

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
                if (strcmp(readString, "|") == )
                // decide to add a new state for ===> or remove it entirely
                // from the grammar
                if (strcmp(readString, "===>") != 0)
                {
                    if(strcmp(readString, "RULE_END") == 0)
                    {
                        printf("adding rule: %s at index: %d", RHString, ind);

                        markFirst(T, getRowIndex(LHString), rule_no)
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

void markFirst(table T, int index, );

// add stack methods

char *GRule[95];
GRule[0] = "<otherFunctions> <mainFunction> ";
GRule[1] = "TK_MAIN <stmts> TK_END ";
GRule[2] = "<function> <otherFunctions> ";
GRule[3] = "eps ";
GRule[4] = "TK_FUNID <input_par> <output_par> TK_SEM <stmts> TK_END ";
GRule[5] = "TK_INPUT TK_PARAMETER TK_LIST TK_SQL <parameter_list> TK_SQR ";
GRule[6] = "TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL <parameter_list> TK_SQR ";
GRule[7] = "eps ";
GRule[8] = "<dataType> TK_ID <remaining_list> ";
GRule[9] = "<primitiveDatatype> ";
GRule[10] = "<constructedDatatype> ";
GRule[11] = "TK_INT ";
GRule[12] = "TK_REAL ";
GRule[13] = "TK_RECORD TK_RECORDID ";
GRule[14] = "TK_COMMA <parameter_list> ";
GRule[15] = "eps ";
GRule[16] = "<typeDefinitions> <declarations> <otherStmts> <returnStmt> ";
GRule[17] = "<typeDefinition> <typeDefinitions> ";
GRule[18] = "eps ";
GRule[19] = "TK_RECORD TK_RECORDID <fieldDefinitions> TK_ENDRECORD TK_SEM ";
GRule[20] = "<fieldDefinition> <fieldDefinition> <moreFields> ";
GRule[21] = "TK_TYPE <primitiveDatatype> TK_COLON TK_FIELDID TK_SEM ";
GRule[22] = "<fieldDefinition> <moreFields> ";
GRule[23] = "eps ";
GRule[24] = "<declaration> <declarations> ";
GRule[25] = "eps ";
GRule[26] = "TK_TYPE <dataType> TK_COLON TK_ID <global_or_not> TK_SEM ";
GRule[27] = "TK_COLON TK_GLOBAL ";
GRule[28] = "eps ";
GRule[29] = "<stmt> <otherStmts> ";
GRule[30] = "eps ";
GRule[31] = "<assignmentStmt> ";
GRule[32] = "<iterativeStmt> ";
GRule[33] = "<conditionalStmt> ";
GRule[34] = "<ioStmt> ";
GRule[35] = "<funCallStmt> ";
GRule[36] = "<singleOrRecId> TK_ASSIGNOP <arithmeticExpression> TK_SEM ";
GRule[37] = "TK_ID <singleA> ";
GRule[38] = "TK_DOT TK_FIELDID ";
GRule[39] = "eps ";
GRule[40] = "<outputParameters> TK_CALL TK_FUNID TK_WITH TK_PARAMETERS <inputParameters> TK_SEM ";
GRule[41] = "TK_SQL <idList> TK_SQR TK_ASSIGNOP ";
GRule[42] = "eps ";
GRule[43] = "TK_SQL <idList> TK_SQR ";
GRule[44] = "TK_WHILE TK_OP <booleanExpression> TK_CL <stmt> <otherStmts> TK_ENDWHILE ";
GRule[45] = "TK_IF TK_OP <booleanExpression> TK_CL TK_THEN <stmt> <otherStmts> <elsePart> ";
GRule[46] = "TK_ELSE <stmt> <otherStmts> TK_ENDIF ";
GRule[47] = "TK_ENDIF ";
GRule[48] = "TK_READ TK_OP <singleOrRecId> TK_CL TK_SEM ";
GRule[49] = "TK_WRITE TK_OP <allVar> TK_CL TK_SEM ";
GRule[50] = "<singleOrRecId> ";
GRule[51] = "TK_RECORDID TK_DOT TK_FIELDID ";
GRule[52] = "<term> <expPrime> ";
GRule[53] = "<lowPrecedenceOperators> <term> <expPrime> ";
GRule[54] = "eps ";
GRule[55] = "<factor> <termPrime> ";
GRule[56] = "<highPrecedenceOperators> <factor> <termPrime> ";
GRule[57] = "eps ";
GRule[58] = "TK_OP <arithmeticExpression> TK_CL ";
GRule[59] = "<all> ";
GRule[60] = "TK_MUL ";
GRule[61] = "TK_DIV ";
GRule[62] = "TK_PLUS ";
GRule[63] = "TK_MINUS ";
GRule[64] = "TK_ID ";
GRule[65] = "TK_NUM ";
GRule[66] = "TK_RNUM ";
GRule[67] = "TK_RECORDID <temp> ";
GRule[68] = "eps ";
GRule[69] = "TK_DOT TK_FIELD ";
GRule[70] = "TK_OP <booleanExpression> TK_CL <logicalOp> TK_OP <booleanExpression> TK_CL ";
GRule[71] = "<var> <relationalOp> <var> ";
GRule[72] = "TK_NOT <booleanExpression> ";
GRule[73] = "TK_ID ";
GRule[74] = "TK_NUM ";
GRule[75] = "TK_RNUM ";
GRule[76] = "TK_AND ";
GRule[77] = "TK_OR ";
GRule[78] = "TK_LT ";
GRule[79] = "TK_LE ";
GRule[80] = "TK_EQ ";
GRule[81] = "TK_GT ";
GRule[82] = "TK_GE ";
GRule[83] = "TK_NE ";
GRule[84] = "TK_RETURN <optionalReturn> TK_SEM ";
GRule[85] = "TK_SQL <idList> TK_SQR ";
GRule[86] = "eps ";
GRule[87] = "TK_ID <more_ids> ";
GRule[88] = "TK_COMMA <idList> ";
GRule[89] = "eps ";


/*
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:driver.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"

// char GRule[95][100] = {
//     "",
//     "otherFunctions mainFunction",
//     "TK_MAIN stmts TK_END",
//     "function otherFunctions",
//     "eps",
//     "TK_FUNID input_par output_par TK_SEM stmts TK_END",
//     "TK_INPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR",
//     "TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR",
//     "eps",
//     "dataType TK_ID remaining_list",
//     "primitiveDatatype",
//     "constructedDatatype",
//     "TK_INT",
//     "TK_REAL",
//     "TK_RECORD TK_RECORDID",
//     "TK_COMMA parameter_list",
//     "eps",
//     "typeDefinitions declarations otherStmts returnStmt",
//     "typeDefinition typeDefinitions",
//     "eps",
//     "TK_RECORD TK_RECORDID fieldDefinitions TK_ENDRECORD TK_SEM",
//     "fieldDefinition fieldDefinition moreFields",
//     "TK_TYPE primitiveDatatype TK_COLON TK_FIELDID TK_SEM",
//     "fieldDefinition moreFields",
//     "eps",
//     "declaration declarations",
//     "eps",
//     "TK_TYPE dataType TK_COLON TK_ID global_or_not TK_SEM",
//     "TK_COLON TK_GLOBAL",
//     "eps",
//     "stmt otherStmts",
//     "eps",
//     "assignmentStmt",
//     "iterativeStmt",
//     "conditionalStmt",
//     "ioStmt",
//     "funCallStmt",
//     "singleOrRecId TK_ASSIGNOP arithmeticExpression TK_SEM",
//     "TK_ID new24",
//     "TK_DOT TK_FIELDID",
//     "eps",
//     "outputParameters TK_CALL TK_FUNID TK_WITH TK_PARAMETERS inputParameters TK_SEM",
//     "TK_SQL idList TK_SQR TK_ASSIGNOP",
//     "eps",
//     "TK_SQL idList TK_SQR",
//     "TK_WHILE TK_OP booleanExpression TK_CL stmt otherStmts TK_ENDWHILE",
//     "TK_IF TK_OP booleanExpression TK_CL TK_THEN stmt otherStmts elsePart",
//     "TK_ELSE stmt otherStmts TK_ENDIF",
//     "TK_ENDIF",
//     "TK_READ TK_OP singleOrRecId TK_CL TK_SEM",
//     "TK_WRITE TK_OP allVar TK_CL TK_SEM",
//     "TK_ID newVar",
//     "TK_NUM",
//     "TK_RNUM",
//     "TK_DOT TK_FIELDID",
//     "eps",
//     "term expPrime",
//     "lowPrecedenceOperators term expPrime",
//     "eps",
//     "factor termPrime",
//     "highPrecedenceOperators factor termPrime",
//     "eps",
//     "TK_OP arithmeticExpression TK_CL",
//     "all",
//     "TK_MUL",
//     "TK_DIV",
//     "TK_PLUS",
//     "TK_MINUS",
//     "TK_NUM",
//     "TK_RNUM",
//     "TK_ID temp",
//     "TK_DOT TK_FIELDID",
//     "eps",
//     "TK_OP booleanExpression TK_CL logicalOp TK_OP booleanExpression TK_CL",
//     "var relationalOp var",
//     "TK_NOT TK_OP booleanExpression TK_CL",
//     "TK_ID",
//     "TK_NUM",
//     "TK_RNUM",
//     "TK_AND",
//     "TK_OR",
//     "TK_LT",
//     "TK_LE",
//     "TK_EQ",
//     "TK_GT",
//     "TK_GE",
//     "TK_NE",
//     "TK_RETURN optionalReturn TK_SEM",
//     "TK_SQL idList TK_SQR",
//     "eps",
//     "TK_ID more_ids",
//     "TK_COMMA idList",
//     "eps",
// };


void commentFreeCode(char const* Filename){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(Filename, "r");
    if(fp == NULL){
        printf("Invalid source file\n");
        exit(-1);
    }
    while((read = getline(&line, &len, fp)) != -1){
        if(line[0] == '\n'){
            continue;
        }
        int position_of_comment = -1;
        int i = 0;
        while(i!=read){
            if(line[i] == '%'){
                position_of_comment = i;
                break;
            }
            i++;
        }

        if(position_of_comment == -1){
            printf("%s\n", line);
        }
        else if (position_of_comment != 0){
            line[position_of_comment] = '\0';
            printf("%s\n", line);
        }
    }
}

void printAllTokens(char const* Filename){
    FILE * fp;
    fp = fopen(Filename, "r");
    buffersize k = 25;
    lineNo=1;
    state = 1;

    buffer b;
    buffersize bufsize = 25;

    b = (buffer) malloc(sizeof(char)*bufsize);

    tokenInfo token = getNextToken(fp, b, k);
    printf("%25s%25s%25d\n", "Token Name", "Lexeme", "Line Number");

    while(strcmp(token.name, "$")!=0){
        printf("%25s%25s%25d\n",getCorrespondingToken(token.id),token.name,token.lineNo);
        state = 1;
        token = getNextToken(fp, b, k);
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 3){
        printf("Insufficient arguments provided, run as follows ./compiler testcase1.txt outfile.txt");
        return 0;
    }

    printf("---------------------------------------------------\n");
    printf("First and Follow Sets automated check firstandfollow.c\n");
    printf("Lexical and Syntax analysis module implemented!\n");
    printf("---------------------------------------------------\n");

    while(1){
        printf("\n---------------------------------------------------\n");
        printf("Press a number to choose the corresponding option\n");
        printf("Press 1 to see comment free code\n");
        printf("Press 2 to see a list of tokens generated by the lexer\n");
        printf("Press 3 for parsing and verifying syntactic correctness of code\n");
        printf("Press 4 for creating the parse tree\n");
        printf("Press 5 to exit\n");
        printf("---------------------------------------------------\n");
        int choice;
        scanf("%d",&choice);
        if (choice == 1)
            commentFreeCode(argv[1]);
        else if(choice == 2)
            printAllTokens(argv[1]);
        else if(choice == 3  || choice == 4)
        {
            table t = (int **) malloc(table_row * sizeof(int *));
            int i = 0;

            for (i=0; i<table_row; i++)
                 t[i] = (int *) malloc(table_row * sizeof(int));

            FILE * fp;
            fp = fopen("grammar.txt", "r");

            createParseTable(fp, t);

            fclose(fp);

            parseTree answer = parseInputSourceCode(argv[1], t);
            if(choice == 4)
            {
                printParseTree(answer, argv[2]);
                printf("You can find your file at --> %s\n", argv[2]);
            }
        }
        else if(choice == 5)
        {
            printf("\n\nThank You!\n");
                exit(0);
        }
        else {
            printf("Please enter valid input\n");
        }
    }


    return 0;
}

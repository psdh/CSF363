// filename: parserDef.h
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

// parserDef.h: Contains all definitions for data types such as grammar, table, parseTree etc. used in parser.c

#ifndef PARSERDEF_H_INCLUDED
#define PARSERDEF_H_INCLUDED

#include <stdio.h>

#define table_row 60

typedef int** table;

struct tree {
    int id;
    struct tree *parent;
    struct tree *firstKid;
    struct tree *siblings;
};

typedef struct tree* parseTree;

parseTree next(parseTree);

struct stack;
typedef struct stack stack;

struct stack
{
    int data;
    stack* next;
};

stack* push_ints(stack*, int* , parseTree);
stack* push(stack*, int);
stack pop(stack*);

int* getRuleRHSrev(int);

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

char termsArray[101][30] = {
                    "program",
                    "mainFunction",
                    "otherFunctions",
                    "function",
                    "input_par",
                    "output_par",
                    "parameter_list",
                    "dataType",
                    "primitiveDatatype",
                    "constructedDatatype",
                    "remaining_list",
                    "stmts",
                    "typeDefinitions",
                    "typeDefinition",
                    "fieldDefinitions",
                    "fieldDefinition",
                    "moreFields",
                    "declarations",
                    "declaration",
                    "global_or_not",
                    "otherStmts",
                    "stmt",
                    "assignmentStmt",
                    "singleOrRecId",
                    "funCallStmt",
                    "outputParameters",
                    "inputParameters",
                    "iterativeStmt",
                    "conditionalStmt",
                    "elsePart",
                    "ioStmt",
                    "allVar",
                    "arithmeticExpression",
                    "expPrime",
                    "term",
                    "termPrime",
                    "factor",
                    "highPrecedenceOperator",
                    "lowPrecedenceOperators",
                    "all",
                    "temp",
                    "booleanExpression",
                    "var",
                    "logicalOp",
                    "relationalOp",
                    "returnStmt",
                    "optionalReturn",
                    "idList",
                    "more_ids",
                    // Terminals now!
                    "TK_AND",
                    "TK_ASSIGNOP",
                    "TK_CALL",
                    "TK_CL",
                    "TK_COLON",
                    "TK_COMMA",
                    "TK_DIV",
                    "TK_DOT",
                    "TK_ELSE",
                    "TK_END",
                    "TK_ENDIF",
                    "TK_ENDRECORD",
                    "TK_ENDWHILE",
                    "TK_EQ",
                    "TK_FIELDID",
                    "TK_FUNID",
                    "TK_GE",
                    "TK_GLOBAL",
                    "TK_GT",
                    "TK_ID",
                    "TK_IF",
                    "TK_INPUT",
                    "TK_INT",
                    "TK_LE",
                    "TK_LIST",
                    "TK_LT",
                    "TK_MAIN",
                    "TK_MINUS",
                    "TK_MUL",
                    "TK_NE",
                    "TK_NOT",
                    "TK_NUM",
                    "TK_OP",
                    "TK_OR",
                    "TK_OUTPUT",
                    "TK_PARAMETER",
                    "TK_PARAMETERS",
                    "TK_PLUS",
                    "TK_READ",
                    "TK_REAL",
                    "TK_RECORD",
                    "TK_RECORDID",
                    "TK_RETURN",
                    "TK_RNUM",
                    "TK_SEM",
                    "TK_SQL",
                    "TK_SQR",
                    "TK_THEN",
                    "TK_TYPE",
                    "TK_WHILE",
                    "TK_WITH",
                    "TK_WRITE",
                    };

#endif

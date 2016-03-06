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
    char* lexeme;
    int lineNo;
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

extern char GRule[95][100];

#endif

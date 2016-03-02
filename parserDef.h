// filename: lexer.c
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

// parserDef.h  : Contains all definitions for data types such as grammar, table, parseTree etc. used in parser.c

#include "parser.h"
#include <stdio.h>

typedef char** table;

struct tree {
    int n;
    struct tree *firstKid;
    struct tree *siblings;
};

typedef *tree parseTree;

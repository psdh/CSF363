/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:parser.h
*/

// parser.h        : Contains function prototype declarations of functions in parser.c


#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "parserDef.h"

#include <stdio.h>

// void createParseTable(grammar G, table T): This function takes as input the grammar G,
// uses FIRST and FOLLOW information to populate  the table T appropriately.

void createParseTable(FILE* G, table T);

parseTree parseInputSourceCode(char *testcaseFile, table T);

void printParseTree(parseTree  PT, char *outfile);

void intializeTable(table T);

int printParseTree_r(parseTree curr, FILE* f, int * size, int print);

char* getCorrespondingToken(int f);

int error_in_parsing;

#endif

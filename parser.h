// filename: lexer.c
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

// parser.h        : Contains function prototype declarations of functions in parser.c


#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

// void createParseTable(grammar G, table T): This function takes as input the grammar G,
// uses FIRST and FOLLOW information to populate  the table T appropriately.

void createParseTable(FILE* G, table T);

parseTree parseInputSourceCode(char *testcaseFile, table T);

void printParseTree(parseTree  PT, char *outfile);

#endif

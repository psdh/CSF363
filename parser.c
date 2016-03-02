// filename: lexer.c
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

#include "parserDef.h"
#include "lexer.h"

typedef char[20] string;

typedef string[] rule;

void createParseTable(FILE* G, table T)
{
    // Assuming that we have one grammar rule in one line
    // read till \n and process rule, increment the number of terminals and non-terminals

    char line[120] =

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

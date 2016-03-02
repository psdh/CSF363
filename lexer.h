// filename: lexer.h
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

// lexer.h           : Contains function prototype declarations of functions in lexer.c

#include <stdio.h>
#include "lexerDef.h"

typedef int buffersize;
typedef char* buffer;

FILE *getStream(FILE *fp, buffer B, buffersize k);

tokenInfo  getNextToken(FILE *fp);

/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:lexerDef.h
*/

// lexerDef.h     : Contains all data definitions used in lexer.c

#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED

#include <stdlib.h>

// id contains a number that corresponds to TK_FIELDID etc
// name contains actual lexeme for example fileName
// lineNo contains line no of lexeme

typedef struct
{
    int id;
    char * name;
    int lineNo;
}tokenInfo;

int lineNo;
int state;
int offset;

typedef int buffersize;
typedef char* buffer;

// buffer b = (buffer) malloc(100*sizeof(buffer));


#endif

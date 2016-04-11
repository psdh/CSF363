/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:lexer.h
*/

// lexer.h           : Contains function prototype declarations of functions in lexer.c

#include <stdio.h>
#include"lexerDef.h"

#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

FILE *getStream(FILE *fp, buffer B, buffersize k);

tokenInfo getNextToken(FILE *fp, buffer b, buffersize k);

#endif

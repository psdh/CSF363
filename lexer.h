// filename: lexer.h
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

// lexer.h           : Contains function prototype declarations of functions in lexer.c

#include <stdio.h>
#include"lexerDef.h"

#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

FILE *getStream(FILE *fp, buffer B, buffersize k);

// TODO<psdh> define tokenInfo (probably a struct that  will be used when storing in the symbol table)
// Figure out where must tokenInfo be defined (which file that is)
tokenInfo  getNextToken(FILE *fp);

#endif

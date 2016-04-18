/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:symboltable.h
*/


#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

#include "symboltabledef.h"
#include "parser.h"
#include "lexer.h"

#include <stdio.h>


hashtable *createSymbolTable(parseTree PT);

void printSymbolTable(hashtable ht);

#endif

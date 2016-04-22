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
#include "ast.h"

#include <stdio.h>

// invoked by driver to create symbol table
hashtable *createSymbolTable(parseTree PT, int size);

// prints symbol table in desired formats
void printSymbolTable(hashtable *ht, int size);

// helper function used by typechecker to fetch input parameters of a given function
entry *getInputParameter(hashtable *ht, char *function, int ParameterNumber);
// helper function used by typechecker to fetch output parameters of a given function
entry *getOutputParameter(hashtable *ht, char *function, int ParameterNumber);

// keeps track of symboltable errors like redeclarations
char symboltable_errors[500][500];
int error_count;

int symbolerror;

#endif

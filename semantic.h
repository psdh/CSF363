/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: typechecker.h
*/

#ifndef SEMANTIC_H_INCLUDED
#define SEMANTIC_H_INCLUDED

#include "symboltable.h"
#include "parser.h"
#include "typechecker.h"

void check_stmt(parseTree pt, hashtable *st, int statementtype, char *scope);

#endif

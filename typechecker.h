/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: typechecker.h
*/

/* used to expose typechecker functions to other files
*/
#ifndef TYPECHECKER_H_INCLUDED
#define TYPECHECKER_H_INCLUDED

#include "symboltable.h"
#include "parser.h"
#include "semantic.h"
#include "typecheckerdef.h"

// invoked by semantic.c
void check_stmt(parseTree pt, hashtable *st, int type, char* scope);

#endif

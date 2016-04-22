/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: typecheckerdef.h
*/

/*
	Contains defintions used by the typechecker module.
*/

#ifndef TYPECHECKERDEF_H_INCLUDED
#define TYPECHECKERDEF_H_INCLUDED

#include "symboltable.h"
#include "parser.h"
#include "semantic.h"

struct list_var;

struct list_var
{
    char *name;
    struct list_var *next;
};

typedef struct list_var list_var;
// typedef *list_var node_var;

#endif

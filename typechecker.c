/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: typechecker.c
*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "typechecker.h"

// things to check here
// 1) expression in if statment is boolean, done => by the parser
// 2)
// 3) call handle_stmts recursively on this, for otherstmts
void check_conditional_stmt(parseTree curr, hashtable *st, char* scope)
{
    curr = curr->firstKid;

    while (curr != NULL)
    {
        printf("%d\n", curr->id);

        curr = curr->siblings;
    }
}

void check_stmt(parseTree curr, hashtable *st, int type, char* scope)
{
    if (type == 3) // iterative statement
        check_conditional_stmt(curr, st, scope);
    // else if (type == 1) // assignment statement
    // else if(type == 10) // iostatment
    // else  if (type == 3) // conditional statement
    // else if (type == 4) // functional call statement
}

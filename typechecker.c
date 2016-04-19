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
#include "semantic.h"

// things to check here
// 1) expression in if statment is boolean, Done => by the parser
// 2) call handle_stmts recursively on this, for otherstmts, Done
void check_conditional_stmt(parseTree curr, hashtable *st, char* scope)
{
    curr = curr->firstKid;

    while (curr != NULL)
    {
        // printf("%d\n", curr->id);

        if (curr->id == 120)
        {
            // call handle_oth_stmts here
            printf("found otherstmts\n");

            handle_oth_stmts(curr->firstKid, st, scope);

            // parseTree kid = curr->firstKid;
            // while(kid != NULL)
            // {
            //     printf("found stmt: %d\n", curr->id);
            //     kid = kid->siblings;
            // }
        }

        if (curr->id == 129)
            curr = curr->firstKid;
        else
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

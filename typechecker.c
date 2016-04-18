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

void check_iterative_stmt(parseTree curr, hashtable *st, char* scope)
{

}

void check_stmt(parseTree curr, hashtable *st, int type, char* scope)
{
    if (type == 1) // iterative statement
        check_iterative_stmt(curr, st, scope);
    // else if (type == 1) // assignment statement
    // else if(type == 10) // iostatment
    // else  if (type == 3) // conditional statement
    // else if (type == 4) // functional call statement
}

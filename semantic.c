/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: semantic.c
    This file helps check and report the semantic errors in the generated AST.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

void semanticAnalyzer(parseTree ast)
{
    // TODO<psdh> this analysis should include stuff like
    // identifier should not be declared multiple times in the same scope
    // Function overloading is not allowed.
    // identifier not declared same as global scope
    //
    do_symboltable_analysis();
}

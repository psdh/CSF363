/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: ast.c
*/

/*
This file handles the creation of the AST. The struct used by the ast is the same as the
one used by the parsetree. Unused nodes are pruned from the parsetree. Making the ast
much smaller and easier to navigate.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "ast.h"

void ast_r(parseTree);

// Function exposed to driver.
// @param parsetree The parse tree created by parser.c
parseTree ast(parseTree parsetree)
{
    parseTree ast = parsetree;

    ast_r(ast);

    return parsetree;
}

void ast_r(parseTree parsetree)
{
    // We'll edit the already present tree to create the abstract syntax tree

    parseTree ast = parsetree;

    // leaf node
    // useful, when contains values like numbers, names of variables etc
    // not useful when points to "eps"
    if (ast->firstKid == NULL && ast->siblings == NULL)
    {
        if (ast->id == 57)
        {
            ast->parent->firstKid = NULL;
            free(ast);
            return;
        }
        else
        {
            // in this branch, the values stored must be returned as is
            return;
        }
    }

    if (ast->firstKid != NULL && ast->siblings == NULL)
    {
        if (ast->id == 100)
        {
            return ast_r(ast->firstKid);
        }
        else
        {
            parseTree parent = ast->parent;

            parent->firstKid = ast->firstKid;
            ast->firstKid->parent = parent;
            free(ast);

            return ast_r(parent->firstKid);
        }
    }

    // linearizing the functions branch
    if (ast->id == 103 && ast->parent->id == 102)
    {
        parseTree it = ast->siblings;
        parseTree prev = ast;
        parseTree parent = ast->parent;

        while(it->id != 57)
        {
            // at "otherfunctions"
            if (it->id == 102)
            {
                prev->siblings = it->firstKid;
                free(it);
                it = prev->siblings;
                it->parent = parent;
                continue;
            }
            prev = it;
            it = it->siblings;
            it->parent = parent;
        }

        prev->siblings = NULL;
        free(it);
    }


    // linearizing the "stmt" branch
    if (ast->id == 121 && ast->parent->id == 120)
    {
        parseTree it = ast->siblings;
        parseTree prev = ast;
        parseTree parent = ast->parent;

        while(it->id != 57)
        {
            // at "otherfunctions"
            if (it->id == 120)
            {
                prev->siblings = it->firstKid;
                free(it);
                it = prev->siblings;
                it->parent = parent;
                continue;
            }
            prev = it;
            it = it->siblings;
            it->parent = parent;
        }

        prev->siblings = NULL;
        free(it);
    }

    // linearizing the "parameter_list", "remaining_list" branch
    if (ast->parent->id == 106 && ast->id == 107 && ast->siblings->id == 4)
    {
        parseTree it = ast->siblings;
        parseTree prev = ast;
        parseTree parent = ast->parent;

        while(it->id != 57)
        {
            // at "remaining_list" or at "parameter_list"
            if (it->id == 106 || it->id == 110)
            {
                prev->siblings = it->firstKid;
                free(it);
                it = prev->siblings;
                it->parent = parent;
                continue;
            }
            prev = it;
            it = it->siblings;
            it->parent = parent;
        }

        prev->siblings = NULL;
        free(it);
    }

    // linearizing the "typeDefinition" branch
    if (ast->parent->id == 112 && ast->id == 113)
    {
        parseTree it = ast->siblings;
        parseTree prev = ast;
        parseTree parent = ast->parent;

        while(it->id != 57)
        {
            // at "typeDefinitions"
            if (it->id == 112)
            {
                prev->siblings = it->firstKid;
                free(it);
                it = prev->siblings;
                it->parent = parent;
                continue;
            }
            prev = it;
            it = it->siblings;
            it->parent = parent;
        }

        prev->siblings = NULL;
        free(it);
    }

    // linearizing the declarations branch
    if (ast->id == 118 && ast->parent->id == 117)
    {
        parseTree it = ast->siblings;
        parseTree prev = ast;
        parseTree parent = ast->parent;

        while(it->id != 57)
        {
            // at "otherfunctions"
            if (it->id == 117)
            {
                prev->siblings = it->firstKid;
                free(it);
                it = prev->siblings;
                it->parent = parent;
                continue;
            }
            prev = it;
            it = it->siblings;
            it->parent = parent;
        }

        prev->siblings = NULL;
        free(it);
    }


    // if the tree has reached here => siblings pointer is not null
    // parsing all siblings to remove ";", "input", "output", "parameters" and the likes

    parseTree level = ast;

    parseTree prev = NULL;

    while (level != NULL)
    {
        if (level->firstKid == NULL)
        {
            // add more here
            switch(level->id)
            {
                case 1: //TK_ASSSIGNOP
                case 9: //TK_WITH
                case 10: //TK_PARAMETERS
                case 11: //TK_END
                case 15: //TK_TYPE
                case 16: //TK_MAIN
                case 18: //TK_PARAMETER
                case 19: //TK_LIST
                case 20: //TK_SQL
                case 21: //TK_SQR
                case 22: //TK_INPUT
                case 23: //TK_OUTPUT
                case 26: //TK_SEM
                case 27: //TK_COLON
                case 28: //TK_DOT
                case 30: //TK_OP
                case 31: //TK_CL
                case 37: //TK_RETURN
                case 42: //TK_CALL
                case 44: //TK_ENDRECORD
                case 56: //TK_COMMA
                        {
                            if (level->id == 16)
                                mainfuncitonline = level->lineNo;

                            // linearizing "stmt otherstmts in iterativestmts"
                            if (level->id == 31 && level->siblings != NULL && level->siblings->id == 121)
                            {
                                parseTree othst = level->siblings->siblings;
                                level->siblings->siblings = othst->firstKid;
                                othst->firstKid = level->siblings;
                                level->siblings = othst;
                                othst->firstKid->parent = othst;
                            }

                            if (prev == NULL)
                            {
                                parseTree parent = level->parent;
                                level->parent->firstKid = level->siblings;

                                free(level);

                                level = parent->firstKid;
                                continue;
                            }

                            prev->siblings = level->siblings;

                            free(level);
                            level = prev->siblings;
                            continue;
                        }

            }


            // linearizing statements in the if branch
            if (level->id == 33)
            {
                parseTree othst = level->siblings->siblings;
                level->siblings->siblings = othst->firstKid;
                othst->firstKid = level->siblings;
                level->siblings = othst;
                othst->firstKid->parent = othst;
            }
            // done for else part of statements
            if (level->id == 45)
            {
                parseTree othst = level->siblings->siblings;
                level->siblings->siblings = othst->firstKid;
                othst->firstKid = level->siblings;
                level->siblings = othst;
                othst->firstKid->parent = othst;
            }

            prev = level;
            level = level->siblings;
            continue;
        }
        else
        {
            ast_r(level->firstKid);
            prev = level;
            level = level->siblings;
        }
    }
}

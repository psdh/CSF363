/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: ast.c
    This file helps create the Abstract Syntax Tree for the already constructed parse tree.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "ast.h"

void ast_r(parseTree);

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
            // assuming that "eps" in the first kid of its parent (mostly the case)
            // TODO <psdh> confirm this
            // sibling wala scene handled elsewhere! (see while before return in this fn)
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
            // Don't remove "program"

            // ast = ast->firstKid;
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
    // TODO<psdh> mention all that is being removed here!

    parseTree level = ast;

    parseTree prev = NULL;

    while (level != NULL)
    {
        if (level->firstKid == NULL)
        {
            // add more here
            switch(level->id)
            {
                case 1:
                case 9:
                case 10:
                case 11:
                case 15:
                case 16:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 26:
                case 27:
                case 28:
                case 30:
                case 31:
                case 37:
                // added 42 for TK_CALL
                case 42:
                case 44:
                case 56:
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
            // TODO<psdh> do this for conditional and elsepart statements too
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
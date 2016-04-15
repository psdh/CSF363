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


    // linearizing the "paramerter_list", "remaining_list" branch
    if (ast->parent->id == 106 && ast->id == 4 && ast->siblings->id == 107)
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
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 26:
                case 28:
                case 30:
                case 31:
                        {
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


int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        printf("filename daalo please");
        return 0;
    }

    table t = (int **) malloc(table_row * sizeof(int *));

    int i = 0;

    for (i=0; i<table_row; i++)
         t[i] = (int *) malloc(table_row * sizeof(int));

    FILE * fp;
    fp = fopen("grammar.txt", "r");

    createParseTable(fp, t);

    fclose(fp);

    parseTree answer = parseInputSourceCode(argv[1], t);

    printParseTree(answer, "outputParse");

    answer = ast(answer);

    printParseTree(answer, "outputAST");

    printf("AST creation done bro!!");

}

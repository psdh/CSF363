/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: codegen.c
    File responsible for generating nasm code, given the Abstract Syntax Tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

void handle_declarations(parseTree decl, FILE* f)
{
    // add static "section .bss to file"
    char sec_bss[] = "section .bss\n";
    fprintf(f, "%s\n", sec_bss);

    while(decl != NULL)
    {
        // add a check here for "TK_INT" or "TK_REAL"
        printf("id: %d %s", decl->firstKid->siblings->id, decl->firstKid->siblings->lexeme);

        // add comments to asm code0
        fprintf(f, "%s:\tresw\t1\n", decl->firstKid->siblings->lexeme);
        decl = decl->siblings;
    }
}


void handle_io_stmt(parseTree curr)
{
    printf("Missing Feature: IO stmt code generation is not yet supported\n");
}


void handle_assign_stmt(parseTree curr)
{
    printf("Missing Feature: assign stmt code generation is not yet supported\n");
}

void handle_iter_stmt(parseTree curr)
{
    printf("Missing Feature: iter stmt code generation is not yet supported\n");
}


void hanlde_cond_stmt(parseTree curr)
{
    printf("Missing Feature: cond stmt code generation is not yet supported\n");
}


void handle_func_stmt(parseTree curr)
{
    printf("Missing Feature: Function Call code generation is not yet supported\n");
}

// TODO ask user to report unexpected errors to compiler developers
void handle_stmt(parseTree stmt_it, FILE* f)
{
    while(stmt_it != NULL)
    {

        if (stmt_it->firstKid->id == 35 || stmt_it->firstKid->id == 36) // io statement
            handle_io_stmt(stmt_it);
        else if (stmt_it->firstKid->id == 123) // assignment statement
            handle_assign_stmt(stmt_it);
        else if(stmt_it->firstKid->id == 12) // iterative statement: (while) might have to recursively call the  handle_stmts functions while handling iterative statments
            handle_iter_stmt(stmt_it);
        else  if (stmt_it->firstKid->id == 32) // conditional statement
            hanlde_cond_stmt(stmt_it);
        else if (stmt_it->firstKid->id == 125) // functional call statement
            handle_func_stmt(stmt_it);

        stmt_it = stmt_it->siblings;
    }
}

void codegen(parseTree ast)
{
    // Opening file for writing in the assembly code
    FILE *output = fopen("main.asm", "wb");

    // given that code files will only have one function: the _main function

    parseTree mf = ast->firstKid->siblings;
    printf("mf id: %d\n", mf->id);

    parseTree typedefinitions = mf->firstKid->firstKid;

    // TODO <psdh> handle type definitions here

    parseTree decl = typedefinitions->siblings;

    handle_declarations(decl->firstKid, output);

    char global_start[] = "\n\nsection .text\nglobal main\n\nmain:\n";

    fprintf(output, "%s", global_start);

    // handling stmt's now
    handle_stmt(decl->siblings->firstKid, output);

    fclose(output);
}

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


void handle_io_stmt(parseTree curr, FILE* f)
{
    printf("Missing Feature: <WAITING FOR SCANF TO BE RESOLVED> IO stmt code generation is not yet supported\n");
}

void handle_arith(parseTree arith, FILE* f)
{
    printf("%d\t %d\n", arith->id, arith->firstKid->id);

    parseTree factor = arith->firstKid->firstKid;

    // handle_termprime(factor->siblings, f);

    if (factor->firstKid->id ==  4)
    {
        fprintf(f, "\tmov eax, [%s]\n", factor->firstKid->lexeme);
    }
    else if (factor->firstKid->id ==  5 || factor->firstKid->id ==  6)
    {
        fprintf(f, "\tmov eax, %s\n", factor->firstKid->lexeme);
    }
    else
    {
        // arithmetic exp ke andar arithmethic exp: inceptioN :(

        // recursively calling might fix this
        // define new fn for that
    }

    parseTree termPrime = factor->siblings;

    // handling termPrime iteratively in the following code
    while(termPrime->firstKid != NULL)
    {
        if (termPrime->firstKid->firstKid->id == 40 || termPrime->firstKid->firstKid->id == 41)
        {
            char *operation;
            operation = (char *) malloc(10* sizeof(char));

            if (termPrime->firstKid->firstKid->id == 40)
                operation = "mul";
            else
                operation = "div";


            parseTree factor2 = termPrime->firstKid->siblings;

            // TK_ID
            if (factor2->firstKid->id ==  4)
            {
                fprintf(f, "\t%s eax, [%s]\n", operation, factor2->firstKid->lexeme);
            }
            // TK_NUM or TK_RNUM
            else if (factor2->firstKid->id ==  5 || factor2->firstKid->id ==  6)
            {
                fprintf(f, "\t%s eax, %s\n", operation, factor2->firstKid->lexeme);
            }
            else
            {
                // arithmetic exp ke andar arithmethic exp: inceptioN :(

                // recursively calling might fix this
                // define new fn for that
            }

        }
        termPrime = termPrime->firstKid->siblings->siblings;
    }

    // handling expPrime iteratively in the following code

    parseTree expPrime = arith->firstKid->siblings;

    while(expPrime->firstKid != NULL)
    {
        if (expPrime->firstKid->firstKid->id == 38 || expPrime->firstKid->firstKid->id == 39)
        {
            char *operation;
            operation = (char *) malloc(10* sizeof(char));

            if (expPrime->firstKid->firstKid->id == 38)
                operation = "add";
            else
                operation = "sub";


            parseTree factor2 = expPrime->firstKid->siblings;

            // TK_ID
            if (factor2->firstKid->firstKid->id ==  4)
            {
                fprintf(f, "\t%s eax, [%s]\n", operation, factor2->firstKid->firstKid->lexeme);
            }
            // TK_NUM or TK_RNUM
            else if (factor2->firstKid->firstKid->id ==  5 || factor2->firstKid->firstKid->id ==  6)
            {
                fprintf(f, "\t%s eax, %s\n", operation, factor2->firstKid->firstKid->lexeme);
            }
            else
            {
                // arithmetic exp ke andar arithmethic exp: inceptioN :(

                // recursively calling might fix this
                // define new fn for that
            }

            termPrime = factor2->firstKid->siblings;

            while(termPrime->firstKid != NULL)
            {
                if (termPrime->firstKid->firstKid->id == 40 || termPrime->firstKid->firstKid->id == 41)
                {
                    char *operation;
                    operation = (char *) malloc(10* sizeof(char));

                    if (termPrime->firstKid->firstKid->id == 40)
                        operation = "mul";
                    else
                        operation = "div";


                    parseTree factor2 = termPrime->firstKid->siblings;

                    // TK_ID
                    if (factor2->firstKid->id ==  4)
                    {
                        fprintf(f, "\t%s eax, [%s]\n", operation, factor2->firstKid->lexeme);
                    }
                    // TK_NUM or TK_RNUM
                    else if (factor2->firstKid->id ==  5 || factor2->firstKid->id == 6)
                    {
                        fprintf(f, "\t%s eax, %s\n", operation, factor2->firstKid->lexeme);
                    }
                    else
                    {
                        // arithmetic exp ke andar arithmethic exp: inceptioN :(

                        // recursively calling might fix this
                        // define new fn for that
                    }

                }
                termPrime = termPrime->firstKid->siblings->siblings;
            }

        }
        expPrime = expPrime->firstKid->siblings->siblings;
    }
}


void handle_assign_stmt(parseTree curr, FILE* f)
{
    // printf("Missing Feature: assign stmt code generation is not yet supported\n");
    parseTree arith = curr->firstKid->siblings;

    handle_arith(arith, f);

    // TODO may have change byte to something else for TK_REAL
    // TODO handle record ids here in singleRecId
    fprintf(f, "\tmov byte [%s], eax ;; assign the calculated value back\n\n", curr->firstKid->firstKid->lexeme);

}

void handle_iter_stmt(parseTree curr, FILE* f)
{
    printf("Missing Feature: iter stmt code generation is not yet supported\n");
}


void hanlde_cond_stmt(parseTree curr, FILE* f)
{
    printf("Missing Feature: cond stmt code generation is not yet supported\n");
}


void handle_func_stmt(parseTree curr, FILE* f)
{
    printf("Missing Feature: Function Call code generation is not yet supported\n");
}

// TODO ask user to report unexpected errors to compiler developers
void handle_stmt(parseTree stmt_it, FILE* f)
{
    while(stmt_it != NULL)
    {

        if (stmt_it->firstKid->id == 35 || stmt_it->firstKid->id == 36) // io statement
            handle_io_stmt(stmt_it, f);
        else if (stmt_it->firstKid->id == 123) // assignment statement
            handle_assign_stmt(stmt_it, f);
        else if(stmt_it->firstKid->id == 12) // iterative statement: (while) might have to recursively call the  handle_stmts functions while handling iterative statments
            handle_iter_stmt(stmt_it, f);
        else  if (stmt_it->firstKid->id == 32) // conditional statement
            hanlde_cond_stmt(stmt_it, f);
        else if (stmt_it->firstKid->id == 125) // functional call statement
            handle_func_stmt(stmt_it, f);

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

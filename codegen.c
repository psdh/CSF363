/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: codegen.c
    File responsible for generating nasm code, given the Abstract Syntax Tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"

int counter_used = 0;

char vars[14][100] = {"temp1", "temp2", "temp3", "temp4", "temp5", "temp6", "temp7", "temp8", "temp9", "temp10", "temp11", "temp12", "temp13", "temp14"};

void handle_io_stmt(parseTree curr, FILE* f)
{
    if (curr->firstKid->id == 35) // read command
    {
        // TODO handle record here
        fprintf(f, "\n\tmov esi, %s\n\tmov edi, numberin_form\n\tmov al, 0\n\tcall scanf\n", curr->firstKid->siblings->firstKid->lexeme);
    }
    else // write command
    {
        // TODO handle record here
        fprintf(f, "\n\tmov di, %s\n\tmov al, 0\n\tcall printf\n", curr->firstKid->siblings->firstKid->lexeme);
    }
}


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
        fprintf(f, "\t%s:\tresw\t1\n", decl->firstKid->siblings->lexeme);
        decl = decl->siblings;
    }
}



void handle_term_arith(parseTree term, FILE* f, char* reg)
{
    parseTree factor = term->firstKid;

    // eax has been stored with the required  value!
    if (factor->firstKid->id == 132) // arithmetic expression
    {
        // handle_arith_r(factor->firstKid, f);
        handle_arith(factor->firstKid, f);
    }
    else if (factor->firstKid->id == 4)
    {
        fprintf(f, "\tmov %s, [%s]\n", reg, factor->firstKid->lexeme);
    }
    else if (factor->firstKid->id == 5)
    {
        fprintf(f, "\tmov %s, %s\n", reg, factor->firstKid->lexeme);
    }
    // else if (factor->firstKid->id == 6) TODO handle TK_RNUM

    // will process termPrime now

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
                fprintf(f, "\t%s %s, [%s]\n", operation, reg, factor2->firstKid->lexeme);
            }
            // TK_NUM or TK_RNUM
            else if (factor2->firstKid->id ==  5 || factor2->firstKid->id ==  6)
            {
                fprintf(f, "\t%s %s, %s\n", operation, reg, factor2->firstKid->lexeme);
            }
            else
            {
                printf("does not support complicated arithmetic expressions as of now\n");
                // arithmetic exp ke andar arithmethic exp: inceptioN :(

                // recursively calling might fix this
                // define new fn for that
            }

        }
        termPrime = termPrime->firstKid->siblings->siblings;
    }
}

void handle_expPrime(parseTree expPrime, FILE *f, char* reg)
{
    // handling expPrime iteratively in the following code

    while(expPrime->firstKid != NULL)
    {
        char *operation;
        operation = (char *) malloc(10* sizeof(char));

        if (expPrime->firstKid->firstKid->id == 38)
            operation = "add";
        else
            operation = "sub";


        parseTree term = expPrime->firstKid->siblings;

        char *reg2 = (char*) malloc(10*sizeof(char));

        if (strcmp(reg, "eax") == 0)
            strcpy(reg2, "ebx");
        else
            strcpy(reg2, "eax");
        handle_term_arith(term, f, reg2);

        fprintf(f, "\n\t%s %s, %s\n", operation, reg, reg2);
        expPrime = expPrime->firstKid->siblings->siblings;
    }
}


void handle_arith(parseTree arith, FILE* f)
{
    printf("%d\t %d\n", arith->id, arith->firstKid->id);

    parseTree term = arith->firstKid;

    char *reg1 = (char *) malloc(10);
    reg1 = "eax";

    handle_term_arith(term, f, reg1);

    parseTree expPrime = term->siblings;
    handle_expPrime(expPrime, f, reg1);
}


void handle_assign_stmt(parseTree curr, FILE* f)
{
    // printf("Missing Feature: assign stmt code generation is not yet supported\n");
    parseTree arith = curr->firstKid->siblings;

    handle_arith(arith, f);

    // TODO may have change byte to something else for TK_REAL
    // TODO handle record ids here in singleRecId
    fprintf(f, "\tmov [%s], eax ;; assign the calculated value back\n\n", curr->firstKid->firstKid->lexeme);

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
    FILE *output = fopen("code.asm", "wb");

    // given that code files will only have one function: the _main function

    parseTree mf = ast->firstKid->siblings;
    printf("mf id: %d\n", mf->id);

    parseTree typedefinitions = mf->firstKid->firstKid;

    // TODO <psdh> handle type definitions here

    parseTree decl = typedefinitions->siblings;



    char data_section[] = "\nsection .data\n\tnumberin_form:\tdb \"%d\", 0\n\n";
    fprintf(output, "%s", data_section);


    handle_declarations(decl->firstKid, output);

    char global_start[] = "section .text\n\tglobal main\n\textern scanf\n\textern printf";
    fprintf(output, "%s", global_start);

    fprintf(output, "\nmain:");
    // handling stmt's now
    handle_stmt(decl->siblings->firstKid, output);

    fclose(output);
}

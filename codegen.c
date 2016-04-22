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
        fprintf(f, "\n\tmov esi, %s\n\tmov edi, numberin_form\n\tmov al, 0\n\tcall scanf\n\n", curr->firstKid->siblings->firstKid->lexeme);
    }
    else // write command
    {
        // TODO handle record here
        fprintf(f, "\n\tmov edi, numberin_form\n\tmov esi, [%s]\n\tmov al, 0\n\tcall printf\n", curr->firstKid->siblings->firstKid->lexeme);
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
        // printf("id: %d %s", decl->firstKid->siblings->id, decl->firstKid->siblings->lexeme);

        // add comments to asm code0
        fprintf(f, "\t%s:\tresd\t1\n", decl->firstKid->siblings->lexeme);
        decl = decl->siblings;
    }
    int i = 0;

    for (i = 0; i < 14; i++)
    {
        fprintf(f, "\t%s:\tresd\t1\n", vars[i]);
    }
}

void move(char* one, char* two, FILE* f)
{
    fprintf(f, "\n\tmov eax, [%s]", two);
    fprintf(f, "\n\tmov [%s], eax\n", one);
}

int handle_term_arith(parseTree term, FILE* f)
{
    char *reg;
    reg = vars[counter_used];
    int ret = counter_used;

    counter_used++;

    parseTree factor = term->firstKid;

    // eax has been stored with the required  value!
    if (factor->firstKid->id == 132) // arithmetic expression
    {
        // handle_arith_r(factor->firstKid, f);

        int ans = handle_arith(factor->firstKid, f);
        // fprintf(f, "\n\tmov word [%s], %s", reg, vars[ans]);
        move(reg, vars[ans], f);
    }
    else if (factor->firstKid->id == 4)
    {
        // fprintf(f, "\n\tmov word [%s], %s\n", reg, factor->firstKid->lexeme);
        move(reg, factor->firstKid->lexeme, f);
    }
    else if (factor->firstKid->id == 5)
    {
        fprintf(f, "\n\tmov word [%s], %s\n", reg, factor->firstKid->lexeme);

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

            fprintf(f, "\n\tmov word eax, [%s]\n", reg);

            // TK_ID
            if (factor2->firstKid->id ==  4)
            {
                fprintf(f, "\n\t%s word [%s]\n", operation, factor2->firstKid->lexeme);
            }
            // TK_NUM or TK_RNUM
            else if (factor2->firstKid->id ==  5 || factor2->firstKid->id ==  6)
            {
                fprintf(f, "\n\t%s word %s\n", operation, factor2->firstKid->lexeme);
            }
            else
            {
                printf("does not support complicated arithmetic expressions as of now\n");
                // arithmetic exp ke andar arithmethic exp: inceptioN :(

                // recursively calling might fix this
                // define new fn for that

                int ans2 = handle_arith(factor->firstKid, f);
                fprintf(f, "\n\t%s word %s", operation, reg, vars[ans2]);
            }

            fprintf(f, "\n\tmov [%s], eax", reg);
        }
        termPrime = termPrime->firstKid->siblings->siblings;
    }
    return ret;
}

int handle_expPrime(parseTree expPrime, FILE *f, int fac)
{
    // handling expPrime iteratively in the following code

    int ret = 0;
    while(expPrime->firstKid != NULL)
    {
        char *operation;
        operation = (char *) malloc(10* sizeof(char));

        if (expPrime->firstKid->firstKid->id == 38)
            operation = "add";
        else
            operation = "sub";


        parseTree term = expPrime->firstKid->siblings;

        int ans = handle_term_arith(term, f);

        fprintf(f, "\n\tmov eax, [%s]", vars[fac]);
        fprintf(f, "\n\t%s eax, [%s]", operation, vars[ans]);
        fprintf(f, "\n\tmov [%s], eax\n", vars[fac]);
        expPrime = expPrime->firstKid->siblings->siblings;
    }
    return ret;
}


int handle_arith(parseTree arith, FILE* f)
{
    // printf("%d\t %d\n", arith->id, arith->firstKid->id);

    parseTree term = arith->firstKid;

    char *reg1;
    reg1 = vars[counter_used];

    int ret = counter_used;

    counter_used++;

    int ans = handle_term_arith(term, f);

    parseTree expPrime = term->siblings;
    handle_expPrime(expPrime, f, ans);

    move(reg1, vars[ans], f);
    // fprintf(f, "\n\tmov word [%s], %s\n", reg1, vars[ans]);
    return ret;
}

int glo_cod_count = 0;

void handle_assign_stmt(parseTree curr, FILE* f)
{
    // printf("Missing Feature: assign stmt code generation is not yet supported\n");
    parseTree arith = curr->firstKid->siblings;

    counter_used = 0;
    int ans = handle_arith(arith, f);

    // reinitialize counter to 0
    counter_used = 0;

    // TODO may have change byte to something else for TK_REAL
    // TODO handle record ids here in singleRecId
    // fprintf(f, "\n\tmov word [%s], %s ;; assign the calculated value back\n\n", curr->firstKid->firstKid->lexeme, vars[ans]);
    move(curr->firstKid->firstKid->lexeme, vars[ans], f);
}

void handle_boolean(parseTree pt, FILE * f, int reverse){
    // printf("%d\n", pt->firstKid->id);
    int cond_count = glo_cod_count;

    if(pt->firstKid->firstKid != NULL && (pt->firstKid->firstKid->id == 4 || pt->firstKid->firstKid->id == 5 || pt->firstKid->firstKid->id == 6)){
        pt = pt->firstKid;

        if(pt->firstKid->id == 6){
            fprintf(f, "\tmov eax,%s\n", pt->firstKid->lexeme);
        }
        else{
            fprintf(f, "\tmov eax,%s\n", pt->firstKid->lexeme);
        }


        if(pt->siblings->siblings->firstKid->id == 6){
            fprintf(f, "\tmov ebx,%s\n", pt->siblings->siblings->firstKid->lexeme);
        }
        else{
            fprintf(f, "\tmov ebx,%s\n", pt->siblings->siblings->firstKid->lexeme);
        }



        fprintf(f, "\tcmp eax, ebx\n\n");

        parseTree relationalOp = pt->siblings->firstKid;

        // printf("%d\t%d\n", relationalOp->id, reverse);
        // lt -> jge
        if(relationalOp->id == 49 && reverse == 0){
            fprintf(f, "\tjge else%d\n", cond_count);
        }
        else if (relationalOp->id == 49 && reverse == 1){
            fprintf(f, "\tjl else%d\n", cond_count);
        }
        else if (relationalOp->id == 49 && reverse == 2){
            fprintf(f, "\tjl then%d\n", cond_count);
        }
        else if(relationalOp->id == 49 && reverse == 3){
            fprintf(f, "\tjge then%d\n", cond_count);
        }


        // le ->jg
        else if(relationalOp->id == 50 && reverse == 0){
            fprintf(f, "\tjg else%d\n", cond_count);
        }
        else if (relationalOp->id == 50 && reverse == 1){
            fprintf(f, "\tjle else%d\n", cond_count);
        }
        else if (relationalOp->id == 50 && reverse == 2){
            fprintf(f, "\tjle then%d\n", cond_count);
        }
        else if(relationalOp->id == 50 && reverse == 3){
            fprintf(f, "\tjg then%d\n", cond_count);
        }

        //eq -> jne
        else if(relationalOp->id == 51 && reverse == 0){
            fprintf(f, "\tjne else%d\n", cond_count);
        }
        else if (relationalOp->id == 51 && reverse == 1){
            fprintf(f, "\tje else%d\n", cond_count);
        }
        else if (relationalOp->id == 51 && reverse ==2){
            fprintf(f, "\tje then%d\n", cond_count);
        }
        else if(relationalOp->id == 51 && reverse == 3){
            fprintf(f, "\tjne then%d\n", cond_count);
        }


        // gt -> jle
        else if(relationalOp->id == 52 && reverse == 0){
            fprintf(f, "\tjle else%d\n", cond_count);
        }
        else if (relationalOp->id == 52 && reverse == 1){
            fprintf(f, "\tjg else%d\n", cond_count);
        }
        else if (relationalOp->id == 52 && reverse == 2){
            fprintf(f, "\tjg then%d\n", cond_count);
        }
        else if(relationalOp->id == 52 && reverse == 4){
            fprintf(f, "\tjle then%d\n", cond_count);
        }

        // ge -> jl
        else if(relationalOp->id == 53 && reverse == 0){
            fprintf(f, "\tjl else%d\n", cond_count);
        }
        else if (relationalOp->id == 53 && reverse == 1){
            fprintf(f, "\tjge else%d\n", cond_count);
        }
        else if (relationalOp->id == 53 && reverse == 2){
            fprintf(f, "\tjge then%d\n", cond_count);
        }
        else if (relationalOp->id == 53 && reverse == 3){
            fprintf(f, "\tjge then%d\n", cond_count);
        }

        //ne -> je
        else if(relationalOp->id == 54 && reverse == 0){
            fprintf(f, "\tje else%d\n", cond_count);
        }
        else if (relationalOp->id == 54 && reverse == 1){
            fprintf(f, "\tjne else%d\n", cond_count);
        }
        else if (relationalOp->id == 54 && reverse == 2){
            fprintf(f, "\tjne then%d\n", cond_count);
        }
        else if(relationalOp->id == 54 && reverse == 3){
            fprintf(f, "\tje then%d\n", cond_count);
        }


    }
    else if(pt->firstKid->id == 48){
        pt = pt->firstKid->siblings;
        if (reverse == 2)
            handle_boolean(pt, f, 3);
        else
            handle_boolean(pt, f, 1);
    }
    else {
        parseTree bool1 = pt->firstKid;
        parseTree logop = bool1->siblings;
        parseTree bool2 = logop->siblings;


        if(logop->firstKid->id == 46){
            handle_boolean(bool1, f, 0);
            handle_boolean(bool2, f, 0);
        }
        else{
            handle_boolean(bool1, f, 2);
            handle_boolean(bool2, f, 0);
        }

    }

}

void handle_iter_stmt(parseTree curr, FILE* f)
{   glo_cod_count+=1;
    int while_count = glo_cod_count;

    parseTree tk_while = curr->firstKid;
    parseTree boolexp = tk_while->siblings;
    parseTree otherstmt = boolexp->siblings;

    fprintf(f, "\tparent%d:\n", while_count);


    handle_boolean(boolexp, f, 0);

    handle_stmt(otherstmt->firstKid, f);

    fprintf(f, "\tjmp parent%d\n", while_count);

    fprintf(f, "\telse%d:\n", while_count);
}



void handle_cond_stmt(parseTree curr, FILE* f)
{
    glo_cod_count +=1;

    int cond_count = glo_cod_count;

    parseTree booleanExp = curr->firstKid->siblings;

    parseTree otherstmt = booleanExp->siblings->siblings;
    parseTree elsePart = otherstmt->siblings;


    handle_boolean(booleanExp, f, 0);

    fprintf(f, "\tthen%d:\n", cond_count);
    handle_stmt(otherstmt->firstKid, f);
    fprintf(f, "\tjmp end%d\n", cond_count);


    if(elsePart->firstKid->id == 34){
        fprintf(f, "\telse%d:\n", cond_count);
    }
    else{
        fprintf(f, "\telse%d:\n", cond_count);
        otherstmt = elsePart->firstKid->siblings;
        handle_stmt(otherstmt->firstKid, f);
    }

    fprintf(f, "\tend%d:\n\n",cond_count);


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
            handle_cond_stmt(stmt_it, f);
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
    // printf("mf id: %d\n", mf->id);

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

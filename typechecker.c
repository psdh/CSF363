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


void handle_boolean_exp(parseTree stmt, hashtable *ht, char* scope)
{
    char *to_check_here;
    to_check_here = (char*) malloc(20*sizeof(char));


    traverse_all_boolean(stmt, ht, scope, to_check_here);
}

void traverse_all_boolean(parseTree curr, hashtable *ht, char *scope, char *check)
{
    if (curr == NULL)
        return;


    if(curr->firstKid != NULL)
    {
        traverse_all_boolean(curr->firstKid, ht, scope, check);
       // do  you thing again!
    }
    else
    {
        // do your thing
        // TK_ID detected
        if (curr->id == 4)
        {
            entry *found = get(ht, curr->lexeme, scope);

            if (found == NULL)
                found = get(ht, curr->lexeme, "global");

            if (found != NULL)
            {
                if (strlen(check) > 0)
                {
                    if (!(strcmp(found->type, "int") == 0 && strcmp(check, "TK_NUM") == 0) && !(strcmp(found->type, "real") == 0 && strcmp(check, "TK_RNUM")))
                    {
                        printf("Variable<%s> is not of expected type: <%s>\n", curr->lexeme, check);
                    }
                }
                else
                {
                    // char answer[10];
                    if (strcmp("int", found->type) == 0 )
                    {
                        // answer = "int";
                        strcpy(check, "int");
                    }
                    else
                    {
                        // answer = "real";
                        strcpy(check, "real");
                    }
                }
            }
            else
            {

                printf("Variable: %s not declared in scope: %s or in global scope\n", curr->lexeme, scope);
            }
        }
        else if (curr->id == 5 || curr->id == 6)
        {
            if (strlen(check) == 0)
            {
                strcpy(check, getCorrespondingToken(curr->id));
            }
            else
                if (strcmp(check, getCorrespondingToken(curr->id)) != 0)
                {
                    printf("Error! types not same :( at line no: %d\n", curr->lineNo);
                }
        }
    }

    parseTree prev = curr;
    curr = curr->siblings;

    if(curr != NULL)
    {
        return traverse_all_boolean(curr, ht, scope, check);
    }
}


// things to check here
// 1) expression in if statment is boolean, Done => by the parser
// 2) call handle_stmts recursively on this, for otherstmts, Done
void check_conditional_stmt(parseTree curr, hashtable *st, char* scope)
{
    curr = curr->firstKid;

    while (curr != NULL)
    {
        // boolean expression
        if (curr->id == 141)
        {
            handle_boolean_exp(curr->firstKid, st, scope);
        }
        else if (curr->id == 120)
        {
            // call handle_oth_stmts here
            printf("found otherstmts\n");

            handle_oth_stmts(curr->firstKid, st, scope);
        }

        if (curr->id == 129)
            curr = curr->firstKid;
        else
            curr = curr->siblings;
    }
}

void check_assignment_stmt(parseTree curr, hashtable *st, char* scope){
    printf("\n%d\n", curr->firstKid->id);
}


void check_stmt(parseTree curr, hashtable *st, int type, char* scope)
{
    if (type == 1) // iterative statement
        check_assignment_stmt(curr, st, scope);
    if (type == 3) // iterative statement
        check_conditional_stmt(curr, st, scope);
    // else if (type == 1) // assignment statement
    // else if(type == 10) // iostatment
    // else  if (type == 3) // conditional statement
    // else if (type == 4) // functional call statement
}

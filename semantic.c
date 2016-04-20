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
#include "semantic.h"


void handle_stmts(parseTree stmts, hashtable *ht, char* scope);
void handle_oth_stmts(parseTree stmt_it, hashtable *ht, char* scope);

void semanticAnalyzer(parseTree ast, hashtable *ht)
{
    // TODO<psdh> this analysis should include stuff like
    //  identifier should not be declared multiple times in the same scope
    // Function overloading is not allowed.
    // global identifer declasred else where
    // Preferable do this when including stuff in the symbol table stage

    // do_symboltable_analysis();

    // From here, we are trying to traverse functions statements and identify semantic errors


    // stuff to be handled in stmt's:
    // An identifier must be declared before its use.
    // The types and  the number of parameters returned by a function must be the same as that of the parameters used in invoking the function.
    // The parameters being returned by a function must be assigned a value. If a parameter does not get a value assigned within the function definition, it should be reported as an error.
    // The function that does not return any value, must be invoked appropriately.
    // Function input parameters passed while invoking it should be of the same type as those used in the function definition. Number of input parameters must be same as that of those used in the function definition.
    // An if statement must have the expression of boolean type.
    // The function cannot be invoked recursively.


    // All of the above might just be irrelevant now :(

    parseTree othfun = ast->firstKid->firstKid;
    parseTree mf_stmts = ast->firstKid->siblings->firstKid;

    // handle stmts for all functions except main
    while (othfun != NULL)
    {
        parseTree stmts = othfun->firstKid->siblings->siblings->siblings;

        char scope[20];
        strcpy(scope, othfun->firstKid->lexeme);
        handle_stmts(stmts, ht, scope);

        othfun = othfun->siblings;
    }

    // handle main function now!
    handle_stmts(mf_stmts, ht, "_main");
    check_for_unassigned_outputs(ht);
}


void handle_stmts(parseTree stmts, hashtable *ht, char* scope)
{
    parseTree stmt_it;
    stmt_it = stmts->firstKid->siblings->siblings->firstKid;
    handle_oth_stmts(stmt_it, ht, scope);
}

void check_for_unassigned_outputs(hashtable *ht){
    int bin = 0;
    entry *temp;
    for (bin =0 ; bin < 100; bin ++){
        temp = ht->table[ bin ];
        while( temp != NULL && temp->key != NULL) {
            if(temp->isOutputParameter == 1 && temp->assigned == -1){
                printf("Error: Variable %s of %s is unassigned\n", temp->key, temp->scope);
            }
            temp = temp->next;
        }
    }
    return NULL;
}

void handle_oth_stmts(parseTree stmt_it, hashtable *ht, char* scope)
{
    if(stmt_it != NULL && stmt_it->id != 121)
    {
        printf("galat hai boss");
        return;
    }

    while (stmt_it != NULL)
    {
        int type;
        // printf("%d  ", stmt_it->firstKid->id);

        if (stmt_it->firstKid->id == 35 || stmt_it->firstKid->id == 36) // io statement
            type = 10;
        else if (stmt_it->firstKid->id == 123) // assignment statement
            type = 1;
        else if(stmt_it->firstKid->id == 12) // iterative statement: (while) might have to recursively call the  handle_stmts functions while handling iterative statments
            type = 2;
        else  if (stmt_it->firstKid->id == 32) // conditional statement
            type = 3;
        else if (stmt_it->firstKid->id == 125) // functional call statement
            type = 4;
        else
            printf("unknown type of stmt :( %d\n", stmt_it->firstKid->id);

        // printf("%d  \n", type);

        check_stmt(stmt_it, ht, type, scope);

        stmt_it = stmt_it->siblings;
    }


}


// Depth first traversal
traverse_all(parseTree curr)
{
    if (curr == NULL)
        return;


    if(curr->firstKid != NULL)
    {
        traverse_all(curr->firstKid);
       // do  you thing again!
    }
    else
    {
        // do your thing
    }

    parseTree prev = curr;
    curr = curr->siblings;

    if(curr != NULL)
    {
        return traverse_all(curr);
    }
}

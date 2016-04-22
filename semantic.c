/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: semantic.c
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "semantic.h"

/*
	Semantic Analysis Module. The function semanticAnalyzer is
	exposed to the driver. It uses several functions from type
	checker.
*/

void handle_stmts(parseTree stmts, hashtable *ht, char* scope);
void handle_oth_stmts(parseTree stmt_it, hashtable *ht, char* scope);

// invoked by driver
void semanticAnalyzer(parseTree ast, hashtable *ht)
{

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

// handle <stmts>
void handle_stmts(parseTree stmts, hashtable *ht, char* scope)
{
    parseTree stmt_it;
    stmt_it = stmts->firstKid->siblings->siblings->firstKid;
    handle_oth_stmts(stmt_it, ht, scope);
    // check return sttmt
    parseTree returnstmt = stmts->firstKid->siblings->siblings->siblings;
    if(returnstmt != NULL && returnstmt->firstKid != NULL)
        check_stmt(returnstmt->firstKid ,ht, 5, scope);
}

// after we are done with a function this function checks if output is unassigned
void check_for_unassigned_outputs(hashtable *ht){
    int bin = 0;
    entry *temp;
    for (bin =0 ; bin < 100; bin ++){
        temp = ht->table[ bin ];
        while( temp != NULL && temp->key != NULL) {
            if(temp->isOutputParameter == 1 && temp->assigned == -1){
                printf("Error: Variable %s of %s is unassigned\n", temp->key, temp->scope);
                symbolerror = 1;
            }
            temp = temp->next;
        }
    }
    return NULL;
}

// handle <otherstmts>
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


        check_stmt(stmt_it, ht, type, scope);

        stmt_it = stmt_it->siblings;
    }


}


// Traverses all statements calls related handler
traverse_all(parseTree curr)
{
    if (curr == NULL)
        return;


    if(curr->firstKid != NULL)
    {
        traverse_all(curr->firstKid);
    }
    else
    {
    	;
    }

    parseTree prev = curr;
    curr = curr->siblings;

    if(curr != NULL)
    {
        return traverse_all(curr);
    }
}

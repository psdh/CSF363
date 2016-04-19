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
            handle_oth_stmts(curr->firstKid, st, scope);
        }

        if (curr->id == 129)
            curr = curr->firstKid;
        else
            curr = curr->siblings;
    }
}

void check_factor(parseTree factor, hashtable *st, char *scope, char *type){
    // a wild 5 was encountered but type expcted was different
    // @ToDo take care of variable
    parseTree all = factor->firstKid;
    if(all->id == 5){
        if(strcmp(type, "int") != 0){
            printf("Error: %s expected got %s\n", type, "int");
        }
    }
    // a wild 5.55 was encountered but type expected was different
    else if(all->id == 6){
        if(strcmp(type, "real") != 0){
            printf("Error: %s expected got %s\n", type, "real");
        }
    }
    else {
        printf("%s\n", "CALM AS POSSIBLE");
        parseTree temp = all->siblings;
        // Normal variable (not record)
        if(temp == NULL || temp->firstKid == NULL){
            printf("!!!!!!!!!%s!!!!!!!\n", all->lexeme);
            // records are dvisible by scalar :(
            entry *var = get(st, all->lexeme, scope);
            printf("%s\n", var->type);
            if (var == NULL){
                printf("Error: Variable %s not in current scope %s, checking global\n", all->lexeme, scope);
                var = get(st, all->firstKid->lexeme, "global");
                // doesnt exist globally
                if (var == NULL){
                    printf("Error: Variable %s not even declared globally\n", all->lexeme);
                }
                // exists globally
                else {
                    if(strcmp(type, var->type) != 0){
                        printf("Error: %s expected got %s in %s\n", type, var->type, all->lexeme);
                    }
                }
            }
            // exists in scope
            else {
                if(strcmp(type, var->type) != 0){
                    printf("Error: %s expected got %s in %s\n", type, var->type, all->lexeme);
                }
            }
        }
        // record type
        else {

            entry * record = get(st, all->firstKid->lexeme, scope);
            if (record == NULL){
                 printf("Error: Record Variable %s not in current scope %s, checking global\n", all->firstKid->lexeme, scope);
                 record = get(st, all->firstKid->lexeme, "global");
                 if (record == NULL){
                    printf("Error: Record Variable %s not even declared globally\n", all->firstKid->lexeme);
                 }
                 else {
                    // record declaration found, we go through linkedlsit to find type
                    record = get(st, record->type, "global");
                    record_dec * rec = record-> record;
                    while(rec!= NULL && strcmp(rec->name, temp->firstKid->lexeme) != 0){
                        rec = rec->next;
                    }
                    if(rec == NULL){
                        printf("Error: Record %s has no field %s\n",record->key, temp->firstKid->lexeme);
                    }
                    else if (strcmp(rec->type, type)){
                        printf("Error: %s expected got %s in %s.%s\n", type, rec->type, all->firstKid->lexeme,rec->name);
                    }
                 }
            }
            else {
                printf("%s\n", record->type);
                record = get(st, record->type, "global");
                record_dec * rec = record-> record;
                while(rec!= NULL && strcmp(rec->name, temp->firstKid->lexeme) != 0){
                    rec = rec->next;
                }
                if(rec == NULL){
                    printf("Error: Record%s has no field %s\n",record->key, temp->firstKid->lexeme);
                }
                else if (strcmp(rec->type, type)){
                    printf("Error: %s expected got %s in %s.%s\n", type, rec->type, all->firstKid->lexeme,rec->name);
                }
            }

        }
    }
}


void check_termprime(parseTree termprime, hashtable *st, char*scope, char* type){
    parseTree hpo = termprime->firstKid;
    parseTree factor = hpo->siblings;
    parseTree tpp = factor->siblings;

    if (factor->firstKid->id == 123){
        printf("%s\n", "AAAA");
        check_arith(factor->firstKid, st, scope, type);
    }
    else {
        check_factor(factor, st, scope, type);
    }

    if(tpp != NULL && tpp->firstKid!=NULL){
        check_termprime(tpp, st, scope, type);
    }
}

void check_expprime(parseTree expprime, hashtable *st, char * scope, char * type){
    parseTree term = expprime->firstKid->siblings;
    parseTree expp = term->siblings;
    if(expp->firstKid!=NULL){}
        check_expprime(expp, st, scope, type);

    parseTree factor = term->firstKid;
    parseTree termprime = factor->siblings;

    printf("%d\n", factor->firstKid->id);

    if (factor->firstKid->id == 123){
        check_arith(factor->firstKid, st, scope, type);
    }
    else {
        check_factor(factor, st, scope, type);
    }

    if(termprime!= NULL && termprime->firstKid != NULL){
        printf("%s\n", "termprime hai exprime mein");
        check_termprime(termprime, st, scope, type);
    }


}


void check_arith(parseTree expr, hashtable *st, char * scope, char * type){
    parseTree  term = expr->firstKid;
    parseTree expprime = term->siblings;
    parseTree factor = term->firstKid;
    parseTree termprime = factor->siblings;
    printf("%d\n", factor->firstKid->id);
    if (factor->firstKid->id == 123){
        check_arith(factor->firstKid, st, scope, type);
    }
    // not another arithmetic expression
    else {
        printf("in check_arith checking factor %s %s %s\n", scope, type, factor->firstKid->lexeme);
        check_factor(factor, st, scope, type);
        printf("%s\n", "after check_arith checking factor");
    }

    if(termprime!= NULL && termprime->firstKid != NULL){
        printf("%s\n", "term prime hai arithmetic mein");
        check_termprime(termprime, st, scope, type);
    }


    if(expprime != NULL && expprime->firstKid != NULL){
        check_expprime(expprime, st, scope, type);
    }

    printf("%s\n", "FFFF");
}


void check_assignment_stmt(parseTree curr, hashtable *st, char* scope){

    parseTree sorrec = curr->firstKid;

    char *type = (char*)  malloc(sizeof(char)*20);

    // non record variable
    if(sorrec->firstKid->siblings->firstKid == NULL){
        printf("Hum yahan\t%s\n", sorrec->firstKid->lexeme);

        entry * var = get(st, sorrec->firstKid->lexeme, scope);
        // not in current scope maybe declared globally
        if(var == NULL){
            printf("Variable %s not in scope %s, Checking globally\n", sorrec->firstKid->lexeme, scope);
            entry * var = get(st, sorrec->firstKid->lexeme, "global");
            if(var == NULL){
                printf("Error: variable %s is not declared\n", sorrec->firstKid->lexeme);
            }
            else{
                strcpy(type, var->type);
            }
        }
        else {
            strcpy(type, var->type);
        }
    }
    // bhai ye toh record hai
    else {
        printf("%s\n", sorrec->firstKid->lexeme);
        entry * record = get(st, sorrec->firstKid->lexeme, scope);
        if (record == NULL){
             printf("Variable %s not in current scope %s, checking global\n", sorrec->firstKid->lexeme, scope);
             record = get(st, sorrec->firstKid->lexeme, "global");
             if (record == NULL){
                printf("Error: Record Variable %s not even declared globally\n", sorrec->firstKid->lexeme);
             }
             else {
                // record declaration found, we go through linkedlsit to find type
                record = get(st, record->type, "global");
                record_dec * rec = record-> record;
                while(strcmp(rec!= NULL &&  rec->name, sorrec->firstKid->siblings->firstKid->lexeme) != 0){
                    rec = rec->next;
                }
                if(rec != NULL){
                    strcpy(type, rec->type);
                }
                else {
                    printf("Error: Record %s has no field %s\n", record->key, sorrec->firstKid->siblings->firstKid->lexeme);
                }
             }
        }
        else {
            printf("%s\t%s\n", "CHAIN OF FOOLS", record->type);
            record = get(st, record->type, "global");
            record_dec * rec = record-> record;
            while(rec!= NULL && strcmp(rec->name, sorrec->firstKid->siblings->firstKid->lexeme) != 0){
                printf("%s\n", rec->name);
                rec = rec->next;
            }
            if(rec != NULL){
                printf("%s\n", rec->name);
                strcpy(type, rec->type);
            }
            else
                printf("Error: Record %s has no field %s\n", record->key, sorrec->firstKid->siblings->firstKid->lexeme);
        }

    }

    printf("%s\n", type);

    parseTree arithmeticex = sorrec->siblings;
    if (arithmeticex == NULL){
        printf("%s\n", "Wrong assignment statement here");
    }
    else {
        check_arith(arithmeticex, st, scope, type);
    }
    printf("%s\n", "next");

}

void check_iterative_stmt(parseTree curr, hashtable *st, char* scope)
{
    curr = curr->firstKid;

    while (curr != NULL)
    {
        // boolean expression
        if (curr->id == 141)
        {
            // TODO check what variabes have been declared and everything here
            handle_boolean_exp(curr->firstKid, st, scope);
        }
        else if (curr->id == 120)
        {
            // call handle_oth_stmts here
            handle_oth_stmts(curr->firstKid, st, scope);
        }

        curr = curr->siblings;
    }
}

void check_stmt(parseTree curr, hashtable *st, int type, char* scope)
{   if (type == 1) // iterative statement
        check_assignment_stmt(curr, st, scope);
    if (type == 3) // iterative statement
        check_conditional_stmt(curr, st, scope);
    if (type == 2)
        check_iterative_stmt(curr, st, scope);
}

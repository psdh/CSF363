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

/*
    Handles typechecking of multiple type of statments. Also takes care of several
    semantic rules. The check_stmt function is invoked by semantic.c for semantic
    analysis.
*/

// Handles boolean expressions
void handle_boolean_exp(parseTree stmt, hashtable *ht, char* scope, list_var **head)
{
    char *to_check_here;
    to_check_here = (char*) malloc(20*sizeof(char));


    traverse_all_boolean(stmt, ht, scope, to_check_here, head);
}

// Adds idList to a linked list called list_var
// Used to keep track of variables changing in itterations
void add_to_list_var(list_var **head, char* name)
{
    if (head != NULL)
    {
        list_var *it = *head;
        list_var *prev = NULL;

        while(it != NULL)
        {
            // found variable already
            if (strcmp(it->name, name) == 0)
                return;

            prev = it;
            it = it->next;
        }
        if (prev == NULL)
        {
            list_var * new = (list_var *) malloc(sizeof(list_var));
            new->next = NULL;
            new->name = (char*) malloc(20*sizeof(char));
            strcpy(new->name, name);
            *head = new;
        }
        else
        {
            list_var * new = (list_var *) malloc(sizeof(list_var));
            new->next = NULL;
            new->name = (char*) malloc(20*sizeof(char));
            strcpy(new->name, name);
            prev->next = new;
        }
    }
    else
    {
        list_var * new = (list_var *) malloc(sizeof(list_var));
        new->next = NULL;
        new->name = (char*) malloc(20*sizeof(char));
        strcpy(new->name, name);
        *head = new;
    }
}

// Traverses all boolean expressions.
void traverse_all_boolean(parseTree curr, hashtable *ht, char *scope, char *check, list_var **head)
{
    if (curr == NULL)
        return;


    if(curr->firstKid != NULL)
    {
        traverse_all_boolean(curr->firstKid, ht, scope, check, head);
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
                {   // made change here changed tk_num to int in strcmp(chec, "int") talk to sodhi @Todo
                    if (!(strcmp(found->type, "int") == 0 && strcmp(check, "int") == 0) && !(strcmp(found->type, "real") == 0 && strcmp(check, "real") == 0))
                    {
                        printf("Error: Variable <%s> is not of expected type: <%s> at line <%d>\n", curr->lexeme, check, curr->lineNo);
                        symbolerror = 1;
                    }
                    else
                    {
                        add_to_list_var(head, curr->lexeme);
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
                    add_to_list_var(head, curr->lexeme);
                }
            }
            else
            {

                printf("Error: <%s> not declared in scope: <%s> or in global scope at line <%d>\n", curr->lexeme, scope, curr->lineNo);
                symbolerror = 1;
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
                    printf("Error! type <%s> expected got <%s> at line no: <%d>\n", check, getCorrespondingToken(curr->id), curr->lineNo);
                    symbolerror = 1;
                }
        }
    }

    parseTree prev = curr;
    curr = curr->siblings;

    if(curr != NULL)
    {
        return traverse_all_boolean(curr, ht, scope, check, head);
    }
}

// Traverses all write statements
// Also used for read statements.
void traverse_all_write(parseTree curr, hashtable *ht, char *scope)
{
    if (curr == NULL)
        return;

    if(curr->firstKid != NULL)
    {
        traverse_all(curr->firstKid, ht, scope);
       // do  you thing again!
    }
    else
    {
        // TK_ID detected
        if (curr->id == 4)
        {
            entry *found = get(ht, curr->lexeme, scope);

            if (found == NULL)
                found = get(ht, curr->lexeme, "global");

            if (found == NULL)
            {
                printf("Error: Variable: <%s> undeclared in <%s> or global scope at line <%d>\n", curr->lexeme, scope, curr->lineNo);
                symbolerror = 1;
                return;
            }


            // record type
            if (found->isRecordInstance == 1)
            {
                if (curr->siblings->firstKid == NULL)
                {	// @Change not an error any more.
                    // printf("Error: Cannot print a record, must specify member at line <%d>\n", found->lineNo);
                    // symbolerror = 1;
                    // return;
                }
                else
                {
                    char *field = curr->siblings->firstKid->lexeme;

                    // to get the members for a record
                    found = get(ht, found->type, "global");

                    record_dec *starter = found->record;

                    int flag = 0;

                    while (starter != NULL)
                    {
                        if (strcmp(starter->name, field) == 0)
                        {
                            flag = 1;
                            // printf("sab equal hai\n");
                            break;
                        }
                        starter = starter->next;
                    }
                    if (flag == 0)
                    {
                        printf("Error: There is no field <%s> in record type <%s> at line <%d>\n", field, found->key, found->lineNo);
                        symbolerror = 1;
                        return;
                    }
                }
            }

            return;
        }
    }

    parseTree prev = curr;
    curr = curr->siblings;

    if(curr != NULL)
    {
        return traverse_all(curr->firstKid, ht, scope);
    }
}

// Tells if a certain value exists in a linked list.
int var_in_list_var(list_var **head, char* name)
{
    if (head == NULL || *head == NULL)
    {
        printf("HEAD NULL SUPER ERROR :(\n");
        return 0;
    }

    list_var *iter;
    iter = *head;

    while(iter != NULL)
    {
        if (strcmp(iter->name, name) == 0)
            return 1;

        iter = iter->next;
    }

    return 0;
}

// Checks if given variable is changed
int check_var_changed(parseTree curr, list_var **head)
{
    parseTree iter = curr;

    while(iter != NULL)
    {
        if (iter->firstKid->id == 123) // check for assignment statements
        {
            parseTree tk_id = iter->firstKid->firstKid;

            // boolean expressions don't allow record type stuff
            if (tk_id->siblings->firstKid == NULL)
            {
                if (var_in_list_var(head, tk_id->lexeme) == 1)
                    return 1;
            }
        }
        iter = iter->siblings;
    }
    return 0;
}


// things to check here
// 1) expression in if statment is boolean, Done => by the parser
// 2) call handle_stmts recursively on this, for otherstmts, Done
// Semantic and Type Checking of conditional statements
void check_conditional_stmt(parseTree curr, hashtable *st, char* scope)
{
    curr = curr->firstKid;

    list_var **head;
    list_var *lis =  NULL;
    head = &lis;

    while (curr != NULL)
    {
        // boolean expression
        if (curr->id == 141)
        {
            handle_boolean_exp(curr->firstKid, st, scope, head);
        }
        else if (curr->id == 120)
        {

            handle_oth_stmts(curr->firstKid, st, scope);
        }

        if (curr->id == 129)
            curr = curr->firstKid;
        else
            curr = curr->siblings;
    }
}

// Finds out if a record is dividable or multiplicable
// A record with all same types is both divisable and multiplicable
// Records containing all ints can only be divided by integer
// Records containing all real can only be divided by real
int recordIsDivMulable(hashtable *st, char * record, char * inpType){
    entry *temp = get(st, record, "global");
    record_dec * rec = temp->record;
    char * type = (char*) malloc(sizeof(char)*30);
    int first = 1;
    while(rec != NULL)
    {   if (first){
            first = 0;
            strcpy(type, rec->type);
        }
        else if(strcmp(type, rec->type) != 0){
            return 1;
        }
        rec = rec->next;
    }
    if (strcmp(inpType, type) == 0)
        return 1;
    else
        return 0;
}


// Type checking of factor
void check_factor(parseTree factor, hashtable *st, char *scope, char *type){
    parseTree all = factor->firstKid;
    int highPrec = 0;

    if(factor->siblings != NULL && factor->siblings->id == 137){
        highPrec =  1;
    }

    if(all->id == 5){
        if(strcmp(type, "int") != 0){
            printf("Error: <%s> expected got <%s> at line <%d>\n", "int", type, all->lineNo);
            symbolerror = 1;
        }
    }
    // a wild 5.55 was encountered but type expected was different
    else if(all->id == 6){
        if(strcmp(type, "real") != 0){
            printf("Error: <%s> expected got <%s> at line <%d>\n", "real", type, all->lineNo);
            symbolerror = 1;
        }
    }
    else {
        parseTree temp = all->siblings;
        // Normal variable (not record)
        if(temp == NULL || temp->firstKid == NULL){
            entry *var = get(st, all->lexeme, scope);
            if (var == NULL){
                var = get(st, all->lexeme, "global");
                // doesnt exist globally
                if (var == NULL){
                    printf("Error: Variable <%s> not even declared globally at line <%d>\n", all->lexeme, all->lineNo);
                    symbolerror = 1;
                }
                // exists globally
                else {
                    if(strcmp(type, "int") != 0 && strcmp(type, "real") != 0){
                        if( strcmp("int", var->type) == 0 || strcmp("real", var->type) == 0){
                            if (recordIsDivMulable(st, type, var->type) == 1){
                                if( highPrec != 1){
                                    printf("Error: cant add/subtract scalar from record at line <%d>\n", var->lineNo);
                                    symbolerror = 1;
                                }
                            }
                            else {
                                printf("Error: Given record <%s> isnt good for multiplication/divsion with type  <%s> as it has fields of different types at line <%d>", type, var->type, var->lineNo);
                                symbolerror = 1;
                            }
                        }
                        else if (strcmp(type, var->type) != 0){
                            printf("Error: expected record of type <%s> got of type <%s> at line <%d>\n", type, var->type, var->lineNo);
                            symbolerror = 1;
                        }
                        else if (strcmp(type, var->type) == 0){
                            if(highPrec == 1){
                                printf("Error: Cant divide record at by record at line <%d>\n", var->lineNo);
                                symbolerror = 1;
                            }
                        }
                    }
                    else if(strcmp(type, var->type) != 0){
                        printf("Error: <%s> expected got <%s> in <%s> at line <%d>\n", type, var->type, all->lexeme, var->lineNo);
                        symbolerror = 1;
                    }
                }
            }
            else {

                if(strcmp(type, "int") != 0 && strcmp(type, "real") != 0){
                    if( strcmp("int", var->type) == 0 || strcmp("real", var->type) == 0){
                        if (recordIsDivMulable(st, type, var->type) == 1){
                            if( highPrec != 1){
                                printf("Error: cant add/subtract scalar from record at line <%d>\n", var->lineNo);
                                symbolerror = 1;
                            }
                        }
                        else {
                            printf("Error: Given record <%s> isnt good for arithmetic with type  <%s> as it has fields of different types at line <%d>\n", type, var->type, var->lineNo);
                            symbolerror = 1;
                        }
                    }
                    else if (strcmp(type, var->type) != 0){
                        printf("Error: expected record of type <%s> got of type <%s> at line <%d>\n", type, var->type, var->lineNo);
                        symbolerror = 1;
                    }
                    else if (strcmp(type, var->type) == 0){
                        if(highPrec == 1){
                            printf("Error: Cant divide record by record at line <%d>\n", var->lineNo);
                            symbolerror = 1;
                        }
                    }
                }
                else if(strcmp(type, var->type) != 0){
                    printf("Error: <%s> expected got <%s> in <%s> at line <%d>\n", type, var->type, all->lexeme, var->lineNo);
                    symbolerror = 1;
                }

            }
        }
        else {

            entry * record = get(st, all->lexeme, scope);
            if (record == NULL){
                 record = get(st, all->lexeme, "global");
                 if (record == NULL){
                    printf("Error: Record Variable <%s> not even declared globally at line <%d>\n", all->firstKid->lexeme, all->lineNo);
                    symbolerror = 1;
                 }
                 else {
                    // record declaration found, we go through linkedlsit to find type
                    record = get(st, record->type, "global");
                    record_dec * rec = record-> record;
                    while(rec!= NULL && strcmp(rec->name, temp->firstKid->lexeme) != 0){
                        rec = rec->next;
                    }
                    if(rec == NULL){
                        printf("Error: Record <%s> has no field <%s> at line <%d>\n",record->key, temp->firstKid->lexeme, record->lineNo);
                        symbolerror = 1;
                    }
                    else if (strcmp(rec->type, type)){
                        printf("Error: <%s> expected got <%s> in <%s.%s> at line <%d>\n", type, rec->type, all->firstKid->lexeme,rec->name, record->lineNo);
                        symbolerror = 1;
                    }
                 }
            }
            else {
                record = get(st, record->type, "global");
                record_dec * rec = record-> record;
                while(rec!= NULL && strcmp(rec->name, temp->firstKid->lexeme) != 0){
                    rec = rec->next;
                }
                if(rec == NULL){
                    printf("Error: Record <%s> has no field <%s> at line <%d>\n",record->key, temp->firstKid->lexeme, temp->firstKid->lineNo);
                    symbolerror = 1;
                }
                else if (strcmp(rec->type, type)){
                    printf("Error: <%s> expected got <%s> in <%s.%s> at line <%d>\n", type, rec->type, all->lexeme,rec->name, temp->firstKid->lineNo);
                    symbolerror = 1;
                }
            }

        }
    }
}

// Checks termPrime part of arithmetic expression
void check_termprime(parseTree termprime, hashtable *st, char*scope, char* type){
    parseTree hpo = termprime->firstKid;
    parseTree factor = hpo->siblings;
    parseTree tpp = factor->siblings;

    if (factor->firstKid->id == 132){
        check_arith(factor->firstKid, st, scope, type);
    }
    else {
        check_factor(factor, st, scope, type);
    }

    if(tpp != NULL && tpp->firstKid!=NULL){
        check_termprime(tpp, st, scope, type);
    }
}

// Checks expprime part of arithmetic expression
void check_expprime(parseTree expprime, hashtable *st, char * scope, char * type){
    parseTree term = expprime->firstKid->siblings;
    parseTree expp = term->siblings;

    if(expp->firstKid!=NULL)
        check_expprime(expp, st, scope, type);

    parseTree factor = term->firstKid;
    parseTree termprime = factor->siblings;


    if (factor->firstKid->id == 132){
        check_arith(factor->firstKid, st, scope, type);
    }
    else {
        check_factor(factor, st, scope, type);
    }

    if(termprime!= NULL && termprime->firstKid != NULL){
        check_termprime(termprime, st, scope, type);
    }


}


void check_arith(parseTree expr, hashtable *st, char * scope, char * type){

    parseTree  term = expr->firstKid;
    parseTree expprime = term->siblings;
    parseTree factor = term->firstKid;
    parseTree termprime = factor->siblings;
    if (factor->firstKid->id == 132){
        check_arith(factor->firstKid, st, scope, type);
    }
    else {
        check_factor(factor, st, scope, type);
    }

    if(termprime!= NULL && termprime->firstKid != NULL){
        check_termprime(termprime, st, scope, type);
    }


    if(expprime != NULL && expprime->firstKid != NULL){
        check_expprime(expprime, st, scope, type);
    }

}


void check_assignment_stmt(parseTree curr, hashtable *st, char* scope){

    parseTree sorrec = curr->firstKid;

    char *type = (char*)  malloc(sizeof(char)*20);

    // non record variable
    if(sorrec->firstKid->siblings->firstKid == NULL){
        entry * var = get(st, sorrec->firstKid->lexeme, scope);
        // not in current scope maybe declared globally
        if(var == NULL){
            entry * var = get(st, sorrec->firstKid->lexeme, "global");
            if(var == NULL){
                printf("Error: variable <%s> is not declared at line <%d>\n", sorrec->firstKid->lexeme, sorrec->firstKid->lineNo);
                symbolerror = 1;
                return;
            }
            else{
                strcpy(type, var->type);
                var->assigned = 1;
            }
        }
        else {
            strcpy(type, var->type);
            var->assigned = 1;
        }
    }
    else {
        entry * record = get(st, sorrec->firstKid->lexeme, scope);
        entry * var = get(st, sorrec->firstKid->lexeme, scope);
        if (record == NULL){
             record = get(st, sorrec->firstKid->lexeme, "global");
             var = get(st, sorrec->firstKid->lexeme, "global");


             if (record == NULL){
                printf("Error: Record Variable <%s> not even declared globally at line <%d>\n", sorrec->firstKid->lexeme, sorrec->firstKid->lineNo);
                symbolerror = 1;
             }
             else {
                // record declaration found, we go through linkedlsit to find type
                record = get(st, record->type, "global");
                record_dec * rec = record-> record;

                while(rec!= NULL && strcmp(rec->name, sorrec->firstKid->siblings->firstKid->lexeme) != 0){
                    rec = rec->next;
                }
                if(rec != NULL){
                    strcpy(type, rec->type);
                    var->assigned = 1;
                }
                else {
                    printf("Error: Record <%s> has no field <%s> at line <%d>\n", record->key, sorrec->firstKid->siblings->firstKid->lexeme, sorrec->firstKid->siblings->firstKid->lineNo);
                    symbolerror =  1;
                }
             }
        }
        else {
            record = get(st, record->type, "global");
            record_dec * rec = record-> record;
            while(rec!= NULL && strcmp(rec->name, sorrec->firstKid->siblings->firstKid->lexeme) != 0){
                rec = rec->next;
            }
            if(rec != NULL){
                strcpy(type, rec->type);
                var->assigned = 1;
            }
            else{
                printf("Error: Record <%s> has no field <%s> at line <%d>\n", record->key, sorrec->firstKid->siblings->firstKid->lexeme, sorrec->firstKid->siblings->firstKid->lineNo);
                symbolerror = 1;
            }

        }

    }


    parseTree arithmeticex = sorrec->siblings;
    if (arithmeticex == NULL){
        ;
    }
    else {
        check_arith(arithmeticex, st, scope, type);
    }

}

// Checks iterative statements for type expressions
void check_iterative_stmt(parseTree curr, hashtable *st, char* scope)
{
    curr = curr->firstKid;

    list_var **head;
    list_var *lis =  NULL;
    head = &lis;

    while (curr != NULL)
    {
        // boolean expression
        if (curr->id == 141)
        {
            handle_boolean_exp(curr->firstKid, st, scope, head);
        }
        else if (curr->id == 120)
        {
            // by this time, list_var would have been populated!
            int any_var_changed = check_var_changed(curr->firstKid, head);
            if (any_var_changed == 0)
            {
                printf("Error: None of variables involved in the iterations are redefined\n");
                symbolerror = 1;
            }

            // call handle_oth_stmts here
            handle_oth_stmts(curr->firstKid, st, scope);
        }

        curr = curr->siblings;
    }
}

void check_io_stmt(parseTree curr, hashtable *st, char* scope)
{
    // read statement
    if (curr->firstKid->id == 35)
    {
        parseTree sor = curr->firstKid->siblings->firstKid;
        entry *temp = get(st, sor->lexeme, scope);
        if(temp != NULL){
            temp->assigned = 1;
        }

        parseTree srid = curr->firstKid->siblings->firstKid;
        traverse_all_write(srid, st, scope);
    }
    else
    {
        traverse_all_write(curr->firstKid->siblings->firstKid, st, scope);
    }
}

// check id list for matches
void check_idlist(hashtable *st, parseTree idList, char * funid, int io, char * scope){
    if (io == 0)
    {
        int i = 0;
        int line;
        while(idList!=NULL && idList->firstKid != NULL){
            entry * temp = getOutputParameter(st, funid, i);
            if(temp  == NULL){
                printf("Error: Function <%s> has only <%d> valid output parameters\n", funid, i + 1);
                symbolerror = 1;
            }
            else {
                entry * var = get(st, idList->firstKid->lexeme, scope);
                line = idList->firstKid->lineNo;

                if(var == NULL){
                    var = get(st, idList->firstKid->lexeme, "global");
                }

                if(var == NULL){
                    printf("Error: variable <%s> undeclared at line <%d>\n", idList->firstKid->lexeme, idList->firstKid->lineNo);
                    symbolerror = 1;
                }
                else{
                    var->assigned = 1;
                    if(strcmp(temp->type, var->type)!=0){
                        printf("Error: output paramter <%d> types <%s> and <%s> dont match at line <%d>\n", i, temp->type, var->type, line);
                        symbolerror = 1;
                    }
                }
            }
            i++;
            idList = idList->firstKid->siblings->firstKid;
        }
        entry * temp = getOutputParameter(st, funid, i);
        if(temp!=NULL){
            printf("Error: The number of output parameters for function <%s> at line <%d> is incorrect", funid, lineNo);
            symbolerror = 1;
        }
    }
    else{
        int i = 0;
        int line;
        while(idList!=NULL && idList->firstKid != NULL){
            entry * temp = getInputParameter(st, funid, i);
            if(temp  == NULL){
                printf("Error: Function <%s> has only <%d> valid input parameters\n", funid, i + 1);
                symbolerror = 1;
            }
            else {
                entry * var = get(st, idList->firstKid->lexeme, scope);
                line = idList->firstKid->lineNo;

                if(var == NULL){
                    var = get(st, idList->firstKid->lexeme, "global");
                }

                if(var == NULL){
                    printf("Error: variable <%s> undeclared at line <%d>\n", idList->firstKid->lexeme, idList->firstKid->lineNo);
                    symbolerror = 1;
                }
                else{
                    if(strcmp(temp->type, var->type)!=0){
                        printf("Error: input paramter <%d> types <%s> and <%s> dont match at line <%d>\n", i, var->type, temp->type, idList->firstKid->lineNo);
                        symbolerror = 1;
                    }
                }
            }
            i++;
            idList = idList->firstKid->siblings->firstKid;

        }
        entry * temp = getInputParameter(st, funid, i);
        if(temp!=NULL){
            printf("Error: The number of input parameters for function <%s> at line <%d> is incorrect\n", funid, line);
            symbolerror = 1;
        }

    }
}

// checks functional semantic errors
void check_fun(parseTree funcall, hashtable *st, char * scope){
    parseTree outputparameters = funcall->firstKid;
    parseTree funid = outputparameters->siblings;
    parseTree inputParameters = funid->siblings;

    if(strcmp(funid->lexeme, scope) == 0){
        printf("Error: function <%s> being recursively called at line <%d>\n", scope, funid->lineNo);
        symbolerror = 1;
        return;
    }

    entry * function = get(st, funid->lexeme, "global");
    entry * current = get(st, scope, "global");

    // undeclared function or function declared after current function
    if (function == NULL || function->lineNo > current->lineNo){
        printf("Error: Undefined function <%s> being called at line <%d>\n", funid->lexeme, funid->lineNo);
        symbolerror = 1;
        return;
    }

    // no return parameters
    if (outputparameters ==  NULL || outputparameters->firstKid == NULL){
        entry *temp = getOutputParameter(st, funid->lexeme, 0);
        if(temp != NULL){
            symbolerror = 1;
            printf("Error: Function has return items but there is no return associated with this function <%s>\n", funid->lexeme);
        }
    }
    else {
        parseTree idList = outputparameters->firstKid;
        check_idlist(st, idList, funid->lexeme, 0, scope);
    }
    parseTree inputParametersList = inputParameters->firstKid;
    check_idlist(st, inputParametersList, funid->lexeme, 1, scope);

}

// checks return stmt
void check_return(parseTree curr, hashtable *st, char *scope){
    if(curr!=NULL && curr->firstKid !=NULL){
        parseTree idList = curr->firstKid;
        check_idlist(st, idList, scope, 0, scope);
    }
}

// invoked by semantic.c
void check_stmt(parseTree curr, hashtable *st, int type, char* scope)
{
    if (type == 1) // assignment statement
        check_assignment_stmt(curr, st, scope);
    else if (type == 3) // conditional statement
        check_conditional_stmt(curr, st, scope);
    else if (type == 2) // iterative statment
        check_iterative_stmt(curr, st, scope);
    else if (type == 10) // IO statement
        check_io_stmt(curr, st, scope);
    else if (type == 4)
        check_fun(curr, st, scope);
    else if(type ==5)
        check_return(curr, st, scope);

}

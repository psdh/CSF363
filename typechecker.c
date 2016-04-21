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


void handle_boolean_exp(parseTree stmt, hashtable *ht, char* scope, list_var **head)
{
    char *to_check_here;
    to_check_here = (char*) malloc(20*sizeof(char));


    traverse_all_boolean(stmt, ht, scope, to_check_here, head);
}

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
                        printf("Variable<%s> is not of expected type: <%s>\n", curr->lexeme, check);
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
        return traverse_all_boolean(curr, ht, scope, check, head);
    }
}

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
                printf("Error: Variable: %s undeclared in %s or global scope\n", curr->lexeme, scope);
                return;
            }


            // record type
            if (found->isRecordInstance == 1)
            {
                if (curr->siblings->firstKid == NULL)
                {
                    printf("Error: Cannot write to a record, must specify member\n");
                    return;
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
                            printf("sab equal hai\n");
                            break;
                        }
                        starter = starter->next;
                    }
                    if (flag == 0)
                    {
                        printf("Error: There is no field <%s> in record type <%s>", field, found->key);
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


            // call handle_oth_stmts here
            handle_oth_stmts(curr->firstKid, st, scope);
        }

        if (curr->id == 129)
            curr = curr->firstKid;
        else
            curr = curr->siblings;
    }
}

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


void check_factor(parseTree factor, hashtable *st, char *scope, char *type){
    // a wild 5 was encountered but type expcted was different
    // @ToDo take care of variable
    parseTree all = factor->firstKid;
    int highPrec = 0;

    if(factor->siblings != NULL && factor->siblings->id == 137){
        highPrec =  1;
    }

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
        parseTree temp = all->siblings;
        // Normal variable (not record)
        // @ToDo Scalar natak
        if(temp == NULL || temp->firstKid == NULL){
            // records are dvisible by scalar :(
            entry *var = get(st, all->lexeme, scope);
            if (var == NULL){
                printf("Error: Variable %s not in current scope %s, checking global\n", all->lexeme, scope);
                var = get(st, all->firstKid->lexeme, "global");
                // doesnt exist globally
                if (var == NULL){
                    printf("Error: Variable %s not even declared globally\n", all->lexeme);
                }
                // exists globally
                else {
                    // ek record hai lhs mein and rhs mein you can have variable or record
                    if(strcmp(type, "int") != 0 && strcmp(type, "real") != 0){
                        //rhs mein variable, operator should be divide or something
                        if( strcmp("int", var->type) == 0 || strcmp("real", var->type) == 0){
                            if (recordIsDivMulable(st, type, var->type) == 1){
                                if( highPrec != 1){
                                    printf("Error: cant add/subtract scalar from record\n");
                                }
                            }
                            else {
                                printf("Error: Given record %s isnt good for arithmetic with type  %s as it has fields of different types", type, var->type);
                            }
                        }
                        // rhs mein record hai
                        else if (strcmp(type, var->type) != 0){
                            printf("Error: expected record of type %s got of type %s\n", type, var->type);
                        }
                        else if (strcmp(type, var->type) == 0){
                            if(highPrec == 1){
                                printf("Error: Cant divide record by record\n");
                            }
                        }
                    }
                    else if(strcmp(type, var->type) != 0){
                        printf("Error: %s expected got %s in %s\n", type, var->type, all->lexeme);
                    }
                }
            }
            // exists in scope
            else {

                if(strcmp(type, "int") != 0 && strcmp(type, "real") != 0){
                    //rhs mein variable, operator should be divide or something
                    if( strcmp("int", var->type) == 0 || strcmp("real", var->type) == 0){
                        if (recordIsDivMulable(st, type, var->type) == 1){
                            if( highPrec != 1){
                                printf("Error: cant add/subtract scalar from record\n");
                            }
                        }
                        else {
                            printf("Error: Given record %s isnt good for arithmetic with type  %s as it has fields of different types\n", type, var->type);
                        }
                    }
                    // rhs mein record hai
                    else if (strcmp(type, var->type) != 0){
                        printf("Error: expected record of type %s got of type %s\n", type, var->type);
                    }
                    else if (strcmp(type, var->type) == 0){
                        if(highPrec == 1){
                            printf("Error: Cant divide record by record\n");
                        }
                    }
                }
                else if(strcmp(type, var->type) != 0){
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

    if (factor->firstKid->id == 132){
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
        printf("%s\n", "termprime hai exprime mein");
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
    // not another arithmetic expression
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
            // printf("Variable %s not in scope %s, Checking globally\n", sorrec->firstKid->lexeme, scope);
            entry * var = get(st, sorrec->firstKid->lexeme, "global");
            if(var == NULL){
                printf("Error: variable %s is not declared\n", sorrec->firstKid->lexeme);
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
    // bhai ye toh record hai
    else {
        entry * record = get(st, sorrec->firstKid->lexeme, scope);
        entry * var = get(st, sorrec->firstKid->lexeme, scope);
        if (record == NULL){
             // printf("Variable %s not in current scope %s, checking global\n", sorrec->firstKid->lexeme, scope);
             record = get(st, sorrec->firstKid->lexeme, "global");
             var = get(st, sorrec->firstKid->lexeme, "global");
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
                    var->assigned = 1;
                }
                else {
                    printf("Error: Record %s has no field %s\n", record->key, sorrec->firstKid->siblings->firstKid->lexeme);
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
            else
                printf("Error: Record %s has no field %s\n", record->key, sorrec->firstKid->siblings->firstKid->lexeme);
        }

    }


    parseTree arithmeticex = sorrec->siblings;
    if (arithmeticex == NULL){
        printf("%s\n", "Wrong assignment statement here");
    }
    else {
        check_arith(arithmeticex, st, scope, type);
    }

}

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
            // TODO check what variabes have been declared and everything here
            handle_boolean_exp(curr->firstKid, st, scope, head);
        }
        else if (curr->id == 120)
        {
            // by this time, list_var would have been populated!
            int any_var_changed = check_var_changed(curr->firstKid, head);
            if (any_var_changed == 0)
            {
                printf("Error: None of variables involved in the iterations are redefined\n");
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

void check_idlist(hashtable *st, parseTree idList, char * funid, int io, char * scope){
    if (io == 0)
    {
        int i = 0;
        while(idList->firstKid != NULL){
            entry * temp = getOutputParameter(st, funid, i);
            if(temp  == NULL){
                printf("Error: Function %s doesnt have %d output parameters\n", funid, i + 1);
            }
            else {
                entry * var = get(st, idList->firstKid->lexeme, scope);

                if(var == NULL){
                    var = get(st, idList->firstKid->lexeme, "global");
                }

                if(var == NULL){
                    printf("Error: variable %s undeclared at line %d\n", idList->firstKid->lexeme, idList->firstKid->lineNo);
                }
                else{
                    if(strcmp(temp->type, var->type)!=0){
                        printf("Error: output paramter %d types dont match at line %d\n", i, idList->firstKid->lineNo);
                    }
                }
            }
            i++;
            idList = idList->firstKid->siblings;
        }
    }
    else{
        int i = 0;
        while(idList->firstKid != NULL){
            entry * temp = getInputParameter(st, funid, i);
            if(temp  == NULL){
                printf("Error: Function %s doesnt have %d input parameters\n", funid, i + 1);
            }
            else {
                entry * var = get(st, idList->firstKid->lexeme, scope);

                if(var == NULL){
                    var = get(st, idList->firstKid->lexeme, "global");
                }

                if(var == NULL){
                    printf("Error: variable %s undeclared at line %d\n", idList->firstKid->lexeme, idList->firstKid->lineNo);
                }
                else{
                    if(strcmp(temp->type, var->type)!=0){
                        printf("Error: input paramter %d types dont match at line %d\n", i, idList->firstKid->lineNo);
                    }
                }
            }
            i++;
            idList = idList->firstKid->siblings;
        }



    }
}


void check_fun(parseTree funcall, hashtable *st, char * scope){
    parseTree outputparameters = funcall->firstKid;
    parseTree funid = outputparameters->siblings;
    parseTree inputParameters = funid->siblings;

    if(strcmp(funid->lexeme, scope) == 0){
        printf("Error: function %s being recursively called at line %d\n", scope, funid->lineNo);
        return;
    }

    entry * function = get(st, funid->lexeme, "global");
    entry * current = get(st, scope, "global");

    // undeclared function or function declared after current function
    if (function == NULL || function->lineNo > current->lineNo){
        printf("Error: Undefined function %s being called at line %d\n", funid->lexeme, funid->lineNo);
        return;
    }

    // no return parameters --> 6th rule I guess
    if (outputparameters ==  NULL || outputparameters->firstKid == NULL){
        entry *temp = getOutputParameter(st, funid->lexeme, 0);
        if(temp != NULL){
            printf("Error: Function has return items but there is no return associated with this function %s\n", funid->lexeme);
        }
    }
    // parameters hain check marte hain
    else {
        parseTree idList = outputparameters->firstKid;
        check_idlist(st, idList, funid->lexeme, 0, scope);
    }
    parseTree inputParametersList = inputParameters->firstKid;
    check_idlist(st, inputParametersList, funid->lexeme, 1, scope);

}

void check_return(parseTree curr, hashtable *st, char *scope){
    if(curr->firstKid !=NULL){
        parseTree idList = curr->firstKid;
        check_idlist(st, idList, scope, 0, scope);
    }
}

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
        check_return(curr, st, scope)

}

/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:symboltable.c
*/


#ifndef __USE_XOPEN2K8
    #define __USE_XOPEN2K8 1
#endif

#include "symboltable.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

hashtable *create(int size){

	hashtable * ht = NULL;

	if (size < 1 ) return NULL;

	ht = malloc(sizeof (hashtable));

	ht->table = malloc(sizeof(entry*)*size);

	for (int i=0; i< size; i++){
		ht->table[i] = NULL;
	}

	return ht;
}

int hash(hashtable ht, char *key){

	unsigned long int hashval = 6669;
	int i = 0;

	while(hashval < ULONG_MAX && i < strlen(key)){
		hashval  =  key[i] + 71 * hashval;
	}

	return hashval % ht->size;

}

entry *newentry( char *key, char *type, char * scope, int offset, int lineNo, int id, int isInputParameter, int isOutputParameter, int ParameterNumber){
	entry * new;

	new = malloc(sizeof(entry));
	new->key = strdup(key);
	new->type = strdup(type);
	new->scope = strdup(scope);
	new->lineNo = lineNo;
	new->id = getColumnIndex(type);

	if (isInputParameter == 1){
		scope->isInputParameter = 1;
	}
	else{
		scope->isInputParameter = -1;
	}

	if (isOutputParameter == 1){
		scope->isOutputParameter = 1;
	}
	else{
		scope->isOutputParameter = -1;
	}


	if(strcmp(type,'int') == 0 || strcmp(type, 'real') == 0){
		new->width = 4;
		new->offset  = offset + new->width;
	}

	if(strcmp(type, 'record')){
		new->isRecordDeclaration = 1;
		new->record = malloc(sizeof(record_dec));
	}
	else{
		new->isRecordDeclaration = 0;
	}

	if( type[0] == '#'){
		new->isRecordInstance = 1;
		temp * entry = get(ht, type, 'global');
		new->offset = offset + temp->width;
		new->width = temp->width;
	}
	else{
		new->isRecordInstance = 0;
	}

	return entry;
}

void upsert(hashtable *ht, char *key, char *type, char * scope, int offset, int lineNo, int id, int isInputParameter, int isOutputParameter, int ParameterNumber){
	int bin = 0;
	entry *newpair = NULL;
	entry *next = NULL;
	entry *last = NULL;

	bin = hash( ht, key );

	next = ht->table[ bin ];

	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 || strcmp(scope, next->scope) > 0 ) {
		last = next;
		next = next->next;
	}

	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 && strcmp(scope, next->scope) == 0) {

		free(next->key);
		free(next->type);

		new->key = strdup(key);
		new->type = strdup(type);
		new->lineNo = lineNo;
		new->id = getColumnIndex(type);

		if (isInputParameter == 1){
			scope->isInputParameter = 1;
		}
		else{
			scope->isInputParameter = -1;
		}

		if (isOutputParameter == 1){
			scope->isOutputParameter = 1;
		}
		else{
			scope->isOutputParameter = -1;
		}

		scope->ParameterNumber = ParameterNumber;

		if(strcmp(type,'int') == 0 || strcmp(type, 'real') == 0){
			new->width = 4;
			new->offset  = offset + new->width;
		}

		if(strcmp(type, 'record')){
			new->isRecordDeclaration = 1;
			new->record = malloc(sizeof(record_dec));
		}
		else{
			new->isRecordDeclaration = 0;
		}

		if( type[0] == '#'){
			new->isRecordInstance = 1;
			temp * entry = get(ht, type, 'global');
			new->offset = offset + temp->width;
			new->width = temp->width;
		}
		else{
			new->isRecordInstance = 0;
		}

	} else {
		newpair = newentry(key, type, scope, offset, lineNo, id, isInputParameter, isOutputParameter, ParameterNumber);

		if( next == ht->table[ bin ] ) {
			newpair->next = next;
			ht->table[ bin ] = newpair;

		} else if ( next == NULL ) {
			last->next = newpair;

		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

entry *get( hashtable *ht, char *key, char*scope ) {
	int bin = 0;
	entry *temp;

	bin = hash( ht, key );

	temp = ht->table[ bin ];
	while( temp != NULL && temp->key != NULL && (strcmp( key, temp->key ) > 0  || strcmp(scope, temp->scope) > 0)) {
		temp = temp->next;
	}

	if( temp == NULL || temp->key == NULL || (strcmp( key, temp->key ) != 0  || strcmp(scope, temp->scope) !=0)) {
		return NULL;

	} else {
		return temp;
	}

}

entry *getInputParameter(hashtable *ht, char *key ,char *scope, int ParameterNumber){

	int bin = 0;
	entry *temp;

	bin = hash(ht, key);

	temp = ht->table[bin];

	while (temp != NULL && temp->key !=NULL && (strcmp(key, temp->key) > 0 || strcmp(scope, temp->scope) || scope->isInputParameter != 1 || scope->ParameterNumber != ParameterNumber ) ){
		temp= temp->next;
	}

	if( temp == NULL || temp->key == NULL || (strcmp( key, temp->key ) != 0  || strcmp(scope, temp->scope) !=0 || scope->isInputParameter != 1 || scope->ParameterNumber != ParameterNumber ) ) {
		return NULL;

	} else {
		return temp;
	}

}

entry *getOutputParameter(hashtable *ht, char *key ,char *scope, int ParameterNumber){

	int bin = 0;
	entry *temp;

	bin = hash(ht, key);

	temp = ht->table[bin];

	while (temp != NULL && temp->key !=NULL && (strcmp(key, temp->key) > 0 || strcmp(scope, temp->scope) || scope->isOutputParameter != 1 || scope->ParameterNumber != ParameterNumber ) ){
		temp= temp->next;
	}

	if( temp == NULL || temp->key == NULL || (strcmp( key, temp->key ) != 0  || strcmp(scope, temp->scope) !=0 || scope->isOutputParameter != 1 || scope->ParameterNumber != ParameterNumber ) ) {
		return NULL;

	} else {
		return temp;
	}

}



void popuplateHashTable(parseTree curr, hashtable ht, char * scope){


	if (curr-> id == 7){
		strcpy(scope, cur->lexeme);
	}

    if (curr == NULL)
        return;

    if(curr->firstKid != NULL)
    {
        printParseTree_r(curr->firstKid, f);
        char* value = (char*) malloc(sizeof(char)*20);
        strcpy(value, "");


    }
    else
    {
        char* value = (char*) malloc(sizeof(char)*20);
        strcpy(value, "");
        if (curr->id == 5 || curr->id == 6)
            strcpy(value, curr->lexeme);

        fprintf(f, "\n %20s %15d %15s %15s %20s %15s %15s", curr->lexeme, curr->lineNo,
                getCorrespondingToken(curr->id), value, getCorrespondingToken(curr->parent->id),
                curr->firstKid == NULL?"yes": "no", getCorrespondingToken(curr->id));
    }
    parseTree prev = curr;
    curr = curr->siblings;

    if(curr != NULL)
    {
        return printParseTree_r(curr, f);
    }

}

hashtable createSymbolTable(parseTree PT){
	hashtable ht* = create(100);
	popuplateHashTable(parseTree,ht, 'global');
}

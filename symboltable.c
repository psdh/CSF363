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
	int i;

	if (size < 1 ) return NULL;

	ht = malloc(sizeof (hashtable));

	ht->table = malloc(sizeof(entry*)*size);

	for (i =0; i< size; i++){
		ht->table[i] = NULL;
	}

	return ht;
}

int hash(hashtable *ht, char *key){

	unsigned long int hashval = 6669;
	int i = 0;

	while(hashval < ULONG_MAX && i < strlen(key)){
		hashval  =  key[i] + 71 * hashval;
	}

	return hashval % ht->size;

}

entry *newentry(char *key, char *type, char *scope, int offset, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber){
	entry *new;

	new = malloc(sizeof(entry));
	new->key = strdup(key);
	new->type = strdup(type);
	new->scope = strdup(scope);
	new->lineNo = lineNo;
	// new->id = getColumnIndex(type);

	if (isInputParameter == 1){
		new->isInputParameter = 1;
	}
	else{
		new->isInputParameter = -1;
	}

	if (isOutputParameter == 1){
		new->isOutputParameter = 1;
	}
	else{
		new->isOutputParameter = -1;
	}


	if(strcmp(type,'int') == 0 || strcmp(type, 'real') == 0){
		new->width = 4;
		new->offset  = offset + new->width;
	}

	if(strcmp(type, 'record') == 0)
	{
		new->isRecordDeclaration = 1;
		new->record = malloc(sizeof(record_dec));
	}
	else
	{
		new->isRecordDeclaration = 0;
	}

	if(type[0] == '#'){
		new->isRecordInstance = 1;
	}
	else{
		new->isRecordInstance = 0;
	}

	return new;
}

void upsert(hashtable *ht, char *key, char *type, char * scope, int offset, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber){
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

		next->key = strdup(key);
		next->type = strdup(type);
		next->lineNo = lineNo;
		// next->id = getColumnIndex(type);

		if (isInputParameter == 1){
			next->isInputParameter = 1;
		}
		else{
			next->isInputParameter = -1;
		}

		if (isOutputParameter == 1){
			next->isOutputParameter = 1;
		}
		else{
			next->isOutputParameter = -1;
		}

		next->ParameterNumber = ParameterNumber;

		if(strcmp(type,'int') == 0 || strcmp(type, 'real') == 0){
			next->width = 4;
			next->offset  = offset + next->width;
		}

		if(strcmp(type, 'record')){
			next->isRecordDeclaration = 1;
			next->record = malloc(sizeof(record_dec));
		}
		else{
			next->isRecordDeclaration = 0;
		}

		if( type[0] == '#'){
			next->isRecordInstance = 1;
			entry * temp = get(ht, type, 'global');
			next->offset = offset + temp->width;
			next->width = temp->width;
		}
		else{
			next->isRecordInstance = 0;
		}

	} else {
		newpair = newentry(key, type, scope, offset, lineNo, isInputParameter, isOutputParameter, ParameterNumber);

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

	bin = hash(ht, key);

	temp = ht->table[ bin ];
	while( temp != NULL && temp->key != NULL && (strcmp(key, temp->key) > 0  || strcmp(scope, temp->scope) > 0)) {
		temp = temp->next;
	}

	if( temp == NULL || temp->key == NULL || (strcmp( key, temp->key ) != 0  || strcmp(scope, temp->scope) !=0)) {
		return NULL;

	} else {
		return temp;
	}

}

entry *getInputParameter(hashtable *ht, char *key, char *scope, int ParameterNumber){

	int bin = 0;
	entry *temp;

	bin = hash(ht, key);

	temp = ht->table[bin];

	while (temp != NULL && temp->key !=NULL && (strcmp(key, temp->key) > 0 || strcmp(scope, temp->scope) || temp->isInputParameter != 1 || temp->ParameterNumber != ParameterNumber ) ){
		temp= temp->next;
	}

	if( temp == NULL || temp->key == NULL || (strcmp( key, temp->key ) != 0  || strcmp(scope, temp->scope) !=0 || temp->isInputParameter != 1 || temp->ParameterNumber != ParameterNumber ) ) {
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

	while (temp != NULL && temp->key !=NULL && (strcmp(key, temp->key) > 0 || strcmp(scope, temp->scope) || temp->isOutputParameter != 1 || temp->ParameterNumber != ParameterNumber ) ){
		temp= temp->next;
	}

	if( temp == NULL || temp->key == NULL || (strcmp( key, temp->key ) != 0  || strcmp(scope, temp->scope) !=0 || temp->isOutputParameter != 1 || temp->ParameterNumber != ParameterNumber ) ) {
		return NULL;

	} else {
		return temp;
	}

}


char* getType(parseTree curr)
{
	char ans[20];

	printf("fn gettype %d\n", curr->id);
	if(curr->firstKid->id == 13)
		strcpy(ans, "int");
	else
		if(curr->firstKid->id == 14)
			strcpy(ans, "real");
		else
			if(curr->firstKid->siblings->id == 8)
				strcpy(ans, curr->firstKid->siblings->lexeme);

	return ans;
}


void add_list(parseTree curr, hashtable *ht, char* scope, int input, int output)
{
	printf("%d\n", curr->id);
	int counter = 0;

	while(curr != NULL)
	{

		upsert(ht, curr->siblings->lexeme, getType(curr), scope, 10, curr->siblings->lineNo, input, output, counter);

		curr = curr->siblings->siblings;

		counter++;
	}
}


void add_function(parseTree curr, hashtable *ht)
{
	char scope[200];
	strcpy(scope, curr->lexeme);

	printf("%d\n", curr->id);

	parseTree input = curr->siblings;

	// to bypass parameter list
	add_list(input->firstKid->firstKid, ht, scope, 1, 0);

	parseTree output = input->siblings;

	add_list(output->firstKid->firstKid, ht, scope, 0, 1);

	// add_stmts()
}


void add_main_function(parseTree main, hashtable *ht)
{
	char scope[20] = "_main";

	printf("main's kid's id: %d\n", main->id);
}


void popuplateHashTable(parseTree head, hashtable *ht, char *scope)
{
	printf("Head's id: %d\n", head->id);

	parseTree othfun = head->firstKid->firstKid;

	// to populate the symbol table from info in the all functions
	while(othfun != NULL)
	{
		add_function(othfun->firstKid, ht);
		othfun = othfun->siblings;
	}

	parseTree mf = head->firstKid->siblings;
	add_main_function(mf->firstKid, ht);
}

hashtable createSymbolTable(parseTree pt)
{
	hashtable *ht = create(100);
	char scope[] = "global";
	popuplateHashTable(pt, ht, scope);
}

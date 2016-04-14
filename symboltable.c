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

	unsigned long int hashval;
	int i = 0;

	while(hashval < ULONG_MAX && i < strlen(key)){
		hashval = hashval<<8;
		hashval += key[i];
	}

	return hashval % ht->size;

}

entry *newentry( char *key, char *type, char * scope, int offset, int lineNo, int id, char *value){
	entry * new;

	new = malloc(sizeof(entry));
	new->key = strdup(key);
	new->type = strdup(type);
	new->scope = strdup(scope);
	new->value = strdup(value);
	new->lineNo = lineNo;
	new->id = getColumnIndex(type);

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

void insert(hashtable *ht, char *key, char *type, char * scope, int offset, int lineNo, int id, char *value){
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
		free(next->value);

		new->key = strdup(key);
		new->type = strdup(type);
		new->value = strdup(value);
		new->lineNo = lineNo;
		new->id = getColumnIndex(type);

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
		newpair = newentry(key, type, scope, offset, lineNo, id, value);

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
	while( temp != NULL && temp->key != NULL && (strcmp( key, temp->key ) > 0  || strcmp(scope, temp->key) > 0)) {
		temp = temp->next;
	}

	if( temp == NULL || temp->key == NULL || (strcmp( key, temp->key ) != 0  || strcmp(scope, temp->scope) !=0)) {
		return NULL;

	} else {
		return temp;
	}

}

hashtable createSymbolTable(parseTree PT){
	hashtable ht* = create(100);
}

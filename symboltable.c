/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:symboltable.c
*/


#ifndef __USE_XOPEN2K8
    #define __USE_XOPEN2K8 1
#endif

int offset = 0;

#include "symboltable.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

hashtable *create(int size){

	hashtable *ht = NULL;
	int i;

	if (size < 1 ) return NULL;

	ht = malloc(sizeof (hashtable));

	ht->size = size;

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
		i++;
	}

	return hashval % ht->size;

}

entry *newentry(hashtable * ht, char *key, char *type, char *scope, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber){
	entry *new;

	new = (entry*) malloc(sizeof(entry));
	new->key = strdup(key);
	new->type = strdup(type);
	new->scope = strdup(scope);
	new->lineNo = lineNo;
	// new->id = getColumnIndex(type);

	if (isInputParameter == 1){
		new->isInputParameter = 1;
	}
	else{
		new->isInputParameter = 0;
	}

	if (isOutputParameter == 1){
		new->isOutputParameter = 1;
	}
	else{
		new->isOutputParameter = 0;
	}

	if(strcmp(type,"int") == 0 || strcmp(type, "real") == 0)
	{
		new->width = 4;
		new->offset  = offset + new->width;
		offset = offset + new->width;
	}

	if(strcmp(type, "record") == 0)
	{
		new->isRecordDeclaration = 1;
		new->record = NULL;
	}
	else
	{
		new->isRecordDeclaration = 0;
	}

	if(type[0] == '#'){
		new->isRecordInstance = 1;
		entry * temp = get(ht, type, "global");
		if (temp != NULL){
			new->width = temp->width;
			new->offset = offset + temp->width;
			offset = offset + new->width;
		}
	}
	else{
		new->isRecordInstance = 0;
	}

	return new;
}

void upsert(hashtable *ht, char *key, char *type, char * scope, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber){

	int bin = 0;

	entry *newpair = NULL;
	entry *next = NULL;
	entry *last = NULL;

	bin = hash(ht, key);

	next = ht->table[bin];


	while(next != NULL && (strcmp(key, next->key) > 0 || strcmp(scope, next->scope) > 0 ))
	{
		// printf("%s\n", next->key);
		last = next;
		next = next->next;
	}

	if(next != NULL && next->key != NULL && (strcmp(key, next->key) == 0 && strcmp(scope, next->scope) == 0))
	{

		free(next->key);
		free(next->type);

		next->key = strdup(key);
		next->type = strdup(type);
		next->lineNo = lineNo;

		if (isInputParameter == 1){
			next->isInputParameter = 1;
		}
		else{
			next->isInputParameter = 0;
		}

		if (isOutputParameter == 1){
			next->isOutputParameter = 1;
		}
		else{
			next->isOutputParameter = 0;
		}

		next->ParameterNumber = ParameterNumber;

		if(strcmp(type, "int") == 0 || strcmp(type, "real") == 0){
			next->width = 4;
			next->offset  = offset + next->width;
			offset = offset + next->width;
		}

		if(strcmp(type, "record")){
			next->isRecordDeclaration = 1;
			next->record = NULL;
		}
		else{
			next->isRecordDeclaration = 0;
		}

		if(type[0] == '#'){
			next->isRecordInstance = 1;
			entry * temp = get(ht, type, "global");
			if(temp != NULL){
				next->offset = offset + temp->width;
				next->width = temp->width;
				offset = offset + next->width;
			}
		}
		else{
			next->isRecordInstance = 0;
		}

	}
	else
	{
		newpair = newentry(ht, key, type, scope, lineNo, isInputParameter, isOutputParameter, ParameterNumber);

		if( next == ht->table[bin] ) {
			newpair->next = next;
			ht->table[bin] = newpair;

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


char* getType(hashtable * ht, parseTree curr, char* ans)
{
	if(curr->firstKid->id == 13)
		strcpy(ans, "int");
	else
		if(curr->firstKid->id == 14)
			strcpy(ans, "real");
		else
			if(curr->firstKid->siblings->id == 8){
				entry * temp = get(ht, curr->firstKid->siblings->lexeme, "global");
				if (temp == NULL){
					printf( "\nBro yahan error hai, record %s toh declareich nahi hua\n", curr->firstKid->siblings->lexeme);
					exit(-1);
				}
				else{
					strcpy(ans, curr->firstKid->siblings->lexeme);
				}
			}

	return ans;
}


void add_list(parseTree curr, hashtable *ht, char* scope, int input, int output)
{
	// printf("list case %d\n", curr->id);

	int counter = 0;

	while(curr != NULL)
	{
		char ans[20];

		upsert(ht, curr->siblings->lexeme, getType(ht, curr, ans), scope, curr->siblings->lineNo, input, output, counter);

		curr = curr->siblings->siblings;

		counter++;
	}
}


void add_fielddef(hashtable *ht, parseTree curr, char * scope, record_dec *record){
	char type[20];
	parseTree datatype = curr->firstKid;
	getType(ht, datatype, type);
	char *id = datatype->siblings->lexeme;
	record->type = (char*) malloc(20*sizeof(char));
	strcpy(record->type, type);
	record->name = id;
	record->next = NULL;
}


void add_moreFileds(hashtable *ht, parseTree curr, record_dec *record, char *scope, int * width)
{
	parseTree fieldDef = curr->firstKid;

	if(fieldDef == NULL){
		printf("%s\n", "No more field defs");
	}
	else
	{
		add_fielddef(ht, fieldDef, scope, record);
		*width = * width + 4;
		record->next = NULL;
		printf("\t%s\t%s\n", record->type, record->name);

		parseTree moreFields = fieldDef-> siblings;

		if(moreFields->firstKid != NULL){
			record_dec *next = (record_dec *) malloc(sizeof(record_dec));
			add_moreFileds(ht, moreFields, next, scope, width);
			printf("\t%s\t%s\n", record->type, record->name);
		}
	}
}


void add_record(parseTree curr, hashtable *ht){
	parseTree recid = curr->siblings;
	char * scope = curr->siblings->lexeme;

	upsert(ht, scope, "record", "global", curr->siblings->lineNo, 0, 0, -1);

	entry *entry_1 = get(ht, scope, "global");
	record_dec *record = (record_dec *) malloc(sizeof(record_dec));

	parseTree fieldDef1 = curr->siblings->siblings->firstKid;
	parseTree fieldDef2 = fieldDef1->siblings;

	add_fielddef(ht, fieldDef1, scope, record);

	printf("\t%s\t%s\n", record->type, record->name);

	record->next = (record_dec *) malloc(sizeof(record_dec));

	add_fielddef(ht, fieldDef2, scope, record->next);

	int width;
	width = 8;

	record_dec * next = record->next;
	printf("\t%s\t%s\n", next->type, next->name);

	// checked for firstkid instead of having two checks at parent  and firstkid level of morefields
	if (fieldDef2->siblings->firstKid == NULL)
	{
		printf("%s\n", "Only two parameters");
	}
	else{

		next->next = (record_dec *) malloc(sizeof(record_dec));
		printf("%s\n", "No  There are more things");
		parseTree moreFields = fieldDef2->siblings;
		add_moreFileds(ht, moreFields, next, scope, &width);

	}

	entry_1->width = width;
	entry_1->record = record;
	entry_1->offset = offset + width;
	offset = offset + width;
}

void add_definitions(parseTree curr, hashtable *ht)
{
	while(curr != NULL)
	{
		printf("definitions %d\n", curr->id);
		add_record(curr->firstKid, ht);
		curr = curr->siblings;
	}
}

void add_declarations(parseTree curr, hashtable *ht, char* scope)
{

	while(curr != NULL)
	{
		parseTree datatype = curr->firstKid;
		parseTree id = datatype->siblings;
		parseTree gon = id->siblings;

		char ans[20];
		if (gon->firstKid != NULL){
			upsert(ht, id->lexeme, getType(ht, datatype, ans), "global", id->lineNo, 0, 0, -1);
		}
		else{
			upsert(ht, id->lexeme, getType(ht, datatype, ans), scope, id->lineNo, 0, 0, -1);
		}

		curr = curr->siblings;
	}

}

void add_function(parseTree curr, hashtable *ht)
{
	char scope[200];
	strcpy(scope, curr->lexeme);

	// printf("%d\n", curr->id);

	parseTree input = curr->siblings;

	// to bypass parameter list
	add_list(input->firstKid->firstKid, ht, scope, 1, 0);

	parseTree output = input->siblings;

	add_list(output->firstKid->firstKid, ht, scope, 0, 1);

	parseTree stmts = output->siblings;
	// printf("%d\n", stmts->id);
	// printf("%d\n", stmts->firstKid->id);

	// if no typedefinitions
	if (stmts->firstKid->firstKid != NULL)
		add_definitions(stmts->firstKid->firstKid, ht);

	parseTree dec = stmts->firstKid->siblings->firstKid;
	// add declarations now
	if (dec != NULL)
		add_declarations(dec, ht, scope);
	else
		printf("\n%s\n", "NULL HAI ji");
	// add_stmts()
}


void add_main_function(parseTree main, hashtable *ht)
{
	char scope[20] = "_main";

	parseTree stmts = main;

	if (stmts->firstKid->firstKid != NULL)
		add_definitions(stmts->firstKid->firstKid, ht);

	parseTree dec = stmts->firstKid->siblings->firstKid;
	// add declarations now
	if (dec != NULL){
		printf("%s\n", "NIGGA KUCH TOH HAI");
		add_declarations(dec, ht, scope);
	}
	else
		printf("%s\n", "NULL HAI Ji");
}


void popuplateHashTable(parseTree head, hashtable *ht, char *scope)
{

	parseTree othfun = head->firstKid->firstKid;

	while(othfun != NULL)
	{
		add_function(othfun->firstKid, ht);
		othfun = othfun->siblings;
	}

	parseTree mf = head->firstKid->siblings;
	add_main_function(mf->firstKid, ht);
	printf("%d\n", offset);
}

hashtable createSymbolTable(parseTree pt)
{
	hashtable *ht = create(100);
	char scope[] = "global";
	popuplateHashTable(pt, ht, scope);

	printf("%s\t%s\t%s\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\t%s\n\n", "key", "type", "scope", "width", "offset", "line", "input", "output", "param", "instance", "declaration");

	entry *temp = get(ht, "b7", "_readMarks");
	printf("%s\t%s\t%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", temp->key, temp->type, temp->scope, temp->width, temp->offset, temp->lineNo, temp->isInputParameter,temp->isOutputParameter, temp->ParameterNumber, temp->isRecordInstance, temp->isRecordDeclaration);

	temp = get(ht, "b3c45", "_readMarks");
	printf("%s\t%s\t%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", temp->key, temp->type, temp->scope, temp->width, temp->offset, temp->lineNo, temp->isInputParameter,temp->isOutputParameter, temp->ParameterNumber, temp->isRecordInstance, temp->isRecordDeclaration);

	temp = get(ht, "#marks", "global");
	printf("%s\t%s\t%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", temp->key, temp->type, temp->scope, temp->width, temp->offset, temp->lineNo, temp->isInputParameter,temp->isOutputParameter, temp->ParameterNumber, temp->isRecordInstance, temp->isRecordDeclaration);

	temp = get(ht, "d4", "_main");
	printf("%s\t%s\t%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", temp->key, temp->type, temp->scope, temp->width, temp->offset, temp->lineNo, temp->isInputParameter,temp->isOutputParameter, temp->ParameterNumber, temp->isRecordInstance, temp->isRecordDeclaration);

	temp = get(ht, "b5", "_main");
	printf("%s\t%s\t%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", temp->key, temp->type, temp->scope, temp->width, temp->offset, temp->lineNo, temp->isInputParameter,temp->isOutputParameter, temp->ParameterNumber, temp->isRecordInstance, temp->isRecordDeclaration);

	temp = get(ht, "d5cb34567", "_main");
	printf("%s\t%s\t%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", temp->key, temp->type, temp->scope, temp->width, temp->offset, temp->lineNo, temp->isInputParameter,temp->isOutputParameter, temp->ParameterNumber, temp->isRecordInstance, temp->isRecordDeclaration);

	temp = get(ht, "b5c6", "_main");
	printf("%s\t%s\t%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", temp->key, temp->type, temp->scope, temp->width, temp->offset, temp->lineNo, temp->isInputParameter,temp->isOutputParameter, temp->ParameterNumber, temp->isRecordInstance, temp->isRecordDeclaration);



}

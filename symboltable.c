/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:symboltable.c
*/


int offset = 0;

char functions[500][500];
int fun_count =0;

error_count = 0;


#include "symboltable.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "ast.h"

// checks if a function has been visited, if yes returns position in array
int seen(char * key){
    int i = 0;
    while(i != fun_count){
        if(strcmp(functions[i], key) == 0 ){
            return i;
        }
        i++;
    }
    return -1;
}

// creates a hash table of given size
hashtable *create(int size){

	hashtable *ht = NULL;

	ht = malloc(sizeof (hashtable));

	ht->size = size;

	ht->table = malloc(sizeof(entry*)*size);

	int i;
	for (i =0; i< size; i++){
		ht->table[i] = NULL;
	}

	return ht;
}

// creates a hash
int hash(hashtable *ht, char *nonce){

	unsigned long int hashvalue = 6669;

	int i = 0;
	while(hashvalue < ULONG_MAX && i < strlen(nonce)){
		hashvalue  =  nonce[i] + 71 * hashvalue;
		i++;
	}

	return hashvalue % ht->size;

}

// creates a hashtable entry
entry *newentry(hashtable * ht, char *key, char *type, char *scope, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber){
	entry *new;
	new = (entry*) malloc(sizeof(entry));
	new->key = (char*) malloc(sizeof(char)* 50);
	new->type = (char*) malloc(sizeof(char)* 50);
	new->scope = (char*) malloc(sizeof(char)* 50);

	strcpy(new->key, key);
	strcpy(new->type, type);
	strcpy(new->scope, scope);

	new->lineNo = lineNo;
	// new->id = getColumnIndex(type);

	new->ParameterNumber =  -1;
	if (isInputParameter == 1){
		new->isInputParameter = 1;
		new->ParameterNumber = ParameterNumber;
	}
	else{
		new->isInputParameter = 0;
	}

	if (isOutputParameter == 1){
		new->isOutputParameter = 1;
		new->ParameterNumber = ParameterNumber;
		new->assigned = -1;
	}
	else{
		new->isOutputParameter = 0;
		new->assigned = 0;
	}


	if(strcmp(type,"int") == 0)
	{
		new->width = 2;

		if(strcmp(scope, "global") != 0){
			new->offset  = offset;
			offset = offset + new->width;
		}
		else
			new->offset = -1;

	}

	if(strcmp(type,"real") == 0)
	{
		new->width = 2;

		if((strcmp(scope, "global")) != 0){
			new->offset  = offset;
			offset = offset + new->width;
		}
		else
			new->offset = -1;

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

			if(strcmp(scope, "global") != 0){
				new->offset  = offset;
				offset = offset + new->width;
			}
			else
				new->offset = -1;


		}
		else{
			new->width = -1;
			new->offset = -1;
		}
	}
	else{
		new->isRecordInstance = 0;
	}

	return new;
}

// ataches entry to hashtable
void upsert(hashtable *ht, char *key, char *type, char * scope, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber){

	int bin = 0;

	entry *newpair = NULL;
	entry *next = NULL;
	entry *last = NULL;

	bin = hash(ht, key);

	next = ht->table[bin];


	while(next != NULL && (strcmp(key, next->key) > 0 || strcmp(scope, next->scope) > 0 ))
	{
		// printf("<%s>\n", next->key);
		last = next;
		next = next->next;
	}

	if(next != NULL && next->key != NULL && (strcmp(key, next->key) == 0 && strcmp(scope, next->scope) == 0))
	{

		sprintf(symboltable_errors[error_count++],"Error: <%s> being re declared at line <%d>\n", next->key, next->lineNo);
		symbolerror = 1;
	}
	else
	{
		newpair = newentry(ht, key, type, scope, lineNo, isInputParameter, isOutputParameter, ParameterNumber);


		if( next == ht->table[bin] ) {
			// printf("1:\t<%s>\n", key);
			newpair->next = next;
			ht->table[bin] = newpair;

		} else if ( next == NULL ) {
			last->next = newpair;

		} else  {
			// printf("3:\t<%s>\n", key);
			newpair->next = next;
			last->next = newpair;
		}
	}
}

// used to fetch from a hash table
entry *get(hashtable *ht, char *key, char*scope)
{
	int hashvalue = hash(ht, key);

	entry *temp = ht->table[hashvalue];

	while( temp != NULL && temp->key != NULL && (strcmp(key, temp->key) != 0  || strcmp(scope, temp->scope) != 0)) {
		temp = temp->next;
	}

	if( temp == NULL || temp->key == NULL || (strcmp( key, temp->key ) != 0  || strcmp(scope, temp->scope) !=0)) {
		return NULL;

	}
	else {
		return temp;
	}

}

// checks if a variable exists non globally
int existsNonGlobally(hashtable *ht, char *varname){
	int i = 0;
	entry * temp;
	while(i!= fun_count){
		temp = get(ht, varname, functions[i]);
		if (temp!=NULL){
			return i;
		}
		i++;
	}
	return -1;
}


// returns input parameter corresponding to parameter number
entry *getInputParameter(hashtable *ht, char *function, int ParameterNumber)
{

	int bin = 0;
	entry *temp;
	for (bin =0 ; bin < 100; bin ++){
		temp = ht->table[ bin ];
		while( temp != NULL && temp->key != NULL) {
			if(strcmp(function, temp->scope) == 0 && temp->isInputParameter == 1 && temp->ParameterNumber == ParameterNumber){
				return temp;
			}
			temp = temp->next;
		}
	}
	return NULL;
}

// returns output parameter corresponding to parameter number
entry *getOutputParameter(hashtable *ht, char *function, int ParameterNumber)
{
	int bin = 0;
	entry *temp;
	for (bin =0 ; bin < 100; bin ++){
		temp = ht->table[ bin ];
		while( temp != NULL && temp->key != NULL) {
			if(strcmp(function, temp->scope) == 0 && temp->isOutputParameter == 1 && temp->ParameterNumber == ParameterNumber){
				return temp;
			}
			temp = temp->next;
		}
	}
	return NULL;
}

// returns datatype of variable
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
					sprintf(symboltable_errors[error_count++],  "\nError: Undeclared record type <%s> being used at line <%d>\n", curr->firstKid->siblings->lexeme, curr->firstKid->siblings->lineNo);
					strcpy(ans, curr->firstKid->siblings->lexeme);
					symbolerror = 1;
				}
				else{
					strcpy(ans, curr->firstKid->siblings->lexeme);
				}
			}

	return ans;
}

// add any list to symbol table, output parameter list, input parameter list etc
void add_list(parseTree curr, hashtable *ht, char* scope, int input, int output)
{

	int counter = 0;

	while(curr != NULL)
	{
		char ans[20];
		getType(ht, curr, ans);
		entry * temp = get(ht, curr->siblings->lexeme, "global");
		if(temp == NULL){

			temp = get(ht, curr->siblings->lexeme, scope);

			if (temp == NULL){
				upsert(ht, curr->siblings->lexeme, ans, scope, curr->siblings->lineNo, input, output, counter);
			}
			else{
				sprintf(symboltable_errors[error_count++], "Error: Variable <%s> being re declared in the same scope at line <%d>\n", curr->siblings->lexeme, curr->siblings->lineNo);
				symbolerror = 1;
			}
		}
		else{

			sprintf(symboltable_errors[error_count++], "Error: Global Variable <%s> is being redeclared at line <%d>\n", curr->siblings->lexeme, curr->siblings->lineNo);
			symbolerror = 1;
		}

		curr = curr->siblings->siblings;

		counter++;
	}
}

// adds field defintion to record
void add_fielddef(hashtable *ht, parseTree curr, char * scope, record_dec *record){
	char type[20];
	parseTree datatype = curr->firstKid;
	getType(ht, datatype, type);

	char *id = datatype->siblings->lexeme;

	record->type = (char*) malloc(20 * sizeof(char));
	strcpy(record->type, type);

	record->name = (char*) malloc(20 * sizeof(char));
	strcpy(record->name, id);
	record->next = NULL;
}

// add morefields to record
void add_more_fields(hashtable *ht, parseTree curr, record_dec *record, char *scope, int * width)
{
	parseTree fieldDef = curr->firstKid;

	if(fieldDef == NULL)
		;
	else
	{
		add_fielddef(ht, fieldDef, scope, record);

		if(strcmp(record->type, "int") == 0)
			*width = *width + 2;
		else
			*width = *width + 2;

		parseTree moreFields = fieldDef->siblings;

		if(moreFields->firstKid != NULL)
		{
			record_dec *next = (record_dec *) malloc(sizeof(record_dec));
			add_more_fields(ht, moreFields, next, scope, width);
			record->next = next;
		}
	}
}

// adds the particular record declaration
void add_record(parseTree curr, hashtable *ht){
	parseTree recid = curr->siblings;
	char *scope = curr->siblings->lexeme;

	entry *entry_1 = get(ht, scope, "global");

	if(entry_1 == NULL)
	{
		upsert(ht, scope, "record", "global", curr->siblings->lineNo, 0, 0, -1);

		entry_1 = get(ht, scope, "global");

		record_dec *recordF = (record_dec *) malloc(sizeof(record_dec));

		parseTree fieldDef1 = curr->siblings->siblings->firstKid;
		parseTree fieldDef2 = fieldDef1->siblings;

		add_fielddef(ht, fieldDef1, scope, recordF);

		record_dec *recordS = (record_dec *) malloc(sizeof(record_dec));
		recordF->next = recordS;

		add_fielddef(ht, fieldDef2, scope, recordS);

		int width = 0;

		if(strcmp(recordF->type, "int") == 0)
			width+=2;
		else
			width+=2;

		if(strcmp(recordS->type, "int") == 0)
			width+=2;
		else
			width+=2;


		if (fieldDef2->siblings->firstKid == NULL)
		{
			;
		}
		else
		{
			record_dec *nrecord;
			nrecord = (record_dec *) malloc(sizeof(record_dec));
			recordS->next = nrecord;
			parseTree moreFields = fieldDef2->siblings;
			add_more_fields(ht, moreFields, nrecord, scope, &width);
		}
		entry_1->width = width;
		entry_1->record = recordF;
		entry_1->offset = -1;
		offset = offset;

	}
	else{
		sprintf(symboltable_errors[error_count++], "Error: Record <%s> being declared again at line <%d>\n", scope, curr->siblings->lineNo);
		symbolerror = 1;
	}
}

// adds data definitions
void add_definitions(parseTree curr, hashtable *ht)
{
	while(curr != NULL)
	{
		add_record(curr->firstKid, ht);
		curr = curr->siblings;
	}
}

// adds declarations to symbol table
void add_declarations(parseTree curr, hashtable *ht, char* scope)
{
	while(curr != NULL)
	{
		parseTree datatype = curr->firstKid;
		parseTree id = datatype->siblings;
		parseTree gon = id->siblings;

		char ans[20];
		if (gon->firstKid != NULL){
			entry * temp = get(ht, id->lexeme, "global");
			if(existsNonGlobally(ht, id->lexeme) == -1 && temp == NULL)
				upsert(ht, id->lexeme, getType(ht, datatype, ans), "global", id->lineNo, 0, 0, -1);
			else {
				int pos = existsNonGlobally(ht, id->lexeme);
				if (pos == -1)
					sprintf(symboltable_errors[error_count++], "Error: Global variable <%s> declared non globally earlier in function <%s> at line <%d>\n", id->lexeme, functions[pos], id->lineNo);
				else
					sprintf(symboltable_errors[error_count++], "Error: Global variable <%s> being redeclared globally at line <%d>\n", id->lexeme, id->lineNo);
				symbolerror = 1;
			}
		}
		else{

			entry * temp = get(ht, id->lexeme, "global");
			//check if globally declared
			if(temp == NULL){
				temp = get(ht, id->lexeme, scope);
				//check if declared in the same socpe
				if (temp == NULL){
					upsert(ht, id->lexeme, getType(ht, datatype, ans), scope, id->lineNo, 0, 0, -1);
				}
				else{
					sprintf(symboltable_errors[error_count++], "Error: Variable <%s> being re declared in the same scope at line <%d>\n", id->lexeme, id->lineNo);
					symbolerror = 1;
				}

			}
			else{
				sprintf(symboltable_errors[error_count++], "Error: Global Variable <%s> is being redeclared at line <%d>\n", id->lexeme, id->lineNo);

				symbolerror = 1;
			}

		}

		curr = curr->siblings;
	}

}

void add_function(parseTree curr, hashtable *ht)
{
	char scope[200];
	strcpy(scope, curr->lexeme);



	parseTree input = curr->siblings;

	add_list(input->firstKid->firstKid, ht, scope, 1, 0);

	parseTree output = input->siblings;

	add_list(output->firstKid->firstKid, ht, scope, 0, 1);

	parseTree stmts = output->siblings;

	if (stmts->firstKid->firstKid != NULL)
		add_definitions(stmts->firstKid->firstKid, ht);

	parseTree dec = stmts->firstKid->siblings->firstKid;
	if (dec != NULL)
		add_declarations(dec, ht, scope);
}


void add_main_function(parseTree main, hashtable *ht)
{
	char scope[20] = "_main";

	parseTree stmts = main;

	if (stmts->firstKid->firstKid != NULL)
		add_definitions(stmts->firstKid->firstKid, ht);

	parseTree dec = stmts->firstKid->siblings->firstKid;
	if (dec != NULL){
		add_declarations(dec, ht, scope);
	}
}


void popuplateHashTable(parseTree head, hashtable *ht, char *scope)
{

	parseTree othfun = head->firstKid->firstKid;
	parseTree mf = head->firstKid->siblings;

	upsert(ht, "_main", "function", "global", mainfuncitonline, 0, 0, -1);
	strcpy(functions[fun_count++], "_main");
	add_main_function(mf->firstKid, ht);

	while(othfun != NULL)
	{
		entry *temp = get(ht, othfun->firstKid->lexeme, "global");
		if (temp == NULL && strcmp(othfun->firstKid->lexeme, "_main") != 0){
			strcpy(functions[fun_count++], othfun->firstKid->lexeme);
			upsert(ht, othfun->firstKid->lexeme, "function", "global", othfun->firstKid->lineNo, 0, 0, -1);
			add_function(othfun->firstKid, ht);
		}
		else if(strcmp(othfun->firstKid->lexeme, "_main") == 0){
			sprintf(symboltable_errors[error_count++], "Error: _main being used for non main function at line <%d>\n", othfun->firstKid->lineNo);
			symbolerror = 1;

		}
		else{
			sprintf(symboltable_errors[error_count++], "Error: Function <%s> is being overloaded at line <%d>\n", othfun->firstKid->lexeme, othfun->firstKid->lineNo);
			symbolerror = 1;
		}
		othfun = othfun->siblings;
	}

}

hashtable * createSymbolTable(parseTree pt, int size)
{	offset = 0;
	hashtable *ht = create(size);
	char scope[] = "global";
	popuplateHashTable(pt, ht, scope);

	return ht;
}


char* getRecordType(hashtable * ht, char *record_name, char *type){
	entry * record = get(ht, record_name, "global");
	record_dec * rec = record->record;
	strcpy(type,"");
	strcat(type, "(");
	while(rec!= NULL){
		if(rec->next == NULL){
			strcat(type, rec->type);
			strcat(type, ")");
		}
		else{
			strcat(type, rec->type);
			strcat(type, ", ");
		}
		rec = rec->next;
	}
	return type;
}

void printSymbolTable( hashtable *ht, int size){
	int bin = 0;
	entry *temp;
	printf("Globals have offset -1, real has width 4, integer has width 2\n");

	printf("\n %20s %35s %15s %15s ", "Lexeme", "Type", "Scope", "Offset");

	for (bin =0 ; bin < size; bin ++){
		temp = ht->table[ bin ];

		while( temp != NULL && temp->key != NULL ) {
			if(strcmp(temp->scope,"") !=0 && (strcmp(temp->type,"int") ==0 &&  strcmp(temp->type,"real")))
				printf("\n %20s %35s %15s %15d ", temp->key, temp->type, temp->scope, temp->offset);

			if(strcmp(temp->scope,"") !=0 && (temp->type[0] == '#')){
				char type[200];
				printf("\n %20s %35s %15s %15d ", temp->key, getRecordType(ht, temp->type, type), temp->scope, temp->offset);
			}


			temp = temp->next;
		}
	}
}

/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:symboltable.c
*/

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


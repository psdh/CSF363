/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:symboltableDef.h
*/


#ifndef SYMBOLTABLEDEF_H_INCLUDED
#define SYMBOLTABLEDEF_H_INCLUDED

#include <stdio.h>

#define table_row 60

typedef struct {
    // the key is also the scope
    char * key;
    char *type;
    int width;
    int offset;
    int lineNo;
    int id;
    char * value;
    struct entry_s *next;
}entry;

typedef struct {
    int size;
    entry **table;
}hashtable;

hashtable *create( int size );
int hash( hashtable *ht, char *key );
entry *newpair( char *key, char *type, int width, int offset, int lineNo, int id, char *value);
void insert(hashtable *ht, char *key, char *type, int width, int offset, int lineNo, int id, char *value);
entry *get(hashtable *ht, char *key);

#endif

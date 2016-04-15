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
    char * key;
    //int
    char *type;
    //_main
    char *scope;
    // 4
    int width;
    // curr_offset + 4
    int offset;
    // lineNo
    int lineNo;
    // id corresponding to key
    int id;
    // pointer
    entry *next;
    // record ka declaration hai kya ye
    int isInputParamater;
    int isOutParamter;
    int inputParPlace;
    int isRecordDeclaration;
    int isRecordInstance;
    record_dec *record;
}entry;

type struct {
    char *type;
    char *name;
    char *value;
    record_dec *next;
}record_dec;

typedef struct {
    int size;
    entry **table;
}hashtable;

hashtable *create( int size );
int hash( hashtable *ht, char *key );
entry *newentry( char *key, char *type, char * scope, int offset, int lineNo, int id, char *value);
void insert(hashtable *ht, char *key, char *type, char * scope, int width, int offset, int lineNo, int id, char *value);
entry get(hashtable *ht, char *key, char * scope);

#endif

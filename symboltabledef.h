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

struct entry;
struct record_dec;


typedef struct {
    char *type;
    char *name;
    struct record_dec *next;
}record_dec;


typedef struct {
    char *key;
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
    // pointer
    struct entry *next;
    // record ka declaration hai kya ye
    // let them all be -1
    int isInputParameter;
    int isOutputParameter;
    int ParameterNumber;
    int isRecordDeclaration;
    int isRecordInstance;
    record_dec *record;
}entry;


typedef struct {
    int size;
    entry **table;
}hashtable;

hashtable *create( int size );
int hash( hashtable *ht, char *key );
entry *newentry( char *key, char *type, char * scope, int offset, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber);
void upsert(hashtable *ht, char *key, char *type, char * scope, int offset, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber);
entry *get(hashtable *ht, char *key, char * scope);

#endif

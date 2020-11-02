#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 997

#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LITINT 2
#define SYMBOL_LITFLOAT 3
#define SYMBOL_LITCHAR 4
#define SYMBOL_STRING 5
#define SYMBOL_TRUE 6
#define SYMBOL_FALSE 7
#define SYMBOL_VARIABLE 8
#define SYMBOL_FUNCTION 9
#define SYMBOL_VECTOR 10
#define SYMBOL_LABEL 11

typedef struct hash_node
{
    int type;
    char *text;
    struct hash_node *next;
} HASH_NODE;

void hashInit(void);
void freeTable(void);
int hashAddres(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
HASH_NODE* makeTemp(void);
HASH_NODE* makeLabel(void);

#endif

//Autor: Nicolas Mauro de Moreira Bohnenberger - 00207160
#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 997

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_FLT 2
#define SYMBOL_LIT_TRU 3
#define SYMBOL_LIT_FLS 4
#define SYMBOL_LIT_CHR 5
#define SYMBOL_LIT_STR 6
#define SYMBOL_TOK_IDT 7


typedef struct hash_node
{
    int type;
    char *text;
    struct hash_node *next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE* hashFind(char *text);
HASH_NODE* hashInsert(int type, char* text);
void hashPrint(void);

#endif

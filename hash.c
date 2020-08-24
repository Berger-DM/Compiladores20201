//Autor: Nicolas Mauro de Moreira Bohnenberger - 00207160
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HASH_NODE*Table[HASH_SIZE];

void hashInit(void)
{
    int i;
    for (i=0; i<HASH_SIZE; i++)
        Table[i] = 0;
}

int hashAddress(char *text)
{
    int address = 1;
    int loopint;
    for (loopint=0; loopint<strlen(text); loopint++)
        address = (address * text[loopint]) % HASH_SIZE + 1;
    return address - 1;
}

HASH_NODE* hashFind(char *text)
{
    HASH_NODE *node;
    int address = hashAddress(text);

    for(node = Table[address]; node; node = node->next)
        if(!strcmp(text, node->text))
            return node;

    return 0;
}

HASH_NODE* hashInsert(char* text)
{
    HASH_NODE *newhashnode;
    int address = hashAddress(text);
    newhashnode = (HASH_NODE*) calloc (1, sizeof(HASH_NODE));
    newhashnode->type = 1;
    newhashnode->text = (char*) calloc(strlen(text)+1, sizeof(char));
    strcpy(newhashnode->text, text);
    newhashnode->next = Table[address];
    Table[address] = newhashnode;
    return newhashnode;
}

void hashPrint(void)
{
    int loopint;
    HASH_NODE *node;
    for (loopint=0; loopint<HASH_SIZE; loopint++)
        for (node=Table[loopint]; node; node = node->next)
            printf("Table[%d] has %s\n", loopint, node->text);
}

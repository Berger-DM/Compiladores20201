#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define MAX_CHILDREN 5

enum
{
    AST_SYMBOL = 1,
    AST_SYMBOL_VECTOR,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_LT,
    AST_GT,
    AST_OR,
    AST_AND,
    AST_LE,
    AST_GE,
    AST_EQ,
    AST_DIF,
    AST_UN_MIN,
    AST_UN_NEG,
    AST_FUN_CALL,
    AST_LPARAM,
    AST_LDECL,
    AST_DECLVAR_NOT_VECTOR,
    AST_DECLVAR_VECTOR,
    AST_LVECTOR,
    AST_FUN,
    AST_FUN_HEADER,
    AST_FUN_PARAMS,
    AST_COMM_SEQ,
    AST_ATTRIB,
    AST_ATTRIB_VEC,
    AST_READ,
    AST_PRINT,
    AST_PRINT_PARAMS,
    AST_RETURN,
    AST_IF,
    AST_IF_ELSE,
    AST_WHILE,
    AST_LOOP,
    AST_TYPECHAR,
    AST_TYPEINT,
    AST_TYPEFLOAT,
    AST_TYPEBOOL,
};

typedef struct ast_node
{
    int type;
    struct ast_node *child[MAX_CHILDREN];
    HASH_NODE *symbol;
} AST;

AST *AST_create(int type, HASH_NODE *symbol, AST *s0, AST *s1, AST *s2, AST *s3, AST *s4);
void AST_print(AST *node, int level);
void file_print(char *str, FILE *out);
void decompile(AST *node, FILE *out);

#endif

#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 5

#include "hash.h"

enum
{
    AST_SYMBOL = 1,
    AST_DECL,
    AST_FUNC,
    AST_FUNC_HD,
    AST_DECL_ID,
    AST_DECL_VEC,
    AST_LIT_LIST,
    AST_PARAM_LIST,
    AST_COM_SEQ,
    AST_ATRIB,
    AST_ATRIB_VEC,
    AST_READ,
    AST_PRINT,
    AST_RETURN,
    AST_PRINT_LIST,
    AST_IF,
    AST_IF_ELSE,
    AST_WHILE,
    AST_LOOP,
    AST_VECTOR,
    AST_LE,
    AST_GE,
    AST_EQ,
    AST_DIF,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_LT,
    AST_GT,
    AST_OR,
    AST_AND,
    AST_UN_NEG,
    AST_UN_MIN,
    AST_FUNC_CALL,
    AST_CALL_PARAM
};

typedef struct astnode
{
    int type;
    HASH_NODE *symbol;
    struct astnode *son[MAX_SONS];
} AST;

AST *ASTcria(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3, AST* s4);
void ASTprint(AST *node, int level);
void decompilation(AST *node, FILE *file);
AST *getRaiz();

#endif

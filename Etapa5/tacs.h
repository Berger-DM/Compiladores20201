#ifndef TACS_HEADER
#define TACS_HEADER

#include "lex.yy.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MUL 4
#define TAC_DIV 5
#define TAC_LT  6 
#define TAC_GT  7
#define TAC_OR  8
#define TAC_AND 9
#define TAC_LE  10
#define TAC_GE  11
#define TAC_EQ  12
#define TAC_DIF 13
#define TAC_COPY 14
#define TAC_IF 15
#define TAC_JFALSE 16
#define TAC_LABEL 17

typedef struct tac_node
{
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tac_node* prev;
    struct tac_node* next;
} TAC;

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC* tac);
TAC* tacJoin(TAC* l1, TAC* l2);


//CODEGEN
TAC* codeGen(AST *node);

#endif
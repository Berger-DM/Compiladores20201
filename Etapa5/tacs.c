#include "tacs.h"


TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2)
{
    TAC* newtac = 0;
    newtac = (TAC*) calloc(1, sizeof(TAC));
    newtac->type = type;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->prev = 0;
    newtac->next = 0;
    return newtac;
}

void tacPrint(TAC* tac)
{
    if (!tac) return;
    if (tac->type == TAC_SYMBOL) return;
    fprintf(stderr, "entrei num tacPrint após o if\n");
    fprintf(stderr, "TAC(");
    switch(tac->type)
    {
        case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
        case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
        case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
        case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
        case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
        case TAC_LT: fprintf(stderr, "TAC_LT"); break;
        case TAC_GT: fprintf(stderr, "TAC_GT"); break;
        case TAC_OR: fprintf(stderr, "TAC_OR"); break;
        case TAC_AND: fprintf(stderr, "TAC_AND"); break;
        case TAC_LE: fprintf(stderr, "TAC_LE"); break;
        case TAC_GE: fprintf(stderr, "TAC_GE"); break;
        case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
        case TAC_DIF: fprintf(stderr, "TAC_DIF"); break;
        case TAC_COPY: fprintf(stderr, "TAC_COPY"); break;
        default: fprintf(stderr, "TAC_UNKNOWN"); break;
    }
    fprintf(stderr,",%s", (tac->res)?tac->res->text:"0");
    fprintf(stderr,",%s", (tac->op1)?tac->op1->text:"0");
    fprintf(stderr,",%s", (tac->op2)?tac->op2->text:"0");
    fprintf(stderr, ");\n");
}

void tacPrintBackwards(TAC* tac)
{
    fprintf(stderr, ".");
    if (!tac) return;
    else
    {
        tacPrintBackwards(tac->prev);
        tacPrint(tac);
    }
}

TAC* tacJoin(TAC* l1, TAC* l2)
{
    TAC* point;
    if (!l1) return l2;
    if (!l2) return l1;
    for (point = l2; point->prev !=0; point = point->prev)
    {

    }
}

TAC* makeBinaryOperation(TAC* code0, TAC* code1, int tactype);
TAC* makeAttrib(TAC* code0, AST* astnode);
TAC* makeIfThen(TAC* code0, TAC* code1);
TAC* makeIfThenElse(TAC* code0, TAC* code1);
TAC* makeLoop(TAC* code0, TAC* code1);
TAC* makeWhile(TAC* code0, TAC* code1);

//CODEGEN
TAC* codeGen(AST *node)
{
    int i;
    TAC *result = 0;
    TAC *code[MAX_CHILDREN];

    if (!node) return 0;

    // PROCESS CHILDREN
    for (i =0; i < MAX_CHILDREN; i++)
        code[i] = codeGen(node->child[i]);
    //PROCESS THIS NODE
    switch(node->type)
    {
        case AST_SYMBOL:        result = tacCreate(TAC_SYMBOL,node->symbol,0,0);
                                break;
        case AST_ADD:           result = makeBinaryOperation(code[0], code[1],
                                TAC_ADD); break;
        case AST_SUB:           result = makeBinaryOperation(code[0], code[1],
                                TAC_SUB); break;
        case AST_MUL:           result = makeBinaryOperation(code[0], code[1],
                                TAC_MUL); break;
        case AST_DIV:           result = makeBinaryOperation(code[0], code[1],
                                TAC_DIV); break;
        case AST_LT:            result = makeBinaryOperation(code[0], code[1],
                                TAC_LT); break;
        case AST_GT:            result = makeBinaryOperation(code[0], code[1],
                                TAC_GT); break;
        case AST_OR:            result = makeBinaryOperation(code[0], code[1],
                                TAC_OR); break;
        case AST_AND:           result = makeBinaryOperation(code[0], code[1],
                                TAC_AND); break;
        case AST_LE:            result = makeBinaryOperation(code[0], code[1],
                                TAC_LE); break;
        case AST_GE:            result = makeBinaryOperation(code[0], code[1],
                                TAC_GE); break;
        case AST_EQ:            result = makeBinaryOperation(code[0], code[1],
                                TAC_EQ); break;
        case AST_DIF:           result = makeBinaryOperation(code[0], code[1],
                                TAC_DIF); break;
        case AST_ATTRIB:        result = makeAttrib(code[0], node); break;
        case AST_ATTRIB_VEC:    result = makeAttrib(code[0], node); break;
        case AST_IF:            result = makeIfThen(code[0], code[1]); break;
        default:                result = tacJoin(code[0], tacJoin(code[1],
                                tacJoin(code[2], code[3]))); break;
    }
    return result;
}

TAC* makeIfThen(TAC* code0, TAC* code1)
{
    TAC* jumptac = 0;
    TAC* labeltac = 0;
    HASH_NODE * newlabel = 0;
    newlabel = makeLabel();

    jumptac = tacCreate(TAC_JFALSE, newlabel, code0->res, 0);
    jumptac->prev = code0;
    labeltac = tacCreate(TAC_LABEL, newlabel, 0, 0);
    labeltac->prev = code1;

    return tacJoin(jumptac, labeltac);
}

TAC* makeBinaryOperation(TAC* code0, TAC* code1, int tactype)
{
    return tacJoin(tacJoin(code0, code1),
    tacCreate(tactype, makeTemp(),
    code0?code0->res:0, code1?code1->res:0));
}

TAC* makeAttrib(TAC* code0, AST* astnode)
{
    return tacJoin(code0, (tacCreate(TAC_COPY, astnode->symbol,
    code0?code0->res:0, 0)));
}

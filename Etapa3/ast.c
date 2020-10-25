#include "ast.h"

AST *ASTcria(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3, AST* s4)
{
    AST *newnode;
    newnode->type =     type;
    newnode->symbol =   symbol;
    newnode->son[0] =   s0;
    newnode->son[1] =   s1;
    newnode->son[2] =   s2;
    newnode->son[3] =   s3;
    newnode->son[4] =   s4;
    return newnode;
}

void ASTprint(AST *node, int level)
{
    int i=0;
    if (node == 0)
        return;
    for (i=0; i<level; ++i)
            fprintf(stderr, "  ");
    fprintf(stderr, "ast(");
    switch(node->type)
    {
        case AST_SYMBOL:        fprintf(stderr, "AST_SYMBOL"); break;
        case AST_FUNC:          fprintf(stderr, "AST_FUNC"); break;
        case AST_FUNC_HD:       fprintf(stderr, "AST_FUNC_HD"); break;
        case AST_DECL_ID:       fprintf(stderr, "AST_DECL_ID"); break;
        case AST_DECL_VEC:      fprintf(stderr, "AST_DECL_VEC"); break;
        case AST_LIT_LIST:      fprintf(stderr, "AST_LIT_LIST"); break;
        case AST_PARAM_LIST:    fprintf(stderr, "AST_PARAM_LIST"); break;
        case AST_COM_SEQ:       fprintf(stderr, "AST_COM_SEQ"); break;
        case AST_ATRIB:         fprintf(stderr, "AST_ATRIB"); break;
        case AST_ATRIB_VEC:     fprintf(stderr, "AST_ATRIB_VEC"); break;
        case AST_READ:          fprintf(stderr, "AST_READ"); break;
        case AST_PRINT:         fprintf(stderr, "AST_PRINT"); break;
        case AST_RETURN:        fprintf(stderr, "AST_RETURN"); break;
        case AST_PRINT_LIST:    fprintf(stderr, "AST_PRINT_LIST"); break;
        case AST_IF:            fprintf(stderr, "AST_IF"); break;
        case AST_IF_ELSE:       fprintf(stderr, "AST_IF_ELSE"); break;
        case AST_WHILE:         fprintf(stderr, "AST_WHILE"); break;
        case AST_LOOP:          fprintf(stderr, "AST_LOOP"); break;
        case AST_VECTOR:        fprintf(stderr, "AST_VECTOR"); break;
        case AST_LE:            fprintf(stderr, "AST_LE"); break;
        case AST_GE:            fprintf(stderr, "AST_GE"); break;
        case AST_EQ:            fprintf(stderr, "AST_EQ"); break;
        case AST_DIF:           fprintf(stderr, "AST_DIF"); break;
        case AST_ADD:           fprintf(stderr, "AST_ADD"); break;
        case AST_SUB:           fprintf(stderr, "AST_SUB"); break;
        case AST_MUL:           fprintf(stderr, "AST_MUL"); break;
        case AST_DIV:           fprintf(stderr, "AST_DIV"); break;
        case AST_LT:            fprintf(stderr, "AST_LT"); break;
        case AST_GT:            fprintf(stderr, "AST_GT"); break;
        case AST_OR:            fprintf(stderr, "AST_OR"); break;
        case AST_AND:           fprintf(stderr, "AST_AND"); break;
        case AST_UN_NEG:        fprintf(stderr, "AST_UN_NEG"); break;
        case AST_UN_MIN:        fprintf(stderr, "AST_UN_MIN"); break;
        case AST_FUNC_CALL:     fprintf(stderr, "AST_FUNC_CALL"); break;
        case AST_CALL_PARAM:    fprintf(stderr, "AST_CALL_PARAM"); break;
        default:                fprintf(stderr, "AST_UNKNOWN"); break;
    }
    for (i=0; i< MAX_SONS; ++i)
        ASTprint(node->son[i], level+1);
    for (i=0; i<level; ++i)
        fprintf(stderr, "  ");
    fprintf(stderr, ")\n");
}

void decompilation(AST *node, FILE *file)
{
    if(!node)
        return;
        
    switch(node->type)
    {
        case AST_SYMBOL:
            fprintf(file, " %s", node->symbol->text);
            break;
        case AST_DECL:
            decompilation(node->son[0], file);
            fprintf(file, ";\n");
            decompilation(node->son[1], file);
            break;
        case AST_FUNC:
            decompilation(node->son[0], file);
            fprintf(file, "{");
            decompilation(node->son[1], file);
            fprintf(file, "}");
            break;
        case AST_FUNC_HD:
            decompilation(node->son[0], file);
            fprintf(file, "(");
            decompilation(node->son[1], file);
            fprintf(file, ") =");
            decompilation(node->son[2], file);
            break;
        case AST_DECL_ID:
            decompilation(node->son[0], file);
            fprintf(file, "=");
            decompilation(node->son[1], file);
            fprintf(file, ":");
            decompilation(node->son[2], file);
            break;
        case AST_DECL_VEC:
            decompilation(node->son[0], file);
            fprintf(file, "=");
            decompilation(node->son[1], file);
            fprintf(file, "[");
            decompilation(node->son[2], file);
            fprintf(file, "]");
            if (node->son[3])
            {
                fprintf(file, " : ");
                decompilation(node->son[3], file);
            }
            break;
        case AST_LIT_LIST:
            decompilation(node->son[0], file);
            if(node->son[1])
            {
                fprintf(file, " ");
                decompilation(node->son[1], file);
            }
            break;
        case AST_PARAM_LIST:    fprintf(stderr, "AST_PARAM_LIST"); break;
        case AST_COM_SEQ:       fprintf(stderr, "AST_COM_SEQ"); break;
        case AST_ATRIB:         fprintf(stderr, "AST_ATRIB"); break;
        case AST_ATRIB_VEC:     fprintf(stderr, "AST_ATRIB_VEC"); break;
        case AST_READ:          fprintf(stderr, "AST_READ"); break;
        case AST_PRINT:         fprintf(stderr, "AST_PRINT"); break;
        case AST_RETURN:        fprintf(stderr, "AST_RETURN"); break;
        case AST_PRINT_LIST:    fprintf(stderr, "AST_PRINT_LIST"); break;
        case AST_IF:            fprintf(stderr, "AST_IF"); break;
        case AST_IF_ELSE:       fprintf(stderr, "AST_IF_ELSE"); break;
        case AST_WHILE:         fprintf(stderr, "AST_WHILE"); break;
        case AST_LOOP:          fprintf(stderr, "AST_LOOP"); break;
        case AST_VECTOR:        fprintf(stderr, "AST_VECTOR"); break;
        case AST_LE:            fprintf(stderr, "AST_LE"); break;
        case AST_GE:            fprintf(stderr, "AST_GE"); break;
        case AST_EQ:            fprintf(stderr, "AST_EQ"); break;
        case AST_DIF:           fprintf(stderr, "AST_DIF"); break;
        case AST_ADD:           fprintf(stderr, "AST_ADD"); break;
        case AST_SUB:           fprintf(stderr, "AST_SUB"); break;
        case AST_MUL:           fprintf(stderr, "AST_MUL"); break;
        case AST_DIV:           fprintf(stderr, "AST_DIV"); break;
        case AST_LT:            fprintf(stderr, "AST_LT"); break;
        case AST_GT:            fprintf(stderr, "AST_GT"); break;
        case AST_OR:            fprintf(stderr, "AST_OR"); break;
        case AST_AND:           fprintf(stderr, "AST_AND"); break;
        case AST_UN_NEG:        fprintf(stderr, "AST_UN_NEG"); break;
        case AST_UN_MIN:        fprintf(stderr, "AST_UN_MIN"); break;
        case AST_FUNC_CALL:     fprintf(stderr, "AST_FUNC_CALL"); break;
        case AST_CALL_PARAM:    fprintf(stderr, "AST_CALL_PARAM"); break;
        default:                fprintf(stderr, "AST_UNKNOWN"); break;

    }
}

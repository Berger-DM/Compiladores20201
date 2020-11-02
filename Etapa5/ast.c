#include <stdio.h>
#include "ast.h"

AST *AST_create(int type, HASH_NODE *symbol, AST *s0, AST *s1, AST *s2, AST *s3, AST *s4)
{
    AST *node = (AST *)calloc(1, sizeof(AST));

    node->type = type;
    node->symbol = symbol;
    node->child[0] = s0;
    node->child[1] = s1;
    node->child[2] = s2;
    node->child[3] = s3;
    node->child[4] = s4;

    return node;
}

void AST_print(AST *node, int level)
{
    if (!node)
    {
        return;
    }

    for (int i = 0; i < level; i++)
    {
        printf("  ");
    }

    switch (node->type)
    {
    case AST_SYMBOL:
        printf("AST_SYMBOL");
        break;
    case AST_SYMBOL_VECTOR:
        printf("AST_SYMBOL_VECTOR");
        break;
    case AST_ADD:
        printf("AST_ADD");
        break;
    case AST_SUB:
        printf("AST_SUB");
        break;
    case AST_MUL:
        printf("AST_MUL");
        break;
    case AST_DIV:
        printf("AST_DIV");
        break;
    case AST_LT:
        printf("AST_LT");
        break;
    case AST_GT:
        printf("AST_GT");
        break;
    case AST_OR:
        printf("AST_OR");
        break;
    case AST_AND:
        printf("AST_AND");
        break;
    case AST_LE:
        printf("AST_LE");
        break;
    case AST_GE:
        printf("AST_GE");
        break;
    case AST_EQ:
        printf("AST_EQ");
        break;
    case AST_DIF:
        printf("AST_DIF");
        break;
    case AST_UN_MIN:
        printf("AST_UN_MIN");
        break;
    case AST_UN_NEG:
        printf("AST_UN_NEG");
        break;
    case AST_FUN_CALL:
        printf("AST_FUN_CALL");
        break;
    case AST_LPARAM:
        printf("AST_LPARAM");
        break;
    case AST_LDECL:
        printf("AST_LDECL");
        break;
    case AST_DECLVAR_NOT_VECTOR:
        printf("AST_DECLVAR_NOT_VECTOR");
        break;
    case AST_DECLVAR_VECTOR:
        printf("AST_DECLVAR_VECTOR");
        break;
    case AST_LVECTOR:
        printf("AST_LVECTOR");
        break;
    case AST_FUN:
        printf("AST_FUN");
        break;
    case AST_FUN_HEADER:
        printf("AST_FUN_HEADER");
        break;
    case AST_FUN_PARAMS:
        printf("AST_FUN_PARAMS");
        break;
    case AST_COMM_SEQ:
        printf("AST_COMM_SEQ");
        break;
    case AST_ATTRIB:
        printf("AST_ATTRIB");
        break;
    case AST_ATTRIB_VEC:
        printf("AST_ATTRIB_VEC");
        break;
    case AST_READ:
        printf("AST_READ");
        break;
    case AST_PRINT:
        printf("AST_PRINT");
        break;
    case AST_PRINT_PARAMS:
        printf("AST_PRINT_PARAMS");
        break;
    case AST_RETURN:
        printf("AST_RETURN");
        break;
    case AST_IF:
        printf("AST_IF");
        break;
    case AST_IF_ELSE:
        printf("AST_IF_ELSE");
        break;
    case AST_WHILE:
        printf("AST_WHILE");
        break;
    case AST_LOOP:
        printf("AST_LOOP");
        break;
    default:
        printf("AST_UNKNOWN");
        break;
    }

    if (node->symbol)
    {
        printf("(%s)", node->symbol->text);
    }

    printf("\n");
    for (int i = 0; i < MAX_CHILDREN; i++)
        AST_print(node->child[i], level + 1);
}

void file_print(char *str, FILE *out)
{
    fprintf(out, "%s", str);
    return;
}

void decompile(AST* node, FILE *out)
{
    if (!node)
    {
        return;
    }
    
    switch(node->type)
    {
        case AST_SYMBOL:
            file_print(node->symbol->text, out);
            break;
        case AST_SYMBOL_VECTOR:
            decompile(node->child[0], out);
            file_print("[(", out);
            decompile(node->child[1], out);
            file_print(")]", out);
            break;
        case AST_ADD:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") + (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_SUB:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") - (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_MUL:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") * (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_DIV:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") / (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_LT:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") < (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_GT:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") > (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_OR:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") | (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_AND:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") ^ (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_LE:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") <= (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_GE:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") >= (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_EQ:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") == (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_DIF:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(") != (", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_UN_MIN:
            file_print("-(", out);
            decompile(node->child[0], out);
            file_print(")", out);
            break;
        case AST_UN_NEG:
            file_print("~(", out);
            decompile(node->child[0], out);
            file_print(")", out);
            break;
        case AST_FUN_CALL:
            decompile(node->child[0], out);
            file_print("(", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_LPARAM:
            file_print("(", out);
            decompile(node->child[0], out);
            file_print(")", out);
            if(node->child[1])
            {
                file_print(",", out);
                decompile(node->child[1], out);
            }
            break;
        case AST_LDECL:
            decompile(node->child[0], out);
            file_print(";\n", out);
            decompile(node->child[1], out);
            break;
        case AST_DECLVAR_NOT_VECTOR:
            decompile(node->child[0], out);
            file_print("=", out);
            decompile(node->child[1], out);
            file_print(":", out);
            decompile(node->child[2], out);
            break;
        case AST_DECLVAR_VECTOR:
            decompile(node->child[0], out);
            file_print("= ", out);
            decompile(node->child[1], out);
            file_print("[", out);
            decompile(node->child[2], out);
            file_print("]", out);
            if(node->child[3])
            {
                file_print(":", out);
                decompile(node->child[3], out);
            }
            break;
        case AST_LVECTOR:
            decompile(node->child[0], out);
            if(node->child[1])
            {
                file_print(" ", out);
                decompile(node->child[1], out);
            }
            break;
        case AST_FUN:
            decompile(node->child[0], out);
            file_print("{", out);
            decompile(node->child[1], out);
            file_print("}", out);
            break;
        case AST_FUN_HEADER:
            decompile(node->child[0], out);
            file_print("(", out);
            decompile(node->child[1], out);
            file_print(")=", out);
            decompile(node->child[2], out);
            break;
        case AST_FUN_PARAMS:
            decompile(node->child[0], out);
            file_print("=", out);
            decompile(node->child[1], out);
            if(node->child[2])
            {
                file_print(",", out);
                decompile(node->child[2], out);
            }
            break;
        case AST_COMM_SEQ:
            decompile(node->child[0], out);
            if(node->child[1])
            {
                file_print(" ", out);
                decompile(node->child[1], out);
            }
            break;
        case AST_ATTRIB:
            decompile(node->child[0], out);
            file_print("=(", out);
            decompile(node->child[1], out);
            file_print(")", out);
            break;
        case AST_ATTRIB_VEC:
            decompile(node->child[0], out);
            file_print("[(", out);
            decompile(node->child[1], out);
            file_print(")]=(", out);
            decompile(node->child[2], out);
            file_print(")", out);
            break;
        case AST_READ:
            file_print("read ", out);
            decompile(node->child[0], out);
            break;
        case AST_PRINT:
            file_print("print ", out);
            decompile(node->child[0], out);
            if(node->child[1])
            {
                file_print(",", out);
                decompile(node->child[1], out);
            }
            break;
        case AST_PRINT_PARAMS:
            decompile(node->child[0], out);
            if(node->child[1])
            {
                file_print(",", out);
                decompile(node->child[1], out);
            }
            break;
        case AST_RETURN:
            file_print("return (", out);
            decompile(node->child[0], out);
            file_print(")", out);
            break;
        case AST_IF:
            file_print("if (", out);
            decompile(node->child[0], out);
            file_print(") then {", out);
            decompile(node->child[1], out);
            file_print("}", out);
            break;
        case AST_IF_ELSE:
            file_print("if (", out);
            decompile(node->child[0], out);
            file_print(") then {", out);
            decompile(node->child[1], out);
            file_print("} else {", out);
            decompile(node->child[2], out);
            file_print("}", out);
            break;
        case AST_WHILE:
            file_print("while (", out);
            decompile(node->child[0], out);
            file_print(") {", out);
            decompile(node->child[1], out);
            file_print("}", out);
            break;
        case AST_LOOP:
            file_print("loop (", out);
            decompile(node->child[0], out);
            file_print(":(", out);
            decompile(node->child[1], out);
            file_print("),(", out);
            decompile(node->child[2], out);
            file_print("),(", out);
            decompile(node->child[3], out);
            file_print(")) {", out);
            decompile(node->child[4], out);
            file_print("}", out);
            break;
        default:
            file_print("Unknown AST node found, ERROR", stderr);
            exit(1);
            break;
    }
}
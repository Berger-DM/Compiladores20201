#include "semantic.h"

int SemanticErrors = 0;

void checkAndSetDeclarations(AST *node)
{
    int i;
    if(node == 0) return;

    switch(node->type)
    {
        case AST_DECLVAR_NOT_VECTOR:
            if (node->symbol)
            {
                if (node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic Error: Variable %s already declared\n", 
                    node->symbol->text);
                    ++SemanticErrors;
                }
            }
            node->symbol->type = SYMBOL_VARIABLE;
            break;
        case AST_DECLVAR_VECTOR:
            if (node->symbol)
            {
                if (node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic Error: Variable %s already declared\n", 
                    node->symbol->text);
                    ++SemanticErrors;
                }
            }
            node->symbol->type = SYMBOL_VECTOR;
            break;
        case AST_FUN:
            if (node->symbol)
            {
                if (node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic Error: Function %s already declared\n", 
                    node->symbol->text);
                    ++SemanticErrors;
                }
            }
            node->symbol->type = SYMBOL_FUNCTION;
            break;
    }

    for (i = 0; i < MAX_CHILDREN; i++)
    {
        checkAndSetDeclarations(node->child[i]);
    }
}

void checkUndeclared();
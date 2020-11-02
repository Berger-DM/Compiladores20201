#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "lex.yy.h"

extern int SemanticErrors;

void checkAndSetDeclarations(AST *node);
void checkUndeclared();

#endif

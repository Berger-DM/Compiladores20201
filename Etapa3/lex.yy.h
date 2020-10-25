#include "ast.h"
#include "hash.h"
#include "y.tab.h"

#define FALSE 0
#define TRUE 1

int isRunning(void);
int getLineNumber(void);
int yylex(void);
void initMe(void); 

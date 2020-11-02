//Autor: Nicolas Mauro de Moreira Bohnenberger - 00207160
#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"

int yylex(void);
void initMe(void);
int getLineNumber(void);
int isRunning(void);
void hashPrint(void);

extern char *yytext;
extern FILE *yyin;

void main(int argc, char ** argv)
{
    initMe();

    if (argc<2)
    {
        fprintf(stderr, "Call: etapa2 fileName\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == 0)
    {
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        exit(2);
    }

	yyparse();
	hashPrint();
	
	exit(0);
}

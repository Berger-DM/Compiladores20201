#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
//#include "yy.lex.h"

int yylex(void);
void initMe(void);
int getLineNumber(void);
int isRunning(void);

extern char *yytext;
extern FILE *yyin;

int main(int argc, char ** argv)
{
    if (argc<2)
    {
        fprintf(stderr, "Call: etapa1 fileName\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == 0)
    {
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        exit(2);
    }

    initMe();

	int tok;
	while (isRunning())
    {
	    tok = yylex();
	    switch(tok)
        {
            case KW_INT: printf("Achei uma palavra reservada int\n"); break;
        }
    }
}

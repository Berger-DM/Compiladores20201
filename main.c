//Autor: Nicolas Mauro de Moreira Bohnenberger - 00207160
#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

int yylex(void);
void initMe(void);
int getLineNumber(void);
int isRunning(void);
void hashPrint(void);

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
            case KW_CHAR:		printf("Achei uma palavra reservada char na linha %d\n", getLineNumber()); break;
			case KW_INT:		printf("Achei uma palavra reservada int na linha %d\n", getLineNumber()); break;
			case KW_FLOAT:		printf("Achei uma palavra reservada float na linha %d\n", getLineNumber()); break;
			case KW_BOOL:		printf("Achei uma palavra reservada bool na linha %d\n", getLineNumber()); break;
			case KW_IF: 		printf("Achei uma palavra reservada if na linha %d\n", getLineNumber()); break;
			case KW_THEN:		printf("Achei uma palavra reservada then na linha %d\n", getLineNumber()); break;
			case KW_ELSE:		printf("Achei uma palavra reservada else na linha %d\n", getLineNumber()); break;
			case KW_WHILE:		printf("Achei uma palavra reservada while na linha %d\n", getLineNumber()); break;
			case KW_LOOP:		printf("Achei uma palavra reservada loop na linha %d\n", getLineNumber()); break;
			case KW_READ:		printf("Achei uma palavra reservada read na linha %d\n", getLineNumber()); break;
			case KW_PRINT:		printf("Achei uma palavra reservada print na linha %d\n", getLineNumber()); break;
			case KW_RETURN:		printf("Achei uma palavra reservada return na linha %d\n", getLineNumber()); break;
			case OPERATOR_LE: 	printf("Achei um operador LE na linha %d\n", getLineNumber()); break;
			case OPERATOR_GE: 	printf("Achei um operador GE na linha %d\n", getLineNumber()); break;
			case OPERATOR_EQ: 	printf("Achei um operador EQ na linha %d\n", getLineNumber()); break;
			case OPERATOR_DIF: 	printf("Achei um operador DIF na linha %d\n", getLineNumber()); break;
			case TK_IDENTIFIER:	printf("Achei o identificador %s na linha %d\n", yytext, getLineNumber()); break;
			case LIT_INTEGER:	printf("Achei o literal inteiro %s na linha %d\n", yytext, getLineNumber()); break;
			case LIT_FLOAT:		printf("Achei o literal real %s na linha %d\n", yytext, getLineNumber()); break;
			case LIT_TRUE:		printf("Achei um TRUE na linha %d\n", getLineNumber()); break;
			case LIT_FALSE:		printf("Achei um FALSE na linha %d\n", getLineNumber()); break;
			case LIT_CHAR:		printf("Achei o char %s na linha %d\n", yytext, getLineNumber()); break;
			case LIT_STRING:	printf("Achei a string %s na linha %d\n", yytext, getLineNumber()); break;
			default:		printf("Encontrei o caractere especial %s na linha %d\n", yytext, getLineNumber()); break;
        }
    }
	hashPrint();
	
	exit(0);
}

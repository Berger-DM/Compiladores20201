# Aluno: Nicolas Mauro de Moreira Bohnenberger - 00207160
# UFRGS - Compiladores B - Marcelo Johann - 2020/ERE - Etapa 3
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa3: main.o hash.o lex.yy.o y.tab.o ast.o
	gcc main.o hash.o lex.yy.o y.tab.o ast.o -o etapa3

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c
	
ast.o: ast.c
	gcc -c ast.c

lex.yy.o: lex.yy.c y.tab.o
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.c: scanner.l
	flex scanner.l

y.tab.c: parser.y
	yacc -d parser.y

clean:
	rm *.o etapa3 lex.yy.c y.tab.c

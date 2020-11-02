ETAPA=etapa4

${ETAPA}: lex.yy.o hash.o main.o y.tab.o ast.o semantic.o
	gcc -o ${ETAPA} lex.yy.o hash.o y.tab.o ast.o semantic.o

main.o: main.c
	gcc -c main.c

semantic.o: semantic.c
	gcc -c semantic.c

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
	yacc parser.y -d

clean:
	rm *.o lex.yy.c y.tab.c y.tab.h ${ETAPA}

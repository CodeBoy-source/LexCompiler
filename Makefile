LEX=flex
CC=gcc

scanner: lex.yy.c scanner.o
	$(CC) scanner.o lex.yy.c -o scanner

scanner.c: scanner.h
	$(CC) -c  scanner.c -I scanner.h

lex.yy.c: scanner.l
	$(LEX) -o lex.yy.c scanner.l

.PHONY : remake
remake :
	-rm scanner scanner.o lex.yy.c && make


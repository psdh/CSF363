all:
	gcc -c -g parser.c -w
	gcc -c -g lexer.c -o lexer.o
	gcc -o parser parser.o lexer.o



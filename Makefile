CC = gcc

lexer:
	gcc -g -o lexer lexer.c

parser: lexer
	gcc -g -o parser parser.c lexer

clean:
	rm parser a.out lexer

output: lexer.o parser.o driver.o firstandfollow.o
	gcc lexer.o parser.o driver.o -o stage1exe

lexer.o: lexer.c lexer.h
	gcc -c -g -w lexer.c

parser.o: parser.c parser.h lexer.h parserDef.h lexerDef.h
	gcc -c -g -w parser.c

driver.o: driver.c parser.h parserDef.h lexer.h  lexerDef.h
	gcc -c -g -w driver.c

firstandfollow.o: firstandfollow.c
	gcc firstandfollow.c -o firstandfollow

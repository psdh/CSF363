gcc -w -g parser.o lexer.o -c semantic.c -o semantic.o
gcc -g -w parser.o semantic.o lexer.o ast.c -o ast

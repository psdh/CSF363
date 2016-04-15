gcc -w parser.o lexer.o -c symboltable.c -o symboltable.o
gcc -g -w parser.o  symboltable.o lexer.o ast.c -o ast

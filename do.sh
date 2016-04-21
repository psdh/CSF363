gcc -w -g -c codegen.c -o codegen.o
gcc -w -g -c symboltable.c -o symboltable.o
gcc -w -g -c typechecker.c -o typechecker.o
gcc -w -g -c semantic.c -o semantic.o
gcc -w -g codegen.o parser.o semantic.o symboltable.o typechecker.o lexer.o ast.c -o ast

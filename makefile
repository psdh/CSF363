# Batch No: 47
# Gyanendra Mishra 2013A7PS126P
# Prabhjyot Singh Sodhi 2013A7PS151P
# Filename:makefile

CC=gcc

output: lexer.o parser.o ast.o symboltable.o typechecker.o semantic.o codegen.o driver.o firstandfollow.o
	gcc lexer.o parser.o ast.o symboltable.o typechecker.o semantic.o codegen.o driver.o -o toycompiler

lexer.o: lexer.c lexer.h
	gcc -c -g -w lexer.c

parser.o: parser.c parser.h lexer.h parserDef.h lexerDef.h
	gcc -c -g -w parser.c


ast.o: ast.c ast.h
	gcc -c -g -w ast.c

symboltable.o: symboltable.h symboltable.c symboltabledef.h
	gcc -c -g -w symboltable.c

typechecker.o: typechecker.h typechecker.c
	gcc -c -g -w typechecker.c

semantic.o: semantic.h semantic.c
	gcc -c -g -w semantic.c


codegen.o: codegen.h codegen.c
	gcc -c -g -w codegen.c

driver.o: driver.c codegen.h semantic.h typechecker.h symboltable.h symboltabledef.h ast.h parser.h parserDef.h lexer.h  lexerDef.h
	gcc -c -g -w driver.c

firstandfollow.o: firstandfollow.c
	gcc firstandfollow.c -o firstandfollow

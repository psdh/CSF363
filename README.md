# Toy Compiler

This is a toy compiler written in C for course CSF363 at **BITS Pilani**

**Known Issues**: Crashes with GCC 5.3 (ships with Ubuntu 5.3)

Tested with GCC 4.9 and below. It works perfectly for them!
Follows the language given in *grammar.txt* and *LanguageSpecifications.pdf*.

## Running Istructions

```bash
$ make #compile the compiler
$ ./toycompiler <filename> #compiles the code
$ ./run #converts the code.asm to machine code and executes
```
# Compiler

This is a toy compiler written in C for course CSF363 at **BITS Pilani**

**Known Issues**: Crashes with GCC 5.3 (ships with Ubuntu 16.04)

Tested with GCC 4.9 and below. It works perfectly for them!
The compiler follows the language given in *grammar.txt* and *LanguageSpecifications.pdf*.

## Running Instructions

```bash
$ make #compile the compiler
$ ./toycompiler <filename> #compiles the code
$ ./run.sh #converts the code.asm to machine code and executes
```

Use with caution.
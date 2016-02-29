// filename: lexer.c
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

// File lexer.c  : This file contains following functions

#include "lexerDef.h"
#define true 1
#define false 0

/* getStream function
 * FILE *getStream(FILE *fp, buffer B, buffersize k)
 * This function takes the  input from the file pointed to by 'fp'. This file is the source code written in the
 * given language. The function uses efficient technique to bring the fixed sized piece (of size k)  of source
 * code into the buffer B  for processing so as to avoid intensive I/O operations mixed with CPU intensive
 * tasks. The function also maintains the file pointer after every access so that it can get more data into
 * the memory on demand.
 */
FILE *getStream(FILE *fp, buffer b, buffersize k)
{
    if (!fp.feof())
        fread(b, 1, k, fp);

    return fp;
}

/* getNextToken function
 * tokenInfo  getNextToken(FILE *fp)
 * This function reads the input character stream and uses efficient mechanism to recognize lexemes.
 * The function tokenizes the lexeme appropriately and returns all relevant information it collects in this
 * phase (lexical analysis phase) encapsulated as  tokenInfo. The function also displays lexical errors
 * appropriately. The input parameters are made flexible and students can select appropriate input parameters.
 * The function also takes care of ignoring the white spaces and comments.
 */
tokenInfo getNextToken(FILE *fp, buffer b, int offset, int lineNo)
{

}

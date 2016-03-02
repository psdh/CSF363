// filename: lexer.c
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

// File lexer.c  : This file contains following functions

#include "lexerDef.h"
#define true 1
#define false 0
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
/*
	Updates line number as '\n' is encountered.
	On finding a token it returns the token.
	The global variable offset and state is continuously updated.
	Let the parser change the state back to 1 for further parsing.
*/
tokenInfo getNextToken(FILE *fp, buffer b, int k)
{
	buffer lexeme = (buffer) malloc(k*sizeof(buffer));
	int i = 0;
	tokenInfo token;
	int error = 0;

	while(1){
		// Buffer is empty let's put something inside it
		if (offset == k){
			fp = getStream(fp, b, k);
			offset = 0;
			//@gyani exit from here
			if(fp.feof()){
				printf("Scanning Complete!\n");
				break;
			}
		}
		switch(state){
			case 1:
				switch(buffer[offset]){
					case '\t':
						state=1;
						offset++;
						break;
					case ' ':
						state=1;
						offset++;
						break;
					case '\n':
						state=1;
						lineNo++;
						offset++;
						break;
					case '%':
						state=2;
						offset++;
						break;
					case '<':
						state=3;
						offset++;
						break;
					case 'a':
					case 'e':
					case 'f':
					case 'g':
					case 'h':
					case 'i':
					case 'j':
					case 'k':
					case 'l':
					case 'm':
					case 'n':
					case 'o':
					case 'p':
					case 'q':
					case 'r':
					case 's':
					case 't':
					case 'u':
					case 'v':
					case 'w':
					case 'x':
					case 'y':
					case 'z':
						state = 8;
						lexeme[i++]=buffer[offset++];
						break;
					case 'b':
					case 'c':
					case 'd':
						state = 9;
						lexeme[i++]=buffer[offset++];
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 13;
						lexeme[i++] = buffer[offset++];
						break;
					case '_':
						state = 17;
						offset++;
						break;
					case '#':
						state = 20;
						offset++;
						break;
					case '[':
						state = 22;
						offset++;
						token.id = 20;
						token.lineNo = lineNo;
						token.name = "[";
						return token;
					case ']':
						state = 23;
						offset++;
						token.id = 21;
						token.lineNo = lineNo;
						token.name = "]";
						return token;
					case ';':
						state = 24;
						offset++;
						token.id = 26;
						token.lineNo = lineNo;
						token.name = ";";
						return token;
					case ':':
						state = 25;
						offset++:
						token.id = 27;
						token.lineNo = lineNo;
						token.name = ":";
						return token;
					case '.':
						state = 26;
						offset++;
						token.id = 28;
						token.lineNo = lineNo;
						token.name = ".";
						return token;
					case '(':
						state = 27;
						offset++;
						token.id = 30;
						token.lineNo = lineNo;
						token.name = "(";
						return token;
					case ')':
						state = 28;
						offset++;
						token.id = 31;
						token.lineNo = lineNo;
						token.name = ")";
						return token;
					case '+':
						state = 29;
						offset++;
						token.id = 38;
						token.lineNo = lineNo;
						token.name = "+";
						return token;
					case '-':
						state = 30;
						offset++;
						token.id = 39;
						token.lineNo = lineNo;
						token.name = "-";
						return token;
					case '*':
						state = 31;
						offset++;
						token.id = 40;
						token.lineNo = lineNo;
						token.name = "*";
						return token;
					case '/':
						state = 32;
						offset++
						token.id = 41;
						token.lineNo = lineNo;
						token.name = "/";
						return token;
					case '&':
						state = 33;
						offset++;
						break;
					case '@':
						state = 36;
						offset++;
						break;
					case '~':
						state = 39;
						offset+;
						token.id = 48;
						token.lineNo = lineNo;
						token.name = "~";
						return token;
					case '=':
						state = 40;
						offset++;
						break;
					case '>':
						state = 42;
						offset++;
						break;
					case '!':
						state = 44;
						offset++;
						break;
					default:
						printf("Unsuported character %c at line %d",buffer[offset], lineNo);
						error = 1;
						break;
				}
			// comments
			case 2:
				while(buffer[++offset]!='\n'){
					if (offset == k || buffer[offset] == '\0'){
						fp = getStream(fp, b, k);
						// comment at end of file
						if (fp.feof()){
							break;
						}
						offset = 0;
					}
				};
				token.id = 2;
				token.lineNo = lineNo;
				token.name = "COMMENT";
				lineNo++;
				return token;
			// <, <--, <=
			case 3:
				switch(buffer[offset]){
					case '-':
						//@Doubt can parts of <-- be on a new line?
						if(offset+2!=k && buffer[offset+1] == '-' && buffer[offset+2] == '-'){
							offset+=3;
							token.id = 1;
							token.lineNo=lineNo
							token.name = "<---";
							state = 6;
							return token;
						}
						else if(offset+1!=k && buffer[offset+1] == '-'){
							fp = getStream(fp, b, k);
							if(fp.feof()){
								printf('Program ended with Unsuported symbol %c at line %d', buffer[offset+1], lineNo);
								error = 1;
								break;
							}
							offset=0;
							if(buffer[offset]=='-'){
								offset++;
								token.id = 1;
								token.lineNo=lineNo;
								token.name = "<---"
								state =6;
								return token
							}
						}
						else if(offset==k){
							fp = getStream(fp, b, k);
							if (fp.feof()){
								printf('Program ended with Unsuported symbol %c at line %d', buffer[offset+1], lineNo);
								error = 1;
								break;
							}
							offset=0;
							if(buffer[offset] == '-' && buffer[offset+1] == '-'){
								offset+=2;
								token.id = 1;
								token.lineNo=lineNo;
								token.name = "<---"
								state = 6;
								return token;
							}
							else{
								printf("Unsuported character %c at line %d",buffer[offset], lineNo);
								error=1;
								break;
							}
						}
						else{
							printf("Unsuported character %c at line %d",buffer[offset], lineNo);
							error=1;
							break;
						}
					case '=':
						offset++;
						token.id = 50;
						token.lineNo = lineNo;
						token.name = "<=";
						state = 7;
						return token;
					default:
						//offset not increased in this case as the character isn't parsed and will be parsed later.
						token.id= 49;
						token.lineNo= lineNo;
						token.name = '<'
						state = 3;
						return tokenInfo;
				}

			case 8:
				while(97 <= buffer[offset] && buffer[offset] <= 122){
					if (offset == k || buffer[offset] == '\0'){
						fp = getStream(fp, b, k);
						// comment at end of file
						if (fp.feof()){
							break;
						}
						offset=0;
					}
					lexeme[i++] = buffer[offset++];
				}
				token.id = 3;
				token.lineNo=lineNo;
				token.name = lexeme;
				// empty the lexeme array
				i = 0;
				memset(lexeme, 0, sizeof(lexeme));
				return token;
			case 9:
				//a-z kuch aaya
				if (97 <= buffer[offset] && buffer[offset]<= 122){
					state = 8;
					lexeme[i++] = buffer[offset++];
					// why repeat the case 8 code, let it take care now.
					break;
				}
				// some number comes up
				else if(48 <= buffer[offset] && buffer[offset]<=57){
					state = 10;
					lexeme[i++] = buffer[offset++];
					break;
				}
				//something random pops in, we are in a final state so thngs are good
				else{
					// can't increase offset as had unsupported symbol but was ata final state
					// change state to 1 @sodhi warna scene hoga
					// unused symbol jaega agar kahin accept hua toh sahi
					// rethink this @gyani
					token.id = 3;
					token.lineNo=lineNo;
					token.name = lexeme;
					memset(lexeme, 0, sizeof(lexeme))
					i=0;
					return token;
				}
			case 10:
				//switch case increases lines for no reason :(
				switch(buffer[offset]){
					case 'b':
					case 'c':
					case 'd':
						state = 11;
						lexeme[i++] = buffer[offset++];
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
						state = 12;
						lexeme[i++] = buffer[offset++];
						break;
					default:
						//final state pe kuch random aaya
						token.id = 4;
						token.name = lexeme;
						token.lineNo = lineNo;
						memset(lexeme, 0, sizeof(lexeme))
						i=0;
						return token;
				}
			case 11:
				//b or d hi aae ja raha hai
				while(98<=buffer[offset] && buffer[offset]<=100){
					if (offset == k || buffer[offset] == '\0'){
						fp = getStream(fp, b, k);
						// comment at end of file
						if (fp.feof()){
							break;
						}
						offset=0;
					}
					lexeme[i++] = buffer[offset++];
				}
				// number aaya matlab state transition
				if (48 <=buffer[offset] || buffer[offset]<=57){
					state = 12;
					lexeme[i++] = buffer[offset++];
					break;
				}
				else{
					// something apart form b-d, number showed up, abhi tak ka jitna useful hai
					//usko send as token, not increased offset as current char is weird and will be parsed in the next run
					token.id = 4;
					token.name = lexeme;
					token.lineNo = lineNo;
					memset(lexeme, 0, sizeof(lexeme));
					i=0;
					return token;
				}
			case 12:
				//@gyani to str copy or not
				//@gyani length of field?
				whie(48<= buffer[offset] &&  buffer[offset]<=57){
					if (offset == k || buffer[offset] == '\0'){
						fp = getStream(fp, b, k);
						// comment at end of file
						if (fp.feof()){
							break;
						}
						offset=0;
					}
					lexeme[i++] = buffer[offset++];
				}
				if(strlen(lexeme) > 20){
					printf("identifier at line %d is longer than allowed limit\n", lineNo);
					error = 1;
					break;
				}
				token.id = 4;
				token.name = lexeme;
				token.lineNo = lineNo;
				memset(lexeme, 0, sizeof(lexeme));
				i = 0;
				return token;
			case 13:
				while(48<= buffer[offset]&& buffer[offset]<=57){
					if (offset == k || buffer[offset] == '\0'){
						fp = getStream(fp, b, k);
						// comment at end of file
						if (fp.feof()){
							break;
						}
						offset=0;
					}
					lexeme[i++] = buffer[offset++];
				}
				if(buffer[offset] == '.'){
					state = 14;
					lexeme[i++] = buffer[offset++];
					break;
				}
				token.id = 5;
				token.name = lexeme;
				token.lineNo = lineNo;
				memset(lexeme, 0, sizeof(lexeme));
				return token;
			case 14:
				if(offset+1!=k){
					if (48 <= buffer[offset] && buffer[offset]<=57 && 48 <= buffer[offset+1] && buffer[offset+1]<=57){
						state = 16;
						lexeme[i++] = buffer[offset++];
						lexeme[i++] = buffer[offset++];
						token.id = 6;
						token.name= lexeme;
						token.lineNo=lineNo++;
						i = 0;
						memset(lexeme, 0, sizeof(lexeme));
						return token;
					}
				}
				else if(offset+1==k){
					if(48 <= buffer[offset] && buffer[offset]<=57){
						state = 15;
						lexeme[i++] = buffer[offset++];
						fp = getStream(fp, b, k);
						if (fp.feof()){
							printf("Program ended while fetching real number\n");
							error =1;
							break;
						}
						offset=0;
						if (48 <= buffer[offset] && buffer[offset]<=57){
							state = 16;
							lexeme[i++] = buffer[offset++];
							token.id = 6;
							token.name = lexeme;
							token.lineNo = lineNo;
							i = 0;
							memset(lexeme, 0, sizeof(lexeme));
							return token;
						}
						else{
							printf("Unknown character %c on line %d while parsing real number",buffer[offset], lineNo);
							error=1;
							break;
						}
					}
				}
				else{
					printf("Unknown character %c on line %d while parsing real number",buffer[offset], lineNo);
					error = 1;
					break;
				}
			case 17:
		}

		if(error==1){
			break;
		}
	}
}

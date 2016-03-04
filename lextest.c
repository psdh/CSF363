#include "lexer.h"
#include "lexerDef.h"
#include "lexer.c"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	FILE * fp;
	fp = fopen("testcase3.txt", "r");
	//buffer size ka scene
	buffersize k = 25;
	lineNo=1;
	state = 1;
	tokenInfo token = getNextToken(fp, b, k);
	while(strcmp(token.name, "ENDOFFILE")!=0){
		printf("\nToken:%s\nID:%d\nLineNo:%d\n\n",token.name,token.id,token.lineNo);
		state = 1;
		token = getNextToken(fp, b, k);
	}
	return 0;
}
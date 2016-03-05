#include<stdio.h>
#include<string.h>
#include <stdlib.h>
// list of terminals and non terminals that have been processed
char done_firsts[500][500];
char done_follows[500][500];
// their corresponding firsts
char firsts[500][500];
char follows[500][500];
// list of seen terminals and non terminals
char seen[110][110];
char nonTerminals[110][110];
char terminals[110][110];

int done_count = 0;
int df_count = 0;
int firsts_count = 0;
int follows_count = 0;
int seen_count = 0;
int non_terminal_count = 0;
int terminal_count = 0;

int exists(char * name){
    int i = 0;
    while(i != seen_count){
        if(strcmp(seen[i], name) == 0 ){
            return 1;
        }
        i++;
    }

    return 0;
}

int isNonTerminal(char * name){
    int i = 0;
    while(i != non_terminal_count){
        if(strcmp(nonTerminals[i], name) == 0 ){
            return 1;
        }
        i++;
    }

    return 0;
}

int isTerminal(char * name){
    if (isNonTerminal(name) == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int isDone(char * name){
    int i = 0;
    while(i != done_count){
        if(strcmp(done_firsts[i], name) == 0 ){
            return i;
        }
        i++;
    }
    return -1;
}

int epsilonInFirst(char  * name){
    int position = isDone(name);
    char rules[500];
    strcpy(rules, firsts[position]);
    char * token = strtok(rules , " ");
    while(token!=NULL){
        if (strcmp("eps", token) == 0){
            return 1;
        }
        token = strtok(NULL, " ");
    }
    return 0;
}

int alreadyThere(char * word, char buffer[500][500], int ff){
    int i =0;
    while(i!=ff){
    	printf("%s\n", buffer[i]);
        if(strcmp(word, buffer[i])==0)
            return i;
        i++;
    }
    return -1;
}

int removeFromString(char str[500], char *str_to_remove)
{
    char *buf;

    char new_str[500];
    memset(new_str, 0, sizeof(new_str));
    buf = strtok(str, " ");
    while(buf)
    {
        if(strcmp(buf, str_to_remove) != 0)
        {
            strcat(new_str, buf);
            strcat(new_str, " ");
        }
        buf = strtok(NULL, " ");
    }
    strcpy(str, new_str);

    return 0;
}

// A -- > B C D
// suppose B-->
void getFirst(char * rule, char * Filename){
	// printf("%s\n", rule);
	int has_eps_rule = 0;
	char temp_seen[500][500];
	int i = 0;
    if(isDone(rule) == -1){
        if (isTerminal(rule) == 1) {
	        if(alreadyThere(rule, temp_seen, i)==-1){
	            strcpy(done_firsts[done_count],rule);
	            strcpy(firsts[done_count++],rule);
	            strcpy(temp_seen[i++], rule);
	        }
        }
        else{
            FILE * fp = fopen(Filename, "r");
            char * line = NULL;
	        size_t len = 0;
	        ssize_t read;
	        char left[100];
	        char right[100];
            char buffer[500];
            strcpy(buffer, "");
            while((read = getline(&line, &len, fp)) != -1){
                sscanf(line, "%s ===> %[^\n\t]", left, right);
                if (strcmp(left, rule)== 0){
                    if (strcmp(right, "eps") == 0){
		                // printf("%s\t%s\n", rule, right);
                    	has_eps_rule = 1;
                    	if(alreadyThere("eps", temp_seen, i)== -1){
	                        strcat(buffer, "eps");
	                        strcat(buffer, " ");
	                        strcpy(temp_seen[i++], "eps");
		                }
                    }
                    else{
                        // printf("%s\n", right);
                        char * token;
                        char *saveptr;
                        token = strtok_r(right , " ", &saveptr);
                        char copy[100];
                        strcpy(copy, token);
                        while(token != NULL){
                            if(strcmp(rule, copy) == 0){
	                            token = strtok_r(NULL, " ", &saveptr);
	                            //other statements recursion due to statements going to eps
	                            if(token!=NULL){
	                                strcpy(copy, token);
	                            }
                            	// printf("%s\n", "YAHS");
                            	continue;
                            }
                            if(isTerminal(copy)){
                                if(alreadyThere(copy, temp_seen, i)==-1){
                                    strcat(buffer, copy);
                                    strcat(buffer, " ");
                                    strcpy(temp_seen[i++], copy);
                                }
                                break;
                            }
                            else if(isDone(copy)!=-1 && epsilonInFirst(copy) == 0){
                                if(alreadyThere(copy, temp_seen, i)==-1){
                                    char* token = strtok(firsts[isDone(copy)]);
                                    while(token!=NULL){
                                    	
                                    }
                                    strcat(buffer, firsts[isDone(copy)]);
                                    strcat(buffer, " ");
                                    strcpy(temp_seen[i++], copy);
                                }
                                break;
                            }
                            else if(isDone(copy)!=-1){
                                if(alreadyThere(copy, temp_seen, i)==-1){
                                    strcat(buffer, firsts[isDone(copy)]);
                                    strcat(buffer, " ");
                                    strcpy(temp_seen[i++], copy);
                                }
                            }
                            else{
                                // char * fname;
                                // printf("%s Called %s\n", rule, copy);
                                getFirst(copy, Filename);
                                if(alreadyThere(copy, temp_seen, i)==-1){
                                    strcat(buffer, firsts[isDone(copy)]);
                                    strcat(buffer, " ");
                                    strcpy(temp_seen[i++], copy);
                                }
                                if (epsilonInFirst(copy) == 0){
                                    break;
                                }
                            }
                            // printf("%s\n",temp23 );
                            token = strtok_r(NULL, " ", &saveptr);
                            //other statements recursion due to statements going to eps
                            // printf("%s\t%s\n", token, rule);
                            if(token!=NULL){
                                strcpy(copy, token);
                                if (has_eps_rule != 1){
                                	int position_of_eps = alreadyThere("eps", temp_seen, i);
                                	printf("%d\t%s\n", position_of_eps, rule);
                                	if(position_of_eps !=-1){
                                		// printf("%s\n", "GANDAGI");
                                		strcpy(temp_seen[position_of_eps], "GARBAGEDATA");
                                		removeFromString(buffer, "eps");
                                		// printf("%/s\n", buffer);
                                	}
                                }
                            }
                        }
                    }
                }
            }
        fclose(fp);
        strcpy(firsts[done_count], buffer);
        strcpy(done_firsts[done_count++],rule);
        }
    }
}

int followFound(char * rule){
	return 0;
}

void getFollow(char * rule, char * Filename){
	if (followFound(rule) == 0){
		char temp_seen[500];
		int i = 0;
		FILE * fp = fopen(Filename, "r");
		char * line = NULL;
        size_t len = 0;
        ssize_t read;
        char left[100];
        char right[100];
        while((read = getline(&line, &len, fp)) != -1){
	        sscanf(line, "%s ===> %[^\n\t]", left, right);
	        char * saveptr;
	        char * token;
	        token = strtok_r(right , " ", &saveptr);
	        int found= 0 ;
	        while(token!=NULL){
	        	//token is found
	        	if (strcmp(token, rule) == 0)
	        	{
	        		found = 1;
	        	}
	        	else if(found == 1 ){

	        	}
	        	token = strtok_r(right , " ", &saveptr);
	        	if(token == NULL && strcmp(token, rule)){
	        		if(followFound(left)){
	        			strcpy(follows[df_count++], follows[followFound(left)]);
	        			strcpy(follows[df_count++], " ");
	        			strcpy(done_follows[df_count++], rule);
	        		}
	        	}
	        }
        }
	}//outmostif
}

void first(char  * Filename){

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char left[100];
    char right[100];

    fp = fopen(Filename, "r");
    if(fp == NULL){
        printf("Invalid source file\n");
        return;
    }

    while((read = getline(&line, &len, fp)) != -1){

        sscanf(line, "%s ===> %[^\n\t]", left, right);

        if (exists(left) == 0){
            strcpy(seen[seen_count++], left);
        }

        if (isNonTerminal(left) == 0){
            strcpy(nonTerminals[non_terminal_count++], left);
        }

        char * token = strtok(right , " ");

        while(token!=NULL){
            if (exists(token) == 0 ){
                // printf("%s\n", token);
                strcpy(seen[seen_count++], token);
            }
            token = strtok(NULL, " ");
        }

    }

    fclose(fp);
    int i =0;

    while(i!= seen_count){
        // printf("RUle:%s\n",seen[i] );
        if (isDone(seen[i]) != 0){
            getFirst(seen[i], Filename);
        }
        i++;
    }
    i=0;

    while(i!= done_count){
        printf("%s\t", done_firsts[i]);
        printf("%s\n", firsts[i++]);
        // i++;
    }

}



int main(int argc, char  * argv[]){
    if (argc < 2){
        printf("Run ./firstandfollow file.txt");
        return 0;
    }
    FILE * fp = fopen(argv[1], "r");

    if (fp == NULL){
        printf("File Not Found\n");
        return 0;
    }
    fclose(fp);

    first(argv[1]);

}
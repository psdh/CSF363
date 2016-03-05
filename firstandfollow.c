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
	            strcpy(firsts[done_count],rule);
	            strcat(firsts[done_count++]," ");
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
            	char lineBuffer[500];
            	strcpy(lineBuffer, "");
                sscanf(line, "%s ===> %[^\r\n\t]", left, right);
                if (strcmp(left, rule)== 0){
                	// printf("===%s\t%s===\n", rule, buffer);
                    if (strcmp(right, "eps") == 0){
		                // printf("\t%s\t%s\n", rule, right);
                    	has_eps_rule = 1;
                    	if(alreadyThere("eps", temp_seen, i) == -1){
                    		// printf("%s\n", "ADDED");
                    		strcat(lineBuffer, "eps");
	                        strcat(lineBuffer, " ");
	                        // printf("%s\t%s\t%s\n", "<<<", buffer, rule);
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
                                    strcat(lineBuffer, copy);
                                    strcat(lineBuffer, " ");
                                    strcpy(temp_seen[i++], copy);
                                }
                                break;
                            }
                            else if(isDone(copy)!=-1 && epsilonInFirst(copy) == 0){
                            	// /("%s\n", firsts[isDone(copy)]);
                            	char* tempstr = (char*) calloc(strlen(firsts[isDone(copy)])+1, sizeof(char));
                            	strcpy(tempstr, firsts[isDone(copy)]);
                                char* token_temp = strtok(tempstr, " ");
                                while(token_temp!=NULL){
                                	if (alreadyThere(token_temp ,temp_seen, i)== -1){
	                                    strcat(lineBuffer, token_temp);
	                                    strcat(lineBuffer, " ");
	                                    strcpy(temp_seen[i++], token_temp);
	                                    token_temp = strtok(NULL, " ");
                                	}
                                }
                            break;
                            }
                            else if(isDone(copy)!=-1){
                            	// printf("%sf", firsts[isDone(copy)]);
                            	char* tempstr = (char*) calloc(strlen(firsts[isDone(copy)])+1, sizeof(char));
                            	strcpy(tempstr, firsts[isDone(copy)]);
                                char* token_temp = strtok(tempstr, " ");
                                while(token_temp!=NULL){
                                	if (alreadyThere(token_temp ,temp_seen, i)==-1){
	                                    strcat(lineBuffer, token_temp);
	                                    strcat(lineBuffer, " ");
	                                    strcpy(temp_seen[i++], token_temp);
	                                    token_temp = strtok(NULL, " ");
                                	}
                                }
                        }
                            else{
                                // char * fname;
                                // printf("%s Called %s\n", rule, copy);
                                getFirst(copy, Filename);
                                // printf("%s\t%s\n", firsts[isDone(copy)],rule);
                            	char* tempstr = (char*) calloc(strlen(firsts[isDone(copy)])+1, sizeof(char));
                            	strcpy(tempstr, firsts[isDone(copy)]);
                                char* token_temp = strtok(tempstr, " ");
                                while(token_temp!=NULL){
                                	if (alreadyThere(token_temp ,temp_seen, i) == -1){
	                                    strcat(lineBuffer, token_temp);
	                                    strcat(lineBuffer, " ");
	                                    strcpy(temp_seen[i++], token_temp);
	                                    token_temp = strtok(NULL, " ");
                                	}
                                }
                                // printf("%s\t%s\t%d\n", firsts[isDone(copy)], copy, epsilonInFirst(copy));
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
                                	// printf("YO\t%s\n", rule);
                                	while(1){
                                		int position_of_eps = alreadyThere("eps", temp_seen, i);
	                                	if(position_of_eps !=-1){
	                                		strcpy(temp_seen[position_of_eps], "GARBAGEDATA");
	                                		removeFromString(lineBuffer, "eps");
	                                		// printf("%/s\n", buffer);
	                                	}
	                                	else{
	                                		break;
	                                	}
                                	}
                                }
                            }
                        }
                    }
                }
                strcat(buffer, lineBuffer);
            }
        fclose(fp);
        // printf("!!!%s\t%s\n", rule, buffer);
        // printf("%d\n", done_count);
        strcpy(firsts[done_count], buffer);
    	// printf("%s\t%s\n", rule, firsts[done_count]);
        strcpy(done_firsts[done_count++], rule);
        // printf("@@@%s\t%s\n", done_firsts[done_count-1], firsts[done_count-1]);
        // printf("%d\n", done_count-1);
        }
    }
}

int followFound(char * name){
    int i = 0;
    while(i != df_count){
        if(strcmp(done_follows[i], name) == 0 ){
            return i;
        }
        i++;
    }
    return -1;
}

int doubleDependence(char * rule1, char * rule2, char * Filename){
	FILE * fp = fopen(Filename, "r");
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char left[100];
    char right[100];
    int one_in_two = 0;
    int two_in_one = 0;
    while((read = getline(&line, &len, fp)) != -1){
    	sscanf(line, "%s ===> %[^\r\n\t]", left, right);
    	char * token = strtok(right, " ");
    	while(token!= NULL){
    		if(strcmp(token, rule2) == 0 && strcmp(left, rule1) == 0){
    			one_in_two = 1;
    		}
    		if(strcmp(token, rule1) == 0 && strcmp(left, rule2) == 0){
    			two_in_one = 1;
    		}
    		token = strtok(NULL, " ");
    	}
    }
    fclose(fp);
    if(two_in_one && one_in_two){
    	return 1;
    }
    return 0;//

}

void getFollow(char * rule, char * Filename, char * original){
	if (followFound(rule) == -1){
		strcpy(follows[df_count], "");
		char temp_seen[500][500];
		int i = 0;
		FILE * fp = fopen(Filename, "r");
		char * line = NULL;
        size_t len = 0;
        ssize_t read;
        char left[100];
        char right[100];
        while((read = getline(&line, &len, fp)) != -1){
        	// printf(">>%s\n", line);
	        sscanf(line, "%s ===> %[^\r\n\t]", left, right);
	        char * saveptr;
	        char * token;
	        int found=-1;
	        token = strtok_r(right , " ", &saveptr);
	        while(token!=NULL){
	        	char * copy = (char*)calloc(strlen(token)+1, sizeof(char));
				strcpy(copy, token);
        		token = strtok_r(NULL , " ", &saveptr);
	        	if(token == NULL && strcmp(copy, rule) == 0){
	        		// printf("FOO%s\t%s\n", left, rule);
	        		if(followFound(left) != -1){
	        			char * tempstr = (char*)calloc(strlen(follows[followFound(left)])+1, sizeof(char));
	        			char * temp_tokens = strtok(tempstr, " ");
	        			strcpy(tempstr, follows[followFound(left)]);
	        			temp_tokens = strtok(tempstr, " ");
	        			while(temp_tokens!= NULL){
	        				// printf("%s\n", temp_tokens);
        					if (alreadyThere(temp_tokens, temp_seen, i ) == -1 && strcmp("$", temp_tokens)!=0){
			        			strcat(follows[df_count], temp_tokens);
			        			strcat(follows[df_count], " ");
			        			strcpy(temp_seen[i++], temp_tokens);
			        		}
		        			temp_tokens = strtok(NULL, " ");
		        		}
	        		}
	        		else{
	        			// printf("%s\n", left);
	        			// printf("%s\n", "XXX");
	        			// printf("%s\t%s\t%s\n", left, original, rule);
	        			if(strcmp(left, original) !=0 && strcmp(left, rule) !=0 && doubleDependence(rule, left, Filename) == 0){
		        			// printf("!%s\t%s\t%s!\n", left, original, rule);
		        			// printf("%s\n", "AGAR");
		        			getFollow(left, Filename, original);
		        			char * tempstr = (char*)calloc(strlen(follows[followFound(left)])+1, sizeof(char));
		        			char * temp_tokens = strtok(tempstr, " ");
		        			strcpy(tempstr, follows[followFound(left)]);
		        			temp_tokens = strtok(tempstr, " ");
		        			while(temp_tokens!= NULL){
	        					if (alreadyThere(temp_tokens, temp_seen, i ) == -1 && strcmp("$", temp_tokens)!=0){
				        			strcat(follows[df_count], temp_tokens);
				        			strcat(follows[df_count], " ");
				        			strcpy(temp_seen[i++], temp_tokens);
				        		}
			        			temp_tokens = strtok(NULL, " ");
			        		}
			        	}
	        		}
	        	}
	        	else if(strcmp(copy, rule) == 0){
	        		// printf("%s\n", "a");
	        		found = 1;
	        	}
	        	else if(found == 1 && token != NULL){
        			char * tempstr = (char*)calloc(strlen(firsts[isDone(copy)])+1, sizeof(char));
        			strcpy(tempstr, firsts[isDone(copy)]);
        			char * temp_tokens = strtok(tempstr, " ");
        			while(temp_tokens!= NULL){
        				if (alreadyThere(temp_tokens, temp_seen, i ) == -1 && strcmp("eps", temp_tokens)!=0){
        					strcat(follows[df_count], temp_tokens);
		        			strcat(follows[df_count], " ");
		        			strcpy(temp_seen[i++], temp_tokens);
		        		}
		        		temp_tokens = strtok(NULL, " ");
	        		}
	        		if(!epsilonInFirst(copy)){
	        			break;
	        		}
	        	}
	        	else if(found ==1){
        			char * tempstr = (char*)calloc(strlen(firsts[isDone(copy)])+1, sizeof(char));
        			strcpy(tempstr, firsts[isDone(copy)]);
        			char * temp_tokens = strtok(tempstr, " ");
        			while(temp_tokens!= NULL){
        				if (alreadyThere(temp_tokens, temp_seen, i ) == -1 && strcmp("eps", temp_tokens)!=0){
        					strcat(follows[df_count], temp_tokens);
		        			strcat(follows[df_count], " ");
		        			strcpy(temp_seen[i++], temp_tokens);
		        		}
		        		temp_tokens = strtok(NULL, " ");
	        		}
	        		if(!epsilonInFirst(copy)){
	        			break;
	        		}
	        		if(followFound(left)!= -1){
	        			free(tempstr);
	        			tempstr = (char*)calloc(strlen(follows[followFound(left)])+1, sizeof(char));
	        			strcpy(tempstr, follows[followFound(left)]);
	        			temp_tokens = strtok(tempstr, " ");
	        			while(temp_tokens!= NULL){
        					if (alreadyThere(temp_tokens, temp_seen, i ) == -1 && strcmp("$", temp_tokens)!=0){
			        			strcat(follows[df_count], temp_tokens);
			        			strcat(follows[df_count], " ");
			        			strcpy(temp_seen[i++], temp_tokens);
			        		}
			        		temp_tokens = strtok(NULL, " ");
		        		}
	        		}
	        		else{
	        			// printf("%s\n", left);
	        			if(strcmp(left, original) !=0 && strcmp(left, rule) !=0 && doubleDependence(rule, left, Filename) == 0){
		        			getFollow(left, Filename, original);
		        			free(tempstr);
		        			tempstr = (char*)calloc(strlen(follows[followFound(left)])+1, sizeof(char));
		        			strcpy(tempstr, follows[followFound(left)]);
		        			temp_tokens = strtok(tempstr, " ");
		        			while(temp_tokens!= NULL){
	        					if (alreadyThere(temp_tokens, temp_seen, i ) == -1 && strcmp("$", temp_tokens)!=0){
				        			strcat(follows[df_count], temp_tokens);
				        			strcat(follows[df_count], " ");
				        			strcpy(temp_seen[i++], temp_tokens);
				        		}
			        			temp_tokens = strtok(NULL, " ");
			        		}
			        	}
	        		}
	        	}
	        	// printf("==%s\t%s\n", rule, token);
	        }
        }//outwhile
        fclose(fp);
	}//outmostif
	// printf("%s\n",follows[df_count] );
	strcat(follows[df_count], "$");
	strcat(follows[df_count], " ");
	strcpy(done_follows[df_count++], rule);
	//printf("%s\t%s\n", done_follows[df_count-1], follows[df_count-1]);
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
        if (isDone(seen[i]) == -1){
            getFirst(seen[i], Filename);
        }
        i++;
    }

    i=0;
    fp = fopen("firsts.txt", "w");
    while(i!= done_count){
    	firsts[i][strlen(firsts[i])-1] = '\0';
    	fprintf(fp, "%s %s\n", done_firsts[i], firsts[i]);
    	i++;
    }
    fclose(fp);

    i=0;
    while(i!= non_terminal_count){
        // printf("RUle:%s\n",seen[i] );
        if (followFound(nonTerminals[i]) == -1){
        	// printf("+=%s\n", nonTerminals[i]);
            getFollow(nonTerminals[i], Filename, nonTerminals[i]);
        }
        i++;
    }

    // printf("%s\n","follows");
    fp =fopen("follows.txt", "w");
    i = 0;
    while(i!=df_count){
    	// printf("%s %s\n", done_follows[i], follows[i]);
    	follows[i][strlen(follows[i])-1] = '\0';
    	fprintf(fp, "%s %s\n", done_follows[i], follows[i]);
    	i++;
    }
    fclose(fp);
    printf("%s\n", "Find firsts at firsts.txt");
    printf("%s\n", "Find follows at follows.txt");
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
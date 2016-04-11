/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:firstandfollow.c
*/

/*
    This is an independent module that we use to generate our firsts and follows list.
*/

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
// list of terminals/non terminals whose that have been found
char done_firsts[500][500];
// list of non terminals for which follows have been found
char done_follows[500][500];
// their corresponding firsts
char firsts[500][500];
// their corresponding follows
char follows[500][500];
// list of seen terminals and non terminals
char seen[110][110];
// listo f seen nonTerminals
char nonTerminals[110][110];
// list of seen terminals
char terminals[110][110];

//number of entries in the done_firsts list
int done_count = 0;
//number of entries in the done folllows list
int df_count = 0;
//number of terminals seen
int seen_count = 0;
//number of non terminals seen
int non_terminal_count = 0;
//number of terminals seen
int terminal_count = 0;

// checks if the given terminal/non terminal has been encountered or not
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

// checks if a given token is a non terminal
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

// checks if a given token is a terminal
int isTerminal(char * name){
    if (isNonTerminal(name) == 0){
        return 1;
    }
    else{
        return 0;
    }
}

// checks if first has been found for a given token
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

// checks if epsilon exists in first of given token
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

// checks if a word already exists in a list of strings
int alreadyThere(char * word, char buffer[500][500], int ff){
    int i =0;
    while(i!=ff){
        if(strcmp(word, buffer[i])==0)
            return i;
        i++;
    }
    return -1;
}

// removes given word from str
void removeFromString(char list_of_words[500], char *word)
{
    char *strbuf;
    char new_list_of_words[500];
    memset(new_list_of_words, 0, sizeof(new_list_of_words));
    strbuf = strtok(list_of_words, " ");
    while(strbuf)
    {
        if(strcmp(strbuf, word) != 0)
        {
            strcat(new_list_of_words, strbuf);
            strcat(new_list_of_words, " ");
        }
        strbuf = strtok(NULL, " ");
    }
    strcpy(list_of_words, new_list_of_words);

}

// a recursive function that finds first of a given rule
void getFirst(char * rule, char * Filename){
    int has_eps_rule = 0;
    char temp_seen[500][500];
    int i = 0;
    // only proceed if the first hasnt been found
    if(isDone(rule) == -1){
        // if it is a terminal then the first is it itself
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
                    // only rule is epsilon A -> e
                    if (strcmp(right, "eps") == 0){
                        has_eps_rule = 1;
                        if(alreadyThere("eps", temp_seen, i) == -1){
                            strcat(lineBuffer, "eps");
                            strcat(lineBuffer, " ");
                            strcpy(temp_seen[i++], "eps");
                        }
                    }
                    else{
                        char * token;
                        char *saveptr;
                        token = strtok_r(right , " ", &saveptr);
                        char copy[100];
                        strcpy(copy, token);
                        while(token != NULL){
                            //token is the rule itself, avoid stack overflow
                            if(strcmp(rule, copy) == 0){
                                token = strtok_r(NULL, " ", &saveptr);
                                if(token!=NULL){
                                    strcpy(copy, token);
                                }
                                continue;
                            }
                            // token is a terminal, simply add the terminal to list of firsts
                            if(isTerminal(copy)){
                                if(alreadyThere(copy, temp_seen, i)==-1){
                                    strcat(lineBuffer, copy);
                                    strcat(lineBuffer, " ");
                                    strcpy(temp_seen[i++], copy);
                                }
                                break;
                            }
                            // a non terminal that has been processed and doesn't contain epsilon
                            else if(isDone(copy)!=-1 && epsilonInFirst(copy) == 0){
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
                            // a non terminal that has been processed but contains epsilon
                            else if(isDone(copy)!=-1){
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
                                getFirst(copy, Filename);
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
                            token = strtok_r(NULL, " ", &saveptr);
                            // in situations where there isn't a rule A->eps and there are rules A-> BCD
                            // only add epsilon if B C and D all have eps in their first
                            if(token!=NULL){
                                strcpy(copy, token);
                                if (has_eps_rule != 1){
                                    while(1){
                                        int position_of_eps = alreadyThere("eps", temp_seen, i);
                                        if(position_of_eps !=-1){
                                            strcpy(temp_seen[position_of_eps], "GARBAGEDATA");
                                            removeFromString(lineBuffer, "eps");
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
        strcpy(firsts[done_count], buffer);
        strcpy(done_firsts[done_count++], rule);
        }
    }
}

// isDone but for follows
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

// checks whether rule a has rule b in itself and the other way around
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
    return 0;

}

// a recursive function to enumerate follows
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
            sscanf(line, "%s ===> %[^\r\n\t]", left, right);
            char * saveptr;
            char * token;
            int found=-1;
            token = strtok_r(right , " ", &saveptr);
            while(token!=NULL){
                char * copy = (char*)calloc(strlen(token)+1, sizeof(char));
                strcpy(copy, token);
                token = strtok_r(NULL , " ", &saveptr);
                // A -> B and B is the rule we want to find follow of
                if(token == NULL && strcmp(copy, rule) == 0){
                    // Follow of A is known
                    if(followFound(left) != -1){
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
                    // Follow of A is unknown
                    else{
                        //Lets avoid a recursion catastrophy
                        // handles A --> FB
                        // B --> FA
                        if(strcmp(left, original) !=0 && strcmp(left, rule) !=0 && doubleDependence(rule, left, Filename) == 0){
                            df_count++;
                            getFollow(left, Filename, original);
                            df_count--;
                            df_count--;
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
                // B has been found of right side but isn't the A -> B rather A-> BC
                else if(strcmp(copy, rule) == 0){
                    found = 1;
                }
                // C is not the last in the right side
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
                    // If C has epsilon in first, move to the next rule say D
                    if(!epsilonInFirst(copy)){
                        break;
                    }
                }
                // C is the last in the right side
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
                    // If there is no eps in c then break, else add FOllow of A to B
                    if(!epsilonInFirst(copy)){
                        break;
                    }
                    if(followFound(left)!= -1){
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
                        if(strcmp(left, original) !=0 && strcmp(left, rule) !=0 && doubleDependence(rule, left, Filename) == 0){
                            df_count++;
                            getFollow(left, Filename, original);
                            df_count--;
                            df_count--;
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
            }
        }//outwhile
        fclose(fp);
    }//outmostif
    strcat(follows[df_count], "$");
    strcat(follows[df_count], " ");
    strcpy(done_follows[df_count++], rule);
}

void firstsandfollows(char  * Filename){

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
                strcpy(seen[seen_count++], token);
            }
            token = strtok(NULL, " ");
        }

    }

    fclose(fp);
    int i =0;

    while(i!= seen_count){
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
        if (followFound(nonTerminals[i]) == -1){
            getFollow(nonTerminals[i], Filename, nonTerminals[i]);
        }
        i++;
    }

    fp =fopen("follows.txt", "w");
    i = 0;
    while(i!=df_count){
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

    firstsandfollows(argv[1]);

}

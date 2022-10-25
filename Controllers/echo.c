#include "../Headers/root.h"
void echo(char args[]){

    char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE];
    int tokens = tokenizeSpace(args, tokenizedCommand);
    for(int i = 1; i < tokens; i++){
        printf("%s ", tokenizedCommand[i]);
    }
    printf("\n");
}
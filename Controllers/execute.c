#include "../Headers/execute.h"
#include <string.h>
#include "../Headers/sizes.h"
#include "../Headers/root.h"
#include "../Headers/tokenizer.h"
#include <stdio.h>


int execute(char* command, char shellRootPath[]){
    // TO DO: add tokenization for the input to detect foreground and background processes

    char commandCopy[MAX_COMMAND_SIZE];
    strcpy(commandCopy, command); // stores a copy of the command since it gets tokenized and the intitial command array gets destroyed

    char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE];
    int tokens = tokenizeSpace(command, tokenizedCommand);

    if(!strcasecmp(tokenizedCommand[0], "pwd")){
        printPwd();
    }

    if(!strcasecmp(tokenizedCommand[0], "cd")){
        if(tokens > 2){
            printf("cd : string not in pwd: %s\n", tokenizedCommand[1]);
            return 0;
        }
        changeDirectory(tokenizedCommand[1], shellRootPath);
    }

    if(!strcasecmp(tokenizedCommand[0], "clear")){
        printf("\033[H\033[J");
    }
    if(!strcasecmp(tokenizedCommand[0], "ls")){
        ls(commandCopy, shellRootPath);
    }
    if(!strcasecmp(tokenizedCommand[0], "echo")){
        echo(commandCopy);
    }
    return 0;
}
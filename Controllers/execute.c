#include "../Headers/execute.h"
#include <string.h>
#include "../Headers/sizes.h"
#include "../Headers/root.h"
#include "../Headers/tokenizer.h"
#include <stdio.h>
#include "../Headers/dir.h"
#include "../Headers/globals.h"

// ADD ERRORS FOR NO REASON

int checkBackground(char command[]) {

    char commandCopy[MAX_COMMAND_SIZE];
    strcpy(commandCopy, command);

    char reconstructedCommand[MAX_COMMAND_SIZE]; // This array stores command without the & in the event that & was detected.
    char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE];
    int tokens;

    tokens = tokenizeSpace(command, tokenizedCommand);
//    printf("%d\n", tokens);
//    for (int i = 0; i < tokens; i++) {
//        printf("\033[0;36m");
//        printf("%d:%s\n", (i + 1), tokenizedCommand[i]);
//        printf("\033[0m");
//    }


    if (!strcasecmp(tokenizedCommand[tokens - 1], "&")) { // if the last element of the tokenized command is a @
//        printf("& detected");
        strcpy(reconstructedCommand, tokenizedCommand[0]);
        strcat(reconstructedCommand, " ");
        for (int i = 1; i < tokens - 1; i++) { // the first token was already copied and the & must not be copied
            strcat(reconstructedCommand, tokenizedCommand[i]);
            strcat(reconstructedCommand, " ");
        }
        strcpy(command, reconstructedCommand);

        return 1; // returns 1 when & was detected
    }
    strcpy(command, commandCopy);

    return 0;
}

int execute(char *command, job jobPool[]) {
    // TO DO: add tokenization for the input to detect foreground and background processes
    char commandCopy[MAX_COMMAND_SIZE];
    strcpy(commandCopy,
           command); // stores a copy of the command since it gets tokenized and the intitial command array gets destroyed

    char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE];
    int tokens = tokenizeSpace(command, tokenizedCommand);

    if (!strcasecmp(tokenizedCommand[0], "pwd")) {
        printPwd();
    } else if (!strcasecmp(tokenizedCommand[0], "cd")) {
        if (tokens > 2) {
            printf("cd : string not in pwd: %s\n", tokenizedCommand[1]);
            return 0;
        }

        if (tokenizedCommand[1][0] == '-') {
            if (!strcasecmp(previousDirectory, "")) {
                printf("No previous directory\n");
                return 0;
            }
            char currDir[MAX_PATH_SIZE];
            getCurrDir(currDir);
            printf("%s\n", previousDirectory);
            changeDirectory(previousDirectory);
            strcpy(previousDirectory, currDir);
        } else {
            char currDir[MAX_PATH_SIZE];
            getCurrDir(currDir);
            strcpy(previousDirectory, currDir);
            changeDirectory(tokenizedCommand[1]);
        }
    } else if (!strcasecmp(tokenizedCommand[0], "clear")) {
        printf("\033[H\033[J");
    } else if (!strcasecmp(tokenizedCommand[0], "ls")) {
        ls(commandCopy);
    } else if (!strcasecmp(tokenizedCommand[0], "echo")) {
        echo(commandCopy);
    } else if (!strcasecmp(tokenizedCommand[0], "discover")) {
        discover(commandCopy);
    } else if (!strcasecmp(tokenizedCommand[0], "history")) {
        printHistory(shellRootPath);
    } else {
        if (checkBackground(commandCopy)) {
            char tokenizedCommandWithoutAnd[MAX_TOKENS][MAX_TOKEN_SIZE];
            int tokens2 = tokenizeSpace(commandCopy, tokenizedCommandWithoutAnd);
            executeBackground(tokenizedCommandWithoutAnd, tokens2);
            return 0;
        } else {
            if (strcmp(commandCopy, " ")) {

                char tokenizedCommandWithoutAnd[MAX_TOKENS][MAX_TOKEN_SIZE];
                int tokens2 = tokenizeSpace(commandCopy, tokenizedCommandWithoutAnd);
                executeForeground(tokenizedCommandWithoutAnd, tokens2);
            }
            return 0;
        }
    }

    return 0;
}

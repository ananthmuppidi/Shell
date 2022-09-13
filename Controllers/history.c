#include <stdio.h>
#include "../Headers/history.h"
#include "../Headers/sizes.h"
#include "../Headers/tokenizer.h"
#include <string.h>

int countLines(char path[]) {

    int idx = 0;
    FILE *fd = fopen(path, "r");


    if (fd == NULL) {
        perror("err");
        printf("Error reading history file\n");
        return -1;
    }

    char currCommand[MAX_COMMAND_SIZE];

    while (fgets(currCommand, MAX_COMMAND_SIZE, fd) != NULL) {
        idx++;
    }

    fclose(fd);
    return idx;
}

void sanitizeCommand(char command[]) {

    char commandCopy[MAX_COMMAND_SIZE];
    strcpy(commandCopy, command);

    char reconstructedCommand[MAX_COMMAND_SIZE]; // This array stores command without the & in the event that & was detected.
    char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE];
    int tokens;

    tokens = tokenizeSpace(command, tokenizedCommand);

    strcpy(reconstructedCommand, tokenizedCommand[0]);
    strcat(reconstructedCommand, " ");
    for (int i = 1; i < tokens; i++) { // the first token was already copied
        strcat(reconstructedCommand, tokenizedCommand[i]);
        strcat(reconstructedCommand, " ");
    }
    strcpy(command, reconstructedCommand);


}

void makeHistoryFile(char shellRootPath[]) {
    char path[MAX_PATH_SIZE];
    strcpy(path, shellRootPath);
    strcat(path, "/history.txt");
    FILE *fp = fopen(path, "a+");
    fclose(fp);
}


int lastCommandSame(char command[], char path[]) {
    FILE *fd = fopen(path, "r");
    char lastCommand[MAX_COMMAND_SIZE];

    int lines = countLines(path);
    for (int i = 0; i < lines; i++) {
        fgets(lastCommand, MAX_COMMAND_SIZE, fd);
    }

    lastCommand[strcspn(lastCommand, "\n")] = 0;

    return !strcmp(lastCommand, command);
}


void printHistory(char shellRootPath[]) {
    char path[MAX_PATH_SIZE];
    strcpy(path, shellRootPath);
    strcat(path, "/history.txt");


    FILE *fd = fopen(path, "r");
    char currCommand[MAX_COMMAND_SIZE];

    int lines = countLines(path);
    if (lines > 10) {

        for(int i = 0; i < lines - 10; i++){
            fgets(currCommand, MAX_COMMAND_SIZE, fd);
        }

        for (int i = lines - 10; i < lines; i++) {
            fgets(currCommand, MAX_COMMAND_SIZE, fd);
            printf("%s", currCommand);
        }
        fclose(fd);
        return;
    }
    for (int i = 0; i < lines; i++) {
        fgets(currCommand, MAX_COMMAND_SIZE, fd);
        printf("%s", currCommand);
    }

    fclose(fd);
}


void addToHistory(char command[], char shellRootPath[]) {

    sanitizeCommand(command);

    char tokenizedInput[MAX_TOKENS][MAX_TOKEN_SIZE];
    char commandCopy[MAX_COMMAND_SIZE];
    strcpy(commandCopy, command);
    int tokens = tokenizeSpace(commandCopy, tokenizedInput);
    if (!tokens) {
        return;
    }
    char path[MAX_PATH_SIZE];

    strcpy(path, shellRootPath);
    strcat(path, "/history.txt");




    if (lastCommandSame(command, path)) {
        return;
    }

    if (countLines(path) == -1) {
        return;
    }

    if (countLines(path) < 20) {
        FILE *fd = fopen(path, "a");
        if (fd == NULL) {
            printf("Error reading history file\n");
            return;
        }
        fprintf(fd, "%s\n", command);
        fclose(fd);
        return;
    } else {
        // here the number of commands IS 20
        FILE *fd = fopen(path, "r");

        char currCommand[MAX_COMMAND_SIZE];

        int idx = 0;
        char allCommands[20][MAX_COMMAND_SIZE];

        for (int i = 0; i < 20; i++) {
            fgets(currCommand, MAX_COMMAND_SIZE, fd);
            strcpy(allCommands[i], currCommand);
        }
        fclose(fd);

        FILE *fd2 = fopen(path, "w");
        for (int i = 1; i < 20; i++) {
            fprintf(fd2, "%s", allCommands[i]);
        }
        fprintf(fd2, "%s\n", command);
        fclose(fd2);
        return;

    }

}
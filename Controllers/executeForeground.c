#include <unistd.h>
#include <stdio.h>
#include "../Headers/executeForeground.h"
#include "../Headers/sizes.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../Headers/globals.h"

void constructArguments(char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE], char *args[MAX_TOKENS], int numArgs) {
    for (int i = 0; i < numArgs; i++) {
        args[i] = tokenizedCommand[i];
    }
    args[numArgs] = NULL;
}

int executeForeground(char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE], int numArgs) {
    char *args[numArgs + 1];
    pid_t pid = fork();

    if (pid < 0) {
        printf("New process creation failed\n");
        exit(1);
    }
    if (pid == 0) {

        // Execute the command in the child process
        constructArguments(tokenizedCommand, args, numArgs);
        if (execvp(tokenizedCommand[0], args) < 0) {
            printf("shell: command not found: %s\n", tokenizedCommand[0]);
            return 1;
        }
    } else {
        currentForeground = pid;
        int status;

        time_t begin = time(0);

        waitpid(pid, &status, WUNTRACED);
        if (!strcmp(tokenizedCommand[0], "cat")) {
            printf("\n");
        }
        currentForeground = -1;

        time_t end = time(0);

        timeTaken = (end - begin);

    }

    return 1;
}
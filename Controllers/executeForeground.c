#include "../Headers/root.h"

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
            exit(1);
        }
    } else {
        currentForeground = pid;
        strcpy(currentForegroundName, tokenizedCommand[0]);
        int status;

        time_t begin = time(0);

        waitpid(pid, &status, WUNTRACED);

        currentForeground = -1;

        time_t end = time(0);

        timeTaken = (end - begin);
        strcpy(currentForegroundName, "");
    }

    return 1;
}
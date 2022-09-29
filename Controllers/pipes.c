#include "../Headers/pipes.h"
#include "../Headers/tokenizer.h"
#include "../Headers/globals.h"
#include "../Headers/execute.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void pipes(char tokenizedCommand[][MAX_TOKEN_SIZE], int tokens) {
    int pipeCount = 0;

    for (int i = 0; i < tokens; i++) {
        if (!strcmp("|", tokenizedCommand[i])) {
            pipeCount++;
        }
    }
    // reconstructing command and tokenizing based on |

    char reconstructedCommand[MAX_COMMAND_SIZE];
    strcpy(reconstructedCommand, "");
    for (int i = 0; i < tokens; i++) {
        strcat(reconstructedCommand, tokenizedCommand[i]);
        strcat(reconstructedCommand, " ");
    }

    // now we have the original string. We now tokenize it based on | and execute it while setting
    // the I/O to comply with the pipes

    char pipeCommands[MAX_TOKENS][MAX_TOKEN_SIZE];
    pipeCount = tokenizePipe(reconstructedCommand, pipeCommands);

    int in_backup = dup(STDIN_FILENO);
    int out_backup = dup(STDOUT_FILENO);

    int currentIn = dup(STDIN_FILENO);

    for (int i = 0; i < pipeCount; i++) {
        int pipes[2];
        pipe(pipes);

        pid_t pid = fork();
        if (pid < 0) {
            printf("shell : forking err\n");
            return;
        }
        if (pid == 0) {
            dup2(currentIn, STDIN_FILENO);
            if (i != pipeCount - 1) {
                dup2(pipes[1], STDOUT_FILENO);
            }
            close(pipes[0]);
            execute(tokenizedCommand[i], jobPool);
            exit(0);
        } else {
            int status;
            waitpid(pid, &status, WNOHANG);
            currentIn = dup(pipes[0]);
            close(pipes[1]);

        }


    }

}

// if its the last command, then dup2(pipes[1], 1);
// else:
//          close(pipes[1]);
//			new_in = pipes[0];

// starting new_in = stdin

// make two pipes
// at any point of time, close read end of previous pipe
// write end of current command
// last -> dont redirect
// first ->
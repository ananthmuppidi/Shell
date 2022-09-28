#include "../Headers/redirection.h"
#include "../Headers/sizes.h"
#include "../Headers/tokenizer.h"
#include "../Headers/globals.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Headers/dir.h"
#include <fcntl.h>
#include <unistd.h>
#include "../Headers/execute.h"

void redirection(char input[][MAX_TOKEN_SIZE], int tokens) {

    int flag_inp = 0; // input redirection (<) file is next to this input symbol to the right
    int flag_out1 = 0; // single redirection (>) truncates files
    int flag_out2 = 0; // single redirection (>>) appends files

    int in_location;
    int out_location;
    int out_type; // 1 = truncate, 2 = append

    char command[MAX_COMMAND_SIZE]; // there can only be one command in the case of redirection
    memset(command, MAX_COMMAND_SIZE, '\0');

    if (!strcmp(input[tokens - 1], ">") || !strcmp(input[tokens - 1], "<") || !strcmp(input[tokens - 1], ">>")) {
        printf("shell : redirection Error\n");
        return;
    }

    for (int i = 0; i < tokens; i++) {
        if (!strcmp(input[i], "<")) {
            strcpy(input[i], "");
            flag_inp++;
            in_location = i + 1;
        } else if (!strcmp(input[i], ">")) {
            strcpy(input[i], "");
            flag_out1++;
            out_location = i + 1;
            out_type = 1;
        } else if (!strcmp(input[i], ">>")) {
            strcpy(input[i], "");
            flag_out2++;
            out_location = i + 1;
            out_type = 2;
        }
    }

    if (flag_inp > 1) {
        printf("shell: too many input redirections\n");
        return;
    }
    if (flag_out1 + flag_out2 > 1) {
        printf("shell: too many output redirections\n");
        return;
    } // since we can't have both at the same time


    int dup_in;
    int dup_out;

    int inputFile;
    int outputFile;

    if (flag_inp) {
        char absIn[MAX_PATH_SIZE];
        getAbsolutePath(input[in_location], absIn);
        strcpy(input[in_location], "");
        inputFile = open(absIn, O_RDONLY);
        if (!inputFile) {
            printf("shell: input file was not found");
            return;
        }
        dup_in = dup(STDIN_FILENO);
        if (dup2(inputFile, STDIN_FILENO) == -1) {
            printf("shell: unable to redirect input\n");
            return;
        }
    }


    if (flag_out1 || flag_out2) {
        char absOut[MAX_PATH_SIZE];
        getAbsolutePath(input[out_location], absOut);
        strcpy(input[out_location], "");
        if (flag_out1) outputFile = open(absOut, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (flag_out2) outputFile = open(absOut, O_CREAT | O_WRONLY | O_APPEND, 0644);

        if (!outputFile) {
            printf("shell: output file was not found");
            return;
        }

        dup_out = dup(STDOUT_FILENO);
        if (dup2(inputFile, 0) == -1) {
            printf("shell: unable to redirect input\n");
            return;
        }
    }

    // now all the redirection has been handled and we need to actually run the command.
    // For this, we need to reconstruct the command without the redirection symbols and files, which have been set to NULL.
    for(int i = 0; i < tokens; i++){
        strcpy(command, input[i]);
        strcpy(command, " ");
    }


    execute(command, jobPool);


    dup2(dup_in, STDIN_FILENO);
    dup2(dup_out, STDOUT_FILENO);
    printf("%s\n", command);
    fflush(stdout);
    fflush(stdin);

}

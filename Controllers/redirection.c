#include "../Headers/root.h"
void redirection(char input[][MAX_TOKEN_SIZE], int tokens) {

    int flag_inp = 0; // input redirection (<) file is next to this input symbol to the right
    int flag_out1 = 0; // single redirection (>) truncates files
    int flag_out2 = 0; // single redirection (>>) appends files

    int in_location;
    int out_location;
    int out_type; // 1 = truncate, 2 = append

    int out_backup;
    int in_backup;

    out_backup = dup(STDOUT_FILENO);
    in_backup = dup(STDIN_FILENO);

    char command[MAX_COMMAND_SIZE]; // there can only be one command in the case of redirection

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
            perror("err:");
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
        if (dup2(outputFile, STDOUT_FILENO) == -1) {
            printf("shell: unable to redirect output\n");
            return;
        }
    }

    // now all the redirection has been handled and we need to actually run the command.
    // For this, we need to reconstruct the command without the redirection symbols and files, which have been set to NULL.

    strcpy(command, "");

    for(int i = 0; i < tokens; i++){
        strcat(command, input[i]);
        strcat(command, " ");
    }

//    char commandCopy[MAX_COMMAND_SIZE];
//    char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE];
//    strcpy(commandCopy, command);
//    int numTokens = tokenizeSpace(command, tokenizedCommand);


    execute(command, jobPool);
    memset(command, MAX_COMMAND_SIZE, '\0' );

    dup2(in_backup, STDIN_FILENO);
    dup2(out_backup, STDOUT_FILENO);


//
//    fflush(stdout);
//    fflush(stdin);

//    printf("%s\n", command);

}

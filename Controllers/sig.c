#include "../Headers/root.h"



void sig(char command[]) {

    char commands[MAX_TOKENS][MAX_TOKEN_SIZE];

    int n = tokenizeSpace(command, commands);
    if(n != 3){
        printf("sig : invalid number of arguments\n");
        return;
    }

    int process = atoi(commands[1]);
    int signal = atoi(commands[2]);

    if(process > countProcesses(jobPool) || countProcesses(jobPool) == 0 || process < 1){
        printf("sig : process with index %d does not exist\n", process);
        return;
    }
    if(jobPool[process - 1].pid == -1){
        printf("sig : process with index: %d does not exist\n", process);
        return;
    }
    kill(jobPool[process - 1].pid, signal);
    printf("\n");
}



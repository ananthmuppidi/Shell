#include "../Headers/root.h"

void bg(char command[]){
    char commands[MAX_TOKENS][MAX_TOKEN_SIZE];
    int n = tokenizeSpace(command, commands);
    if (n != 2) {
        printf("bg: invalid number of commands\n");
        fflush(stdout);
        return;
    }

    int idx = atoi(commands[1]);

    if (idx > countProcesses(jobPool) || idx < 1) {
        fflush(stdout);
        printf("bg : process with %d index does not exist\n", idx);
        fflush(stdout);
        return;
    }

    if (jobPool[idx - 1].pid == -1) {

        printf("bg : process with %d index does not exist\n", idx);
        fflush(stdout);
        return;

    } else {
        
        kill(jobPool[idx - 1].pid, SIGCONT);
        return;
    }

}
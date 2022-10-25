#include "../Headers/bg.h"
#include "../Headers/sig.h"
#include <stdio.h>
#include "../Headers/childHandler.h"
#include <signal.h>
#include <stdlib.h>
#include "../Headers/jobHandler.h"
#include <sys/types.h>
#include <sys/wait.h>



#include "../Headers/globals.h"
#include "../Headers/tokenizer.h"
#include "stdlib.h"

#include "../Headers/globals.h"
#include "../Headers/sizes.h"


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
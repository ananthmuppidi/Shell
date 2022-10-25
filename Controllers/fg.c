#include "../Headers/fg.h"
#include "../Headers/sig.h"
#include <stdio.h>
#include "../Headers/childHandler.h"
#include <signal.h>
#include <stdlib.h>
#include "../Headers/jobHandler.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#include "../Headers/globals.h"
#include "../Headers/tokenizer.h"
#include "stdlib.h"

#include "../Headers/globals.h"
#include "../Headers/sizes.h"

void fg(char command[]) {


    char commands[MAX_TOKENS][MAX_TOKEN_SIZE];
    int n = tokenizeSpace(command, commands);
    if (n != 2) {
        printf("fg: invalid number of commands\n");
        fflush(stdout);
        return;
    }

    int idx = atoi(commands[1]);

    if (idx > countProcesses(jobPool) || idx < 1) {
        fflush(stdout);
        printf("fg : process with %d index does not exist\n", idx);
        fflush(stdout);
        return;
    }

    if (jobPool[idx - 1].pid == -1) {

        printf("fg : process with %d index does not exist\n", idx);
        fflush(stdout);
        return;

    } else {


        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);

        strcpy(currentForegroundName, jobPool[idx - 1].name);
        currentForeground = jobPool[idx - 1].pid;
        
        kill(jobPool[idx - 1].pid, SIGCONT);
        

        if (tcsetpgrp(0, getpgid(jobPool[idx - 1].pid))) {
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            printf("fg: error: failed to get to foreground since terminal control denied");
            fflush(stdout);
            return;
        }
        
        
        
        
       
        int status;
        removeJob(jobPool, currentForeground, status,  currentForegroundName);

    
        waitpid(currentForeground, &status, WUNTRACED);
        currentForeground = -1;
        strcpy(currentForegroundName, "");

        tcsetpgrp(0, shellPid);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        return;

    }
}
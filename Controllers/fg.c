#include "../Headers/root.h"

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
        
        startTime = time(0);
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
        endTime = time(0);
        timeTaken = endTime - startTime;
        return;

    }
}
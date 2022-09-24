#include "../Headers/childHandler.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../Headers/jobHandler.h"
#include "../Headers/prompt.h"
#include <sys/wait.h>

#include "../Headers/globals.h"
#include "../Headers/sizes.h"

void childHandler() {
    signal(SIGCHLD, handleExit);
    signal(SIGINT, handleSigInt);
    signal(SIGTSTP, handleSigStp);
}

void handleExit() {

    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        status = WIFEXITED(status);
        char name[MAX_COMMAND_SIZE];
        int ret = removeJob(jobPool, pid, status, name);
        if (ret) {
            char arr[1000];
            getPrompt(arr);
            if (status) {
                printf("\n%s with pid %d exited normally\n%s", name, pid, arr);
                fflush(stdout);
            } else {
                printf("\n%s with pid %d exited abnormally \n %s", name, pid, arr);
                fflush(stdout);
            }
        }


        return;
    }
}

void handleSigInt() {
    if(currentForeground != -1){
        printf("Here");
        kill(currentForeground, SIGINT);
        currentForeground = -1;
    }
    return;
}


void handleSigStp() {

}

#include "../Headers/childHandler.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../Headers/jobHandler.h"
#include "../Headers/children.h"
#include "../Headers/prompt.h"
#include "../Headers/shellRootPathHolder.h"
#include "../Headers/execute.h"
#include <sys/wait.h>
#include <sys/types.h>

void childHandler() {

    struct sigaction childAction;
    struct sigaction tempAction;

    memset(&childAction, 0, sizeof(struct sigaction));
    memset(&tempAction, 0, sizeof(struct sigaction));

    childAction.sa_handler = handleExit;
    childAction.sa_flags = SA_RESTART | SA_SIGINFO;
    sigemptyset(&childAction.sa_mask);

    if (sigaction(SIGCHLD, &childAction, &tempAction) < 0) {
        printf("shell : signal error (fatal)");
        exit(0);
    }


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
            getPrompt(shellRootPathHolder, arr);
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

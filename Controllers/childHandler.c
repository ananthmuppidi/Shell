#include "../Headers/root.h"

void childHandler()
{
    signal(SIGCHLD, handleExit);
    signal(SIGINT, handleSigInt);
    signal(SIGTSTP, handleSigStp);
}

void handleExit()
{

    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {

        status = WIFEXITED(status);
        char name[MAX_COMMAND_SIZE];
        int ret = removeJob(jobPool, pid, status, name);
        if (ret)
        {
            char arr[1000];
            getPrompt(arr);
            if (status)
            {
                printf("\n%s with pid %d exited normally\n%s", name, pid, arr);
                fflush(stdout);
            }
            else
            {
                printf("\n%s with pid %d exited abnormally\n%s", name, pid, arr);
                fflush(stdout);
            }
        }
    }

    return;
}

void handleSigInt()
{
    if (currentForeground != -1)
    {
        kill(currentForeground, SIGINT);
        currentForeground = -1;
        printf("\n");
    }
    return;
}

void handleSigStp()
{
    if (currentForeground != -1)
    {
        if (countProcesses(jobPool) >= MAX_JOBS)
        {
            printf("Too many background processed to push current process to background");
            return;
        }
        setpgid(currentForeground, 0);
        kill(currentForeground, SIGTSTP);
        insertJob(jobPool, currentForegroundName, currentForeground);
        tcsetpgrp(0, shellPid);
        currentForeground = -1;
        strcpy(currentForegroundName, "");
        printf("\n");
    }
    return;
}

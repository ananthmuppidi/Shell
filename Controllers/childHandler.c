#include "../Headers/root.h"

int exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int inJobPool(pid_t pid){
    for(int i = 0; i < MAX_JOBS; i++){
        if(pid == jobPool[i].pid){
            return 1;
        }
    }
    return 0;
}
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

            if (status)
            {
                printf("\n%s with pid %d exited normally\n", name, pid);
                fflush(stdout);
                promptUser();
            }
            else
            {
                printf("\n%s with pid %d exited abnormally\n", name, pid);
                fflush(stdout);
                promptUser();
            }
        }
    }

        for(int j = 0; j < MAX_JOBS; j++){
        if(jobPool[j].pid != -1){
            char arrTemp[1000];
            strcpy(arrTemp, "/usr/bin/");
    
            strcat(arrTemp, jobPool[j].name);

            
            if(!exists(arrTemp)){
                printf("\n%s with pid %d exited abnormally (invalid command)", jobPool[j].name, jobPool[j].pid);
                jobPool[j].pid = -1;
                strcpy(jobPool[j].name, "");
            } else {
        
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
        if(!inJobPool(currentForeground))insertJob(jobPool, currentForegroundName, currentForeground);
        tcsetpgrp(0, shellPid);
        currentForeground = -1;
        strcpy(currentForegroundName, "");
        printf("\n");
    }
    return;
}

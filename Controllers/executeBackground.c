#include "../Headers/root.h"

void constructArgumentsBg(char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE], char *args[MAX_TOKENS], int numArgs)
{
    for (int i = 0; i < numArgs; i++)
    {
        args[i] = tokenizedCommand[i];
    }
    args[numArgs] = NULL;
}




int executeBackground(char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE], int numArgs)
{

    char *args[numArgs + 1];
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("New process creation failed\n");
        exit(1);
    }
    if (pid == 0)
    {
        // Execute the command in the child process
        setpgid(0,0);
        if (countProcesses(jobPool) >= MAX_JOBS)
        {
            printf("\nshell: job pool is full, cannot run background command.");
            exit(1);
        }



        constructArgumentsBg(tokenizedCommand, args, numArgs);
        if (execvp(tokenizedCommand[0], args) < 0)
        {

            // printf("\33[2K\r");
            // printf("shell: command not found: %s\n", tokenizedCommand[0]);
            // promptUser(shellRootPath);
            // fflush(stdout);
            // exit(1);
            printf("shell: command not found: %s\n", tokenizedCommand[0]);
            err = 1;
            exit(12);
        }


    }
    else
    {
        printf("[%d] %d\n", countProcesses(jobPool) + 1, pid);
        insertJob(jobPool, tokenizedCommand[0], pid);
        return 1;
    }

    return 1;
}
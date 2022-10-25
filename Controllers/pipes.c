#include "../Headers/root.h"

void pipes(char tokenizedCommand[][MAX_TOKEN_SIZE], int tokens)
{
    int pipeCount = 0;

    for (int i = 0; i < tokens; i++)
    {
        if (!strcmp("|", tokenizedCommand[i]))
        {
            pipeCount++;
        }
    }
    // reconstructing command and tokenizing based on |

    char reconstructedCommand[MAX_COMMAND_SIZE];
    strcpy(reconstructedCommand, "");
    for (int i = 0; i < tokens; i++)
    {
        strcat(reconstructedCommand, tokenizedCommand[i]);
        strcat(reconstructedCommand, " ");
    }

    // now we have the original string. We now tokenize it based on | and execute it while setting
    // the I/O to comply with the pipes

    char pipeCommands[MAX_TOKENS][MAX_TOKEN_SIZE];
    pipeCount = tokenizePipe(reconstructedCommand, pipeCommands);

    int in_backup = dup(STDIN_FILENO);
    int out_backup = dup(STDOUT_FILENO);

    int currentIn = dup(STDIN_FILENO);
    int pipes[2][2];

    for (int i = 0; i < pipeCount; i++)
    {
        
        
        pipe(pipes[i % 2]);


        dup2(currentIn, STDIN_FILENO);
        if (i != pipeCount - 1)
        {
            dup2(pipes[i % 2][1], STDOUT_FILENO);
        } else {
            dup2(out_backup, STDOUT_FILENO);
        }
        execute(pipeCommands[i]);
        close(pipes[i % 2][1]);
        close(pipes[(i + 1) % 2][0]);

       dup2(pipes[i % 2][0], currentIn);
    }

    close(pipes[(pipeCount - 1) % 2][0]);
    close(currentIn);
    dup2(in_backup, STDIN_FILENO);
    dup2(out_backup, STDOUT_FILENO);
    
}

#include "../Headers/input.h"
#include <string.h>
#include "../Headers/history.h"
#include <stdio.h>


void getInput(char buffer[], char shellRootPath[]){

    char inputString[MAX_COMMAND_SIZE];
    fgets(inputString, MAX_COMMAND_SIZE, stdin);
    inputString[strcspn(inputString, "\n")] = 0;
    strcpy(buffer, inputString);
    addToHistory(buffer, shellRootPath);

}

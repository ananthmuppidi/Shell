#include "../Headers/input.h"
#include "../Headers/sizes.h"
#include <string.h>
#include <stdio.h>


void getInput(char buffer[][MAX_PATH_SIZE]){

    char inputString[MAX_COMMAND_SIZE];
    fgets(inputString, MAX_COMMAND_SIZE, stdin);

    inputString[strcspn(inputString, "\n")] = 0;
    strcpy(buffer[0], inputString);
}

#include "../Headers/input.h"
#include <string.h>
#include "../Headers/history.h"
#include <stdio.h>
#include "../Headers/globals.h"


void getInput(char buffer[]){

    strcpy(buffer, "");
    char inputString[MAX_COMMAND_SIZE];
    fgets(inputString, MAX_COMMAND_SIZE, stdin);
    fflush(stdin);
    inputString[strcspn(inputString, "\n")] = 0;
//    printf("|%s|\n", inputString);
    strcpy(buffer, inputString);
//    printf("%s\n", buffer);

    addToHistory(inputString);

}

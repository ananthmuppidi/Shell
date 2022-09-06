#include "../Headers/execute.h"
#include <string.h>
#include "../Headers/sizes.h"
#include "../Headers/root.h"
#include <stdio.h>


int execute(char* command){
    printf("COMMAND: %s\n", command);
    // TO DO: add tokenization for the input to detect foreground and background processes
    if(!strcmp(command, "pwd")){
        printPwd();
    }
}
#include "../Headers/pwd.h"
#include "../Headers/dir.h"
#include "../Headers/sizes.h"
#include <stdio.h>


void printPwd() {
    char currentDirectory[MAX_PATH_SIZE];
    getCurrDir(currentDirectory);
    printf("%s\n", currentDirectory);
}



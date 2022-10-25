#include "../Headers/root.h"

void printPwd() {
    char currentDirectory[MAX_PATH_SIZE];
    getCurrDir(currentDirectory);
    printf("%s\n", currentDirectory);
}



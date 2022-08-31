#include "../Headers/dir.h"
#include "../Headers/sizes.h"
#include <unistd.h>
#include <string.h>

void getShellRoot(char buffer[]){
    char shellRootPath[MAX_PATH_SIZE];
    getcwd(shellRootPath, MAX_PATH_SIZE);
    strcpy(buffer, shellRootPath);
}


void getCurrDir(char buffer[], char shellRootPath[]){

    
    strcpy(buffer, "~");

    char absoluteTempPath[MAX_PATH_SIZE];
    getcwd(absoluteTempPath, MAX_PATH_SIZE);

    int isEqual = !strcmp(shellRootPath, absoluteTempPath);

    if(isEqual){
        return;
    }

    int idx = 0;
    int i = 1;
    
    while(shellRootPath[idx] == absoluteTempPath[idx]) idx++;
    while(absoluteTempPath[idx] != '\0') buffer[i++] = absoluteTempPath[idx++];
}


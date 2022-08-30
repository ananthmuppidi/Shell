#include "../Headers/currDir.h"
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LENGTH 10000

/// @brief Returns the absolute path of the working directory where the shell is started. 
/// @param buffer Char array where the path must be stored.

void getShellRoot(char buffer[]){
    char shellRootPath[MAX_PATH_LENGTH];
    getcwd(shellRootPath, MAX_PATH_LENGTH);
    strcpy(buffer, shellRootPath);
}


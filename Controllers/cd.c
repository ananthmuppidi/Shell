#include "../Headers/cd.h"
#include "../Headers/dir.h"
#include "../Headers/sizes.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void changeDirectory(char path[], char shellRootPath[]) {
    int chDirReturn = 0;
    char currentAbsoluteDir[MAX_PATH_SIZE];

    getcwd(currentAbsoluteDir, MAX_PATH_SIZE);

    // branching based on weather the path is absolute
    if (path[0] == '/') {
        // absolute path detected

        chDirReturn = chdir(path);

        if (chDirReturn == -1) {
            fprintf(stderr, "cd: %s: %s\n", strerror(errno), path);
        }

        return;
    }

    char tempArray[MAX_PATH_SIZE];

    strcat(currentAbsoluteDir, "/");
    strcat(currentAbsoluteDir, path);

    chDirReturn = chdir(currentAbsoluteDir);
    if (chDirReturn == -1) {
        fprintf(stderr, "cd: %s: %s\n", strerror(errno), path);
        // error handling
    }
}
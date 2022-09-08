#include "../Headers/cd.h"
#include "../Headers/dir.h"
#include "../Headers/sizes.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void changeDirectory(char path[], char shellRootPath[]) {
    int chDirReturn = 0;
    char absoluteDir[MAX_PATH_SIZE];

    getAbsolutePath(path, absoluteDir, shellRootPath);
    chDirReturn = chdir(absoluteDir);
    if (chDirReturn == -1) {
        fprintf(stderr, "cd: %s: %s\n", strerror(errno), path);
        // error handling
    }
}
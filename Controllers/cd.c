#include "../Headers/root.h"

void changeDirectory(char path[]) {
    int chDirReturn = 0;
    char absoluteDir[MAX_PATH_SIZE];
    getAbsolutePath(path, absoluteDir);
    chDirReturn = chdir(absoluteDir);

    if (chDirReturn == -1) {
        fprintf(stderr, "cd: %s: %s\n", strerror(errno), path);
    }

}
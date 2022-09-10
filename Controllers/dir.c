#include "../Headers/dir.h"
#include "../Headers/sizes.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void getShellRoot(char buffer[]) {
    char shellRootPath[MAX_PATH_SIZE];
    getcwd(shellRootPath, MAX_PATH_SIZE);
    strcpy(buffer, shellRootPath);
}

void getCurrDir(char buffer[]) {
    getcwd(buffer, MAX_PATH_SIZE);
}

void getPromptCurrDir(char buffer[], char shellRootPath[]) {

    char absoluteTempPath[MAX_PATH_SIZE];
    getcwd(absoluteTempPath, MAX_PATH_SIZE);

    int isEqual = strcmp(shellRootPath, absoluteTempPath);
    if (!isEqual) {
        strcpy(buffer, "~");
        return; // the strings are equal then return home -> ~
    }

    if (isEqual < 0) { // actual Path is subdirectory of root
        if (strstr(absoluteTempPath, shellRootPath)) {

            int idx = 0;
            int i = 1;

            while (shellRootPath[idx] == absoluteTempPath[idx])
                idx++;
            while (absoluteTempPath[idx] != '\0')
                buffer[i++] = absoluteTempPath[idx++];

            buffer[i] = '\0';
            return;
        }
    }

    strcpy(buffer, absoluteTempPath);
    return;

}

void getAbsolutePath(char arg[], char buffer[], char shellRootPath[]) {
    if (arg[0] == '/') {
        strcpy(buffer, arg);
        return;
    }
    if (arg[0] == '~') {
        strcpy(buffer, shellRootPath);
        if (arg[1] == '/') {
            strcat(buffer, "/");
            int idx = 2;
            int bufferIdx = strlen(buffer);
            while (arg[idx] != '\0') {
                buffer[bufferIdx++] = arg[idx++];
            }
            buffer[bufferIdx] = '\0';
        }
        return;
    } else {
        char cwd[MAX_PATH_SIZE];
        getCurrDir(cwd);
        strcat(cwd, "/");
        strcat(cwd, arg);
        strcpy(buffer, cwd);
        return;
    }

}


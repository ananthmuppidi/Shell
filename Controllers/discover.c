#include <stdio.h>
#include "../Headers/ls.h"
#include "../Headers/sizes.h"
#include "../Headers/dir.h"
#include "../Headers/tokenizer.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "../Headers/sizes.h"
#include <sys/stat.h>
#include "../Headers/helpers.h"
#include <pwd.h>
#include <time.h>
#include <libgen.h>
#include <grp.h>
#include "../Headers/discover.h"

// ASSUMES THAT THE TARGET (the entity being searched for) IS ALWAYS A FILE
// PRINT THE SEARCH DIR (only when either -d or no flag)

int getFlagsDiscover(char input[], int *f, int *d) {

    int err = 0;
    int idx = 1;

    while (idx < strlen(input)) {
        if (input[idx] == 'd' || input[idx] == 'D') {
            *d = 1;
        } else if (input[idx] == 'f' || input[idx] == 'F') {
            *f = 1;
        } else {
            err = 1;
            printf("discover: invalid option -- %c\n", input[idx]);
        }
        idx++;
    }
    return err;
}

void printRelativePath(char path[], char searchDirectory[]) {
    // here path is guaranteed to be a subdirectoy of search directory

    char outputArray[MAX_PATH_SIZE];
    strcpy(outputArray, ".");

    int idx = strlen(searchDirectory);
    int idx2 = 1;

    while (path[idx] != '\0') {
        outputArray[idx2++] = path[idx++];
    }
    outputArray[idx2] = '\0';
    printf("%s\n", outputArray);

}


// recursive function to find all the instances of out target
// path is the absolute path of where the search starts
void search(char path[], char target[], char originalSearchDirectory[], int d, int f, int printAll) {

    DIR *dp;
    dp = opendir(path);

    if (!dp) {
        char err[MAX_PATH_SIZE];
        sprintf(err, "discover : %s", basename(path));
        perror(err);
        return;
    }

    struct dirent **ep;
    int n;

    n = scandir(path, &ep, 0, alphasort);
    if (n < 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        if (ep[i]->d_name[0] != '.') {
            char fullPath[MAX_PATH_SIZE];
            strcpy(fullPath, path);

            if (fullPath[strlen(fullPath) - 1] != '/') {
                strcat(fullPath, "/");
                strcat(fullPath, ep[i]->d_name);
            } else {
                strcat(fullPath, ep[i]->d_name);
            }

            struct stat stats;
            if (stat(fullPath, &stats) == -1) {
                continue;
            }

            if (S_ISDIR(stats.st_mode)) {
                if (!(strcmp(ep[i]->d_name, target)) | printAll) {
                    if (d)printRelativePath(fullPath, originalSearchDirectory);
                }
                search(fullPath, target, originalSearchDirectory, d, f, printAll);
            } else {
                if (!(strcmp(ep[i]->d_name, target)) | printAll) {
                    if (f)printRelativePath(fullPath, originalSearchDirectory);
                }
            }

        }
    }

    closedir(dp);
    return;

}


void discover(char arg[], char shellRootPath[]) {

    char tokenizedInput[MAX_TOKENS][MAX_TOKEN_SIZE];
    int tokens = tokenizeSpace(arg, tokenizedInput);

    int foundSearchDirectory = 0;
    int foundTarget = 0;
    int foundFlags = 0;

    int f = 0, d = 0;
    char target[MAX_PATH_SIZE];
    char searchDir[MAX_PATH_SIZE];

    if (tokens > 4) {
        printf("discover : too many arguments");
        return;
    }

    if (tokens == 1) { // print entire tree
        f = 1;
        d = 1;
        getCurrDir(searchDir);
        search(searchDir, target, searchDir, d, f, 1);
    }

    if (tokens > 1) {
        for (int i = 1; i < tokens; i++) {
            if (tokenizedInput[i][0] != '-' && tokenizedInput[i][0] != '"') {
                if (foundSearchDirectory) {
                    printf("discover : too many search directories provided\n");
                    return;
                } else {
                    foundSearchDirectory = 1;
                    getAbsolutePath(tokenizedInput[i], searchDir, shellRootPath);
                }
            } else if (tokenizedInput[i][0] == '-' && tokenizedInput[i][1] != '\0') {
                if (foundFlags) {
                    printf("discover: too many flags provided\n");
                    return;
                } else {
                    getFlagsDiscover(tokenizedInput[i], &f, &d);
                    foundFlags = 1;
                }

            } else if (tokenizedInput[i][0] == '\"') {
                if (foundTarget) {
                    printf("discover: too many targets provided\n");
                    return;
                } else {
                    foundTarget = 1;

                    char tempArr[MAX_PATH_SIZE];

                    int idx1 = 1;
                    int idx2 = 0;

                    while (tokenizedInput[i][idx1] != '\"') {
                        tempArr[idx2++] = tokenizedInput[i][idx1++];
                    }
                    tempArr[idx2] = '\0';
                    strcpy(target, tempArr);
                }
            }
        }

        if (!foundFlags) {
            f = 1;
            d = 1;
        }

        if (!foundSearchDirectory) {
            getCurrDir(searchDir);
        }

        if (!foundTarget) {
            search(searchDir, target, searchDir, d, f, 1);
            return;
        }

    }

    search(searchDir, target, searchDir, d, f, 0);

}
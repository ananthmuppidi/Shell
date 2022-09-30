#include "../Headers/autocomplete.h"
#include "../Headers/tokenizer.h"
#include <string.h>
#include <stdio.h>
#include "../Headers/ls.h"
#include "../Headers/sizes.h"
#include "../Headers/dir.h"
#include "../Headers/tokenizer.h"
#include <dirent.h>
#include <sys/stat.h>
#include "../Headers/helpers.h"
#include <pwd.h>
#include <time.h>
#include <libgen.h>
#include <grp.h>
#include "../Headers/prompt.h"
#include <errno.h>

void autoComplete(char command[], int len) {


    char options[1000][1000];
    int idx = 0;

    int entities = 0;

    char path[10000];
    getCurrDir(path);

    char temp[10102] = {'\0'};
    char lastCommand[10102] = {'\0'};




    DIR *dp;
    dp = opendir(path);
    struct dirent **ep;
    int n;

    n = scandir(path, &ep, 0, alphasort);

    for (int i = 0; i < n; i++) {

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
        sprintf(options[idx++], "%s", ep[i]->d_name);
    }


    if (len) {
        for (int i = len - 1; i >= 0; i--) {
            if (command[i] != ' ') temp[len - i - 1] = command[i];
            else break;
        }

        for (int i = 0; i < strlen(temp); i++) {
            lastCommand[i] = temp[strlen(temp) - 1 - i];
        }
    } else {
        printf("<ADAKJDSFOOUojsd\n");

        for (int i = 0; i < idx; i++) {
            printf("%s\n", options[i]);
        }
        promptUser();
        return;
    }

    if (!strlen(lastCommand)) {
        DIR *dp;
        dp = opendir(path);
        struct dirent **ep;
        int n;

        n = scandir(path, &ep, 0, alphasort);


        for (int i = 0; i < n; i++) {

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
            sprintf(options[idx++], "%s", ep[i]->d_name);


        }

        for (int i = 0; i < idx; i++) {
            printf("%s\n", options[i]);
        }
        return;
    }


    char matchedOptions[1000][1000];
    int matches = 0;
    for (int i = 0; i < idx; i++) {
        if (!strncmp(lastCommand, options[i], strlen(lastCommand))) {

             printf("%s\n", options[i]);
        }
    }



    promptUser();


    return;
}
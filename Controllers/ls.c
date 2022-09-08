#include "../Headers/ls.h"
#include "../Headers/sizes.h"
#include "../Headers/dir.h"
#include "../Headers/tokenizer.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>


void ls(char args[], char shellRootPath[]) {

    int tokens;
    DIR *dp;


    int a = 0;
    int l = 0;

    char tokenizedInput[MAX_TOKENS][MAX_TOKEN_SIZE];
    tokens = tokenizeSpace(args, tokenizedInput);

    if (tokens == 1) {

        // Here we print the current directories info
        char currentDirectory[MAX_PATH_SIZE];
        getCurrDir(currentDirectory);
        dp = opendir(currentDirectory);
        if (!dp) {
            perror(currentDirectory);
            return;
        }
        struct dirent *ep;
        while ((ep = readdir(dp))) {
            printf("%s\n", ep->d_name);
        }
    } else {

        // here the number of tokens is greater than 1
        // only the first token can be options else the argument is an error

        if (tokenizedInput[1][0] == '-') {
            if (strchr(tokenizedInput[1], 'a') != NULL)
                a = 1;
            if (strchr(tokenizedInput[1], 'l') != NULL)
                l = 1;
        }

        printf("LS EXECUTED: FLAGS A: %d   L: %d   \n", a, l);

        tokens -= 2; // this is the number of paths provided to ls.
        // First we handle when there are no paths provided.

    }
}
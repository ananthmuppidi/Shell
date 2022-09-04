#include "../Headers/tokenizer.h"
#include <string.h>
#include "../Headers/sizes.h"
#include <stdio.h>

int tokenizeSemiColon(char input[], char output[][MAX_TOKEN_SIZE]) {

    char *delimiter = ";";
    char *token;

    int idx = 0;
    int tokenCount = 0;

    token = strtok(input, delimiter);
    while (token != NULL) {
        tokenCount++;
        strcpy(output[idx++], token);
//        printf("\033[0;36m");
//        printf("%d:%s   ", tokenCount ,token);
//        printf("\033[0m");
        token = strtok(NULL, delimiter);
    }
    return tokenCount;
}

int tokenizeAnd(char input[], char output[][MAX_TOKEN_SIZE]) {
    char *delimiter = "&";
    char *token;

    int idx = 0;
    int tokenCount = 0;

    token = strtok(input, delimiter);
    while (token != NULL) {
        tokenCount++;
        strcpy(output[idx++], token);
//        printf("\033[0;36m");
//        printf("%d:%s   ", tokenCount ,token);
//        printf("\033[0m");
        token = strtok(NULL, delimiter);
    }
    return tokenCount;
}

int tokenizeInput(char input[], char output[][MAX_TOKEN_SIZE]) {

    char semiColonTokens[MAX_TOKENS][MAX_TOKEN_SIZE];
    char andTokens[MAX_TOKENS][MAX_TOKEN_SIZE];

    int idx = 0; // Index of final return array.

    int semiColonTokenCount;
    int andTokenCount;

    semiColonTokenCount = tokenizeSemiColon(input, semiColonTokens);

    for (int i = 0; i < semiColonTokenCount; i++) {
        if(semiColonTokens[i][0] == '&'){

        }
        andTokenCount = tokenizeAnd(semiColonTokens[i], andTokens);
        for (int j = 0; j < andTokenCount; j++) {
            strcpy(output[idx], andTokens[j]);
            if (j != (andTokenCount - 1)) {
                strcat(output[idx], " &");
            }
            idx++;
        }
    }

    for (int i = 0; i < idx; i++) {
        printf("\033[0;36m");
        printf("%d:%s\n", (i + 1), output[i]);
        printf("\033[0m");
    }


    return idx;
}



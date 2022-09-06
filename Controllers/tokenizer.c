#include "../Headers/tokenizer.h"
#include <string.h>
#include "../Headers/sizes.h"
#include <stdio.h>


int tokenizeSpace(char input[], char output[][MAX_TOKEN_SIZE]) {

    char *delimiter = " \t";
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

    // Temporary variables to count the number of & symbols
    int symbolCount = 0;
    int symbolTraversal = 0;

    while (input[symbolTraversal] != '\0') {
        if (input[symbolTraversal++] == '&') {
            symbolCount++; // stores the total number of & symbols in the variable
        }
    }

    token = strtok(input, delimiter);
    while (token != NULL) {
        tokenCount++;
        strcpy(output[idx++], token);
//        printf("\033[0;36m");
//        printf("%d:%s   ", tokenCount ,token);
//        printf("\033[0m");
        token = strtok(NULL, delimiter);
    }

    // This section appends the & symbol to all the tokens, depending on how many & symbols were found
    int symbolAppendCount = 0; // To store which token the symbol is being appended to
    while (symbolCount--) {
        strcat(output[symbolAppendCount++],
               " &"); // with space so that it gets detected later during command tokenization
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
        andTokenCount = tokenizeAnd(semiColonTokens[i], andTokens);
        for (int j = 0; j < andTokenCount; j++) {
            strcpy(output[idx], andTokens[j]);
            idx++;
        }
    }
//
//    for (int i = 0; i < idx; i++) {
//        printf("\033[0;36m");
//        printf("%d:%s\n", (i + 1), output[i]);
//        printf("\033[0m");
//    }


    return idx;
}



#include "Headers/prompt.h"
#include "Headers/dir.h"
#include "Headers/sizes.h"
#include "Headers/cd.h"
#include "Headers/input.h"
#include "Headers/tokenizer.h"
#include "Headers/execute.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {

    char shellRootPath[MAX_PATH_SIZE];
    getShellRoot(shellRootPath);

    while (1) {

        char input[MAX_COMMAND_SIZE];

        char tokenizedInput[MAX_TOKENS][MAX_TOKEN_SIZE];
        int tokens;

        char semiColonTokens[MAX_TOKENS][MAX_TOKEN_SIZE];
        char finalTokens[MAX_TOKENS][MAX_TOKEN_SIZE];

        promptUser(shellRootPath);
        getInput(input);
        tokens = tokenizeInput(input, tokenizedInput);

        for(int i = 0; i < tokens; i++){
            execute(tokenizedInput[i]);
        }

    }
}


#pragma clang diagnostic pop
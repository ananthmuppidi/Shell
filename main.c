#include "Headers/prompt.h"
#include "Headers/dir.h"
#include "Headers/sizes.h"
#include "Headers/input.h"
#include "Headers/tokenizer.h"
#include "Headers/execute.h"
#include "Headers/history.h"
#include "Headers/job.h"
#include "Headers/jobHandler.h"
#include "Headers/childHandler.h"
#include "Headers/globals.h"

#include <stdio.h>
#include <string.h>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {

    initializeConstants();
    childHandler();
    shellPid = getpid();


    while (1) {

        char input[MAX_COMMAND_SIZE];
        char tokenizedInput[MAX_TOKENS][MAX_TOKEN_SIZE];
        int tokens;

        char semiColonTokens[MAX_TOKENS][MAX_TOKEN_SIZE];
        char finalTokens[MAX_TOKENS][MAX_TOKEN_SIZE];

        promptUser();
        getInput(input);
        tokens = tokenizeInput(input, tokenizedInput);
        for (int i = 0; i < tokens; i++) execute(tokenizedInput[i]);
    }
}



#pragma clang diagnostic pop
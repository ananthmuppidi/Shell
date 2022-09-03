#include "../Headers/tokenizer.h"
#include <string.h>

char* tokenizeSemiColon(char* input, char** output){
    char* entryPoint = strtok(input, ";");
    return entryPoint;
}

char* tokenizeAnd(char* input, char** output){
    char* entryPoint = strtok(input, "@");
    return entryPoint;
}

char*  tokenizeSpace(char* input, char** output){
    char* entryPoint = strtok(input, " ");
    return entryPoint;
}

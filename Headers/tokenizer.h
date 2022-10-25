#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "sizes.h"

int tokenizeSemiColon(char input[], char output[][MAX_TOKEN_SIZE]);
int tokenizeAnd(char input[], char output[][MAX_TOKEN_SIZE]);
int tokenizeInput(char input[], char output[][MAX_TOKEN_SIZE]);
int tokenizeSpace(char input[], char output[][MAX_TOKEN_SIZE]);
int tokenizePipe(char input[], char output[][MAX_TOKEN_SIZE]);

#endif

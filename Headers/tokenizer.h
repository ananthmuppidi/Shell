#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "sizes.h"


/// @breif Tokenizes given input string based on delimiter space
/// @param input The input string
/// @param output A 2 dimensional array of tokens
/// @return Returns the number of tokens

int tokenizeSemiColon(char input[], char output[][MAX_TOKEN_SIZE]);

/// @breif Tokenizes given input string based on delimiter &
/// @param input The input string
/// @param output A 2 dimensional array of tokens
/// @return Returns the number of tokens
int tokenizeAnd(char input[], char output[][MAX_TOKEN_SIZE]);

/// @breif Tokenizes given input string and returns an array of executable commands, with flags delimited by space(s). Background commands have the & symbol appended to the last token (delimited by space).
/// @param input The input string
/// @param output A 2 dimensional array of tokens
/// @return Returns the number of tokens
int tokenizeInput(char input[], char output[][MAX_TOKEN_SIZE]);


/// @breif Tokenizes given input string and returns an an array of strings delemited by the " ". This is to split a command with its options and arguments.
/// @param input The input string
/// @param output A 2 dimensional array of tokens
/// @return Returns the number of tokens
int tokenizeSpace(char input[], char output[][MAX_TOKEN_SIZE]);

#endif

#ifndef __TOKENIZER_H_
#define __TOKENIZER_H_

#include "sizes.h"

/// @brief Tokenized commands delemited by space.
/// @param input The input read from the command line.
/// @param output The output is a array of tokenized commands delimited by " ".
/// @return Returns character pointer to the first command.
char* tokenizeSpace(char* input, char** output);

/// @brief Tokenized commands delemited by &.
/// @param input The input read from the command line.
/// @param output The output is a array of tokenized commands delimited by "&".
/// @return Returns character pointer to the first command.
char* tokensizeAnd(char* input, char** output);

/// @brief Tokenized commands delemited by ;.
/// @param input The input read from the command line.
/// @param output The output is a array of tokenized commands delimited by ";".
/// @return Returns character pointer to the first command.
char* tokenizeSemiColon(char* input, char** output);

#endif
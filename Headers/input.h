#ifndef __INPUT_H__
#define __INPUT_H__

#include "sizes.h"

/// @breif Gets input from the shell and tokenizes it. Appends &(background process) to the command.
/// @param buffer Where the input is stored
void getInput(char buffer[], char shellRootPath[]);

#endif
#ifndef __EXECUTE_FOREGROUND_H__
#define __EXECUTE_FOREGROUND_H__

#include "sizes.h"
#include "job.h"

/// @breif Executes a command in the foreground. This command must be present in the path of the given file.
/// @param tokenizedCommand This is the command that must be executed at index 0, along with all the other arguments to the command in order.
/// @param numArgs This is the number of arguments provided to the command (including the command itself).
int executeForeground(char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE], int numArgs);

#endif

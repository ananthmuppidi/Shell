#ifndef __EXECUTE_FOREGROUND_H__
#define __EXECUTE_FOREGROUND_H__

#include "sizes.h"
#include "job.h"

int executeForeground(char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE], int numArgs);

#endif

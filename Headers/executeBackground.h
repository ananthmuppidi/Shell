#ifndef __EXECUTE_BACKGROUND__H_
#define __EXECUTE_BACKGROUND__H_
#include "sizes.h"
#include "job.h"

int executeBackground(char tokenizedCommand[MAX_TOKENS][MAX_TOKEN_SIZE], int numArgs, char shellRootPath[]);
#endif

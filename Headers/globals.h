#ifndef _ASSIGNMENT2__GLOBALS__H_
#define _ASSIGNMENT2__GLOBALS__H_

#include "job.h"
#include "jobHandler.h"

char *shellRootPath;
job* jobPool;
double timeTaken;
char* previousDirectory;
pid_t currentForeground;

void initializeConstants();

#endif

#ifndef _ASSIGNMENT2__GLOBALS__H_
#define _ASSIGNMENT2__GLOBALS__H_

#include "job.h"
#include "jobHandler.h"

char *shellRootPath;
job* jobPool;
double timeTaken;
char* previousDirectory;
pid_t currentForeground;
pid_t shellPid;
char *currentForegroundName;
pid_t errPid;
int err;

void initializeConstants();

#endif

#ifndef _ASSIGNMENT2__GLOBALS__H_
#define _ASSIGNMENT2__GLOBALS__H_

#include "job.h"
#include "jobHandler.h"
#include <time.h>

char *shellRootPath;
job* jobPool;
double timeTaken;
char* previousDirectory;
pid_t currentForeground;
pid_t shellPid;
char *currentForegroundName;
pid_t errPid;
int err;
time_t startTime;
time_t endTime;

void initializeConstants();

#endif

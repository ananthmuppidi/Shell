#ifndef __JOB_HANDLER_H__
#define __JOB_HANDLER_H__
#include "job.h"

void initializeJobPool(job jobPool[]);
int insertJob(job jobPool[], char name[], pid_t pid);
int removeJob(job jobPool[], pid_t pid, int status, char name[]);
int countProcesses(job jobPool[]);

#endif

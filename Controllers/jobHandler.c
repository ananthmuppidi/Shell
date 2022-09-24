#include "../Headers/job.h"
#include "../Headers/jobHandler.h"
#include "../Headers/sizes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Headers/prompt.h"
#include "../Headers/globals.h"


void initializeJobPool(job jobPool[]) {
    for (int i = 0; i < MAX_JOBS; i++) {
        jobPool[i].pid = -1;
        jobPool[i].name = (char *) malloc(sizeof(char) * MAX_TOKEN_SIZE);
        strcpy(jobPool[i].name, "");
    }
}

int insertJob(job jobPool[], char name[], pid_t pid) {
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobPool[i].pid == -1) {
            strcpy(jobPool[i].name, name);
            jobPool[i].pid = pid;
            return 1;
        }
    }
    return 0;
}

int removeJob(job jobPool[], pid_t pid, int status, char name[]) {
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobPool[i].pid == pid) {
            jobPool[i].pid = -1;
            strcpy(name, jobPool[i].name);
            strcpy(jobPool[i].name, "");
            return 1;
        }
    }
    return 0;
}

int countProcesses(job jobPool[]) {
    int jobs = 0;
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobPool[i].pid != -1) {
            jobs++;
        }
    }
    return jobs;
}

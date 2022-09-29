#include "../Headers/jobs.h"
#include "../Headers/globals.h"
#include "../Headers/sizes.h"
#include "../Headers/tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _tempJob {
    char *name;
    int idx;
    pid_t pid;
    char *status;
} tempJob;

void swap(tempJob *a, tempJob *b) {
    tempJob temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(tempJob arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
                printf("HERE\n");

                swap(&arr[j], &arr[j + 1]);
            }
}


void jobs() {

    int idx = 0;
    tempJob tempJobs[MAX_JOBS];

    for (int i = 0; i < MAX_JOBS; i++) {
        tempJobs[i].name = (char *) malloc(sizeof(char) * MAX_COMMAND_SIZE);
        tempJobs[i].status = (char *) malloc(sizeof(char) * 10);
        memset(tempJobs[i].name, MAX_COMMAND_SIZE, '\0');
        tempJobs[i].idx = -1;
    }

    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobPool[i].pid != -1) {

            tempJobs[idx].idx = i + 1;
            strcpy(tempJobs[idx].name, jobPool[i].name);
            tempJobs[idx].pid = jobPool[i].pid;

            char tempProc[100];
            memset(tempProc, 100, '\0');
            sprintf(tempProc, "/proc/%d/stat", jobPool[i].pid);
            FILE *fp = fopen(tempProc, "r");

            if (fp) {
                char t;

                while (t != ')') t = fgetc(fp);
                fgetc(fp);
                t = fgetc(fp);

                if (t == 'T') {
                    strcpy(tempJobs[idx++].status, "Stopped");
                } else { strcpy(tempJobs[idx++].status, "Running"); }


            }


        } else {
            printf("shell : procfile not found");
            return;
        }
    }

    bubbleSort(tempJobs, idx);
    for (int i = 0; i < idx; i++) {
        printf("[%d] %s %s with pid %d\n", tempJobs[i].idx, tempJobs[i].status, tempJobs[i].name, tempJobs[i].pid);
    }

}
#include "../Headers/root.h"

int getFlagsW(char input[], int *r, int *s) {

    int err = 0;
    int idx = 1;

    while (idx < strlen(input)) {
        if (input[idx] == 'r' || input[idx] == 'R') {
            *r = 1;
        } else if (input[idx] == 's' || input[idx] == 'S') {
            *s = 1;
        } else {
            err = 1;
            printf("ls: invalid option -- %c\n", input[idx]);
        }
        idx++;
    }
    return err;
}



typedef struct _tempJob
{
    char *name;
    int idx;
    pid_t pid;
    char *status;
} tempJob;

void swap(tempJob *a, tempJob *b)
{
    tempJob temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(tempJob arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j].name, arr[j + 1].name) > 0)
            {

                swap(&arr[j], &arr[j + 1]);
            }
}

void jobs(char command[])
{

    int idx = 0;
    tempJob tempJobs[MAX_JOBS];

    for (int i = 0; i < MAX_JOBS; i++)
    {
        tempJobs[i].name = (char *)malloc(sizeof(char) * MAX_COMMAND_SIZE);
        tempJobs[i].status = (char *)malloc(sizeof(char) * 10);
        memset(tempJobs[i].name, MAX_COMMAND_SIZE, '\0');
        tempJobs[i].idx = -1;
    }

    for (int i = 0; i < MAX_JOBS; i++)
    {
        if (jobPool[i].pid != -1)
        {
    

            tempJobs[idx].idx = i + 1;
            strcpy(tempJobs[idx].name, jobPool[i].name);
            tempJobs[idx].pid = jobPool[i].pid;

            char tempProc[100];
            memset(tempProc, 100, '\0');
            sprintf(tempProc, "/proc/%d/stat", jobPool[i].pid);
            FILE *fp = fopen(tempProc, "r");

            if (fp)
            {
                char t;

                while (t != ')')
                    t = fgetc(fp);
                fgetc(fp);
                t = fgetc(fp);

                if (t == 'T')
                {
                    strcpy(tempJobs[idx++].status, "Stopped");
                }
                else
                {
                    strcpy(tempJobs[idx++].status, "Running");
                }
            }
        }
    }

    bubbleSort(tempJobs, idx);  
    char ins[1000][1000];
    int tokens = tokenizeSpace(command, ins);
    int r = 0, s = 0;
    

    if(tokens >= 2){

        getFlagsW(ins[1], &r, &s);
    }


    
    

    
    for (int i = 0; i < idx; i++)
    {
        if(tokens == 1)
        printf("[%d] %s %s with pid %d\n", tempJobs[i].idx, tempJobs[i].status, tempJobs[i].name, tempJobs[i].pid);

        else {
            if(r == 1)  {
                if(!strcmp(tempJobs[i].status, "Running")){
                    printf("[%d] %s %s with pid %d\n", tempJobs[i].idx, tempJobs[i].status, tempJobs[i].name, tempJobs[i].pid);

                }
            }
             if(s == 1)  {
                if(!strcmp(tempJobs[i].status, "Stopped")){
                    printf("[%d] %s %s with pid %d\n", tempJobs[i].idx, tempJobs[i].status, tempJobs[i].name, tempJobs[i].pid);

                }
            }
        }

    }
}
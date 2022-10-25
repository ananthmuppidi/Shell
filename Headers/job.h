#ifndef _JOB_H_
#define _JOB_H_
#include <unistd.h>


 typedef struct _job{
    pid_t pid;
    char *name;
}job;



#endif

#include "../Headers/globals.h"
#include "../Headers/sizes.h"
#include "../Headers/globals.h"
#include "../Headers/history.h"
#include "../Headers/dir.h"
#include "../Headers/job.h"
#include "../Headers/jobHandler.h"
#include "../Headers/dir.h"

#include <stdlib.h>
#include <string.h>

void initializeConstants() {

    shellRootPath = (char *) malloc(sizeof(char) * MAX_PATH_SIZE);
    previousDirectory = (char *) malloc(sizeof(char) * MAX_PATH_SIZE);

    getShellRoot(shellRootPath);

    makeHistoryFile();

    jobPool = (job*) malloc(sizeof(job) * 1000);
    initializeJobPool(jobPool);

    strcpy(previousDirectory, "");

    timeTaken = 0.0;


}



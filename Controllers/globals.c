#include "../Headers/root.h"

void initializeConstants() {


    autocompleted = 0;
    errPid = 0;
    err = 0;


    shellRootPath = (char *) malloc(sizeof(char) * MAX_PATH_SIZE);
    previousDirectory = (char *) malloc(sizeof(char) * MAX_PATH_SIZE);
    currentForegroundName = (char*)malloc(sizeof(char) * MAX_COMMAND_SIZE);

    getShellRoot(shellRootPath);

    makeHistoryFile();

    jobPool = (job*) malloc(sizeof(job) * 1000);
    initializeJobPool(jobPool);

    strcpy(previousDirectory, "");

    timeTaken = 0.0;
    currentForeground = -1;

}



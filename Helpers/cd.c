#include "../Headers/cd.h"
#include "../Headers/dir.h"
#include "../Headers/sizes.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>


void changeDirectory(char path[], char shellRootPath[]){

    int chDirReturn = 0;

    char currentAbsoluteDir[MAX_PATH_SIZE];
    getcwd(currentAbsoluteDir, MAX_PATH_SIZE);

    printf("%s\n", currentAbsoluteDir);
    printf("HERE\n\n\n");
    strcat(currentAbsoluteDir, "/../../../../../../../../../../../../asdf");

    chDirReturn = chdir(currentAbsoluteDir);
    printf("\n %d  \n", chDirReturn);
    if(chDirReturn == -1){
        fprintf(stderr, "cd: %s: %s\n", strerror(errno), path) ;

    }
  





}
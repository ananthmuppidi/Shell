#include "../Headers/dir.h"
#include "../Headers/sizes.h"
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <assert.h>


void promptUser(char shellRootPath[])
{
    char prompt[MAX_PATH_SIZE];
    char hostname[MAX_USERNAME_SIZE];
    char currDir[MAX_PATH_SIZE];

    struct passwd *p = getpwuid(getuid()); // Check for NULL!
    gethostname(hostname, sizeof(hostname)); // Check the return value!

    getCurrDir(currDir, shellRootPath);

    
    for(int i = 0; i < 1000; i++) prompt[i] = '\0';

    strcat(prompt, p->pw_name);
    strcat(prompt, "@");
    strcat(prompt, hostname);
    strcat(prompt, ":");
    strcat(prompt, currDir);
    strcat(prompt, "> ");

    printf("%s", prompt);


}


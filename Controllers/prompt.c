#include "../Headers/dir.h"
#include "../Headers/sizes.h"
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <assert.h>
#include "../Headers/timeTaken.h"


void promptUser(char shellRootPath[])
{
    char prompt[MAX_PATH_SIZE];
    char hostname[MAX_USERNAME_SIZE];
    char currDir[MAX_PATH_SIZE];

    struct passwd *p = getpwuid(getuid()); // Check for NULL!
    gethostname(hostname, sizeof(hostname)); // Check the return value!

    getPromptCurrDir(currDir, shellRootPath);

    
    for(int i = 0; i < 1000; i++) prompt[i] = '\0';

    strcat(prompt, p->pw_name);
    strcat(prompt, "@");
    strcat(prompt, hostname);
    strcat(prompt, ":");
    strcat(prompt, currDir);

    if(timeTaken > 1.0){
        int cattime = (int) timeTaken;
        char append[1000];
        sprintf(append, "took %ds", cattime);
        timeTaken = 0.0;
        strcat(prompt, append);
    }
    strcat(prompt, "> ");


    printf("%s", prompt);

}

void getPrompt(char shellRootPath[], char buffer[])
{
    char prompt[MAX_PATH_SIZE];
    char hostname[MAX_USERNAME_SIZE];
    char currDir[MAX_PATH_SIZE];

    struct passwd *p = getpwuid(getuid()); // Check for NULL!
    gethostname(hostname, sizeof(hostname)); // Check the return value!

    getPromptCurrDir(currDir, shellRootPath);


    for(int i = 0; i < 1000; i++) prompt[i] = '\0';

    strcat(prompt, p->pw_name);
    strcat(prompt, "@");
    strcat(prompt, hostname);
    strcat(prompt, ":");
    strcat(prompt, currDir);
    strcat(prompt, "> ");

    strcpy(buffer, prompt);

}



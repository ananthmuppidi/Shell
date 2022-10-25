#include "../Headers/root.h"


void promptUser() {
    char prompt[MAX_PATH_SIZE];
    char hostname[MAX_USERNAME_SIZE];
    char currDir[MAX_PATH_SIZE];

    struct passwd *p = getpwuid(getuid()); // Check for NULL!
    gethostname(hostname, sizeof(hostname)); // Check the return value!

    getPromptCurrDir(currDir);


    for (int i = 0; i < MAX_PATH_SIZE; i++) prompt[i] = '\0';

    strcat(prompt, p->pw_name);
    strcat(prompt, "@");
    strcat(prompt, hostname);
    strcat(prompt, ":");
    strcat(prompt, "[");
    strcat(prompt, currDir);
    strcat(prompt, "]");

    if (timeTaken > 1.0) {
        int catTime = (int) timeTaken;
        char append[1000];
        sprintf(append, "[took %ds]", catTime);
        timeTaken = 0.0;
        strcat(prompt, append);
    }
    strcat(prompt, "$ ");
    printf("\r%s", prompt);

}

void getPrompt(char buffer[]) {

    char prompt[MAX_PATH_SIZE];
    char hostname[MAX_USERNAME_SIZE];
    char currDir[MAX_PATH_SIZE];

    struct passwd *p = getpwuid(getuid()); // Check for NULL!
    gethostname(hostname, sizeof(hostname)); // Check the return value!

    getPromptCurrDir(currDir);


    for (int i = 0; i < 1000; i++) prompt[i] = '\0';

    strcat(prompt, p->pw_name);
    strcat(prompt, "@");
    strcat(prompt, hostname);
    strcat(prompt, ":");
    strcat(prompt, currDir);
    strcat(prompt, "$ ");

    strcpy(buffer, prompt);

}



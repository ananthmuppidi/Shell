
#include "../Headers/headers.h"
#include "../Headers/sizes.h"
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <assert.h>


void promptUser()
{
    char prompt[MAX_PATH_SIZE];
    char hostname[MAX_PATH_SIZE];

    struct passwd *p = getpwuid(getuid()); // Check for NULL!
    
    gethostname(hostname, sizeof(hostname)); // Check the return value!

    
    for(int i = 0; i < 1000; i++) prompt[i] = '\0';

    strcat(prompt, p->pw_name);
    strcat(prompt, "@");
    strcat(prompt, hostname);

    printf("%s\n", prompt);


}


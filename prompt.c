#include "prompt.h"
#include "headers.h"
#include <unistd.h>
#include <pwd.h>
#include <string.h>

#define HOST_NAME_MAX 1000

void prompt()
{
    struct passwd *p = getpwuid(getuid()); // Check for NULL!
    printf("User name: %s\n", p->pw_name);

    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, sizeof(hostname)); // Check the return value!
    printf("Host name: %s\n", hostname);
}


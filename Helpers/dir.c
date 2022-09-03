#include "../Headers/dir.h"
#include "../Headers/sizes.h"
#include <unistd.h>
#include <string.h>

void getShellRoot(char buffer[])
{
    char shellRootPath[MAX_PATH_SIZE];
    getcwd(shellRootPath, MAX_PATH_SIZE);
    strcpy(buffer, shellRootPath);
}

int getCurrDir(char buffer[])
{
    char absoluteTempPath[MAX_PATH_SIZE];
    getcwd(absoluteTempPath, MAX_PATH_SIZE);
}

int getPromptCurrDir(char buffer[], char shellRootPath[])
{

    char absoluteTempPath[MAX_PATH_SIZE];
    getcwd(absoluteTempPath, MAX_PATH_SIZE);

    int isEqual = strcmp(shellRootPath, absoluteTempPath);
    if (!isEqual)
    {
        strcpy(buffer, "~");
        return 0; // the strings are equal then return home -> ~
    }

    if (isEqual < 0)
    { // actual Path is subdirectory of root
        int idx = 0;
        int i = 1;

        while (shellRootPath[idx] == absoluteTempPath[idx])
            idx++;
        while (absoluteTempPath[idx] != '\0')
            buffer[i++] = absoluteTempPath[idx++];

        return 0;
    }

    if (isEqual > 0)
    {
        strcpy(buffer, absoluteTempPath);
        return 0;
    }
}

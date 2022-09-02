#include "Headers/prompt.h"
#include "Headers/dir.h"
#include "Headers/sizes.h"
#include "Headers/cd.h"
#include <unistd.h>
#include <stdio.h>

int main()
{
    char shellRootPath[MAX_PATH_SIZE];
    getShellRoot(shellRootPath);

    char arr2[MAX_PATH_SIZE];

    promptUser(shellRootPath);  
    changeDirectory("THISISTHEARG", "");

    char currentAbsoluteDirTest[MAX_PATH_SIZE];

      getcwd(currentAbsoluteDirTest, MAX_PATH_SIZE);

    printf("\n%s\n", currentAbsoluteDirTest);
}

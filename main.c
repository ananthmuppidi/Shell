#include "Headers/prompt.h"
#include "Headers/dir.h"
#include "Headers/sizes.h"
#include <stdio.h>

int main()
{
    char shellRootPath[MAX_PATH_SIZE];
    getShellRoot(shellRootPath);

    char arr2[MAX_PATH_SIZE];

    
        promptUser(shellRootPath);
    

    
}

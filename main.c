#include "Headers/prompt.h"
#include "Headers/dir.h"
#include "Headers/sizes.h"
#include "Headers/cd.h"
#include <unistd.h>
#include <stdio.h>

int main()
{

  char shellRootPath[MAX_PATH_SIZE];
  char input[MAX_COMMAND_SIZE];

  getShellRoot(shellRootPath);


  promptUser(shellRootPath);
  getInput();
  tokenizeInput();
  

  
}

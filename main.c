#include "Headers/prompt.h"
#include "Headers/dir.h"
#include "Headers/sizes.h"
#include "Headers/cd.h"
#include "Headers/input.h"
#include <unistd.h>
#include <stdio.h>

int main()
{

  char shellRootPath[MAX_PATH_SIZE];


  getShellRoot(shellRootPath);

  while(1) {

      char inputTokens[10][MAX_COMMAND_SIZE];
      promptUser(shellRootPath);
      getInput(inputTokens);
      printf("%s", inputTokens[0]);

      // tokenizeInput();


  }
}

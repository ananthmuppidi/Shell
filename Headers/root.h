#ifndef __ROOT_H_
#define __ROOT_H_



// This section interfaces to all the commands that are implemented in controllers
#include "sig.h"
#include "fg.h"
#include "bg.h"
#include "jobs.h"
#include "cd.h"
#include "dir.h"
#include "pwd.h"
#include "ls.h"
#include "echo.h"
#include "discover.h"
#include "history.h"
#include "executeForeground.h"
#include "executeBackground.h"
#include "redirection.h"
#include "pipes.h"
#include "pinfo.h"


// This section has all the global variables
#include "globals.h"
#include "sizes.h"

// These are all the standard libraries that are required
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <libgen.h>
#include <grp.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <assert.h>

// This seciton contains intefaces to the rest of the helper commands that are not user implemented functions
#include "childHandler.h"
#include "execute.h"
#include "executeForeground.h"
#include "executeBackground.h"
#include "helpers.h"
#include "job.h"
#include "jobHandler.h"
#include "tokenizer.h"
#include "prompt.h"
#include "autocomplete.h"





#endif

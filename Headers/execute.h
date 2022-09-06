#ifndef _EXECUTE__H_
#define _EXECUTE__H_

/// @brief This function compares the input with all available commands and executes the appropriate command if found
/// @Param The command to be executed
/// @return Returns 1 on success, 0 if command not found
int execute(char command[], char shellRootPath[]);

#endif

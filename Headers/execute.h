#ifndef _EXECUTE__H_
#define _EXECUTE__H_

/// @brief This function compares the input with all available commands and executes the appropriate command if found
/// @Param The command to be executed
/// @return Returns 1 on success, 0 if command not found
int execute(char command[], char shellRootPath[]);

/// @breif Checks if there is a @ appended to the end of the command, indicating that the command must be run in the background
/// @param command Is the argument to check @ for. If there is a @, it removes it from the array.
/// @warning MAY modify the command array depending on wether @ was detected
/// @return Returns true if @ symbol was found
int checkBackground(char command[]);

#endif

#ifndef __CURR_DIR__
#define __CURR_DIR__


/// @brief Returns the absolute path of the working directory where the shell is started. 
/// @param buffer Char array where the path must be stored.
void getShellRoot(char buffer[]);

/// @brief Prints into buffer the path relative to where the shell is started (if the path is deeper than the shell root) or the absolute path (if it is the current ) . Returns wether the path provided is smaller than root, equal to root, or greater than root.
/// @param buffer Char array where the path must be stored. @param shellRootPath The absolute path to the root of the shell
void getPromptCurrDir(char buffer[], char shellRootPath[]);

/// @brief Returns the present working directory
/// @param buffer Buffer array where the present working directory is stored.
/// @return Returns 0 = Failure, 1 = Success.  
void getCurrDir(char buffer[]);

#endif

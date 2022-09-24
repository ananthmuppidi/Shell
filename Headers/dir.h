#ifndef __CURR_DIR__
#define __CURR_DIR__


/// @brief Returns the absolute path of the working directory where the shell is started. 
/// @param buffer Char array where the path must be stored.
void getShellRoot(char buffer[]);

/// @brief Prints into buffer the path relative to where the shell is started (if the path is deeper than the shell root) or the absolute path (if it is the current ) . Returns wether the path provided is smaller than root, equal to root, or greater than root.
/// @param buffer Char array where the path must be stored.
void getPromptCurrDir(char buffer[]);

/// @brief Returns the present working directory
/// @param buffer Buffer array where the present working directory is stored.
/// @return Returns 0 = Failure, 1 = Success.  
void getCurrDir(char buffer[]);

/// @brief Returns the absolute path a path that can be both relative and absolute
/// @param buffer Buffer array where the present working directory is stored.
/// @param arg The string that must be converted to absolute
/// @return Returns 0 = Failure, 1 = Success.
void getAbsolutePath(char arg[], char buffer[]);


#endif

#ifndef __CURR_DIR__
#define __CURR_DIR__


/// @brief Returns the absolute path of the working directory where the shell is started. 
/// @param buffer Char array where the path must be stored.
void getShellRoot(char buffer[]);


/// @brief Returns the path relative to where the shell is started.
/// @param buffer Char array where the path must be stored. @param shellRootPath The absolute path to the root of the shell
void getCurrDir(char buffer[], char shellRootPath[]);

#endif
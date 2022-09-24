// MAKING THE ASSUMPTION THAT THERE IS NO DIRECTORY OF THE NAME OF THE FLAGS

#ifndef _LS__H_
#define _LS__H_

/// @brief This is a function that lists all the directories, files and optionally the hidden files.
/// @aparams Accepts the input for the options and the path. Can provide as many directories as required
/// @aparams The path to the root of the shell
void ls(char args[]);

/// @breif Prints the name of the directory
/// @param absolutePath The absolute path of the directory that needs its contents listed
/// @param Set to one if new line characters are required
void printDirectory(int line);


/// @param Prints the directory list along with

#endif

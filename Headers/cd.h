#ifndef __CD_H__
#define __CD_H__

/// @brief Changes directory as passed into path (relative to the shell path)
/// @param path Path provided to cd
/// @param shellRootPath Where the shell is intialized
void changeDirectory(char path[], char shellRootPath[]);

#endif
#ifndef __SIZES_H__
#define __SIZES_H__

/// @brief This is the max size that any path string can be.
#define MAX_PATH_SIZE 10000

/// @brief This is the max size that any user name string can be.
#define MAX_USERNAME_SIZE 1000

/// @brief This is the max size of a command in the terminal.
#define MAX_COMMAND_SIZE 10000

/// @breif This is the max number of tokens in a command.
#define MAX_TOKENS 100

/// @brief This is max size of each token in a given command
#define MAX_TOKEN_SIZE 1000

/// @breif This is the max number of files / directories / devices that can be printed in an ls command before return sixsegv signal.
#define MAX_LS_ENTITIES 5000

/// @brief This is the max string size of the name of files / directories / devices.
#define MAX_NAME_SIZE 1000

#endif
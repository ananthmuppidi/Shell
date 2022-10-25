#ifndef _HISTORY__H_
#define _HISTORY__H_

///@breif Prints 10 history.
void printHistory();

///@brief Adds the given command to history, after checking if the last instance is already there. Handles all ( n </=/> 10 cases).
///@param command command to be added (after sanitization)
///@param shellRootDirectory where the shell is started

void addToHistory(char command[]);
void makeHistoryFile();

#endif

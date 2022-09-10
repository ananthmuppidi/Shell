#include "../Headers/ls.h"
#include "../Headers/sizes.h"
#include "../Headers/dir.h"
#include "../Headers/tokenizer.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../Headers/helpers.h"
#include <pwd.h>
#include <time.h>
#include <libgen.h>
#include <grp.h>


// ASSUPTION: USED used listxattr which is not POSIX compliant but does run on OSX and Limux distros
// call closedir
// error
// wont resolve symlinks
// total print
// folder:
// cd -
// colour coding only colours the name and not the permissions
// Options alwats resolce from anywhere and are applied to all the files

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

int getFlags(char input[], int *a, int *l) {

    int err = 0;
    int idx = 1;

    while (idx < strlen(input)) {
        if (input[idx] == 'a' || input[idx] == 'A') {
            *a = 1;
        } else if (input[idx] == 'l' || input[idx] == 'L') {
            *l = 1;
        } else {
            err = 1;
            printf("ls: invalid option -- %c\n", input[idx]);
        }
        idx++;
    }
    return err;
}

void printLsInfo(char path[], int hardLinks, int userSize, int groupSize, int storageSize, int a) {

    DIR *dp;
    dp = opendir(path);

    if (!dp) {
        perror(path);
        return;
    }

    struct dirent **ep;
    int n;

    n = scandir(path, &ep, 0, alphasort);
    if (n < 0) {
        perror("scandir");
    } else {
        for (int i = 0; i < n; i++) {
            {
                if (!(ep[i]->d_name[0] == '.' && !a)) {
                    char fullPath[MAX_PATH_SIZE];
                    strcpy(fullPath, path);

                    if (fullPath[strlen(fullPath) - 1] != '/') {
                        strcat(fullPath, "/");
                        strcat(fullPath, ep[i]->d_name);
                    } else {
                        strcat(fullPath, ep[i]->d_name);
                    }

                    struct stat stats;

                    if (stat(fullPath, &stats) == -1) {
                        continue;
                    }

                    char tempArray[MAX_NAME_SIZE];

                    if (S_ISREG(stats.st_mode)) printf("-");
                    else if (S_ISDIR(stats.st_mode)) printf("d");
                    else if (S_ISCHR(stats.st_mode)) printf("c");
                    else if (S_ISBLK(stats.st_mode)) printf("b");
                    else if (S_ISFIFO(stats.st_mode)) printf("f");
                    else if (S_ISSOCK(stats.st_mode)) printf("s");
                    else printf("-");

                    (stats.st_mode & S_IRUSR) ? printf("r") : printf("-");
                    (stats.st_mode & S_IWUSR) ? printf("w") : printf("-");
                    (stats.st_mode & S_IXUSR) ? printf("x") : printf("-");
                    (stats.st_mode & S_IRGRP) ? printf("r") : printf("-");
                    (stats.st_mode & S_IWGRP) ? printf("w") : printf("-");
                    (stats.st_mode & S_IXGRP) ? printf("x") : printf("-");
                    (stats.st_mode & S_IROTH) ? printf("r") : printf("-");
                    (stats.st_mode & S_IWOTH) ? printf("w") : printf("-");
                    (stats.st_mode & S_IXOTH) ? printf("x") : printf("-");
                    printf(" ");

                    if (countDigits(stats.st_nlink) < hardLinks) {
                        int digits = countDigits(stats.st_nlink);
                        int spaces = hardLinks - digits;
                        for (int i = 0; i < spaces; i++) {
                            printf(" ");
                        }
                        printf("%d ", stats.st_nlink);

                    } else {
                        printf("%d ", stats.st_nlink);
                    }

                    struct group *gid;
                    gid = getgrgid(stats.st_gid);

                    struct passwd *pw;
                    pw = getpwuid(stats.st_uid);

                    if (strlen(pw->pw_name) < userSize) {
                        int chars = strlen(pw->pw_name);
                        int spaces = userSize - chars;
                        for (int i = 0; i < spaces; i++) {
                            printf(" ");
                        }
                        printf("%s ", pw->pw_name);
                    } else {
                        printf("%s ", pw->pw_name);
                    }

                    gid = getgrgid(stats.st_gid);
                    if (strlen(gid->gr_name) < groupSize) {
                        int chars = strlen(gid->gr_name);
                        int spaces = groupSize - chars;
                        for (int i = 0; i < spaces; i++) {
                            printf(" ");
                        }
                        printf("%s ", gid->gr_name);
                    } else {
                        printf("%s ", gid->gr_name);
                    }
                    if (countDigits(stats.st_size) < storageSize) {
                        int digits = countDigits(stats.st_size);
                        int spaces = storageSize - digits;
                        for (int i = 0; i < spaces; i++) {
                            printf(" ");
                        }
                        printf("%lld ", stats.st_size);
                    } else {
                        printf("%lld ", stats.st_size);
                    }

                    struct tm *time;
                    char timeStampArray[200];

                    time = localtime(&stats.st_mtime);
                    strftime(timeStampArray, sizeof(timeStampArray), "%b %d %R", time);
                    printf("%s ", timeStampArray);

                    if (stats.st_mode & S_IXUSR) printf(GREEN);
                    if (S_ISDIR(stats.st_mode)) printf(BLUE);
                    printf("%s\n", ep[i]->d_name);
                    printf(RESET);
                }
            }
        }
    }
}

void printLs(char path[], int a, int l, int printName) {



    if (l == 0) {
        DIR *dp;
        dp = opendir(path);

        if (!dp) {
            char err[MAX_PATH_SIZE];
            sprintf(err, "ls : %s", basename(path));
            perror(err);
            return;
        }
        if (printName == 1) {
            char pathCopy[MAX_PATH_SIZE];
            strcpy(pathCopy, path);
            char *baseName;
            baseName = basename(pathCopy);
            printf("%s:\n", baseName);
        }


        struct dirent **ep;
        int n;

        n = scandir(path, &ep, 0, alphasort);
        if (n < 0) {
            perror("scandir");
            return;
        }
        for (int i = 0; i < n; i++) {
            if (!(ep[i]->d_name[0] == '.' && !a)) {
                char fullPath[MAX_PATH_SIZE];
                strcpy(fullPath, path);

                if (fullPath[strlen(fullPath) - 1] != '/') {
                    strcat(fullPath, "/");
                    strcat(fullPath, ep[i]->d_name);
                } else {
                    strcat(fullPath, ep[i]->d_name);
                }
                struct stat stats;
                if (stat(fullPath, &stats) == -1) {
                    continue;
                }
                if (stats.st_mode & S_IXUSR) printf(GREEN);
                if (S_ISDIR(stats.st_mode)) printf(BLUE);
                printf("%s\n", ep[i]->d_name);
                printf(RESET);
            }
        }
    }
    if (l == 1) {
        long long total = 0;
        int hardLinks = 4;
        int userSize = 0;
        int groupSize = 0;
        int storageSize = 6;

        DIR *dp;
        dp = opendir(path);

        if (!dp) {
            char err[MAX_PATH_SIZE];
            sprintf(err, "ls : %s", basename(path));
            perror(err);
            return;
        }

        if (printName == 1) {
            char pathCopy[MAX_PATH_SIZE];
            strcpy(pathCopy, path);
            char *baseName;
            baseName = basename(pathCopy);
            printf("%s:\n", baseName);
        }

        struct dirent **ep;

        int n;
        n = scandir(path, &ep, 0, alphasort);
        if (n < 0) {
            perror("scandir");
            return;
        }
        char fullPath[MAX_PATH_SIZE];
        for (int i = 0; i < n; i++) {

            strcpy(fullPath, path);

            if (fullPath[strlen(fullPath) - 1] != '/') {
                strcat(fullPath, "/");
                strcat(fullPath, ep[i]->d_name);
            } else {
                strcat(fullPath, ep[i]->d_name);
            }

            struct stat stats;
            if (stat(fullPath, &stats) == -1) {
                continue;
            }
            total += (stats.st_blocks * 512 + 1023) / 1024;
            if (!(ep[i]->d_name[0] == '.' && !a)) {

                hardLinks = max(hardLinks, countDigits(stats.st_nlink));

                struct passwd *pw;
                pw = getpwuid(stats.st_uid);
                userSize = max(userSize, strlen(pw->pw_name));

                struct group *gid;
                gid = getgrgid(stats.st_gid);
                groupSize = max(groupSize, strlen(gid->gr_name));

                storageSize = max(storageSize, countDigits(stats.st_size));
            }
        }
        printf("total: %lld\n", total);
        printLsInfo(path, hardLinks, userSize, groupSize, storageSize, a);
    }
    return;


}

void ls(char args[], char shellRootPath[]) {

    int tokens;


    char tokenizedInput[MAX_TOKENS][MAX_TOKEN_SIZE];
    tokens = tokenizeSpace(args, tokenizedInput);

    int a = 0;
    int l = 0;

    char currentLsDirectory[MAX_PATH_SIZE];
    getCurrDir(currentLsDirectory);

    if (tokens == 1) {
        printLs(currentLsDirectory, 0, 0, 0);
        return;
    }
    int flagCount = 0; // Counts the number of directories provided to the command
    for (int i = 1; i < tokens; i++) { // skipping over the ls token

        // check for flags first
        if (tokenizedInput[i][0] == '-' && tokenizedInput[i][1] != '\0') {
            flagCount++;
            int err = getFlags(tokenizedInput[i], &a, &l);
            if (err) return;
        }
    }

    // Now we know flag count, and we know that one token is ls
    int dirCount = tokens - 1 - flagCount;
    if (dirCount == 0) {
        printLs(currentLsDirectory, a, l, 0);
        return;
    }
    if (dirCount == 1) {
        for (int i = 1; i < tokens; i++) {
            if (!(tokenizedInput[i][0] == '-' && tokenizedInput[i][1] != '\0')) {
                char absPath[MAX_PATH_SIZE];
                getAbsolutePath(tokenizedInput[i], absPath, shellRootPath);
                printLs(absPath, a, l, 0);
            }
        }
        return;
    } else {
        for (int i = 1; i < tokens; i++) {
            if (!(tokenizedInput[i][0] == '-' && tokenizedInput[i][1] != '\0')) {
                char absPath[MAX_PATH_SIZE];
                getAbsolutePath(tokenizedInput[i], absPath, shellRootPath);
                printLs(absPath, a, l, 1);
            }
        }

    }
}



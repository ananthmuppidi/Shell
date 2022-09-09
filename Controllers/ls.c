#include "../Headers/ls.h"
#include "../Headers/sizes.h"
#include "../Headers/dir.h"
#include "../Headers/tokenizer.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/xattr.h>
#include "../Headers/helpers.h"
#include <pwd.h>
#include <time.h>
#include <libgen.h>
#include <sys/types.h>
#include <grp.h>


// ASSUPTION: USED used listxattr which is not POSIX compliant but does run on OSX and Limux distros
// call closedir
// error

int getFlags(char input[], int *a, int *l) {

    int err = 0;
    int idx = 0;
    while (input[idx++] != 0) {
        if (input[idx == 'a'] || input[idx == 'A']) {
            *a = 1;
        }
        if (input[idx == 'l'] || input[idx == 'L']) {
            *l = 1;
        } else {
            err = 1;
        }
    }
    return err;
}

void printLsInfo(char finalArray[][MAX_NAME_SIZE], int *finalArrayIdx,  char path[], int hardLinks, int userSize, int groupSize, int storageSize) {

    DIR *dp;
    dp = opendir(path);

    if (!dp) {
        perror(path);
        return;
    }

    struct dirent *ep;

    while ((ep = readdir(dp))) {

        char fullPath[MAX_PATH_SIZE];
        strcpy(fullPath, path);
        strcat(fullPath, "/");
        strcat(fullPath, ep->d_name);

        struct stat stats;
        if (stat(fullPath, &stats) == -1) {
            perror("stat");
            return;
        }

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
        printf(" %s\n", ep->d_name);

        *finalArrayIdx
    }
}

void printLs(char path[], int a, int l) {

    char finalArray[MAX_LS_ENTITIES][MAX_NAME_SIZE]; // This is the array where all the files and directories are stored.
    int finalArrayIdx = 0;
//
//    if (l == 0 || a == 0) {
//    DIR *dp;
//    dp = opendir(path);
//
//    if (!dp) {
//        perror(path);
//        return;
//    }
// struct dirent *ep;
//        while ((ep = readdir(dp))) {
//            if (ep->d_name[0] != '.') {
//                printf(" %s\n", ep->d_name);
//            }
//        }
//    }
//
//    if (l == 0 || a == 1) {
//        while ((ep = readdir(dp))) {
//            printf(" %s\n", ep->d_name);
//        }
//    }

    if (l == 0 || a == 0) {

        int hardLinks = 4;
        int userSize = 0;
        int groupSize = 0;
        int storageSize = 6;

        DIR *dp;
        dp = opendir(path);

        if (!dp) {
            perror(path);
            return;
        }

        struct dirent *ep;

        while ((ep = readdir(dp))) {
            char fullPath[MAX_PATH_SIZE];
            strcpy(fullPath, path);
            strcat(fullPath, "/");
            strcat(fullPath, ep->d_name);


            struct stat stats;
            if (stat(fullPath, &stats) == -1) {
                perror("stat");
                return;
            }

            hardLinks = max(hardLinks, countDigits(stats.st_nlink));

            struct passwd *pw;
            pw = getpwuid(stats.st_uid);
            userSize = max(userSize, strlen(pw->pw_name));

            struct group *gid;
            gid = getgrgid(stats.st_gid);
            groupSize = max(groupSize, strlen(gid->gr_name));

            storageSize = max(storageSize, countDigits(stats.st_size));
        }
        printLsInfo(path, hardLinks, userSize, groupSize, storageSize);
        return;
    }


}

void ls(char args[], char shellRootPath[]) {

    int tokens;

    int a = 0;
    int l = 0;

    char tokenizedInput[MAX_TOKENS][MAX_TOKEN_SIZE];
    tokens = tokenizeSpace(args, tokenizedInput);

    if (tokens == 1) {
        char currentDirectory[MAX_PATH_SIZE];
        getCurrDir(currentDirectory);
        printLs(currentDirectory, 0, 0);
    }
    tokens--; // ls command is also counted as a token, and now it is removed

}



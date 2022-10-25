#include "../Headers/input.h"
#include <string.h>
#include "../Headers/history.h"
#include <stdio.h>
#include "../Headers/globals.h"
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "../Headers/prompt.h"
#include "../Headers/root.h"
#include "../Headers/autocomplete.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void getInput(char buffer[]) {
    strcpy(buffer, "");

    char *inp = malloc(sizeof(char) * MAX_COMMAND_SIZE);
    char c;

    setbuf(stdout, NULL);
    enableRawMode();

    memset(inp, '\0', MAX_COMMAND_SIZE);
    int pt = 0;

    while (read(STDIN_FILENO, &c, 1) == 1) {

        if (c == 4) exit(0);
        if (c == 9 || c == 127) {
            if (c == 127) {
                if(pt > 0){
                    printf("\b \b");
                    inp[--pt] = '\0';
                }
            } else {
                autoComplete(inp, pt);
            }
        } else if (c != 10) {
            inp[pt++] = c;
            printf("%c", c);
        }
        if (c == 10) {
            break;
        }


    }
    disableRawMode();
    memset(buffer, MAX_COMMAND_SIZE, '\0');
    if (strlen(inp) != 0) {
        strcpy(buffer, inp);
        addToHistory(buffer);
        printf("\n");
    } else {
        buffer[0] = '\0';
        printf("\n");
    }
}
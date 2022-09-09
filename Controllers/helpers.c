#include "../Headers/helpers.h"

int countDigits(int n) {
    int result = 0;
    while (n) {
        n /= 10;
        result++;
    }
    return result;
}

int max(int a, int b){
    return a > b ? a : b;
}
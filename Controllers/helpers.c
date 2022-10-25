#include "../Headers/root.h"

int countDigits(int n) {
    if(n == 0) return 1;
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
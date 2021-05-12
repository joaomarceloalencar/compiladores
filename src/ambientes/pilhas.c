// Pilhas.c
#include <stdio.h>

int x = 2;

void g(int);

void f(int n) {
    static int x = 1;
    g(n);
    x--;
}

void g(int m) {
    int y = m - 1;
    if (y > 0) {
        f(y);
        x--;
        g(y);
    }
}

int main() {
    g(x);
    return 0;
}

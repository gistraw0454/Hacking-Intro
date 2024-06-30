#include <stdio.h>

int sum(int a, int b, int c) {
    return a + b + c;
}

int main()
{
    int s;

    s = sum(1, 2, 3);
    printf("% d\n", s);

    return 0;
}


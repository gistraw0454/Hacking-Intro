#include <stdio.h>
int main() {
    int lv = 2;
    switch (lv) {
    case 0:
        printf("lv is 0\n");
        break;
    case 1:
        printf("lv is 1\n");
        break;
    case 2:
        printf("lv is 2\n");
        break;
    case 3:
        printf("lv is 3\n");
        break;
    case 4:
        printf("lv is 4\n");
        break;
    default:
        printf("default");
    }
    return 0;
}
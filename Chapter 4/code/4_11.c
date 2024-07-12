#include <stdio.h>
#include <string.h>

const int kBufSize=16;

int main(int argc, char* argv[]){
    char buf_one[kBufSize]="hello";
    char buf_two[kBufSize]="World";

    strcpy(buf_two,argv[1]);

    printf("&buf_one = %p, content = %s\n",&buf_one,buf_one);
    printf("&buf_two = %p, content = %s\n",&buf_two,buf_two);
}
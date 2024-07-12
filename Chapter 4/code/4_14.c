//예제 4-14 ) 형식 문자열 취약점이 있는 소스 코드
#include <stdio.h>
int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr,"Usage>%s [string]\n",argv[0]);
    }
    printf(argv[1]);
}
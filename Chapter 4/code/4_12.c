//예제 4-12 ) 각 변수의 메모리 주소를 출력하는 프로그램
#include <stdio.h>
int main(){
    int buf11, buf12;
    int buf21, buf22;
    printf("&buf11 = %p, &buf12 = %p\n",&buf11,&buf12);
    printf("&buf21 = %p, &buf22 = %p\n",&buf21,&buf22);
}
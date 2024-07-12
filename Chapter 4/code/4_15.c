//예제 4-15 ) 정수형 오버플로우 발생
#include <stdio.h>
int main(){
    int a=1234567890;
    int b= 1234567890;
    int c= a+b;

    printf("a   = %d\n",a);
    printf("b   = %d\n",b);
    printf("a + b = %d\n",a+b);
}
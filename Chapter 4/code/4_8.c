//예제 4-8 ) 정수형 변수와 문자열 형태의 변수를 문자열로 출력하는 코드
#include <stdio.h>

int main()
{
    int a=0x00434241;
    char b[4] = "ABC";

    printf("%s\n",b);
    printf("%s\n",&a);

    return 0;
}
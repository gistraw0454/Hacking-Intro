//���� 4-8 ) ������ ������ ���ڿ� ������ ������ ���ڿ��� ����ϴ� �ڵ�
#include <stdio.h>

int main()
{
    int a=0x00434241;
    char b[4] = "ABC";

    printf("%s\n",b);
    printf("%s\n",&a);

    return 0;
}
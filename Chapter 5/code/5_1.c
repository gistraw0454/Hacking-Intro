// ���� 5-1 ) ������ ���� �����÷ο� ��
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void vuln(const char* src){
    char temp[10];
    strcpy(temp,src);
}
int32_t main(int32_t argc, char** argv){
    char buf[100];
    fgets(buf,sizeof(buf),stdin);
    vuln(buf);
    return 0;
}
//예제 4-9 ) 1바이트 오버플로우에 취약한 예제
#include <stdio.h>
#include <string.h>

const int kBufSize = 128;

void off_by_one1(char* in_buf){
    char out_buf[128]="";
    int in_buf_len=strlen(in_buf);
    for (int i=0; i<=in_buf_len;i++){
        out_buf[i]=in_buf[i];
    }
}

void off_by_one2(char* in_buf){
    char out_buf[128]="";
    int in_buf_len=strlen(in_buf);

    if(in_buf_len<=kBufSize){
        strcpy(out_buf,in_buf);
    }

    printf("%s\n",out_buf);
}

int main(int argc, int* argv[]){
    off_by_one1(argv[1]);
}
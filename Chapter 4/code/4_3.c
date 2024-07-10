//예제 4-3 ) 인자로 디렉터리명을 받아 파일 목록을 출력하는 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int kCmdLen = 400;
void print_dir_with_system(char *path){
    char cmd[kCmdLen];
    const char* cmd_prefix = "dir /B";
    if (strlen(cmd_prefix)+strlen(path)+1<kCmdLen){
        _snprintf(cmd,kCmdLen,"%s %s",cmd_prefix,path); //cmd_prefix와 path를 %s %s 로 결합한 문자열을 kCmdLen만큼 cmd에 저장
    }
    system(cmd);
}

int main(int argc, char* argv[]){
    char* exec_file = argv[0];  //실행파일명
    char* path = argv[1];   //경로
    if (argv==2) print_dir_with_system(path);
    else printf("Usage> %s [filename]\n",exec_file);
    return 0;
}
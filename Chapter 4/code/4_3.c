//���� 4-3 ) ���ڷ� ���͸����� �޾� ���� ����� ����ϴ� ���α׷�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int kCmdLen = 400;
void print_dir_with_system(char *path){
    char cmd[kCmdLen];
    const char* cmd_prefix = "dir /B";
    if (strlen(cmd_prefix)+strlen(path)+1<kCmdLen){
        _snprintf(cmd,kCmdLen,"%s %s",cmd_prefix,path); //cmd_prefix�� path�� %s %s �� ������ ���ڿ��� kCmdLen��ŭ cmd�� ����
    }
    system(cmd);
}

int main(int argc, char* argv[]){
    char* exec_file = argv[0];  //�������ϸ�
    char* path = argv[1];   //���
    if (argv==2) print_dir_with_system(path);
    else printf("Usage> %s [filename]\n",exec_file);
    return 0;
}
//���� 4-14 ) ���� ���ڿ� ������� �ִ� �ҽ� �ڵ�
#include <stdio.h>
int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr,"Usage>%s [string]\n",argv[0]);
    }
    printf(argv[1]);
}
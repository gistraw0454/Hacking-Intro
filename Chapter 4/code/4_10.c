//���� 4-10 ) �������� ���׿� ����� �ڵ�
#include <stdio.h>
int main(){
    char* ptr= (char*)malloc(SIZE);
    //...
    if (abrt){
       free(ptr); 
    }
    //...
    free(ptr);
}
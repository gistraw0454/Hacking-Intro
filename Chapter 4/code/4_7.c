//���� 4-7 ) ������ MyThreadFunction() �Լ�
#include <stdio.h>
#include <windows.h>

const int kLoopCount = 400;
const int kNumThread = 4;
const int kIncreaseLoopCount = kLoopCount/kNumThread;
int total_count_ = 0;

DWORD WINAPI MyThreadFunction (LPVOID lpParam){
    for (int i=0; i<kIncreaseLoopCount;i++) total_count_++;
    return 0;
}

void concurrent_solver(){
    total_count_=0;
    HANDLE hThreadArray[kNumThread];
    DWORD dwThreadIdArray[kNumThread];

    for (int i=0; i<kNumThread;i++){
        hThreadArray[i]=CreateThread(
            NULL,   //�⺻ ���� �ĺ��� ���
            0,  //�⺻ ���� ������ ���
            MyThreadFunction,   //������� ������ �Լ� �̸�
            NULL,   //�����忡 ���޵� ����
            0,  //���� �÷���
            &dwThreadIdArray[i]);   //������ �ĺ��ڸ� ������ ����
    }

    WaitForMultipleObjects(kNumThread,hThreadArray,TRUE,INFINITE);

    for (int i=0; i<kNumThread;i++) CloseHandle(hThreadArray[i]);
    
}
int main(){
    while(1){
        concurrent_solver();

        printf("total_count_ = %d\n",total_count_);

        if (total_count_ != kLoopCount){
            getchar();
        }
    }
    return 0;
}
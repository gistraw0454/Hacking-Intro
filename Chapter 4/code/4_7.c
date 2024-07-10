//예제 4-7 ) 수정된 MyThreadFunction() 함수
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
            NULL,   //기본 보안 식별자 사용
            0,  //기본 스택 사이즈 사용
            MyThreadFunction,   //스레드로 실행할 함수 이름
            NULL,   //스레드에 전달될 인자
            0,  //생성 플래그
            &dwThreadIdArray[i]);   //스레드 식별자를 저장할 변수
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
//예제 4-4 ) 병행성 테스트를 위한 코드
#include <stdio.h>
#include <windows.h>

const int kLoopCount = 4*100;
int total_count_ = 0;
int main(){
    for (int i=0; i<kLoopCount;i++){
        total_count_++;
    }
    printf("total_count_ = %d\n",total_count_);
    return 0;
}
//출력
//total count =400
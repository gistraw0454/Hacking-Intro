//예제 4-10 ) 더블프리 버그에 취약한 코드
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
//예제 4-13 ) 형식 문자열 사용 예제
#include <stdio.h>
using namespace std;

const char* name[]={"Jeff Dean","Sanjay Ghemawat","Sebastian Thrun","Larry Page","Sergey Brin"};
const int score[] ={1968,-1,1967,1973,1973};
const int num_of_people=sizeof(score)/sizeof(int);
int main(){
    printf("%20s %s\n","Name","Brith year");
    for (int i=0;i<num_of_people;i++) printf("%20s %d\n",name[i],score[i]);
}

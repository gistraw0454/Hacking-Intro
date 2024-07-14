## 🌈 Chapter 1: 맛보기
- 익스플로잇 (exploit) : 보안취약점을 이용해 임의의 권한을 얻는것 == 취약점 공격
### 🔥 취약점 찾는 방법
#### 소스 코드 검사 (Auditing)
- 소프트웨어의 원본소스 코드를 하나씩 분석하면서 취약점을 찾는 방법
```c
// 예제 5-1 ) 간단한 스택 오버플로우 예
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void vuln(const char* src){
    char temp[10];
    strcpy(temp,src);
}
int32_t main(int32_t argc, char** argv){
    char buf[100];
    fgets(buf,sizeof(buf),stdin);
    vuln(buf);
    return 0;
}
```
(일반적 감사방법)
1. 사용자가 컨트롤할 수 있는 변수나 흐름 찾기
    - fgets로 입력을 받으니 함수의 호출 이후부터 buf변수를 컨트롤 가능
2. 컨트롤 가능한 buf변수의 흐름을 추적하며 취약점이 발생할 수 있는지 판정
    - buf 변수가 vuln 함수의 인자로 들어가고, vuln함수 내에서 다시 strcpy함수의 인자로 주어진다
    - **vuln 함수의 지역 변수인 tmp변수의 크기보다 인자로 주어진 buf크기가 더 크면 스택 오버플로우 취약점 발생!!**
#### 바이너리 검사
- 소스 코드를 구할수 없을때, 바이너리를 분석하며 어셈블리어를 봐야함. => 툴을 쓰자.
#### 퍼징 (Fuzzing)
- 소프트웨어의 입력값 (파일 포맷, 프로토콜)을 자동으로 생성해 소프트웨어에 입력하고 그 결과를 통해 취약점을 찾는 방법
    - **퍼저 (Fuzzer)** : 퍼징을 수행하는 툴
    - 퍼저 동작 과정
        1. 입력값 생성
        2. 소프트웨어 실행 및 입력
        3. 소프트웨어 모니터링 및 결과 분석
        4. 다시 과정 1수행
    - 퍼저 제작과정
    1. 퍼저의 대상이될 소프트웨어 정하기 (ex 동영상 플레이어)
    2. 입력값의 기본 모델 정하기 (ex avi, mp4, mkv 등)
        - 결정한 파일 포맷의 샘플 파일 몇개를 구글링으로 구한뒤 이를 모델로 삼는다.
        - 샘플파일은 1MB 안넘는게 좋다. (파일 포맷 구조상 대부분의 영역이 취약점과는 대체로 무관하기 때문)
    3. 기본 모델로 선택한 샘플파일을 바탕으로 새로운 모델을 생성하는 코드 작성 (`뮤테이션``mutation`)
        ```py
        # 예제 5-2 ) 입력 데이터의 일부를 무작위 변경하는 파이썬 함수와 50글자의 A를 해당 함수에 넣었을 때 변경된 값의 출력 결과
        import random

        def mutate(data, n=20):
            tmp = [c for c in data]
            for _ in range(n):
                tmp[random.randint(0, len(tmp) - 1)] = chr(random.randint(0, 255))
            return ''.join(tmp)

        print(repr(mutate('A' * 50)))
        print(repr(mutate('A' * 50)))
        print(repr(mutate('A' * 50)))
        print(repr(mutate('A' * 50)))
        ```
        - 입력 데이터의 일부를 무작위로 변경하는 간단한 파이썬 함수와 간단히 50글자의 a를 해당 함수에 넣었을 때 변경된 값을 출력한 것. 실제 퍼저 구현에서는 A대신 샘플 파일의 내용을 인자로 넣으면 됨.
    4. 모니터링 단계
        - 보통 파이썬으로 구현된 디버거를 소프트웨어에 붙여 실행하기도함.
            - 윈도우에서 기본으로 제공하는 Error Reporting기능을 사용해 구현해보자.
                - Error Reporting : 소프트웨어 실행중 예외가 발생하면 dump파일로 해당 정보를 저장해줌
                    - dump 파일은 windbg 에서 파싱할 수 있으므로, windbg의 커맨드라인버전인 cdb로 간단히 명령어 몇 줄만 입력하면 예외 정보를 얻어올 수 있다.
            - Error Reporting 작동시키는 방법
                - 레지스트리 HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows\Windows Error Reporting 경로에 LocalDumps라는 이름의 키를 생성해주고, DontShowUI라는 이름의 DWORD값을 1로 주면됨.
                    - 예외 발생하며 죽을때마다 %localappdata%\CrashDumps경로에 dmp파일이 저장
            - cdb가 실행된 이후에 windbg와 같이 명령어를 입력할 수 있으며 `!analyze -v` 명령어를 입력하면 크래시의 자세한 정보를 볼 수 있다.
            - `cdb-exe -z <dump경로> -c "!analyze -v;q" 로도 cdb의 인자로 전해줄 수 있다.
            - 모니터링 스크립트는 위의 명령줄을 실행한뒤 이를 파싱해 로그로 남겨주기만하면됨. -> 낡은 방법이긴함.
            
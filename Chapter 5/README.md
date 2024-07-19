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
            
### 🧮 취약점의 종류
#### 메모리오염
- 메모리를 직접 다루는 언어 C/C++ 등에서 주로 발생하며, 커널을 포함한 많은 주류 소프트웨어들이 이러한 언어들로 작성되어있기에 메모리 오염 취약점이 자주 발견된다
- **스택 버퍼 오버플로우**
    - 지역변수의 정해진 크기를 넘어서까지 데이터를 입력하는 것
    - x86, x86_64 리틀인디안 아키텍처의 스택 구조상 sfp나 ret가 뒤쪽에 존재하므로 이를 덮어 익스플로잇한다.
    - canary 같은 미티게이션으로 인해 특수한 경우가 아니면 이 한 취약점으론 익스플로잇 불가. (memory leak 계열 취약점 더 필요)
- **힙 오버플로우**
    - 힙 변수의 정해진 크기를 넘어서까지 데이터를 입력하는 것
    - 힙헤더를 덮어 익스플로잇 시도할 수도 있고, 변수 뒤쪽에있는 다른 객체를 덮어 이를 통해 익스플로잇을 하기도함
- **널 포인터 역참조**
    - 어떤 이유에서든지 널 포인터를 참조할 때 발생하는 것
    - 할당 실패한 포인터나 다 쓰고 해제된 포인터를 참조하며 발생, 대부분의 경우 익스플로잇 불가
- **해제 후 사용**
    - 힙에 관련된 취약점. 이미 해제된 객체 포인터를 참조하면서 발생
    - 익스프로잇은 대부분 이미 해제된 객체에 원하는 값을 할당한 뒤 이를 다시 참조하게끔 함으로써 수행

### 웹에서의 버그헌팅
#### 제로보드 XE 원격코드실행

### 안드로이드에서 버그헌팅
#### 애플리케이션 권한 상승 취약점
- 애플리케이션에 부여된 권한을 강제로 상승시키는 취약점
    - 아무 권한 없는 애플리케이션이 문자메세지를 가로채거나 연락처를 유출하는 행위등을 할 수 있음
- 일반적으로 이런 로컬 상승 취약점은 로컬에서의 쉘이 있어야 하기 때문에 단독으로 운용되기는 어렵고, 주로 다른 원격 취약점과의 연계로 이용된다.

- 안드로이드는 애플리케이션마다 각기 다른 권한을 부여할 수 있고, 해당 애플리케이션이 이미 부여된 권한 이상의 행동을 하는 것이 불가능하다
- 이 권한들은 인터넷접속, GPS, SMS 전송 및 읽기 등 디바이스를 관리할 수 있는 전반적인 것들로 나뉘어져있다.
- 권한은 반드시 애플리케이션에 포함된 AndroidManifest.xml파일에 명시되어야하고, 설치 시 사용자에게 이러이러한 권한이 있습니다. 라고 보여지게끔 되어있다.
    - AndroidManifest.xml : 외부에서 해당 애플리케이션의 기능을 일부 사용할 수 있게끔 해주는 서비스와 같은 애플리케이션에 관한 많은 정보를 포함함

```
// 예제 5-11 ) 서비스의 취약점을 트리커하는 코드의 예
Intent itnInstall = new Intent("android.intent.action.PACKAGEINSTALLERSERVICE");
itnInstall.setClassName("xxx.xxxxx.xx","xxx.xxxxx.xx.xxxxxxxxx.PackateInstallerService");
itnInstall.setData(Uri.parse("file:///data/data/kr.lokihardt/backdoor.apk"))
;
startService(itnInstall);
```
- 사용자의 허가없이 원하는 애플리케이션을 설치하거나 이미 설치된 애플리케이션을 마음대로 지울 수 있으므로, 금융권 애플리케이션을 지우고 피싱앱을 설치하는 등의 악성코드에 악용될 수 있다.

### 윈도우 소프트웨어에서 버그헌팅
- 일반적으로 소프트웨어들에서 발견되는 취약점은 해당 소프트웨어에서 지원하는 파일 포맷을 잘못 해석하면 발생한다.
- 곰플레이어 원격코드 실행 취약점
- 한글워드 원격코드 실행 취약점
    - 다른 소프트웨어에서도 한글의 기능을 사용할 수 있도록 액티브X(ActiveX)로 만들어진 플러그인 제공.
        - 액티브X : 윈도우 기본 웹 브라우저인 인터넷 익스플로러에서 자바스크립트나 비주얼 베이직 스크립트를 통해 사용할 수 있다. 웹페이지 발문만으로 취약점 트리거가능.
    - boolean RunScriptMacro (string FunctionName, number uMacroType,number uScriptType)
        - 문서내에 포함된 자바스크립트를 실행시켜주는 함수로, 첫번째 인자로 실행될 함수 이름을 지정가능
        ```c
        //예제 5-16 ) RunScriptMacro 함수의 추정코드
        bool RunScriptMacro(const char* Function){
            sprintf(buffer,"%s()",FunctionName);
            return javascript_eval(buffer).
        }
        ```
        - 윈도우에서는 ActiveXObject 라고하는 특수한 개체를 통해 파일을 읽거나 쓰거나 실행하는 등의 다양한 명령어를 제공하며, 이 명령어들은 비주얼 베이직 스크립트나 자바스크립트를 통해 사용 가능
        - RunScriptMacro 를 사용해 원하는 코드를 실행시켜보자. (계산기 실행)
            ```javascript
            obj.RunScriptMacro("(function() {new ActiveXObject('WScript.Shell').run('calc');})",0,0);
            ```
            - 액티브X를 통한 호출에서는 스크립트 코드 실행을 제대로 막아놓지않아 이러한 취약점이 발생함.
## 🌈 Chapter 3: 리버스 엔지니어링

**Reverse Engineering** : 만들어진 제품, 도구를 분해해 분석하거나 재조합하는 것

#### 리버싱으로 뭘 할 수 있냐..? 🔍
- 컴퓨터 원리와 구조이해
- 프로그램 유지보수
- 개발에 활용 : 한국에서는 프로그램 리버싱을 금지함
- 보안점검 및 취약점 찾기
- 악성코드 분석

### 환경구축 📌
1. Visual Studio 설치
2. [올리디버거 (OllyDbg) 설치](http://www.ollydbg.de)
    
    압축해제 후 , Plugin, UDD (breakpoint, 주석 등 작업내용 저장) 2개의 directory를 만들어준다.

    OllyDbg -> Option -> Appearance -> Directories -> UDD, Plugin 경로 변경해주기. 

    ollydbg.ini 수정해주기
    ```md
    [Settings]
    Check DLL versions=0
    Show jump direction=1
    Show jump path=1
    Show jumpfrom path=1
    Show path if jump is not taken=1
    ```
    `잘 안되면 관리자권한으로 설정해주면 다 해결된다.`
3. 계산기

    단축키: 2진수F5 8진수F6 10진수F7 16진수F8

### 기초지식 IA-32(x86-32) 📌
#### 중앙연산처리장치 CPU 💻
*외부로부터 명령어를 입력받아 해석하고 연산해서 실행함*

CPU 내부에서 각종 정보를 저장하기 위해 임시 기억 장치인 레지스터를 사용하고, 레지스터만으로는 저장할 수 있는 정보 양이 매우 적으므로 주기억장치인 메모리를 사용한다.

**주기억장치 메모리 == RAM (random access memory)** : 휘발성 메모리 volatile memory

**하드디스크** : Non-volatile memory <- 컴퓨터가 사용

(빠르고 용량 작음) `CPU - 레지스터 - 메모리 - 하드디스크` (느리고 용량 큼)

![alt text](img/img1.jpg)

#### IA-32 레지스터 💻


<레지스터 종류>
- 8개의 32bit 범용레지스터 (general register)
- 6개의 16bit 세그먼트 레지스터(segment register)
- 32bit EFLAGS 레지스터 (Program status and control register)
- 32bit ELP 레지스터 (Extended Instruction Pointer register)

![alt text](img/img2.jpg)

**<범용 레지스터>**
![alt text](img/img3.jpg)
16비트나 8비트 등으로 나눠 쓸수도 있다. 64bit -> rax..

    EAX : return 값 , 산술연산
    EBX : 특정 주소 지정
    ECX : 반복적인 명령어 수행시 횟수 저장
    EDX : 큰수 곱셈, 나눗셈 등의 연산시 EAX 레지스터와 함께 사용
    ESI : 문자열 복사, 비교시 소스 문자열 주소 저장에 사용
    ESP : 스택위치 저장
    EBP : 함수인자, 스택변수에 접근하기 위해 사용

**<세그먼트 레지스터>**

메모리에 저장되어있는 특정 세그먼트 가리킴

    CS : 코드 세그먼트 가리킴
    SS : 스택 세그먼트 가리킴
    DS, ES, FS, GS : 데이터 세그먼트 가리킴

**<ELFAG 레지스터>**

프로그램의 현재상태나 분기문의 조건 등을 검사하는데 사용되는 플래그들을 모아놓은 레지스터

**<EIP 레지스터>**

CPU 가 다음에 수행해야 할 명령어를 담은 메모리의 주소 저장

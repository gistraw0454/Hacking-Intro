## ? Chapter 4: �ý��� ��ŷ
#### <ins>�ý��� ��ŷ</ins> ?
- �ü�� ��ŷ (OS System Hacking)
- ���ٱ����� ���� ��ǻ���� �ڿ��� ���� �����ϰų� ������ �����ϴ� ��� ���

#### ��ǻ�� ��
- ���ͳݿ� �ִ� ����� �ý����� ã�� �����θ� �����ϴ� �Ǽ� ���α׷�, ���� �ٸ� ��ǻ�͸� ������ �ڽ��� ������
    - SQL ������ ��
        - MS-SQL ������ ���� �����÷ο� ������ �ϱ� ���� UDP port 1434 �̿�
        - ����� ������ 400byte�� UDP ��Ŷ�ȿ� ���� ������ TCP������ ���� ������ ��ٸ� �ʿ䰡 ���� ������ Ȯ�� 
    - Code-Red �� 

#### ��ŷ
- ���� ����(ID/PW)�� ���� ��ǻ�Ϳ� ����� ������.
- ���� ���� ������ �ִ� �ý��ۿ��� �� ���� ���� ������ ��´�. (Priviliedge Escalation)
- How ???
    - <ins>�������� ���α׷��� ���� �帧�� �ٲ۴�</ins>
    - <ins>���� �Ҷ� �ڵ����� ���� ������ �ο��޴� ���α׷��� ���� �帧�� �ٲ۴�</ins>

### ȯ�� ���� ??
---
- ���α׷� �м� : windbg , IDA , gdb
- ���� �ڵ� �ۼ� : ���̽� 

1. ���̽� ��ġ
2. cmd > `python` ���̽� ����

### ��ɾ� ���� ���� ???��?
---
- ���� ��ɾ���� �����ϰų� �� ��ɾ���� �̿��� Ư�� ��� ����� �߻� ����
```c
//���� 4-1 ) ���͸��� �ִ� ���� ����� ǥ��������� ����ϴ� ��� ���� �Լ�
void print_current_dir_with_api(void){
    WIN32_FIND_DATA ffd;    //FindFileData
    HANDLE hFind = FindFirstFile(TEXT("*"),&ffd);
    if (hFind == INVALID_HANDLE_VALUE){
        printf("FindFirstFile failed (%d)\n",GetLastError());
        exit(1);
    }
    do{
        if (wcscmp(ffd.cFIleName,TEXT("."))!=0 && wcscmp(ffd.cFIleName,TEXT(".."))!=0){
            printf("%S\n",ffd.cFileName);
        }
    }while (FindNextFile(hFind,&ffd)!=0);
}
```
�����쿡�� �����ϴ� �⺻API (WINAPI)�鸸 �̿��� ���� ������ ��� ������ ����ϴ� �ڵ��.

�ش� ����� �����ϴ� �ܺ� ���α׷��� ������ �ܺ� ���α׷��� ������ �� ����� �״�� ����ȴ�.

���� ���α׷��� ������ �ܺ� ���α׷��� �����ϱ� ���� ������� �ؽ�Ʈ��� ��ɾ� ó���⸦ �̿��Ѵ�.
#### ��ɾ� ó����
- C������ �ܺ� ���α׷��� ������ �� �ִ� �Լ��� `system()`�� ����
    - �ü�� �⺻��ɾ� ó����
    - ���ڷ� ���� ���ڿ��� �����ϰ� �װ�� ���
    ```c
    //���� 4-2 ) system()���� dir��ɾ� ���������ν� �Ȱ��� ����� �����ϴ� ���α׷��� �� ������ �ۼ�����
    void print_current_dir_with_system(void){
        system("dir /B");
    }
    ```
    ��? �̷������� "����"

#### ��ɾ� ���� ����
```c
//���� 4-3 ) ���ڷ� ���͸����� �޾� ���� ����� ����ϴ� ���α׷�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int kCmdLen = 400;
void print_dir_with_system(char *path){
    char cmd[kCmdLen];
    const char* cmd_prefix = "dir /B";
    if (strlen(cmd_prefix)+strlen(path)+1<kCmdLen){
        _snprintf(cmd,kCmdLen,"%s %s",cmd_prefix,path); //cmd_prefix�� path�� %s %s �� ������ ���ڿ��� kCmdLen��ŭ cmd�� ����
    }
    system(cmd);
}

int main(int argc, char* argv[]){
    char* exec_file = argv[0];  //�������ϸ�
    char* path = argv[1];   //���
    if (argv==2) print_dir_with_system(path);
    else printf("Usage> %s [filename]\n",exec_file);
    return 0;
}
```
ù��° ���ڷ� �Ѿ�� ������ �ִ� ���� ����� ����Ѵ�.

> ? ù��° ���ڷ� ���� ���ϸ� �ڿ� `. && echo oops`�� �Է��ϸ�? sprintf������ cmd.exe�� ���� `dir /B . && echo oops` �� ����ȴ�.`&&` �� ��ɾ� ó���⿡�� �� �ٿ� �緯 ��ɾ �����ϵ��� �Ѵ�. 

#### ��ɾ� ���� ������� �߻��ϴ� ����
- � ������ ���� �Ϲ������� ���α׷� ������ `system()`���� ������������ ��ɾ� ó���⸦ ����ϴ� �Լ��� ȣ���ϴ� �ڵ尡 �־���Ѵ�.

�� �� �� �����ؾ��� ���� �Լ�
|���|����|
|--|--|
|C/C++|�ü�� ����: system(),popen(),execlp(),execvp()|
||������ ����: ShellExecute, CreateProcess_wsystem()|
|Perl|System(),exec(),\`,\|,eval(),����ǥ����/e������|
|���̽�|exec,eval,os.sytem,os.open,execfile,input,compile|
|�ڹ�|Class,forName(string name),class,newInstance,Runtime,exec()|
|C#|System,Diagnostics,Process,Start()|



#### ��ɾ� ���԰��ݿ� ���Ǵ� ��ɾ� ó���� ������

�� ��ɾ� ó���⿡ Ư���ϰ� ���Ǵ� ��ɾ�
|������|����|�ǹ�|
|---|---|--|
|>|prog>file|prog�������� ���� ǥ������� file�� ����. (�����)|
|>>|prog>>file|prog�������� ���� ǥ������� file�ڿ� �߰�|
|<|prog<file|file�� ������ prog�� ǥ���Է����� ����|
|\||prog1\|prog2|prog1�� ǥ������� prog2�� ǥ���Է����� ����|
|&&|prog1&&prog2|prog1 ��ɼ����� �������̸� prog2 ȣ��|
|\|\||prog1\|\|prog2|prog1 ��ɼ����� �����ϸ� prog2 ȣ��|
|;(������)|prog1;prog2|prog1 ���� �� prog2 ����|
|&(������)|prog1&prog2|prog1 ���� �� prog2 ����|
|&(������)|prog&prog1|prog�� ��׶��忡�� �����ϰ� prog1�� ����|
|$()(������)|$(command)| �ش� ������ command�� ������ ����� ġȯ|
|`(������)|'command'|�ش� ������ command�� ������ ����� ġȯ|

>Ư�� ���н��迭���� �ִ� $() �� ` �� �յ��� ��ɾ ���� �Ͱ� ������� ��ɾ� ���� ���� ���������� ������ �� �־ ���� ���ݿ��� ���� �����ϰ� ����.


### ���̽� ����� ? 
---
- Race Condition Attack 
- ���δٸ� ���μ����� �����尡 ���� �ڿ��� ������ ��, ���� ������ ���� ����� �޶��� �� �ִ� ������ �̿�
- ���༺ : �ü������ ���� ������ ���ÿ� ó���Ҽ��ִ� Ư��
    - ���� ó��
    - ��Ƽ �ھ�
 ```c
 //���� 4-4 ) ���༺ �׽�Ʈ�� ���� �ڵ�
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
//���
//total count =400
```
���༺�� �̿��� �� ���α׷��� ������ �����ϵ��� �غ���. 
- CPU�� �������� �����带 ����� ������ ���ϸ� 1/(�ھ��)�� �����ν�, ������ �ϳ��� CPU������ �۵��Կ� ���� ����� ���ϸ� ���� �� �ִ�.
- �޸𸮺��� (total_count_)�� ��������ν� �߻��ϴ� ���ϸ� ���̱� ����, ��� ������ �߰� ��� ���� ���� ������ �����ؼ� ������ �������� �̸� �ݿ��ϵ��� �Ѵ�.
```c
//���� 4-5 ) ���༺�� �̿��� ���� ���� ���α׷�
#include <stdio.h>
#include <windows.h>

const int kLoopCount = 400;
const int kNumThread = 4;
const int kIncreaseLoopCount = kLoopCount/kNumThread;
int total_count_ = 0;

DWORD WINAPI MyThreadFunction(LPVOID lpParam){
    int temp =total_count_;

    for ( int i=0; i<kIncreaseLoopCount;i++) temp++;
    total_count_=temp;
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
    concurrent_solver();
    printf("total_count_ = %d\n",total_count_);
    return 0;
}
//���
//total count =400
```
MyThreadFunction() �Լ��� ������ ������ ���� ��귮�� ���� �д��� ����Ѵ�

4���� �����带 ������ 100���� ���� ������ �����Ѵ�.

���⼭ main�Լ��� �ٲ㺸��.
```c
//���� 4-6 ) 4-5���� ������ main �Լ�
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
```
![alt text](img/image.png) �̷��� �������ٿ� total count���� 300�� ���� �� �� �ִ�.
���α׷��� �츮�� �ۼ��� ��� ���������� �׻� 4*100=400�� �Ǿ�������� �ٸ��� ���Դ�.

Why???

�� ���� 4-6���� �� �����尡 �����ϴ� ����� �ð��� ���� ����ȭ
|�ð�|Thread A (CPU 0)|Thread B (CPU 1)|
|---|---|---|
|1|int temp=total_count_;|int temp =total_count_;|
|2|for() temp++|for() temp++|
|3|total_count_=temp;|total_count_|temp;|

ǥ������, MyThreadFunction() ù��° ���� �����̴�.

temp ������ ���� �Է¿� ���� total_count_ ������� �������µ�, ������A, ������B �Ѵ� total_count_ �κ��� ���� ���� �ޱ� ������ ���� �ϳ��� �����带 ������ ������� �ݿ��ȴ�.

���� �� �����带 �����ϰ� �ϳ��� �����常 ������ ȿ���� ��´�.

> ���� ���μ����� �����尡 ����Ǵ� ������ ���� �������� �޶����� ������ <ins>���̽� �����</ins>�̶�� �Ѵ�.

#### ���̽� ����� �����
���� MyThreadFunction�Լ��� �Ʒ��� ���� �����غ���
```c
//���� 4-7 ) ������ MyThreadFunction() �Լ�
DWORD WINAPI MyThreadFunction (LPVOID lpParam){
    for (int i=0; i<kIncreaseLoopCount;i++) total_count_++;
    return 0;
}
```
�� ���� 4-7���� �� �����尡 �����ϴ� ����� �ð��� ���� ����ȭ
|�ð�|Thread A (CPU 0)|Thread B (CPU 1)|
|---|---|---|
|1|total_count_++;|total_count_++;|

CPU���� �ѹ��� ó���Ǵ� ����̹Ƿ� �ذ�ɱ� �;��µ� �ٽ� ������ ���ڰ� ���´�.

Why???

total_count_ ++ �� C���� �ϳ��� ����������, ��Ģ����� ���õ� ��ɾ���� ���ڰ� �� �ϳ��� �������Ϳ����ϴ� ��Ģ�� �־� 3���� ������� ������.
```assembly
mov eax,dword ptr ds:[01078130h] 
add eax,1
mov dword ptr ds:[9197813h],eax
```
����ȭ ������ ���� total_count_ �� �̸� �������Ϳ� ����� ��쵵 �ֱ⶧���� �̸� �״�� ����Ѵ�.

�� total_count++ �� CPU���� <ins>����</ins>�� ����Ǵ� ���
|�ð�|Thread A (CPU 0)|Thread B (CPU 1)|
|--|---|---|
|1|mov eax,dword ptr ds:[01078130h]|mov eax,dword ptr ds:[01078130h]|
|2|add eax,1|add eax,1|
|3|mov dword ptr ds:[9197813h],eax|mov dword ptr ds:[9197813h],eax|
4-6���� ����� ���ϰ� ���� �ϴ�. ���� ������ ������ �߻��ϰ� �ȴ�.

### �޸� ���� ���� ??
---
- **�޸� ���� (Memory corruption)** : ���α׷��� ����� �޸�, �߸��� ���� ������ �ǵ����� ���� �޸𸮸� ����ڰ� ��� �� �ִ� ������
#### �޸� ���� ����
- �������� ���α׷� ������ �����ϴ� �޸� ����
- ���α׷��� �������� �ǵ��� �ٸ��� �޸𸮸� ���ų� �д� ����
```c
//���� 4-8 ) ������ ������ ���ڿ� ������ ������ ���ڿ��� ����ϴ� �ڵ�
#include <stdio.h>

int main()
{
    int a=0x00434241;
    char b[4] = "ABC";

    printf("%s\n",b);
    printf("%s\n",&a);

    return 0;
}
```
�ҽ��� ���� a�� ���������� ������� �� �� �ִ�.

�����ϵ� �ڵ带 �������ϴ� ���忡���� a,b ��� ���ڿ� ������� �м��Ѵ�.

Why ???

���α׷��� ����� �ҽ��ڵ尡 ����� �����Ǹ鼭 �̷� ���ƿ� ���� ������ ��������� ����.

int�� ���ڿ�ó�� ����ϴ� ����ϻ�. �����ڰ� ó�� ���α׷��� ������ ������ ���� ������ �߰ߵ� �� �ִ�. �̸� <ins>������ ���� (Design Flaw)</ins> ����ϴµ�, ���α׷��Ӱ� �ǵ��� �ٸ� �����ϴ� ��� ��ü�� ������ �ִ� ���̴�. 

+ ��ɾ� ���� ������ �߻��ϴ� ����Ʈ����� ��ɾ� ó���⿡�� Ư�����ڰ� ��� ó���Ǵ����� �����ؼ� �߻��ϴ� ������ ������ ���ֿ� ���Ѵ�.

���α׷� : ��ǻ�Ϳ��� Ư�� �۾��� �����ϵ��� �ϴ� ������ ��ɾ� ����

`�ҽ��ڵ� -> (�����Ϸ�) -> ������ڵ� -> (�����) -> ���� -> (CPU) -> ����`

����� ���ϸ� C���� high level ���� ���� �߻��� ������ �����ϰ��ִ�.
- ex) C���� ����ϴ� ������ Ÿ���� ����� ǥ���� �� ���� �߻��� �����̴�. `�迭����, int, char, double ���� ������ Ÿ�� ���� ����� ǥ�� �Ұ�.` �ٸ� ��ɾ��� ���ڷ� ���������� ���߰���. 

#### ���� �����÷ο� ����


#### ���� ���ڿ�

#### ���� �����÷ο�/����÷ο� ����

### ����
---
#### ũ���� �߻���Ű��
#### EIP �����

//���� 4-1 ) ���͸��� �ִ� ���� ����� ǥ��������� ����ϴ� ��� ���� �Լ�
#include <windows.h>
void print_current_dir_with_api(void){
    WIN32_FIND_DATA ffd;    //FindFileData
    HANDLE hFind = FindFirstFile(TEXT("*"),&ffd);
    if (hFind == INVALID_HANDLE_VALUE){
        printf("FindFirstFile failed (%d)\n",GetLastError());
        exit(1);
    }
    do{
        if (wcscmp(ffd.cFileName,TEXT("."))!=0 && wcscmp(ffd.cFileName,TEXT(".."))!=0){
            printf("%S\n",ffd.cFileName);
        }
    }while (FindNextFile(hFind,&ffd)!=0);
}
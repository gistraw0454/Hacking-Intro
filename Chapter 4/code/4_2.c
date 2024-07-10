//예제 4-2 ) system()으로 dir명령어 수행함으로써 똑같은 기능을 수행하는 프로그램을 더 빠르게 작성가능
    void print_current_dir_with_system(void){
        system("dir /B");
    }
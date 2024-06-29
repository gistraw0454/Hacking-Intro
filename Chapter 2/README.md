## 🌈 Chapter 1: 웹 해킹

**DDos (Distributed Denial of Service)** : 분산 서비스 공격, 여러대의 컴퓨터를 악성코드에 감염시켜 좀비 PC로 만든 뒤, C&C(명령제어) 서버의 명령을 받아 일제히 특정 서버에 대량 패킷을 전송하는 공격기법

### 📌 환경 구축
[참고](https://soda-dev.tistory.com/52)
1. 아파치 설치
2. PHP 설치

    경로 : `C:\Apache Group\php8\`
3. MySQL 설치

    **<mysql 로그인 방법>**

    cmd 관리자 권한으로 실행 -> `mysql -u root -p` -> 비밀번호 입력

    **<데이터 베이스 생성하기>** 
        
    mysql 로그인 -> cmd에 `create database test;`
4. 툴 설치
    
    웹 프록시 Web Proxy 툴 : 일반적인 외부 서버와 접속하는 프록시가 아니라, 해당 PC의 내부에서 가상 포트를 열고 해당 프로그램이 서버와 웹 브라우저의 HTTP 패킷을 중간에서 전달해주는 역할을 함.
    
    -> Request 혹은 Response 해킷을 가로채거나 수정할 수 있고 드롭도 가능
    
    [**파로스(Paros)**](https://sourceforge.net/projects/paros/)
    
    32bit java jdk를 깔아주고 환경변수에 그 exe 위치를 넣어준후 paros의 바로가기 경로를 그 exe위치로 넣어주면 돌아간다.

    구글 -> 설정 -> 프록시설정 -> localhost, 8080설정후 아무 홈페이지나 들어가면 paros 사이트부분에 이것저것 뜨는것을 볼 수 있다. -> 사용후에 꺼주기.


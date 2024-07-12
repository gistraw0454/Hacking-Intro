//예제 4-16 ) 취약한 OpenBSD 소스 부분
int nresp;
...
nresp = packet_get_int();
if (nresp>0){
    response = xmalloc(nreap*sizeof(char*));
    for (i=0; i<nresp;i++){
        response[i]=packet_get_string(NULL);
    }
}
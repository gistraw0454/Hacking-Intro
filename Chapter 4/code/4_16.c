//���� 4-16 ) ����� OpenBSD �ҽ� �κ�
int nresp;
...
nresp = packet_get_int();
if (nresp>0){
    response = xmalloc(nreap*sizeof(char*));
    for (i=0; i<nresp;i++){
        response[i]=packet_get_string(NULL);
    }
}
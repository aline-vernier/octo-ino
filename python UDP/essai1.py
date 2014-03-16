import socket
import time
import sys


UDP_IP = "192.168.79.100"
UDP_PORT = 5005
NUMBER = 65
MESSAGE = chr(0b0) + chr(0b0)

print "UDP target IP: ", UDP_IP
print "UDP target port: ", UDP_PORT
print "Message: ", MESSAGE

data =0

while True:
	print "starting to send stuff"
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
	start = time.clock()
	print "stuff sent"
	elapsed = 0
	while data == 0:
		print "waiting for reply"
		elapsed = time.clock()-start
		data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
		print "received message:", data
		print "i received ", len(data), "bytes"
		print "translated", ''.join(format(ord(x),'b')for x in data)
		print "i waited for ", elapsed, "seconds" 
	time.sleep(1)
	data = 0
	print "finished sleeping"
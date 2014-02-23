import socket
import time

UDP_IP = "192.168.79.100"
UDP_PORT = 5005
MESSAGE = "Hallo"

print "UDP target IP: ", UDP_IP
print "UDP target port: ", UDP_PORT
print "Message: ", MESSAGE

data =0

with open('stats.txt', 'a') as f:
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
			print "i waited for ", elapsed, "seconds" 
			elapsedstr = str(elapsed)
			elapsedstr = elapsedstr + '\n'
			f.write(elapsedstr)
		time.sleep(.5)
		data = 0
		print "finished sleeping"
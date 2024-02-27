c:
	gcc client.c -o client
s:
	gcc server.c -o server
g:
	gcc -g server.c -o server

f:
	gcc -g file.c -o file
all: c s

clean:
	rm -f client server client gtest

var:
	valgrind --leak-check=full ./client
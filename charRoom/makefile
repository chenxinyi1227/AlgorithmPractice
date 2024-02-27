client:
	gcc client.c -o client -ljson-c

server:
	gcc server.c -o server -ljson-c -lmysqlclient

all:client server

clean:
	rm -f client server
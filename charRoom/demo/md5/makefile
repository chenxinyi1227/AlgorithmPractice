c:
	gcc client.c -o client -lcrypto
s:
	gcc server.c -o server -lcrypto
md5:
	gcc md5.c -o md5 -lcrypto
all: c s

clean:
	rm -f client server md5
	
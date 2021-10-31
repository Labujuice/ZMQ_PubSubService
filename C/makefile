CC:=gcc
exe:=server client
obj:=server.o client.o

all:
	make server
	make client

server:
	$(CC) -o server server.c -lzmq

client:
	$(CC) -o client client.c -lzmq -lpthread

.PHONY:clean
clean:
	rm -rf $(obj) $(exe)

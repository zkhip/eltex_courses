CC=gcc
TARGET=server tcp_client udp_client

.PHONY: clean

all: $(TARGET)

server: server.c
	gcc $^ -o $@ -pthread

tcp_client: client_tcp.c
	gcc $^ -o $@ 

udp_client: client_udp.c
	gcc $^ -o $@ 

clean:
	rm -rf $(TARGET)
CC=gcc
TARGET=client server

.PHONY: clean

all: $(TARGET)

server: server.c
	gcc $^ -o $@ -pthread

client: client.c
	gcc $^ -o $@ 

clean:
	rm -rf $(TARGET)
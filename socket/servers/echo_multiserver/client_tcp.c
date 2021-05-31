#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>

#define IP "127.0.0.1"
#define PORT 5000
#define BUF_SIZE 128

int main() {
    struct sockaddr_in server;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (inet_pton(AF_INET, IP, &server.sin_addr) <= 0) {
        perror("inet_pton");
        exit(1);
    }

    if (connect(fd, (const struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("connect");
        exit(1);
    }

    char buff[BUF_SIZE];
    if (send(fd, "### Client tcp connected ###", BUF_SIZE, 0) == -1) {
        perror("send");
        exit(1);
    }

    memset(&buff, 0, sizeof(buff));
    if (recv(fd, buff, BUF_SIZE, 0) == -1) {
        perror("recv");
        exit(1);
    }
    
    printf("Time: ");
    puts(buff);

    close(fd);
}

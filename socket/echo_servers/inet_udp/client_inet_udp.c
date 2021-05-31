#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>

#define IP "127.0.0.1"
#define BUF_SIZE 30

int main() {
    char buff[BUF_SIZE];
    struct sockaddr_in server;

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = INADDR_ANY;

    if (connect(fd, (const struct sockaddr *)&server, sizeof(server)) == -1) {
        fprintf(stderr, "Can't create a connection");
        exit(1);
    }

    sendto(fd, "### Client connected ###", BUF_SIZE, MSG_CONFIRM, (const struct sockaddr *)&server, sizeof(server));
    printf("To end session enter 'end'\n");

    while (1) {
        printf(" - Enter message: ");
        memset(&buff, 0, sizeof(buff));
        fgets(buff, BUF_SIZE, stdin);
        if (strcmp(buff, "end\n") == 0) {
            send(fd, "end", BUF_SIZE, 0);
            break;
        }
        send(fd, buff, BUF_SIZE, 0);
        recv(fd, buff, BUF_SIZE, 0);
        printf(" + Answer: ");
        puts(buff);
    }

    close(fd);
}

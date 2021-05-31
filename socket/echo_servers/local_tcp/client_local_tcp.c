#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "/tmp/stream_server"
#define BUF_SIZE 30

int main() {
    char buff[BUF_SIZE];
    struct sockaddr_un server;

    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server, 0, sizeof(struct sockaddr_un));
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, SOCK_PATH, sizeof(server.sun_path) - 1);

    if (connect(fd, (const struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("connect");
        exit(1);
    }

    if (send(fd, "### Client connected ###", BUF_SIZE, 0) == -1) {
        perror("send");
        exit(1);
    }
    printf("To end session enter 'end'\n");
    while (1) {
        memset(&buff, 0, sizeof(buff));
        printf(" - Enter message: ");
        fgets(buff, BUF_SIZE, stdin);
        if (strcmp(buff, "end\n") == 0) {
            if (send(fd, "end", BUF_SIZE, 0) == -1) {
                perror("send");
                exit(1);
            }
            break;
        }
        if (send(fd, buff, BUF_SIZE, 0) == -1) {
            perror("send");
            exit(1);
        }
        if (recv(fd, buff, BUF_SIZE, 0) == -1) {
            perror("recv");
            exit(1);
        }
        printf(" + Answer: ");
        puts(buff);
    }
    close(fd);
}
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
    struct sockaddr_un server, client;

    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, SOCK_PATH, sizeof(server.sun_path) - 1);

    if (bind(fd, (const struct sockaddr *) &server, sizeof(server)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(fd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    int new_fd;
    int len = sizeof(client);
    while (1) {
        new_fd = accept(fd, (struct sockaddr *)&client, &len);

        if (new_fd == -1) {
            perror("accept");
            exit(1);
        }

        if (recv(new_fd, buff, BUF_SIZE, 0) == -1) {
            perror("recv");
            exit(1);
        }
        puts(buff);
        
        while (1) {
            memset(&buff, 0, sizeof(buff));
            char str[BUF_SIZE] = "Hello! ";
            if (recv(new_fd, buff, BUF_SIZE, 0) == -1) {
                perror("accept");
                exit(1);
            }
            if (strcmp(buff, "end") == 0) {
                printf("### Client disconnected ###\n\n");
                break;
            }
            puts(buff);
            strcat(str, buff);
            strcpy(buff, str);
            if (send(new_fd, buff, BUF_SIZE, 0) == -1) {
                perror("send");
                exit(1);
            }
        } 
        close(new_fd);
    }
    close(fd);
}

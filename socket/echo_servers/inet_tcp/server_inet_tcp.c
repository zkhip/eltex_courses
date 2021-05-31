#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUF_SIZE 30

int main() {
    char buff[BUF_SIZE];
    struct sockaddr_in server, client;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(5000);

    if (bind(fd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(fd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    int new_fd;
    while (1) {
        int len = sizeof(client);
        new_fd = accept(fd, (struct sockaddr *)&client, (socklen_t * restrict)&len);

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
                perror("recv");
                exit(1);
            }
            if (strcmp(buff, "end") == 0) {
                printf("### Client disconnected ###\n\n");
                break;
            }
            puts(buff);
            strcat(str, buff);
            strcpy(buff, str);
            if (sendto(new_fd, buff, strlen(buff), 0, (const struct sockaddr *)&client, len) == -1) {
                perror("sendto");
                exit(1);
            }
        } 
    }

    close(fd);
}

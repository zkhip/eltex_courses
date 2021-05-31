#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>
#include <time.h> 

#define BUF_SIZE 128
#define PORT 5000

int main() {
    struct sockaddr_in server, client_tcp, client_udp;
    
    int fd_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_tcp == -1) {
        perror("socket tcp");
        exit(1);
    }

    int fd_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_udp == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    memset(&client_tcp, 0, sizeof(client_tcp));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if (bind(fd_tcp, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("bind");
        exit(1);
    }

    if (bind(fd_udp, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(fd_tcp, 5) == -1) {
        perror("listen");
        exit(1);
    }

    struct pollfd fds[2];
    fds[0].fd = fd_tcp;
    fds[0].events = POLLIN;

    fds[1].fd = fd_udp;
    fds[1].events = POLLIN;

    char timing[BUF_SIZE];
    char buff[BUF_SIZE];
    int new_fd, len;
    long int ttime;

    while (1) {
        int ret = poll(fds, 2, 5000);
        if (ret == -1) {
            perror("poll");
            exit(1);
        }

        if (fds[0].revents & POLLIN) {
            len = sizeof(client_tcp);
            new_fd = accept(fd_tcp, (struct sockaddr *)&client_tcp, (socklen_t * restrict)&len);
            if (new_fd == -1) {
                perror("accept");
                exit(1);
            }

            if (recv(new_fd, buff, BUF_SIZE, 0) == -1) {
                perror("recv");
                exit(1);
            }
            puts(buff);

            ttime = time(NULL);
            memset(&timing, 0, BUF_SIZE);
            strcpy(timing, ctime (&ttime));
            if (sendto(new_fd, timing, BUF_SIZE, 0, (struct sockaddr *)&client_tcp, len) == -1) {
                perror("sendto");
                exit(1);
            }
        }

        if (fds[1].revents & POLLIN) {
            len = sizeof(client_udp);
            if (recvfrom(fd_udp, buff, BUF_SIZE, MSG_WAITALL, (struct sockaddr *)&client_udp, &len) == -1) {
                perror("recvfrom");
                exit(1);
            }
            puts(buff);

            ttime = time (NULL);
            memset(&timing, 0, BUF_SIZE);
            strcpy(timing, ctime (&ttime));

            if (sendto(fd_udp, timing, BUF_SIZE, MSG_CONFIRM, (const struct sockaddr *)&client_udp, len) == -1) {
                perror("sendto");
                exit(1);
            }
        }
    }
}
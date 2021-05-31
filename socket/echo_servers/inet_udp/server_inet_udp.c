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

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);

    if (bind(fd, (const struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("bind");
        exit(1);
    }

    while (1) {
        int len = sizeof(client);
        recvfrom(fd, buff, BUF_SIZE, MSG_WAITALL, (struct sockaddr *)&client, &len);
        puts(buff);
        while (1) {
            memset(&buff, 0, sizeof(buff));
            char str[BUF_SIZE] = "Hello! ";
            recvfrom(fd, buff, BUF_SIZE, MSG_WAITALL, (struct sockaddr *)&client, &len);
            if (strcmp(buff, "end") == 0) {
                printf("### Client disconnected ###\n\n");
                break;
            }
            // buff[n] = '\0';
            puts(buff);
            strcat(str, buff);
            strcpy(buff, str);
            sendto(fd, buff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *)&client, len);
        } 
    }

    close(fd);
}

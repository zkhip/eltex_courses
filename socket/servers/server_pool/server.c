#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define PORT 5000
#define BUF_SIZE 30
#define THREADS_NUM 5

int file_descriptors[THREADS_NUM] = {0};

void *connection(void *fd) {
    int* d = (int *)fd;
    int thrd_id = *d;

    int new_fd;
    char buff[BUF_SIZE];
    while (1) {
        while (1) {
            if (file_descriptors[thrd_id] != 0) {
                new_fd = file_descriptors[thrd_id];
                break;
            }
        }

        if (recv(new_fd, buff, BUF_SIZE, 0) == -1) {
            perror("recv");
            exit(1);
        }
        puts(buff);
        
        while (1) {
            memset(&buff, 0, BUF_SIZE);
            char str[BUF_SIZE] = "Hello! ";
            if (recv(new_fd, buff, BUF_SIZE, 0) == -1) {
                perror("recv");
                return NULL;
            }
            if (strcmp(buff, "end") == 0) {
                file_descriptors[thrd_id] = 0;
                printf("### Client disconnected ###\n\n");
                break;
            }
            puts(buff);
            strcat(str, buff);
            strcpy(buff, str);
            if (send(new_fd, buff, strlen(buff), 0) == -1) {
                perror("sendto");
                return NULL;
            }
        }
    }
}

int main() {
    struct sockaddr_in serv, client;
    int new_fd;
    pthread_t thread_id[THREADS_NUM];

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    int index[THREADS_NUM];
    for (int i = 0; i < THREADS_NUM; i++) {
        index[i] = i;
        void* thread_data = &index[i];
        if (pthread_create(&thread_id[i], NULL, connection, thread_data) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    memset(&serv, 0, sizeof(serv));
    memset(&client, 0, sizeof(client));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(PORT);

    int len = sizeof(serv);
    if (bind(fd, (struct sockaddr *)&serv, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(fd, THREADS_NUM) == -1) {
        perror("listen");
        exit(1);
    }

    int curr_index = -1;
    while (1) {
        for (int i = 0; i < THREADS_NUM; i++) {
            if (file_descriptors[i] == 0) {
                curr_index = i;
                break;
            }
        }

        if (curr_index != -1) {
            new_fd = accept(fd, (struct sockaddr *)&client, &len);
            if (new_fd == -1) {
                perror("accept");
                exit(1);
            }
            file_descriptors[curr_index] = new_fd;
            curr_index = -1;
        }
    }
}

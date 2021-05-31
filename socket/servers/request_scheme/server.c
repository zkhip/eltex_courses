#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PORT 5000
#define BUF_SIZE 30
#define THREADS_NUM 5

struct msgbuf {
    long mtype;
    int descriptor;
};

void *connection() {
    key_t key;
    if ((key = ftok("test", 1)) == -1)
    {
        perror("ftok");
        exit(1);
    }
        
    int queue = msgget(key, 0666);
    if (queue == -1) {
        perror("msgget conn");
        exit(1);
    }
    struct msgbuf msg;

    while (1) {
        if (msgrcv(queue, (void *)&msg, 128, 1, IPC_NOWAIT) > 0) {
            int new_fd = msg.descriptor;
            char buff[BUF_SIZE];
        
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

    key_t key;
    if ((key = ftok("test", 1)) == -1)
    {
        perror("ftok");
        exit(1);
    }
        
    int queue = msgget(key, IPC_CREAT | 0666);
    if (queue == -1) {
        perror("msgget");
        exit(1);
    }

    struct msgbuf msg;
 
    for (int i = 0; i < THREADS_NUM; i++) {
        if (pthread_create(&thread_id[i], NULL, connection, NULL) != 0) {
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

    while (1) {
        new_fd = accept(fd, (struct sockaddr *)&client, &len);
        if (new_fd == -1) {
            perror("accept");
            exit(1);
        }
    
        msg.mtype = 1;
        msg.descriptor = new_fd;
        msgsnd(queue, (void *)&msg, sizeof(msg.descriptor), IPC_NOWAIT);
    }
}

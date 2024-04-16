#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

void *sender_thread(void *data)
{
    int client_fd = *(int *)data;
    char buffer[1024] = {0};
    while (1)
    {
        fscanf(stdin, "%s", buffer);
        send(client_fd, buffer, 1024, 0);
        fprintf(stdout, "Sent to server: %s\n", buffer);
    }
}

void *listener_thread(void *data)
{
    int client_fd = *(int *)data;
    char buffer[1024] = {0};
    int valread;
    while (1)
    {
        valread = read(client_fd, buffer, 1024);
        if (valread == 0)
        {
            break;
        }
        printf("Received from server: %s\n", buffer);
    }
    close(client_fd);
}

int main() {
    pthread_t sender, listener;

    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address");
        return -1;
    }

    if (connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed");
        return -1;
    }

    pthread_create(&sender, NULL, sender_thread, (void *)&client_fd);
    pthread_create(&listener, NULL, listener_thread, (void *)&client_fd);
    pthread_join(sender, NULL);
    pthread_join(listener, NULL);

    return 0;
}


#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <asm-generic/socket.h>

#define PORT 8080
#define MAX_CLIENTS 10

void client_thread(void* data) {
    int client_socket = *(int*)data;
    char buffer[1024] = {0};
    int valread;
    while (1) {
        valread = read(client_socket, buffer, 1024);
        if (valread == 0) {
            break;
        }
        printf("Received from client: %s\n", buffer);
        send(client_socket, buffer, 1024, 0);
    }
    close(client_socket);
}

int main() {
    pthread_t client_threads[MAX_CLIENTS];
    int server_fd;
    int client_socket[MAX_CLIENTS];
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int counter = 0;

    while (1)
    {
        client_socket[counter] = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_socket[counter] < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        fprintf(stdout, "Client no. %d connected\n", counter);
        pthread_create(&client_threads[counter], NULL, (void*)client_thread, (void*)&client_socket[counter]);
        counter+=1;
    }
    
    close(server_fd);
    return 0;
}
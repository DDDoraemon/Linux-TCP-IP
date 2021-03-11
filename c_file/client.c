#include "client.h"

int main() {
    init_socket();
    connection();
    communication();

    close(client_socket_fd);

    return 0;
}

void init_socket() {
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_fd == -1) {
        PERROR("socket")
    }

    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_family = AF_INET;
    int ret;
    ret = inet_pton(AF_INET, SERVER_IP, &(server_addr.sin_addr));
    switch (ret){
        case 0: puts("src does not contain a character");
        break;
        case -1: puts("inet_pton error");
        case 1: puts("success");
        break;
    }
        
}

void connection() {
    server_size = sizeof(server_addr);
    connect_ret = connect(client_socket_fd, (struct sockaddr*)&server_addr, server_size);
    if (connect_ret == -1) {
        printf("%d\n", errno);
        PERROR("connect");
    }
    puts("connect success");
}

void communication() {
    while (1) {
        //发数据
        char* input_buf = (char*)malloc(BUFSIZ);
        fgets(input_buf, 128, stdin);

        char* send_buf = NULL; 
        send_buf = strtok(input_buf, "\n");

        int send_size;
        send_size = send(client_socket_fd, send_buf, strlen(send_buf), 0);
        if (send_size == -1) {
            free(input_buf);
            PERROR("send")
        }
        printf("send size:%d\n", send_size);
        free(input_buf);

        //读数据
        char* recv_buf = (char*)malloc(BUFSIZ);
        int recv_size;
        recv_size = recv(client_socket_fd, recv_buf, BUFSIZ, 0);
        if (recv_size == -1) {
            free(recv_buf);
            close(client_socket_fd);
            PERROR("recv")
        }
        else if (recv_size == 0) {
            free(recv_buf);
            close(client_socket_fd);
            puts("remote host closed connection");
        }
        else {
            printf("recv message:%s\n", recv_buf);
            free(recv_buf);
        }
    }
}
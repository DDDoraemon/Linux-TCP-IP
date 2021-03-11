#include "server.h"

int main() {
    init_server_socket();
    connection();

    close(server_fd);
    return 0;
}



int init_server_socket() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0); //创建服务器的socket文件标识符
    if (server_fd == -1) {
        PERROR("socket") //宏函数 此处不用加分号是因为这是一个宏定义 该函数用来反馈错误位置
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, ADDR, &server_addr.sin_addr.s_addr); //将点分十进制转换为网络字节序

    bind_ret = bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));  //将参数与服务器绑定
    if (bind_ret == -1) {
        PERROR("bind")
    }

    listen_ret = listen(server_fd, MAX_LINK);  //设置连接最大值
    if (listen_ret == -1) {
        PERROR("listen")
    }    

    return 0;
}

void connection() {
    //给客户端socket分配内存地址
    struct sockaddr_in* client_addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in)); 
    //客户端大小
    socklen_t client_size = sizeof(struct sockaddr_in);

    int client_fd;
    client_fd = accept(server_fd, (struct sockaddr*)client_addr, &client_size);  //监听等待连接
    if (client_fd == -1) {
        
        free(client_addr);  //连接失败 退出程序前释放分配的内存
        PERROR("accept")
    }
    else {
        // 用来接受客户端的端口和IP
        int client_port = ntohs(client_addr->sin_port);
        char* client_ip;
        //inet_ntop(AF_INET, &(client_addr->sin_addr.s_addr), (char *)&client_ip, sizeof(client_ip)); 失败
        client_ip = inet_ntoa(client_addr->sin_addr);

        printf("[%s:%d] connected\n", client_ip, client_port);
 
        communicate(client_fd, client_addr);
    }
}

void communicate(int client_fd, struct sockaddr_in* client_addr) {
    while (1) {
        // 接收数据
        int recv_ret; // 接收数据的大小
        char* recv_buf = (char*)malloc(BUFSIZ);
        recv_ret = recv(client_fd, recv_buf, BUFSIZ, 0);
        if (recv_ret == 0) {
            puts("The remote closed connection");
            close(client_fd);
            free(client_addr);
            free(recv_buf);
            return;
        }
        else if (recv_ret == -1) {
            close(client_fd);
            free(client_addr);
            free(recv_buf);
            PERROR("recv")
        }
        else {
            printf("receive message: %s\n", recv_buf);
            free(recv_buf);
        }


        // 发送数据
        char* input_buf = (char*)malloc(BUFSIZ);
        fgets(input_buf, 128, stdin);  //fgets会在后面自动添加一个换行符

        char* send_buf;        
        send_buf = strtok(input_buf, "\n");  //字符串分割函数

        int send_size;
        send_size = send(client_fd, send_buf, strlen(send_buf), 0);
        if (send_size == -1) {
            free(input_buf);
            PERROR("send")
        }
        printf("send size:%d\n", send_size);
        free(input_buf);
    }
    
}
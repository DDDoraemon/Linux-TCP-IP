#ifndef __SERVER_H
#define __SERVER_H

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*宏函数
include <stdlib.h>
void perror(const char *str)
把一个描述性错误消息输出到标准错误 stderr。首先输出字符串 str，后跟一个冒号，然后是一个空格

include <stdlib.h>
void exit(int status)
立即终止调用进程。任何属于该进程的打开的文件描述符都会被关闭，
该进程的子进程由进程 1 继承，初始化，且会向父进程发送一个 SIGCHLD 信号。*/
#define PERROR(text)  \
    perror(text);     \
    exit(EXIT_FAILURE); 


#define PORT 9527 // socket服务的端口号
#define ADDR "192.168.148.128" // 服务器器的IP地址
#define MAX_LINK 128  //listen的最大连接数

int server_fd;  // 服务器的socket文件标识符
struct sockaddr_in server_addr;  // 服务器的socket地址结构

static int bind_ret; // bind函数的返回值 成功返回0  失败返回-1 静态数据 防止被外部访问
static int listen_ret; //listen函数的返回值 成功返回0  失败返回-1  静态数据 防止被外部访问


int init_server_socket();
void connection();
void communicate();

#endif
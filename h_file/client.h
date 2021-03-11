#ifndef __CLIENT_H
#define __CLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //close
#include <errno.h>

#define PERROR(text)  \
    perror(text);     \
    exit(EXIT_FAILURE); 

#define SERVER_PORT 9527
#define SERVER_IP "192.168.148.128"


static int client_socket_fd;
static struct sockaddr_in server_addr;
static socklen_t server_size;

static int connect_ret;

void init_socket();
void connection();
void communication();
#endif
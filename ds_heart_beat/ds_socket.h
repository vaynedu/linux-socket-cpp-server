#ifndef DS_SOCKET_H
#define DS_SOCKET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/sendfile.h>



#define    ds_PORT        (8080)                    // 我的常用端口
#define    BREAK_CONNECT   "I_LOVE_YOU_I_MISS_YOU_CAO_YAN_QIN"  //定义断开连接的宏定义
#define    BACKLOG         (5)



#define    ds_two_max(a,b)          ((a)>(b)?(a):(b))
#define    ds_three_max(a,b,c)      (((((a)>(b))?(a):(b))>(c))?((((a)>(b))?(a):(b)):(c)))

#define    ds_two_min(a,b)          ((a)<(b)?(a):(b))
#define    ds_three_min(a,b,c)      (((((a)<(b))?(a):(b))<(c))?((((a)<(b))?(a):(b)):(c)))

//封装 socket
int ds_socket(int domain,int type,int protocol);

//填充struct sockaddr_in 结构体，注意传32位整数ip
void ds_sockaddr_in(struct sockaddr_in *addr,
                    unsigned short sin_family,
                    unsigned short int port,
                    uint32_t ip_addr
                    );
//封装bind，里面还有可以重用处于timewait期间的socket地址
void ds_bind(int sockfd,struct sockaddr *my_addr,int addrlen);

// 封装listen
void ds_listen(int sockfd,int backlog);

// 封装accept
int ds_accept(int sockfd,struct sockaddr *addr,int *addrlen);

// 封装connect
void ds_connect(int sockfd,struct sockaddr *addr,int addrlen);

//创建一个监听socket直接返回回去，所有的麻烦的装在里面 
int   ds_create_socket();


//完整的写，错误返回-1，成功返回0
int   ds_write(int fd,void *buffer,int length);

//完整的读，错误返回-1，成功返回0
int   ds_read (int fd,void *buffer,int length);

// 设置非阻塞
void ds_setnonblocking(int sockfd);



#endif

















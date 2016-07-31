/*==========================================================
     > File Name: server.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 31 Jul 2016 12:10:51 PM CST
===========================================================*/
#include "ds_socket.h"
#include <pthread.h>

#define   BUFFER_SIZE   1024


enum Type{HEART,OTHER};

struct PACKET_HEAD
{
    enum Type type;
    int  length;
    char content[100];
};

void *recv_heart(void *arg)
{
    int n = 0;
    int count = 0;
    struct PACKET_HEAD receivebuf,heartbuf,sendbuf;
    int newfd = *((int*)arg);
    char buf_heart[] = "I am alive";
    char buf_send[]  = "I love you too";

    while(1){
        if((n = read(newfd,&receivebuf,sizeof(receivebuf))) < 0){
             printf("read error :%s\n",strerror(errno));
             close(newfd);
             exit(1);
        }else if(n == 0){
             printf("client is over\n");
             close(newfd);
             break;
        }
        if(receivebuf.type == HEART){
             heartbuf.type = HEART;
             heartbuf.length = 0;
             memcpy(heartbuf.content,buf_heart,sizeof(heartbuf));
             write(newfd,&heartbuf,sizeof(heartbuf));
        }else if(receivebuf.type == OTHER){
             printf("receive client data:%s\n",receivebuf.content);
             sendbuf.type = OTHER;
             sendbuf.length = 0;
             memcpy(sendbuf.content,buf_send,sizeof(sendbuf));
             write(newfd,&sendbuf,sizeof(sendbuf));
        }
        sleep(3);
        memset(&receivebuf,0x00,sizeof(receivebuf));
    }

    printf("thread exit,a new accept break\n");
    pthread_exit(NULL);

    return NULL;
}
int main(int argc,char *argv[])
{
    int sockfd;
    int newfd;
    struct sockaddr_in client_addr;
    socklen_t   client_addr_length = sizeof(client_addr);

    sockfd = ds_create_socket();

    while(1){
         newfd = ds_accept(sockfd,(struct sockaddr*)(&client_addr),&client_addr_length);

         pthread_t  thread;
         if(pthread_create(&thread,NULL,recv_heart,(void*)(&newfd)) !=  0){
              printf("pthread_create failed\n");
              exit(1);
         }
    }

    return 0;
}









































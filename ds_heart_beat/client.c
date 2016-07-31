/*==========================================================
     > File Name: client.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 31 Jul 2016 12:11:17 PM CST
===========================================================*/

#include "ds_socket.h"
#include <pthread.h>
#include <signal.h>

enum Type{HEART,OTHER};

struct PACKET_HEAD
{
    enum Type type;
    int length;
    char content[100];
};



void sig_pipe(int sig)
{
    printf("signal = %d\n",sig);
}



void *start_keepalive(void *arg)
{
    int count = 0;
    int newfd = *(int*)(arg);
    char buf[] = "I hate you";
    struct PACKET_HEAD head;

    while(1){
         head.type = HEART;
         memcpy(head.content,buf,sizeof(buf));
         head.length = sizeof(head.content);
         printf("head.length = %d\n",head.length);
         write(newfd,&head,sizeof(head));

         sleep(1);
         count++;
         if(count > 10){
             break;
         }
    }
    close(newfd);
    pthread_exit(NULL);
    exit(1);
    return NULL;
}



int main(int argc,char *argv[])
{
    int sockfd;
    int n = 0;
    char *ip = "127.0.0.1";
    char buf[100] = "I love you";
    struct sockaddr_in  server_addr;
    struct PACKET_HEAD sendbuf,receivebuf;

    sockfd = ds_socket(AF_INET,SOCK_STREAM,0);

    inet_aton(ip,&server_addr.sin_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(ds_PORT);

    ds_connect(sockfd,(struct sockaddr*)(&server_addr),sizeof(server_addr));

    if(signal(SIGPIPE,sig_pipe) == SIG_ERR){
        printf("signal error\n");
        exit(1);
    }

    while(1){
         sendbuf.type = OTHER;
        // printf("sizeof(buf) = %d\n",sizeof(buf));
         memcpy(sendbuf.content,buf,sizeof(buf));
         sendbuf.length = sizeof(sendbuf.content);
         //printf("sendbuf.length = %d\n",sendbuf.length);
         write(sockfd,&sendbuf,sizeof(sendbuf));


         if((n=read(sockfd,&receivebuf,sizeof(receivebuf))) < 0){
              printf("read error,start keepalive\n");
              pthread_t thread;
              pthread_create(&thread,NULL,start_keepalive,(void*)(&sockfd));
              pthread_join(thread,NULL);
              printf("server is over\n");
              close(sockfd);
              exit(1);
              sleep(2);
         }else if(n == 0){
              printf("read 0\n");
              sleep(2);
         }else{
              printf("receive server from:%s\n",receivebuf.content);
         }
    }
    return 0;
}


























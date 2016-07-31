#include "ds_socket.h"

//封装 socket
int ds_socket(int domain,int type,int protocol)
{
    int sockfd;
    sockfd = socket(domain,type,protocol);
    if(sockfd == -1){
       fprintf(stderr,"sockfd create failed....................\n");
       exit(1);
    }
    return sockfd;
}

//填充struct sockaddr_in 结构体，注意传32位整数ip
void ds_sockaddr_in(struct sockaddr_in *addr,
                    unsigned short sin_family,
                    unsigned short int port,
                    uint32_t ip_addr
                    )
{
    addr->sin_family = sin_family;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(ip_addr);

}

//封装bind，里面还有可以重用处于timewait期间的socket地址
void ds_bind(int sockfd,struct sockaddr *my_addr,int addrlen)
{
    int ret = -1;
    int opt = 1;

    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
    ret = bind(sockfd,my_addr,addrlen);
    if(ret == -1){
        fprintf(stderr,"bind failed...........................\n");
        exit(1);
    }
}

// 封装listen
void ds_listen(int sockfd,int backlog)
{
    int ret;
    ret = listen(sockfd,backlog);
    if(ret == -1){
        fprintf(stderr,"listen error.............................");
        exit(1);
    }
}

// 封装accept
int ds_accept(int sockfd,struct sockaddr *addr,int *addrlen)
{
    int newfd;
    newfd = accept(sockfd,addr,addrlen);
    if((newfd < 0)&&(errno == EINTR)){
        fprintf(stderr,"accept EINTR..........................\n");
        exit(1);
    }else if(newfd < 0){
        fprintf(stderr,"accept error:.......%s\n",strerror(errno));
        exit(1);
    }
    return newfd;
}
//封装connect
void ds_connect(int sockfd,struct sockaddr *addr,int addrlen)
{
     int ret;
     ret = connect(sockfd,addr,addrlen);
     if(ret == -1){
          fprintf(stderr,"connect error........................\n");
          exit(1);
     }
}

// 直接创建一个监听socket出来
int   ds_create_socket()
{
      int sockfd;
      int ret = 1;

      struct sockaddr_in  server_addr;

      sockfd = ds_socket(AF_INET,SOCK_STREAM,0);

      ds_sockaddr_in(&server_addr,AF_INET,ds_PORT,INADDR_ANY);

      setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&ret,sizeof(int));

      ds_bind(sockfd,(struct sockaddr*)(&server_addr),sizeof(server_addr));

      ds_listen(sockfd,BACKLOG);

      return sockfd;
}

//完整的写，错误返回-1，成功0
int ds_write(int fd,void *buffer,int length)
{
    int bytes_left;
    int written_bytes;
    char *ptr;

    ptr = buffer;
    bytes_left = length;

    while(bytes_left){
        written_bytes = write(fd,ptr,bytes_left);
        if(written_bytes <= 0){ //出错了
            if(errno == EINTR){ //中断错误
                written_bytes = 0;
                printf("write errno  =  EINTR\n");
            }else{              //
                printf("write error\n");
                return (-1);
            }//end if
        }//end if
        bytes_left -= written_bytes;
        ptr +=  written_bytes;  //
    }//end while
    printf("write succeed\n");
    return  0;
}
// 完整的读，错误返回-1，成功返回0
int ds_read(int fd,void *buffer,int length)
{
    int bytes_left;
    int read_bytes;
    char *ptr;

    ptr = buffer;
    bytes_left = length;

    while(bytes_left){
          read_bytes = read(fd,ptr,bytes_left);
          if(read_bytes < 0){
              if(errno == EINTR){
                  printf("read erron = EINTR\n");
                  read_bytes = 0;
              }else{
                  printf("read error\n");
                  return (-1);
              }
          }else if(read_bytes == 0){
              printf("break  internet connect\n");
              break;
          }//end if else

          bytes_left -= read_bytes;
          ptr += read_bytes;
    }//end while

    return (length - bytes_left);
}

void ds_setnonblocking(int sockfd)
{
      int opts;
      int ret;

      opts = fcntl(sockfd,F_GETFL);
      if(opts < 0){
          fprintf(stderr,"fcntl F_GETFL  error\n");
          exit(1);
      }//end if
      opts = opts | O_NONBLOCK;
      ret = fcntl(sockfd,F_SETFL,opts);
      if(ret < 0){
          fprintf(stderr,"fcntl F_SETFL error\n");
          exit(0);
      }

}



































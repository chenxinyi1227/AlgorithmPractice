#include "threadPoll.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define MAX_LISTEN  128
#define LOCAL_IPADDRESS "127.0.0.1"
#define EPOLL_SIZE 1024

#if 1
void conver_char(char *p)
{
    if(p == NULL)
    {
        return;
    }
    for(; *p != '\0'; p++)
    {
        if(*p >= 'a' && *p <= 'z')
        {
            *p = *p - 'a' + 'A';
        }
    }
}
#endif

int main()
{
    /*
    1、socket:创建套接字
    2、初始结构体struct sockaddr_in
    3、bind:给套接字绑定端口和ip
    4、listen:监听 主动文件描述符变为被动（等待连接）
    5、accept:处理请求(阻塞) -- 连接套接字（收发数据）
    6、recv/send:接受发送数据（SIGPIPE忽略）
    7、shutdown:关闭连接
    sockfd//连接   cfd//通信
    */
//    signal(SIGPIPE, SIG_IGN);
//    signal(SIGINT, server_exit);//

   //1
    int sockfd = socket(AF_INET,SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket error");
        // exit(-1);
    }

    // int flags = fcntl(sockfd, F_GETFL, 0);
    // flags |= O_NONBLOCK;
    // fcntl(sockfd, F_SETFL, flags);

    /* 端口复用 */
    int opt = 1;
    int retOpt = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));
    if(retOpt == -1)
    {
        perror("setsockopt error");
        // exit(-1);
    }

    //2
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;//地址族TCP
    s_addr.sin_port = htons(8080);//端口号
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP

    //3
    int retBind = bind(sockfd, (struct sockaddr*)&s_addr, sizeof(struct sockaddr_in));
    if(retBind == -1)
    {
        perror("bind error");
        // exit(-1);
    }
    printf("bind successfully\n");

    //4 愿意接受连接请求 TCP 默认128
    int retlisten = listen(sockfd, MAX_LISTEN);//监听人数
    if(retlisten == -1)
    {
        perror("bind error");
    }
    printf("listen successfully\n");



#if 0
    //可操作1、select 多路转接
    fd_set readSet;
    bzero(&readSet, sizeof(readSet));//文件描述符集合（关于读的集合）
    // FD_ZERO(&readSet);
    int maxfd = sockfd;

    FD_SET(sockfd, &readSet);

    //更新集合的备份
    fd_set tmpreadSet;
    FD_ZERO(&tmpreadSet);

    while(1)
    {
        tmpreadSet = readSet;
        int retSelect = select(maxfd + 1, &tmpreadSet, NULL, NULL,NULL, 0);
        if(retSelect == -1)
        {
            perror('select error');
            break;
        }

        if(FD_ISSET(sockfd, &readSet))
        {
            //通信句柄
            int acceptfd = accept(sockfd, NULL, NULL);
            if(acceptfd == -1)
            {
                perror("accpet error");
                exit(-1);
            }
            FD_SET(acceptfd, &readSet);
            maxfd = maxfd < acceptfd ? acceptfd : maxfd;
        }

        //有通信 todo...
    }
#endif

#if 1

    //5 获取连接请求并建立连接 
    //返回的是新的套接字描述符 可以与客户端通信
    printf("accepting...\n");
    struct sockaddr_in c_addr;//客户端的IP
    memset(&c_addr, 0, sizeof(c_addr));
   

    char buffer[BUFFER_SIZE] = {0};//发送缓冲区
    char relaybuffer[BUFFER_SIZE] = {0};//发送缓冲区
    int recvLen = 0;//接收长度
#if 1
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    struct epoll_event events[BUFFER_SIZE] = {0};//发生的变化数
    int epfd = epoll_create(1);
    if(epfd == -1)
    {
        perror("epoll error");
    }
    event.events = EPOLLIN;//读
    event.data.fd = sockfd;
    int ret_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
    if(ret_ctl == -1)
    {
        perror("epoll ctl error");
        exit(-1);
    }
    char message[1024];
#endif

#endif
    socklen_t size = sizeof(c_addr);
    //循环处理线程
   
#if 1
    while(1)
    {
        int rnum = epoll_wait(epfd, events, EPOLL_SIZE, -1);//events返回的是变化的
        if(rnum == -1)
        {
            perror("epoll wait error");
        }
        printf("rnum = %d\n", rnum);
        /* 
        程序执行到这个地方有两种情况：
        1、超时
        2、有监听数据来了 */
        
        for(int i= 0; i <EPOLL_SIZE; i++)
        {
            if(events[i].events == EPOLLIN)//可读
            {
                if(events[i].data.fd == sockfd)//sockfd
                {
                    size = sizeof(c_addr);
                    int cfd = accept(sockfd, (struct sockaddr *)&c_addr, &size);//cfd新的套接字描述符
                    //cfd连接套接字：每连接一个客户端成功，就会生成一个描述符，只要知道这个描述符，就能够与客户端通信
                    if(cfd == -1 )
                    {
                        perror("accept error");
                    }
                    //ntoa:
                    printf("xxx上线......\n");
                    printf("info client1 : ip = %s, port:%d\n", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port));
                
                    event.events = EPOLLIN;
                    event.data.fd = cfd;
                    int ctrret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &event);
                    if(ctrret == -1)
                    {
                        perror("epoll_ctl error");
                    }
                    printf("epoll_ctl success\n");
                 
                    if(--rnum <= 0)
                    {
                        break;//退出循环
                    }
                }
                else//不是sockfd, 连接的fd
                {
                    // printf("info client2 : ip = %s, port:%d\n", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port));
                    int fd = events[i].data.fd;
                    memset(buffer, 0, sizeof(buffer));
                    int r_n = read(fd, buffer, sizeof(buffer) - 1);
                    if(r_n < 0)
                    {
                        printf("read data error\n");
                        close(fd);
                        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &event);
                    }
                    if(r_n == 0)
                    {
                        printf("客户端退出\n");
                        close(fd);
                        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &event);
                        break;
                    }
                    printf("data data:%s\n", buffer);
                    conver_char(buffer);
                    write(fd, buffer, strlen(buffer));
                    
                    if(--rnum <= 0)
                    {
                        break;//返回wait
                    }
                }
            } 
        }
#endif
      }
#if 0

        /* 接收数据 */
        char message[BUFFER_SIZE] = {0};
        int retRecv = recv(cfd, message, sizeof(message) - 1, 0);
        int retRead;
        if(retRecv == -1)
        {
            perror("recv massage error");
            exit(-1);
        }
        //recv = 0, 代表对应的客户端退出
        if(retRecv  == 0)
        {
            printf("client is close@\n");
        }
        else
        {
            printf("send to msg :%s\n", message);
            //发送数据
            memset(message, 0, sizeof(message));
            scanf("%s", message);
            retRead = send(cfd, message, strlen(message), 0);//0阻塞式发送
            // retRead = send(cfd, message, strlen(message), MSG_NOSIGNAL);//忽略SIGPIPE信号

            if(retRead < 0)
            {
                perror("send data error");
                exit(-1);
            }
            printf("send to msg successfully ! size:%d\n", retRead);
        }
  
    //开线程
    // threadPoolAddTask(&poll, threadFunc, (void*)&cfd);
    shutdown(cfd, SHUT_RDWR);//关掉读写
#endif
#if 0
while(1)
{
        int cfd = accept(sockfd, (struct sockaddr *)&c_addr, &size);
        if(cfd == -1)
        {
            perror("accept error");
            exit(-1);
        }
        while(1)
        {
            //接收客户端发送的消息
            memset(buffer, 0, sizeof(buffer));
            int retread = recv(cfd, buffer, sizeof(buffer) - 1, 0);// 留出一个字符的空间给'\0'
            // printf("%d\n", retread);
            if(retread <= 0)
            {
                if(retread == 0)
                {
                    printf("Client disconnected\n");
                }
                else
                {
                    perror("recv error");
                }
                close(cfd);
                break;;//跳出当前循环的剩余部分
            }
            printf("buffer:%s\n", buffer);
            //发送回复消息
            // conver_char(buffer);
            memset(relaybuffer, 0 ,sizeof(relaybuffer));
            printf("回复：");
            scanf("%s", relaybuffer);
            int retsend = send(cfd, relaybuffer, strlen(relaybuffer), 0);
            if(retsend == -1)
            {
                perror("send error");
                close(cfd);
                break;
            }
        } 
   }
    close(sockfd);
#endif
    return 0;
}


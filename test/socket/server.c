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

#define BUFFER_SIZE 1024
#define MAX_LISTEN  128
#define LOCAL_IPADDRESS "127.0.0.1"

int sockfd;//连接
void server_exit(int sig)
{
    if(sig == SIGPIPE)
    {
        shutdown(sockfd, SHUT_RDWR);
        printf("server exit\n");
    }
    else
    {
        shutdown(sockfd, SHUT_RDWR);
        exit(-1);
    }
}

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
   signal(SIGPIPE, SIG_IGN);
   signal(SIGINT, server_exit);//


   //1
    sockfd = socket(AF_INET,SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }

    /* 端口复用 */
    int opt = 1;
    int retOpt = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));
    if(retOpt == -1)
    {
        perror("setsockopt error");
        exit(-1);
    }
    //2
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;//地址族TCP
    addr.sin_port = htons(8080);//端口号
    addr.sin_addr.s_addr = INADDR_ANY;//IP
    // addr.sin_addr.s_addr = inet_addr("172.18.188.222");
    // addr.sin_addr.s_addr = htonl("192.168.1.105");

    //3
    int retBind = bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if(retBind == -1)
    {
        perror("bind error");
        exit(-1);
    }
    printf("bind successfully\n");

    //4 愿意接受连接请求 TCP 默认128
    int retlisten = listen(sockfd, MAX_LISTEN);//监听人数
    if(retlisten == -1)
    {
        perror("bind error");
        exit(-1);
    }
    printf("listen successfully\n");

    //5 获取连接请求并建立连接 
    //返回的是新的套接字描述符 可以与客户端通信
    struct sockaddr_in c_addr;//客户端的IP
    memset(&c_addr, 0, sizeof(c_addr));

    socklen_t size = sizeof(struct sockaddr_in);
    int cfd = accept(sockfd, (struct sockaddr *)&c_addr, &size);//cfd新的套接字描述符
    //cfd连接套接字：每连接一个客户端成功，就会生成一个描述符，只要知道这个描述符，就能够与客户端通信
    if(cfd == -1)
    {
        perror("accept error");
        exit(-1);
    }
    //ntoa:
    printf("info client : ip = %s, port:%d\n", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port));

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
        printf("send to msg :%d\n", message);
        //发两次就会产生信号
        while(1)
        {
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
    }
    shutdown(cfd, SHUT_RDWR);//关掉读写
    
    return 0;
}

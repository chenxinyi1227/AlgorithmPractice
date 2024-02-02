#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define MAX_LISTEN  128
#define SERVER_PORT 8080
#define SERVER_IP  "172.18.188.222"

/* 
    1、socket 套接字 TCP
    2、connect 进行连接
    3、read write收发数据
    4、shutdown 关闭连接
     */
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket falied");
    }
    printf("socket success\n");

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    //端口
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    //IP地址 
    int ret = inet_pton(AF_INET, SERVER_IP, (void *)&serverAddr.sin_addr.s_addr);
    // serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);已被废弃
    if (ret != 1)
    {
        perror("inet_pton error");
        exit(-1);
    }
    ret = connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret == -1)
    {
        perror("connect error");
        exit(-1);
    }

    char recvBuffer[BUFFER_SIZE] = {0};
    memset(recvBuffer, 0, sizeof(recvBuffer));
    
    //写缓冲区
    char writebuffer[BUFFER_SIZE];
    memset(writebuffer, 0, sizeof(writebuffer));

    while(1)
    {
        memset(writebuffer, 0, sizeof(writebuffer));
        printf("input:");
        scanf("%s",writebuffer);
        // fgets(writebuffer, sizeof(writebuffer), stdin); // 使用fgets代替scanf
        // writebuffer[strcspn(writebuffer, "\n")] = 0; // 移除fgets读取的换行符
      
        //发送消息给服务器
        int retsend = send(sockfd, writebuffer, strlen(writebuffer), 0);
        if(retsend == -1) 
        {
            perror("send error");
            exit(-1);
        }
        /* 接收回复消息 */
        memset(recvBuffer, 0, sizeof(recvBuffer));
        int readBytes = recv(sockfd, recvBuffer, sizeof(recvBuffer) - 1, 0);
        if(readBytes <= 0)
        {
            if(readBytes == 0)
            {
                perror("Connection closed by peer");
                exit(-1);
            }
            else
            {
                perror("recv error");
            }
            close(sockfd);
            break;
        }
        printf("recv:%s\n", recvBuffer);
    }

    sleep(3);
    close(sockfd);
    return 0;

}
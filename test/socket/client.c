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
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
    printf("connect success\n");

    char buffer[BUFFER_SIZE] = {0};
    //读写 write read
    printf("请输入消息\n");
    scanf("%s", buffer);
    // sprintf(buffer, "chenfdf");
    write(sockfd, buffer, sizeof(buffer));

    char recvbuffer[BUFFER_SIZE] = {0};
    read(sockfd, recvbuffer, sizeof(recvbuffer));
    printf("recvbuffer:%s\n", recvbuffer);
    sleep(3);

    // close(sockfd);
    return 0;
}
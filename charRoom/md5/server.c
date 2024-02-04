#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/md5.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//gcc 编译 -lcrypto
//makefile 编译 make all

#define BUFFER_SIZE 1024
#define MALLOC_ERROR -1
#define SUCCESS 0

/* 创建文件缓存目录 */
int ChatRoomInit(const char *filepath)
{
    /* 创建用户本地数据目录 */
    if(access(filepath, F_OK) == -1)
    {
        if (mkdir(filepath, 0777) == -1)
        {
            perror("mkdir error");
            return MALLOC_ERROR;
        }
        else
        {
            printf("目录创建成功\n");
            return 1;
        }
    }
    else
    {
        printf("目录已存在\n");
        return 1;
    }
}

//计算MD5值
int calculateMD5(const char *filename, unsigned char *md5Digest) 
{
    // 打开要发送的文件
    int fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {
        perror("open error");
        return -1;
    }

    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    unsigned char buffer[BUFFER_SIZE] = {0};
    size_t bytesRead;
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) 
    {
        MD5_Update(&md5Context, buffer, bytesRead);
    }

    MD5_Final(md5Digest, &md5Context);

    close(fd);
    return SUCCESS;
}

int main() 
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    FILE *file;
    size_t bytesRead;

    // 创建套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 配置服务器地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    // 绑定套接字到指定端口
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    // 监听连接请求
    if (listen(serverSocket, 10) == 0)
        printf("Listening...\n");
    else
        printf("Error in listening.\n");

    // 接受客户端连接
    addr_size = sizeof(serverStorage);
    newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);


    printf("请输入要传输的文件名：");
    char fileName[BUFFER_SIZE] = {0};
    scanf("%s", fileName);
    printf("dir:%s\n", fileName);

    // 打开要发送的文件
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) 
    {
        perror("open error");
        return -1;
    }
     printf("open success\n");
    // 计算文件的MD5值
    unsigned char md5Digest[MD5_DIGEST_LENGTH];
    int ret = calculateMD5(fileName, md5Digest);
    if(ret != 0)
    {
        return 1;
    }

    // 发送文件的MD5值给客户端
    send(newSocket, md5Digest, MD5_DIGEST_LENGTH, 0);

    // 逐片读取并发送文件数据
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) 
    {
        send(newSocket, buffer, bytesRead, 0);
    }

    // 关闭文件和套接字
    close(fd);
    close(newSocket);

    return SUCCESS;
}

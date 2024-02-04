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
#define MAX_PATH 1024
#define SERVER_IP "127.0.0.1"
#define NULL_PTR -1
#define SUCCESS 0

/* 拼接路径 */
static int JoinPath(char *path, const char *dir, const char *filename)
{
    int ret = 0;
    if (path == NULL || dir == NULL || filename == NULL)
    {
        return NULL_PTR;
    }
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, filename);
    return SUCCESS;
}

int main() 
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    FILE *file;
    size_t bytesReceived;

    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 配置服务器地址和端口
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    // 连接到服务器
    addr_size = sizeof(serverAddr);
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    // 接收服务器发送的文件的MD5值
    unsigned char serverMd5Digest[MD5_DIGEST_LENGTH];
    recv(clientSocket, serverMd5Digest, MD5_DIGEST_LENGTH, 0);

    // 打开文件以写入接收到的数据
#if 0
    char src_path[MAX_PATH] = "/home/user/data/file.txt"; // 源文件路径
    char dest_dir[MAX_PATH] = "/home/user/output/"; // 目标目录路径
    char dest_path[MAX_PATH * 2] = ""; // 目标文件路径
#endif

    char src_path[MAX_PATH] = "/home/AlgorithmPractice/AlgorithmPractice/charRoom/md5/record"; // 源文件路径
  
    printf("请输入要接收的的文件名:\n");
    char dest_dir[MAX_PATH] = {0}; // 目标目录路径
    scanf("%s", dest_dir);

    char dest_path[MAX_PATH * 2] = {0}; // 目标文件路径
    JoinPath(dest_path, src_path, dest_dir);

    int fd = open(dest_path, O_WRONLY | O_CREAT, 0664);
    if (fd == -1) 
    {
        perror("open error");
        return 1;
    }
    printf("文件成功\n");
    
    // 计算接收到的文件的MD5值
    unsigned char clientMd5Digest[MD5_DIGEST_LENGTH];
    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    // 接收并写入文件数据
    while ((bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) 
    {
        write(fd, buffer, bytesReceived);                                                                                                                            
        MD5_Update(&md5Context, buffer, bytesReceived);
    }

    MD5_Final(clientMd5Digest, &md5Context);

    // 比较MD5值是否匹配
    if (memcmp(serverMd5Digest, clientMd5Digest, MD5_DIGEST_LENGTH) == 0) 
    {
        printf("File transfer successful. MD5 matches.\n");
    } 
    else 
    {
        printf("File transfer failed. MD5 does not match.\n");
    }

    // 关闭文件和套接字
    close(fd);
    close(clientSocket);

    return 0;
}

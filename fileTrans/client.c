#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080

int main() 
{
    int client_fd;
    struct sockaddr_in address;
    char filename[256];
    char buffer[1024];

    // 创建套接字
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror("套接字创建失败");
        exit(EXIT_FAILURE);
    }

    // 连接服务器
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &address.sin_addr) <= 0) 
    {
        perror("无效的地址");
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {
        perror("连接失败");
        exit(EXIT_FAILURE);
    }

    printf("连接服务器成功\n");

    // 输入文件名
    memset(filename, 0, sizeof(filename));
    printf("请输入要上传的文件名：");
    scanf("%s", filename);

    // 发送文件名
    if (send(client_fd, filename, strlen(filename) + 1, 0) < 0)
    {
        perror("发送文件名失败");
        exit(EXIT_FAILURE);
    }

    // 打开文件
    int file_fd = open(filename, O_RDONLY);
    if (file_fd < 0) 
    {
        perror("打开文件失败");
        exit(EXIT_FAILURE);
    }

    // 读取文件内容并发送
    ssize_t bytes_read;
    while((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) 
    {
        printf("%s\n", buffer);
        if (send(client_fd, buffer, bytes_read, 0) < 0) 
        {
            perror("发送文件内容失败");
            exit(EXIT_FAILURE);
        }
        memset(buffer, 0, sizeof(buffer)); // 清空buffer，准备下一次读取
    }
   
    if (bytes_read < 0) 
    {
        perror("读取文件内容失败");
        exit(EXIT_FAILURE);
    }

    #if 0
    memset(buffer, 0, sizeof(buffer));
    // 等待服务器回复
    if (recv(client_fd, buffer, sizeof(buffer), 0) < 0) 
    {
        perror("读取服务器回复失败");
        exit(EXIT_FAILURE);
    }

    printf("服务器回复：%s\n", buffer);
    #endif 
    
    printf("文件上传完成\n");
    close(file_fd);
    close(client_fd);

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <fcntl.h>

#define PORT 8080
#define BUFFER_SIZE 1024

/* 拼接路径 */
static int JoinPath(char *path, const char *dir, const char *filename)
{
    int ret = 0;
    if (path == NULL || dir == NULL || filename == NULL)
    {
        return -1;
    }
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, filename);
    return 0;
}

int receiveFile(int client_fd, int file_fd) 
{
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_received;

    while ((bytes_received = recv(client_fd, buffer, sizeof(buffer), 0)) > 0) 
    {
        ssize_t bytes_written = write(file_fd, buffer, bytes_received);
        // printf("buffer:%s\n", buffer);
        if (bytes_written < 0) 
        {
            perror("写入文件内容失败");
            exit(EXIT_FAILURE);
        }
        // 清空buffer
        memset(buffer, 0, sizeof(buffer));
    }

    if (bytes_received < 0) 
    {
        perror("接收文件内容失败");
        exit(EXIT_FAILURE);
    }
    printf("文件接收完成\n");
    return 0;
}

int main() 
{
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    // 创建套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("套接字创建失败");
        exit(EXIT_FAILURE);
    }

    // 设置套接字端口复用
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) 
    {
        perror("设置套接字端口复用失败");
        exit(EXIT_FAILURE);
    }

    // 绑定地址和端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {
        perror("bind error");
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_fd, 1) < 0) 
    {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    printf("等待客户端连接...\n");

    // 接受连接
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
    {
        perror("接受连接失败");
        exit(EXIT_FAILURE);
    }

    printf("客户端连接成功\n");

    // 读取文件名
    memset(buffer, 0, sizeof(buffer));
    if (recv(client_fd, buffer, sizeof(buffer), 0) <= 0) 
    {
        perror("读取文件名失败");
        exit(EXIT_FAILURE);
    }

    printf("接收文件：%s\n", buffer);

    // 打开文件
    char src_path[1024] = {0};
    char dir[1024] = {"./record"};
    JoinPath(src_path, dir, buffer);
    printf("文件路径：%s\n", src_path);
    int file_fd = open(src_path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (file_fd < 0) 
    {
        perror("创建文件失败");
        exit(EXIT_FAILURE);
    }
    receiveFile(client_fd, file_fd);
    #if 0
    // 接收文件
    int ret = receiveFile(client_fd, file_fd);
    if(ret == 0)
    {
        // 发送响应
        const char *response = "文件接收成功";
        ssize_t bytes_sent = send(client_fd, response, strlen(response), 0);
        if (bytes_sent < 0) 
        {
            perror("发送响应失败");
            exit(EXIT_FAILURE);
        } 
        else if (bytes_sent < strlen(response)) 
        {
            fprintf(stderr, "发送响应不完全\n");
        // 可以选择继续发送剩余的部分或重新发送整个响应
        }
    }
    #endif
    
    close(file_fd);
    close(client_fd);
    close(server_fd);

    return 0;
}

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
/* 1千字节（KB）= 1024字节 */
/* 一个文件大小为1024字节意味着该文件占用了1024个字节的存储空间。 */
int GetFileLength(const char *filename)
{
    int fd = open(filename, O_RDWR);
    if(fd == -1)
    {
        perror("open filename error");
        return 0;
    }
    //获取文件长度
    struct stat statbuf;
    stat(filename, &statbuf);
    int size = statbuf.st_size;
    close(fd);
    return size;
}

int main()
{
    char buffer[1024] = {0};
    printf("请输入要查找的文件名：\n");
    scanf("%s", buffer);

    int fileLength = GetFileLength(buffer);
    if(fileLength == 0)
    {
        printf("没有这个文件\n");
    }
    else
    {
        printf("%s 的大小 %d Bytes\n", buffer, fileLength);
    }

    return 0;
}
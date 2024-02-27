#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//gcc 编译 -lcrypto

#define BUFFER_SIZE 1024
#define MALLOC_ERROR -1

/* 创建文件缓存目录 */
int createDirectory(const char *filepath)
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


//计算文件的MD5值
int calculateMD5(const char *filename, unsigned char *md5Digest) 
{
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
    return 0;
}

int main() 
{
#if 0
    unsigned char md5Digest[MD5_DIGEST_LENGTH];
    int ret = calculateMD5("server.c", md5Digest);
    if(ret != 0)
    {
        return 0;
    }
    printf("MD5: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) 
    {
        printf("%02x", md5Digest[i]);
    }
    printf("\n");
#else
    char dir[BUFFER_SIZE] = {0};
    scanf("%s", dir);
    printf("dir:%s\n", dir);
    int ret = createDirectory(dir);
    if(ret)
    {
        printf("success\n");
    }
#endif
    return 0;
}

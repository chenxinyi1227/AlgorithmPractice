#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 20

typedef struct user
{
    char name[10];
    char password[10];
}user;

int main()
{
    #if 1
    int fd = open("./1.txt", O_RDWR);
     if(fd == -1)
    {
        perror("open error");
        exit(-1);
    }

    int fdCopy = open("./copy.txt", O_RDWR | O_CREAT);
     if(fdCopy == -1)
    {
        perror("open error");
        exit(-1);
    }
    #endif
    char arr[BUFFER_SIZE] = {0};
   
    #if 0
    int readBytes = 0;
    while((readBytes = read(fd, arr, sizeof(arr) - 1)) > 0)
    {
        int writeBytes = write(fdCopy, arr, readBytes);
        if(writeBytes < 0)
        {
            break;
        }
    }
    #else
    int readLen = 0;
    while(1)
    {
        readLen = read(fd, arr, BUFFER_SIZE - 1);
        write(fdCopy, arr, readLen);
        if (readLen < BUFFER_SIZE - 1 || readLen == 0)
        {
            break;
        }
    }
    // printf("arr:\n%s\n", arr);
    #endif
    close(fd);
    close(fdCopy);
}
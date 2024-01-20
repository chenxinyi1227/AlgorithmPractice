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
    user us1;
    memset(&us1, 0, sizeof(user));

    // strncpy(us1.name, "chen", strlen("chen"));
    // strncpy(us1.password, "123", strlen("123123"));
    printf("%s%s\n", us1.name, us1.password);

#if 1
    int fd = open("./test.txt",O_RDWR | O_CREAT | O_APPEND, 0644);
    if(fd == -1)
    {
        perror("open error");
        exit(-1);
    }
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%s %s", us1.name, us1.password);

    int ret = write(fd, buffer, BUFFER_SIZE - 1);
    if(ret == -1)
    {
        perror("write error");
        exit(-1);
    }


    lseek(fd, 0, SEEK_SET);    

    char readBuffer[BUFFER_SIZE];
    memset(readBuffer, 0, sizeof(readBuffer));

    int retRead = read(fd, readBuffer, sizeof(readBuffer) - 1);
    if(retRead == -1)
    {
        perror("read error");
        exit(-1);
    }

    printf("readbuffer:%s\n", readBuffer);
    #endif
    close(fd);
    return 0;
}
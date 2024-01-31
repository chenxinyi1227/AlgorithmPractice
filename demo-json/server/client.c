#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/stat.h>

//打印历史信息
void print_history(char *id)
{
    char filename[128] = {};
    sprintf(filename,"%s/%s%s","./record.txt",id,".txt");
    int fd;
    fd = open(filename,O_RDONLY);
    if(fd == -1){
        perror("client open record error\n");
    }
    int len;
    char buf[1024];
    while((len = read(fd,buf,1024)) != 0)
    {
        printf("%s",buf);
        memset(buf,'\0',1024);
    }
    printf("------------历史群聊信息-----------\n");
    close(fd);
}

int main(int argc, char *argv[])
{
    const char *ip;
    unsigned short int port;
    //如果没指明，默认是ip = "127.0.0.1",port = 533
    if(argc < 3){
        ip = "127.0.0.1";
        port = 8080;
    }else{
        ip = argv[1];
        port = atoi(argv[2]);
    }
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd == -1){
        perror("socket error\n");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    socklen_t addrlen = sizeof(addr);

    int ret = connect(sfd,(const struct sockaddr*)(&addr),addrlen);
    if(ret == -1){
        perror("connect error\n");
        return -1;
    }
    char name[50];
    char id[8];
    printf("请输入群号：");
    fgets(id,8,stdin);
    printf("请输入你的群聊昵称：");
    fgets(name,49,stdin);
    char temp[128];
    strncat(temp,id,6);
    strncat(temp,name,strlen(name) - 1);
    send(sfd, temp, strlen(temp), 0);
    char cutid[7] = {};
    strncat(cutid,id,6);
    sleep(1);
    print_history(cutid);
    //创建两个进程，父进程负责收消息，子进程负责发消息
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error\n");
    }else if(pid == 0)
    {
        while(1)
        {
            char buf[1024] = {};
            fgets(buf,1023,stdin);
            if(send(sfd,buf,strlen(buf) + 1,0) <= 0)
            {
                break;
            }
            printf("\n");
        }
    }else{
        while(1)
        {
            char buf[1024] = {};
            if(recv(sfd,buf,1024,0) <= 0)
            {
                break;
            }
            time_t current_time;
            time(&current_time);
            printf("%s",ctime(&current_time));
            printf("%s\n\n",buf);
        }
    }
    close(sfd);
    return 0;
}
//编译代码
//gcc client.c -o client

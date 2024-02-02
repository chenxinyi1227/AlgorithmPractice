#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<time.h>
#include<fcntl.h>

#define PORT 8080
#define SERVER_IP "172.18.188.222"
#define BUFFER_SIZE 128
#if 0
typedef struct Client
{
    //socket文件描述符
    int cfd;
    //客户端名称
    char name[50];
    //群号，6位
    char id[7];
    //群聊信息文件地址
    char address[128];
}Client;

//设置最多群聊人数
Client client[MAX] = {};
size_t count = 0;

//初始化互斥锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//保存聊天记录
void save(char *msg, Client c)
{
    char record[1024] = {};
    time_t current_time;
    time(&current_time);
    char *str = ctime(&current_time);
    int fd;
    fd = open(c.address,O_APPEND | O_WRONLY);
    if(fd == -1){
        perror("server open record error\n");
        return;
    }
    sprintf(record,"%s%s\n\n",str,msg);
    int ret = write(fd,record,strlen(record));
    if(ret == -1){
        perror("wirte record error\n");
        return;
    }
    close(fd);
}

//广播函数
void broadcast(char *msg, Client c)
{
    pthread_mutex_lock(&mutex);
    save(msg,c);
    //广播给与当前用户在同一群聊中的所有其他用户
    for(size_t i = 0; i < count; i++)
    {
        if(client[i].cfd != c.cfd && strcmp(client[i].id,c.id) == 0)
        {
            if(send(client[i].cfd,msg,strlen(msg),0) <= 0)
            {
                break;
            }
        }
    }
    pthread_mutex_unlock(&mutex);
}

//判断群号是否存在于record目录里，否创建文件
void exits(Client c){
    DIR *db;
    struct dirent *p;
    db = opendir("./record.txt");
    char temp[20];
    sprintf(temp,"%s%s",c.id,".txt");
    int flag = 0;
    while((p = readdir(db)))
    {
        if(strcmp(p->d_name,temp) == 0)
        {
            flag = 1;
              break;
        }
    }
    if(flag == 0)
    {
        umask(0);
        int ret = creat(c.address,0666);
        if(ret == -1) perror("creat record error\n");
    }
    closedir(db);
}

//对每一个客户端连接都创建一个线程处理
void *pthread_run(void *arg)
{
    Client c = *(Client*)(arg);
    exits(c);
    //单次通信最大数据长度
    char buf[100] = {};
    strcpy(buf,c.name);
    strcat(buf,"已加入群聊");
    broadcast(buf,c);
    while(1){
        char buf[1024] = {};
        strcpy(buf,c.name);
        strcat(buf," :");
        int ret = recv(c.cfd,buf + strlen(buf), 1024 - strlen(buf), 0);
        //如果没有接收到该客户端的消息，说明该客户端离线
        if(ret <= 0){
            for(size_t i = 0; i < count; i++)
            {
                if(client[i].cfd == c.cfd)
                {
                    //把该客户端的信息从客户端列表中删除
                    client[i] = client[count - 1];
                    count--;
                    strcpy(buf,c.name);
                    strcat(buf,"已退出群聊");
                    break;
                }
            }
            broadcast(buf,c);
            close(c.cfd);
            return NULL;
        }
        else
        {
            //接收到了客户端消息，则广播该消息
            broadcast(buf,c);
        }
    }
}

//接收用户要加入的群号和用户昵称,并将客户端保存到客户端列表
void receive(int cfd)
{
    char temp[128] = {};
    recv(cfd,temp,128,0);
    int i = 0;
    while(i < 6){
        client[count].id[i] = temp[i];
        i++;
    }
    client[count].id[i] = '\0';
    int j = 0;
    while(i < strlen(temp))
    {
        client[count].name[j] = temp[i];
        i++;
        j++;
    }
    client[count].name[i] = '\0';
    sprintf(client[count].address,"%s/%s%s","./record",client[count].id,".txt");
    client[count].cfd = cfd;
}
#endif
//服务端socket初始化
int inet_init(const char *ip, unsigned short int port)
{
    //使用TCP/IP(V4)协议
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("socket err\n");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    //将port转换为网络字节序（大端模式）
    addr.sin_port = htons(port);
    //将点分十进制的IPv4地址转换成网络字节序列的长整型
    addr.sin_addr.s_addr = inet_addr(ip);
    socklen_t addrlen = sizeof(addr);
    //将ip地址绑定套接字
    int ret = bind(sockfd,(struct sockaddr*)(&addr), addrlen);
    if( ret == -1){
        perror("bind error\n");   
        return -1;
    }
    //监听链接请求队列，accept()应答之前，允许在进入队列中等待的连接数目是10
    if(listen(sockfd,10) == -1)
    {
        perror("listen error\n");
        return -1;
    }
    return sockfd;
}

int main()
{
    const char *ip;
    unsigned short int port;
    //如果没有指定ip地址和端口号，则使用默认ip地址（本机）和端口号

    int sfd = inet_init(SERVER_IP, PORT);
    if(sfd == -1)
    {
        perror("server socket init error\n");
        return -1;
    }
    printf("服务器已启动...\n");
    while(1){
        struct sockaddr_in caddr;
        socklen_t len = sizeof(caddr);
       
        int cfd = accept(sfd,(struct sockaddr*)(&caddr),&len);
        if(cfd == -1){
            perror("accept error\n");
            return -1;
        }
        receive(cfd);
        //创建一个线程处理此次连接
        pthread_t tid;
        int ret = pthread_create(&tid,NULL,pthread_run,(void*)(&client[count]));
        count++;
        if(ret != 0){
            printf("pthread_create: %s\n",strerror(ret));
            continue;
        }
        printf("有一个客户端成功连接: ip <%s> port [%hu]\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
    }
    
    return 0;
}
//编译代码
//gcc server.c -o server -lpthread

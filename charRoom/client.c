#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <error.h>
#include <pthread.h>
#include <json-c/json.h>

/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,        // 成功
    NULL_PTR = -1,      // 空指针
    MALLOC_ERROR = -2,  // 内存分配失败
    SEND_ERROR = -3,    // 发送错误
    RECV_ERROR = -4,    // 接收错误
    JSON_ERROR = -5,   // json错误
    OTHER_ERROR = -6,  // 其他错误
};

#define SERVER_PORT 8080
#define SERVER_IP   "172.18.188.222"
#define BUFFER_SIZE 1024
#define CONTENT_SIZE 1024 //信息内容长度

//接收参数
typedef struct RecvArgs
{
    int sockfd;
    json_object *friends;
}RecvArgs;

//全局变量
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
//接收标识
int g_recv_flag = 0;

//登录
int ChatRoomLogin(int sockfd);
//注册
int logon(int sockfd);

int ChatRoomExit();
/* 登录成功的主界面 */
static int ChatRoomMain(int fd, json_object *json);

/* 发送json到服务器 */
static int SendJsonToServer(int fd, const char *json)
{
    int ret = 0;
    int len = strlen(json);
    ret = send(fd, json, len, 0);
    if (ret < 0)
    {
        perror("send error");
    }
    return SUCCESS;
}
/* 接收json */
static int RecvJsonFromServer(int fd,  char *json)
{
    int ret = recv(fd, json, CONTENT_SIZE, 0);
    if (ret < 0)
    {
        perror("recv error");
        return ret;
    }
    
    return SUCCESS;
}

int main()
{
    pthread_mutex_init(&g_mutex, NULL);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    int ret = inet_pton(AF_INET, SERVER_IP, (void *)&(serverAddress.sin_addr.s_addr));
    if (ret != 1)
    {
        perror("inet_pton error");
        exit(-1);
    }

    /* ip地址 */
    ret = connect(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (ret == -1)
    {
        perror("connect error");
        exit(-1);
    }

    printf("欢迎来到聊天室\n");
    while (1)
    {
        printf("请输入要进行的功能:\na.登录\nb.注册\n其他.退出聊天室\n");
        char ch;
        while ((ch = getchar()) == '\n');   // 读取一个非换行的字符
        while ((getchar()) != '\n');        // 吸收多余的字符
        switch (ch)
        {
            case 'a':
                ChatRoomLogin(fd);
                break;
            case 'b':
                logon(fd);//注册
                break;
            default:
                ChatRoomExit();
                close(fd);
                return 0;
        }
    }

    return 0;
}

/* 聊天室登录 */
int ChatRoomLogin(int sockfd)
{
    char name[20] = {0};
    char password[20] = {0};

    printf("登录\n");
    printf("请输入账号:");
    scanf("%s", name);
    /* 不显示输入的密码 */
    printf("请输入密码：");
    scanf("%s", password);
    /* 登录信息转化为json，发送给服务器 */
    json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "type", json_object_new_string("login"));
    json_object_object_add(jobj, "name", json_object_new_string(name));
    json_object_object_add(jobj, "password", json_object_new_string(password));
    const char *json = json_object_to_json_string(jobj);

    SendJsonToServer(sockfd, json);

    /* 等待服务器响应 */
    printf("登录中 ");
    char retJson[CONTENT_SIZE] = {0};
    RecvJsonFromServer(sockfd, retJson);
    json_object *jreceipt = json_tokener_parse(retJson);

    if (jreceipt == NULL)
    {
        printf("登录失败\n");
        json_object_put(jreceipt);
        json_object_put(jobj);
        jreceipt = NULL;
        jobj = NULL;
        return JSON_ERROR;
    }

    const char *receipt = json_object_get_string(json_object_object_get(jreceipt,"receipt"));
    if (strcmp(receipt, "success") == 0)
    {
        printf("登录成功\n");
        json_object_put(jobj);
        jobj = NULL;
        json_object_object_del(jreceipt, "receipt");    // 删除掉多余的回执数据
        ChatRoomMain(sockfd,jreceipt);
    }
    else
    {
        const char *reason = json_object_get_string(json_object_object_get(jreceipt,"reason"));
        printf("登录失败:%s\n",reason);
        json_object_put(jreceipt);
        json_object_put(jobj);
        jreceipt = NULL;
        jobj = NULL;
        return SUCCESS;
    }
    return SUCCESS;
}

//注册
int logon(int sockfd)
{
    printf("=====注册=====\n");
    char name[10] = {0};
    char password[10] = {0};
    printf("请输入账号: ");
    scanf("%s", name);
    printf("请输入密码: ");
    scanf("%s", password);

    char buffer[BUFFER_SIZE] = {0};
    json_object *sendjson = json_object_new_object();
    json_object_object_add(sendjson, "type", json_object_new_string("register"));
    json_object_object_add(sendjson, "name", json_object_new_string(name));
    json_object_object_add(sendjson, "password", json_object_new_string(password));

    const char *sendMessage = json_object_to_json_string(sendjson);
    printf("sendMessage:%s\n",sendMessage);
    SendJsonToServer(sockfd, sendMessage);
    
    printf("注册中...\n");

    //回复的消息
    char returnbuffer[CONTENT_SIZE] = {0};
    RecvJsonFromServer(sockfd, returnbuffer);
    printf("returnMessage:%s\n", returnbuffer);
    json_object *returnMessage = json_tokener_parse(returnbuffer);
    if (returnMessage == NULL)
    {
        printf("注册失败\n");
        json_object_put(returnMessage);
        json_object_put(sendjson);
        returnMessage = NULL;
        sendjson = NULL;
        return JSON_ERROR;
    }

    const char *receipt = json_object_get_string(json_object_object_get(returnMessage,"receipt"));
    if (strcmp(receipt, "success") == 0)
    {
        printf("注册成功\n");
        json_object_put(sendjson);
        sendjson = NULL;
        /* 初始化好友列表和群组列表 */
        ChatRoomMain(sockfd,returnMessage);  
    }
    else
    {
        const char *reason = json_object_get_string(json_object_object_get(returnMessage,"reason"));
        printf("注册失败:%s\n",reason);
        sleep(1);
        json_object_put(returnMessage);
        json_object_put(sendjson);
        returnMessage = NULL;
        sendjson = NULL;
    }
    return SUCCESS; 
}

/* 登录成功的主界面 */
static int ChatRoomMain(int fd, json_object *json)
{
    //此时已经获取用户名
    json_object *usernameJosn = json_object_object_get(json, "name");
    if(usernameJosn == NULL)
    {
        printf("json_object_object_get error\n");
        return JSON_ERROR;
    }
    const char *username = json_object_get_string(usernameJosn);
    
    //朋友名
    json_object *friendsJson = json_object_object_get(json, "friends");
    if(usernameJosn == NULL)
    {
        printf("json_object_object_get error\n");
        return JSON_ERROR;
    }
    const char *friends = json_object_get_string(friendsJson);
    printf("friend:%s\n",friends);

    //开启接收
    pthread_t tid;
    g_recv_flag = 1;
    RecvArgs recvArgs;
    recvArgs.sockfd = fd;
    recvArgs.friends = friends;
    pthread_create(&tid, NULL, ChatRoomRecvMsg, (void *)&recvArgs);
    printf("登录成功\n");
    printf("请选择功能\n");
    printf("a.打印好友列表 b.私聊");
    char choice = 0;
    scanf("%s", &choice);
    switch(choice)
    {
        case 'a':printf("😘1\n");

                break;
        case 'b':printf("😘2\n");
                break;
        default:
        return SUCCESS;
    }
    
    return SUCCESS;
}

int ChatRoomExit()
{
    printf("退出\n");
    // return 0;
}

/* 接收消息 */
static void* ChatRoomRecvMsg(void* args)
{
    
}
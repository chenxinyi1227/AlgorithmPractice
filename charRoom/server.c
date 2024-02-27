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
#include <sys/epoll.h>
#include <ctype.h>
#include <mysql/mysql.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <fcntl.h>
#include <pthread.h>
#include <mysql/mysql.h>

#define SERVER_PORT 8080
#define MAX_LISTEN  128
#define LOCAL_IPADDRESS "127.0.0.1"
#define BUFFER_SIZE 128

//任务参数：需要正在监听的套接字和数据库的句柄
typedef struct TaskArgs
{
    int client_fd;
    MYSQL *mysql;
}TaskArgs;

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
int sockfd;

/* 接收请求并分类/处理请求 */
void *handleRequest(void* arg);
/* 用户注册 */
static int userRegister(int client_fd, json_object *json, MYSQL *mysql);
/* 用户登录 */
static int userLogin(int client_fd, json_object *json,  MYSQL *mysql);
/* 获取用户的群组和好友列表 */
static int getUserInfo(const char *name, json_object *json,  MYSQL *mysql);

/* 数据库查询 */
static int sqlQuery(const char *sql, MYSQL *mysql, MYSQL_RES **res)
{
    int sql_ret = mysql_query(mysql, sql);
    if (sql_ret != 0)
    {
        printf("sql: %s\n", sql);
        printf("sql_ret:%d\n", sql_ret);
        printf("sqlQuery error:%s\n", mysql_error(mysql));
        return -1;
    }
    *res = mysql_store_result(mysql);
    if (*res == NULL)
    {
        printf("sql store result error:%s\n", mysql_error(mysql));
        return -1;
    }
    return SUCCESS;
}


static int userRegister(int client_fd, json_object *json,  MYSQL *mysql);

#if 1
void *createSocket()
{
    /* 创建socket套接字 */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }

    /* 设置端口复用 */
    int enableOpt = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&enableOpt, sizeof(enableOpt));
    if (ret == -1)
    {
        perror("setsockopt error");
        exit(-1);
    }
}

/* 绑定 */
void *bindSocket()
{
    struct sockaddr_in localAddress;  
    memset(&localAddress, 0, sizeof(localAddress)); /* 清除脏数据 */

    localAddress.sin_family = AF_INET;   /* 地址族 */
    localAddress.sin_port = htons(SERVER_PORT); /* 端口需要转成大端 */
    localAddress.sin_addr.s_addr = htonl(INADDR_ANY);  /* ip地址需要转成大端 */

    int localAddressLen = sizeof(localAddress);
    int ret = bind(sockfd, (struct sockaddr *)&localAddress, localAddressLen);
    if (ret == -1)
    {
        perror("bind error");
        exit(-1);
    }

}

/* 监听 */
void *listenSocket()
{
    int ret = listen(sockfd, MAX_LISTEN);
    if (ret == -1)
    {
        perror("listen error");
        exit(-1);
    }
}
#endif
#if 1
//数据库初始化和建立表
int mysql_Table_Init(MYSQL **recvSQL)
{
    MYSQL *mysql = mysql_init(NULL);//数据库初始化
    if(mysql == NULL)
    {
        printf("mysql_init:%s\n", mysql_error(mysql));
        return -1;
    }

    mysql_real_connect(mysql, "localhost", "root", "1234", "demo", 3306, NULL, 0);

    //建表
    //使用者
    char buffer[1024] = {0};
    sprintf(buffer, "create table if not exists users(name varchar(10), password varchar(10))");
    int sql_ret = mysql_query(mysql, buffer);
    if(sql_ret != 0)
    {
        printf("create users table error:%s\n", mysql_error(mysql));
        return -1;
    }
    memset(buffer, 0, sizeof(buffer));
    //朋友表
    sprintf(buffer, "create table if not exists friends(name varchar(%d), friend_name varchar(%d))", 10, 10);
    sql_ret = mysql_query(mysql, buffer);
    if (sql_ret != 0)
    {

        printf("create friends table error:%s\n", mysql_error(mysql));
        return -1;
    }
    memset(buffer, 0, sizeof(buffer));

    //信息表
    sprintf(buffer, "create table if not exists messages(sender_name varchar(10), receiver_name varchar(10), message varchar(%d))", 1024);
    sql_ret = mysql_query(mysql, buffer);
    if (sql_ret != 0)
    {
        printf("create messages table error:%s\n", mysql_error(mysql));
        return -1;
    }
    memset(buffer, 0, sizeof(buffer));
    *recvSQL = mysql;

    return SUCCESS;
}
#endif

int main()
{
    //初始化套接字
    createSocket(&sockfd);
    bindSocket();
    listenSocket();
#if 1
    MYSQL *mysql;
    //数据库初始化和建立表
    mysql_Table_Init(&mysql);
#endif
    //创建epoll 红黑树 实例
    int epfd = epoll_create(1);
    if(epfd == -1)
    {
        perror("epoll create error");
        exit(-1);
    }

    //2 将socked 添加到红黑树实例里面
    struct epoll_event event;
    //清楚脏数据
    memset(&event, 0, sizeof(event));
    event.data.fd = sockfd;
    event.events = EPOLLIN;//读事件
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
    if(ret == -1)
    {
        perror("epoll ctl error");
        exit(-1);
    }

    int nums = 0;       //监听的数量

    while(1)
    {
        struct epoll_event events[BUFFER_SIZE];
        memset(events, 0, sizeof(events));

        nums = epoll_wait(epfd, events, BUFFER_SIZE, -1);//不等待
        if(nums == -1)
        {
            perror("epoll wait error");
            exit(-1);
        }
        /* 
        程序执行到这个地方有两种情况：
        1、超时
        2、有监听数据来了 */
        for(int idx = 0; idx < nums; idx++)
        {
            int fd = events[idx].data.fd;
            if(fd == sockfd)//处理新连接
            {
                //有连接
                int client_fd = accept(sockfd, NULL, NULL);
                if(client_fd == -1)
                {
                    perror("accept error");
                    exit(-1);
                }
                printf("%d上线......\n", client_fd);

                struct epoll_event conn_event;
                memset(&conn_event, 0, sizeof(conn_event));
                conn_event.data.fd = client_fd;
                conn_event.events = EPOLLIN;

                //将通信的句柄 添加到数节点中
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &conn_event);
                if(ret == -1)
                {
                    perror("epoll_ctl error");
                    continue;;
                }
                TaskArgs *args = (TaskArgs*)malloc(sizeof(TaskArgs));
                if (args == NULL)
                {
                    perror("malloc error");
                    continue;
                }
                args->client_fd = client_fd;
                args->mysql = mysql;

                #if 1
                pthread_t tid;
                /* 开一个线程去服务acceptfd */
                int ret = pthread_create(&tid, NULL, handleRequest, (void *)args);
                if (ret != 0)
                {
                    perror("thread create error");
                    exit(-1);
                }
                #endif
            }
            else
            {
                //处理已连接的客户端
                //接收信息
            }
        }
    }
    
    /* 关闭文件描述符 */
    close(sockfd);

    return 0;
}

void *handleRequest(void* arg)
{
    pthread_detach(pthread_self());
    printf("success\n");
    int client_fd = ((TaskArgs*)arg)->client_fd;
    MYSQL *mysql = ((TaskArgs*)arg)->mysql;
    printf("client_fd:%d\n", client_fd);
    char recvbuffer[1024] = {0};
    while(1)
    {
        memset(recvbuffer, 0, sizeof(recvbuffer));
        int readBytes = read(client_fd, recvbuffer, sizeof(recvbuffer) - 1);
        if(readBytes < 0)
        {
            perror("recv error");
            break;
        }
        else if (readBytes == 0)
        {
            //todo...移除在线状态
            printf("client %d disconnected\n", client_fd);
            close(client_fd);
            return NULL;
        }
        else 
        {
            //处理请求
            printf("recv:%s\n", recvbuffer);
            //解析json
            json_object *recvjobj = json_tokener_parse(recvbuffer);
            if (recvjobj == NULL)
            {
                printf("json parse error\n");
                return NULL;
            }
            json_object *type = json_object_object_get(recvjobj, "type");
            if (type == NULL)
            {
                printf("json type error\n");
                return NULL;
            }
            const char * typeStr = json_object_get_string(type);
            printf("%s\n", typeStr);
            //分类处理请求
            if(strcmp(typeStr, "register") == 0)
            {
                printf("deer\n");
                userRegister(client_fd, recvjobj, mysql);
            }
            if(strcmp(typeStr,"login") == 0)
            {
                userLogin(client_fd, recvjobj, mysql);
            }
        }
    }
    return NULL;
}

//注册
static int userRegister(int client_fd, json_object *json,  MYSQL *mysql)
{
    printf("注册\n");
    const char *name = json_object_get_string(json_object_object_get(json, "name"));
    const char *password = json_object_get_string(json_object_object_get(json, "password"));
    printf("name: %s\n", name);
    printf("password: %s\n", password);

    /* 返回用json */
    json_object *returnJson = json_object_new_object();

    /* 查询数据库 */
    char sql[1024] = {0};
    sprintf(sql, "select * from users where name='%s'", name);
    printf("sql: %s\n", sql);
    MYSQL_RES *res = NULL;
    int sql_ret = sqlQuery(sql, mysql, &res);
    if (sql_ret != 0)
    {
        printf("sql query error:%s\n", mysql_error(mysql));
        json_object_object_add(returnJson, "receipt", json_object_new_string("fail"));
        json_object_object_add(returnJson, "reason", json_object_new_string("数据库查询错误"));
    }
    else
    {
        /* 处理数据库查询结果 */
        int num_rows = mysql_num_rows(res);     // 行数
        if (num_rows > 0)
        {
            json_object_object_add(returnJson, "receipt", json_object_new_string("fail"));
            json_object_object_add(returnJson, "reason", json_object_new_string("用户名已存在"));
        }
        else
        {
            /* 插入数据库 */
            sprintf(sql, "insert into users(name, password) values('%s', '%s')", name, password);
            sql_ret = mysql_query(mysql, sql);
            if (sql_ret != 0)
            {
                printf("sql insert error:%s\n", mysql_error(mysql));
                json_object_object_add(returnJson, "receipt", json_object_new_string("fail"));
                json_object_object_add(returnJson, "reason", json_object_new_string("数据库插入错误"));
            }
            else
            {
                /* 注册成功 */
                printf("sql: %s\n", sql);
                json_object_object_add(returnJson, "receipt", json_object_new_string("success"));
                json_object_object_add(returnJson, "name", json_object_new_string(name));
                json_object * friends = json_object_new_object();
                json_object_object_add(returnJson, "friends",friends);
                json_object * messages = json_object_new_array();
                json_object_object_add(returnJson, "messages", messages);
                // /* 记录登录状态 */
                // updateUserStatus(name, client_fd, mysql);
            }
        }
    }

    const char *sendJson = json_object_to_json_string(returnJson);
    printf("send json: %s\n", sendJson);
    /* 发送json */
    int ret = send(client_fd, sendJson, strlen(sendJson), 0);

    /* 释放json */
    json_object_put(json);
    json_object_put(returnJson);

    /* 释放结果集 */
    if (res != NULL)
    {
        mysql_free_result(res);
        res = NULL;
    }

    if (ret == -1)
    {
        perror("send error");
        return -1;
    }
    return 0;
}

/* 登录 */
static int userLogin(int client_fd, json_object *json,  MYSQL *mysql)
{
    printf("登录\n");
    /* 返回用json */
    json_object *returnJson = json_object_new_object();
    /* 获取json中的内容 */
    const char *name = json_object_get_string(json_object_object_get(json, "name"));
    const char *password = json_object_get_string(json_object_object_get(json, "password"));
    printf("name: %s\n", name);
    printf("password: %s\n", password);
    /* 查询数据库 */
    char sql[1024] = {0};
    sprintf(sql, "select password from users where name='%s'", name);
    printf("sql: %s\n", sql);
    MYSQL_RES *res = NULL;
    int sql_ret = sqlQuery(sql, mysql, &res);
    if (sql_ret != 0)
    {
        printf("sql query error:%s\n", mysql_error(mysql));
        json_object_object_add(returnJson, "receipt", json_object_new_string("fail"));
        json_object_object_add(returnJson, "reason", json_object_new_string("数据库查询错误"));
    }
    else
    {
        /* 处理数据库查询结果 */
        int num_rows = mysql_num_rows(res);     // 行数
        if (num_rows > 0)
        {
            /* 判断密码是否正确 */
            MYSQL_ROW row = mysql_fetch_row(res);
            const char *dbPassword = row[0];
            if (strcmp(password, dbPassword) == 0)
            {
                /* 登录成功 */
                json_object_object_add(returnJson, "receipt", json_object_new_string("success"));
                json_object_object_add(returnJson, "name", json_object_new_string(name));
                getUserInfo(name, returnJson, mysql);
                // getOfflineMessages(name, returnJson, mysql);
                // /* 记录登录状态 */
                // updateUserStatus(name, client_fd, mysql);
            }
            else
            {
                /* 密码错误 */
                json_object_object_add(returnJson, "receipt", json_object_new_string("fail"));
                json_object_object_add(returnJson, "reason", json_object_new_string("密码错误"));
            }
        }
        else
        {
            /* 用户名不存在 */
            json_object_object_add(returnJson, "receipt", json_object_new_string("fail"));
            json_object_object_add(returnJson, "reason", json_object_new_string("用户名不存在"));
        }
    }
    /* 发送json */
    const char *sendJson = json_object_to_json_string(returnJson);
    printf("send json: %s\n", sendJson);
    int ret = send(client_fd, sendJson, strlen(sendJson), 0);
    /* 释放json */
    json_object_put(json);
    json_object_put(returnJson);
    /* 释放结果集 */
    if (res != NULL)
    {
        mysql_free_result(res);
        res = NULL;
    }
    if (ret == -1)
    {
        perror("send error");
        return SEND_ERROR;
    }
    return SUCCESS;
}

/* 获取用户的群组和好友列表 */
static int getUserInfo(const char *name, json_object *json,  MYSQL *mysql)
{
    MYSQL_RES *res = NULL;
    char buffer[1024] = {0};
    sprintf(buffer,"select friend_name from friends where name='%s'", name);
    int sql_ret = mysql_query(mysql, buffer);
    if(sql_ret != 0)
    {
        printf("sqlQuery error:%s\n", mysql_error(mysql));
        return -1;
    }
    res = mysql_store_result(mysql);
    if(res == NULL)
    {   
        printf("sql store result error:%s\n", mysql_error(mysql));
        return -1;
    }
    MYSQL_ROW row;
    int row_num = mysql_num_rows(res);
    int i = 0;
    json_object *friends = json_object_new_object();
    while (row = mysql_fetch_row(res))
    {
        printf("row[0]:%s\n",row[0]);
        json_object_object_add(json, "friend", json_object_new_string(row[0]));
        if(i ==row_num)
        {
            break;
        }
    }
    if(res != NULL)
    {
        mysql_free_result(res);
        res = NULL;
    }
}

#include <stdio.h>
#include <mysql/mysql.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 128

int main()
{
    int fd = open("./test.txt", O_RDONLY);
    char buffer[128] = {0};
    int readBytes = read(fd, buffer, sizeof(buffer) - 1);
    if(readBytes == -1)
    {
        perror("read errror");
        exit(-1);
    }
    printf("buffer:%s\n", buffer);

    json_object *recvjson = json_tokener_parse(buffer);
    if (recvjson == NULL)
    {
        printf("json parse error\n");
        return 0;
    }

    json_object *idObj = json_object_object_get(recvjson, "id");
    int id = json_object_get_int(idObj);
    json_object *nameObj = json_object_object_get(recvjson, "name");
    const char *name = json_object_to_json_string(nameObj);
    json_object *passwdObj = json_object_object_get(recvjson, "password");
    int passwd = json_object_get_int(passwdObj);
    // printf("recv id : %s\n", str);
    
    #if 1
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    if(mysql == NULL)
    {
        printf("mysql_init failed\n");
        return -1;
    }

    const char *host = "localhost";
    const char *user = "root";
    const char *password = "1234";
    const char *db = "demo";//数据库
    unsigned int port = 3306;
    mysql_real_connect(mysql, host, user, password, db, port, NULL, 0);
    if(mysql == NULL)
    {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(mysql));
        return -1;
    }
    char buffer1[128] = {0};
    
#if 1
    sprintf(buffer1, "create table if not exists user(id int primary key, name varchar(20), password int)");
    #endif
    int ret = mysql_query(mysql, buffer1);
     if(ret != 0)
    {
        fprintf(stderr, "create failed: %s\n", mysql_error(mysql));
        return -1;
    }
    printf("创建表成功\n");
#else
    sprintf(buffer1, "drop table if exists user");
    int ret = mysql_query(mysql, buffer1);
     if(ret != 0)
    {
        fprintf(stderr, "create failed: %s\n", mysql_error(mysql));
        return -1;
    }
    printf("创建表成功\n");
#endif

    sprintf(buffer1, "insert into user values(%d, %s, %d)", id, name, passwd);
    ret = mysql_query(mysql, buffer1);
    if(ret != 0)
    {
        fprintf(stderr, "insert failed: %s\n", mysql_error(mysql));
        return -1;
    }
    printf("插入数据库成功\n");
    return 0;
}



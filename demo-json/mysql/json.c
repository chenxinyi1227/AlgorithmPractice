#include <json-c/json.h>
#include <json-c/json_object.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024
int main()
{
    struct json_object *jsonObj = json_object_new_object();
#if 0
    //发送
    json_object_object_add(jsonObj, "id", json_object_new_string("2015"));
    json_object_object_add(jsonObj, "name", json_object_new_string("chen"));
    json_object_object_add(jsonObj, "password", json_object_new_string("1111"));

    const char *json = json_object_to_json_string(jsonObj);
    printf("json:%s\n", json);
    int fd = open("./test.txt", O_RDWR | O_CREAT, 0644);
    char buffer[128] = {0};
    strncpy(buffer, json, strlen(json));
    write(fd, buffer, strlen(json));
#else
    //接收
    MYSQL *mysql = mysql_init(NULL);
    if(mysql == NULL)
    {
        fprintf(stderr, "init failed: %s\n", mysql_error(mysql));
        return -1;
    }
    printf("插入数据库成功\n");
    
    char buffer[BUFFER_SIZE]= {0};
    sprintf(buffer, "select id from user ");



#endif
}
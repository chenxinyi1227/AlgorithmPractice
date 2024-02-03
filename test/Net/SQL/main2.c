#include <mysql/mysql.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

#define TIME_LEN 80
#define BUFFER_SIZE 1024

//获取当前时间
char *getCurTime()
{
    time_t currentTime;
    struct tm *timeinfo;
    static char timeString[TIME_LEN] = {0};//将timeString改为静态变量
    time(&currentTime);  //获取当前时间
    timeinfo = localtime(&currentTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);
    return timeString;
}

int main()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char buffer[BUFFER_SIZE] = {0};

    char *server = "localhost";
    char *user = "root";
    char *password = "1234";
    char *database = "mytest";
 
    conn = mysql_init(NULL);
 
    // 连接数据库
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    //建表user
    sprintf(buffer, "create table if not exists users(id int primary key auto_increment, name varchar(20), time varchar(255))");
    int ret = mysql_query(conn, buffer);
    if(ret != 0)
    {
        fprintf(stderr, "create table users error:%s\n", mysql_error(conn));
        return 1;
    }
   printf("create table user success\n");

#if 1
    //计算表的大小
    //1、建表1
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "create table if not exists tableSize(table_name varchar(50) primary key, table_size int default 0)");
    ret = mysql_query(conn, buffer);
    if(ret != 0)
    {
        fprintf(stderr, "create table tableSize error :%s\n", mysql_error(conn));
        return 1;
    }
    printf("create table table_num success\n");
#endif
    //2、建立触发器
   


    // while(1)
    // {
     
        //插入数据
        memset(buffer, 0, sizeof(buffer));
        char *time = getCurTime();
        sprintf(buffer, "insert into tableSize(table_name) values ('user')");
        ret = mysql_query(conn, buffer);
        if(ret != 0)
        {
            fprintf(stderr, "insert table tableSize error: %s\n", mysql_error(conn));
            return 1;
        }
        printf("insert1 success\n");

    /* 从键盘输入字符 */
    // printf("Please enter a string: ");
    // fgets(str, sizeof(str), stdin);

        memset(buffer, 0, sizeof(buffer));
        char *timeNow = getCurTime();
        sprintf(buffer, "create trigger if not exists update_tableSize after insert on users \
        for each row \
        update tableSize set table_size = table_size + 1 where table_name = new.name");
        ret = mysql_query(conn, buffer);
        if(ret != 0)
        {
            fprintf(stderr, "create table trigger error %s\n", mysql_error(conn));
            return 1;
        }

    int num = 0;
     while(1)
    {
        num++;
        //插入数据
        memset(buffer, 0, sizeof(buffer));
        char name[10];
        printf("请输入发送者姓名:");
        scanf("%s", name);
        char receiver[10];
        char *time = getCurTime();
        // printf("name:%s time:%s\n",name, time);
        sprintf(buffer, "insert into users(name, time) values ('%s', '%s')", name, time);
        printf("buffer: %s\n", buffer);
        ret = mysql_query(conn, buffer);
        if(ret != 0)
        {
            fprintf(stderr, "insert table users error:%s\n", mysql_error(conn));
            return 1;
        }
        printf("insert1 success\n");

           // 执行SQL查询
        if (mysql_query(conn, "select * from users")) 
        {   
            fprintf(stderr, "select table %s\n", mysql_error(conn));
            return 1;
        }

        res = mysql_store_result(conn);
        int row_num = mysql_num_rows(res);
        int field_num = mysql_num_fields(res);
        printf("查询结果有%d行 %d列\n", row_num, field_num);
        // 处理查询结果
        while ((row = mysql_fetch_row(res)) != NULL) 
        {
            for(int i = 0; i < mysql_num_fields(res); i++) 
            {
                printf("%-4s ", row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
           if(num > 4)
        {
            break;
        }
    }

   
    
    // 释放结果集和关闭连接
    mysql_free_result(res);
    mysql_close(conn);
 
    return 0;
}
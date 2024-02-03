#include <mysql/mysql.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
 
    char *server = "localhost";
    char *user = "root";
    char *password = "1234";
    char *database = "demo";
 
    conn = mysql_init(NULL);
 
    // 连接数据库
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
 
    // 执行SQL查询
    if (mysql_query(conn, "select * from user")) 
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
 
    res = mysql_use_result(conn);
 
    // 处理查询结果
    while ((row = mysql_fetch_row(res)) != NULL) 
    {
        for(int i = 0; i < mysql_num_fields(res); i++) 
        {
            printf("%-4s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
    
    time_t currentTime;
    struct tm *timeinfo;
    char timeString[80];
    //获取当前时间
    time(&currentTime);
    timeinfo = localtime(&currentTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("当前时间：%s\n", timeString);
    
    
    // 释放结果集和关闭连接
    mysql_free_result(res);
    mysql_close(conn);
 
    return 0;
}
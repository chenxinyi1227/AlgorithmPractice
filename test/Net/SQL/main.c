#include <mysql/mysql.h>
#include <stdio.h>
 
int main()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
 
    char *server = "localhost";
    char *user = "username";
    char *password = "password";
    char *database = "database_name";
 
    conn = mysql_init(NULL);
 
    // 连接数据库
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
 
    // 执行SQL查询
    if (mysql_query(conn, "SELECT * FROM table_name")) 
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
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
 
    // 释放结果集和关闭连接
    mysql_free_result(res);
    mysql_close(conn);
 
    return 0;
}
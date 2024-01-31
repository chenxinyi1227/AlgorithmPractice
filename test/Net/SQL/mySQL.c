#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
int main()
{
#if 0
  MYSQL Test;//定义MYSQL变量
  MYSQL_ROW res_row;//
  unsigned long *len = NULL;
  mysql_init(&Test);//chushihua
  if(mysql_real_connect(&Test,"localhost","root","1234","test", 0, NULL, 0) == NULL)
  {
    printf("连接失败\n");
    return -1;
  }
  printf("mysql 连接成功\n");
  char name[20]={0};
  printf("请输入用户名\n");
  scanf("%s",name);
  //char buf[300]="create table infor(user varchar(20),passwd int(4))";//1.创建表格
  //char buf[300]="insert into infor values('哒宰',999)";
  //插入数据
  //char buf[300]="select * from infor";//无法显示
  char buf[300]="select passwd from report where user = ";
  //查看相关用户的密码 
  sprintf(buf,"%s '%s'",buf, name);//命令写入buf
  
  printf("buf = %s\n",buf);
  if(mysql_real_query(&Test,buf,strlen(buf)) != 0)
 //执行命令行
  {
    perror("query");//失败
    return -1;
  }
  printf("语句执行成功\n");
  MYSQL_RES *res = NULL;//定义返回值
  res = mysql_store_result(&Test);//存放结果
  if(res == NULL)
    printf("函数执行失败\n");//表格内容位空
  else{
    printf("存在用户\n");
    unsigned int field = mysql_num_fields(res);//返回列
    unsigned int row = mysql_num_rows(res);//返回行
    printf("查询结果有%u行 %u列\n",row,field);//打印结果
    if(row == 0)
    {
      printf("没有该用户\n");
    }
    else{
      while(res_row=mysql_fetch_row(res))
      {
        len = mysql_fetch_lengths(res);//内容长度
        for(int i=0;i<field;i++)//按列查询
        {
          printf("用户在第 %u 列，密码 is %s,密码lenth is %lu\n",i,res_row[i],*(len+i));
        }
      }
    }
  }
#endif
    //连接数据库 连接句柄用于表示已建立的数据库连接
    MYSQL *mysql;//定义一个sql变量。连接句柄 存放连接句柄
    mysql = mysql_init(NULL);//初始化连接句柄，参数是句柄，返回值是句柄
    //mysql_init(MYSQL *mysql);
    if(mysql == NULL)
    {
      printf("mysql_init failed\n");
      return -1;
    }

    #if 0
    mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "utf8");    // 设置数据库  中文
    // MYSQL *ret = mysql_real_connect(mysql, "localhost", "root", "1234", "test", 3306, NULL, 0);
    #endif
    
    //连接登录
    const char *host = "localhost";
    const char *user = "root";
    const char *passwd = "1234";
    const char *db = "test";//数据库
    unsigned int port = 3306;

    //建立连接
    if(mysql_real_connect(mysql, host, user, passwd, db, port, NULL, 0) == NULL)
    {
      fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(mysql));
      return -1;
    }
    printf("mysql_real_connect success\n");

    //检测连接是存活
    if(mysql_ping(mysql) != 0)
    {
      fprintf(stderr, "mysql_ping failed: %s\n", mysql_error(mysql));
      mysql_close(mysql);
      return -1;
    }
    printf("mysql_ping success\n");

    //创建表格
    char buf[300] = {0};
 
    #if 0
    //primary key  主键 auto_increment 自动增长列
    sprintf(buf, "create table if not exists list1(id int primary key, name varchar(20), age int)");
    #else
    //插入数据
    sprintf(buf, "insert into list1 values(1015,'雪音1', 123)");
    mysql_real_query(mysql, buf, strlen(buf));
    //删除表
    // sprintf(buf, "drop table if exists list1");
    #endif

    //删除数据
    sprintf(buf, "delete from list1 where name = '雪音1' ");
    int ret1 = mysql_query(mysql, buf);
    if(ret1 != 0)
    {
      fprintf(stderr, "delete failed: %s\n", mysql_error(mysql));
      return -1;
    }

    //排序
    sprintf(buf, "select * from list1 order by age;");//倒序
    ret1 = mysql_query(mysql, buf);
    if(ret1 != 0)
    {
      fprintf(stderr, "order failed: %s\n", mysql_error(mysql));
      return -1;
    }
    printf("order success\n");
    
    //查看相关用户的信息
    sprintf(buf, "select * from list1;");
    ret1 = mysql_real_query(mysql, buf, strlen(buf));
    printf("buf:%s\n", buf);

    // int ret1 = mysql_query(mysql, buf);
    if(ret1 != 0)
    {
      fprintf(stderr, "insert failed: %s\n", mysql_error(mysql));
      // return -1;
    }
    
    //将读取的结果读取到客户端置于分配的MYSQL_RES结构中
    MYSQL_RES *res = mysql_store_result(mysql);
    if(res == NULL)
    {
      fprintf(stderr, "mysql_store_result failed: %s\n", mysql_error(mysql));
      exit(-1);
    }   
    printf("mysql_store_result success\n");

    #if 1
    /* 获取结果集中的列的数目 */
    //获取结果集的列数; 参数是结果集的句柄; 返回值是代表结果集的列数的整数;
    int field_num = mysql_num_fields(res);//返回列
    // 获取结果集的行数; 参数是结果集的句柄; 返回值是代表结果集的行数的整数;
    int row_num = mysql_num_rows(res);//返回行
    printf("查询结果有%d 行 %d列\n", row_num, field_num);

#if 0
    MYSQL_FIELD *field = mysql_fetch_field(res);        //用于存放结果集的一行数据;
    if(field == NULL)
    {
      fprintf(stderr, "mysql_fetch_field failed: %s\n", mysql_error(mysql));
    }
    
    unsigned long *len = mysql_fetch_lengths(res);//内容长度
    if(len == NULL)
    {
      fprintf(stderr, "mysql_fetch_lengths failed: %s\n", mysql_error(mysql));
    }
    printf("len:%ld\n", *len);
#endif
   
    //显示数据
    MYSQL_ROW row;        //用于存放结果集的一行数据;
    while(row = mysql_fetch_row(res))//获取结果集的一行数据，返回值是结果集的一行数据的指针;
    {
      for(int idx = 0; idx < field_num; idx++)
      {
        printf("%s\t", row[idx]);
        if(idx == field_num - 1)
        {
          printf("\n");
        }
      }
    }
    #endif

    #if 1
    //删除表
    sprintf(buf, "drop table if exists test;");
    ret1 = mysql_real_query(mysql, buf, strlen(buf));
    // int ret1 = mysql_query(mysql, buf);
    if(ret1 != 0)
    {
      fprintf(stderr, "insert failed: %s\n", mysql_error(mysql));
      return -1;
    }
    printf("删除表成功!\n");
    #endif
    //更改数据 update 表名 set 要修改的内容 where 条件
    sprintf(buf, "update list1 set age = 18 where name = '雪音'");
    ret1 = mysql_query(mysql, buf);
    if(ret1 != 0)
    {
      fprintf(stderr, "update failed: %s\n", mysql_error(mysql));
      return -1;
    }

   #if 0
    sprintf(buf, "alter table list1 add sex char;");
    ret1 = mysql_query(mysql, buf);
    if(ret1 != 0)
    {
      fprintf(stderr, "add column failed: %s\n", mysql_error(mysql));
      return -1;
    }
    printf("order success\n");

    #elif 0
    //删除一列
    sprintf(buf, "alter table list1 drop sex;");
    ret1 = mysql_query(mysql, buf);
    if(ret1 != 0)
    {
      fprintf(stderr, "order failed: %s\n", mysql_error(mysql));
      return -1;
    }
  #else
    //修改列的属性
    sprintf(buf, "alter table list1 modify id int(4);");
    ret1 = mysql_query(mysql, buf);
    if(ret1 != 0)
    {
      fprintf(stderr, "modify failed: %s\n", mysql_error(mysql));
      return -1;
    }
  #endif


    mysql_free_result(res);           //释放结果集;
    mysql_close(mysql);              //关闭连接
    printf("mysql_close success\n");
    /* 释放资源 */  
    mysql_library_end();             //释放资源; 返回值是0;

  return 0;
}
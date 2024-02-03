#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
int main()
{
  MYSQL Test;//定义MYSQL变量
  MYSQL_ROW res_row;//
  unsigned long *len = NULL;
  mysql_init(&Test);//chushihua
  if(mysql_real_connect(&Test,"localhost","root","1234","test",3306,NULL,0) == NULL)
  {
    printf("连接失败\n");
    return -1;
  }
  printf("mysql 连接成功\n");
  char name[20]={0};
  printf("请输入id\n");
  scanf("%s",name);
  //char buf[300]="create table infor(user varchar(20),passwd int(4))";//1.创建表格
  //char buf[300]="insert into infor values('哒宰',999)";
  //插入数据
  //char buf[300]="select * from infor";//无法显示
  char buf[300]="select age from list1 where id = ";
  //查看相关用户的密码 
  sprintf(buf,"%s '%s'",buf,name);//命令写入buf
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
  else
  {
    printf("存在用户\n");
    unsigned int field = mysql_num_fields(res);//返回列
    unsigned int row = mysql_num_rows(res);//返回行
    printf("查询结果有%u行 %u列\n",row,field);//打印结果
    if(row == 0)
    {
      printf("没有该用户\n");
    }
    else
    {
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
  return 0;
}
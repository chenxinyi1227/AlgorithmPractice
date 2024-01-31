#include <stdio.h>

/* 当前系统为大端存储模式时，其低地址处存储 00，而当前系统为小端存储模式时，其低地址处存储 01 */

//法1：指针法
int JudgeSystem(void) 
{
	int a = 1;
 
	// 如果是小端则返回 1，如果是大端则返回 0  char * 访问一个字节 指针变量解引时能访问多少个字节，
	//和指针±的步长为多大。
	return *(char *)&a;
}
//法2：联合体法
int is_byteorder(int* p)
{
	union un   //定义一个联合体类型
    {
		int i;
		char c;
	}u;

	u.i = 1;//修改i的值，c的值也会随之发生变化//// 如果是小端则返回 1，如果是大端则返回 
	return u.c;
}
int main()
{
	int n = 2;
	int ret = is_byteorder(&n);
	if (ret == 1)
	{
		printf("小端\n");
	}
	else
	{
		printf("大端\n");
	}
	return 0;
}

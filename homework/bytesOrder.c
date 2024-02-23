#include <stdio.h>

/* 当前系统为大端存储模式时，其低地址处存储 00，而当前系统为小端存储模式时，其低地址处存储 01 */
/* 我们知道指针类型决定了
指针变量解引时能访问多少个字节，和指针±的步长为多大。
这里明显就是和访问字节相关，char * 类型的指针能访问1个字节
也就说
 如果是小端 * str的值就是1，
 如果是小端 *str的值就是0， */
//法1：指针法
#if 0
int jugde(int a)
{
	#if 0
	char* str = (char *) & a;
	if (*str == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	#else
	return *(char*)&a;
	#endif
}
int main()
{
	int a = 0x1;
	int i = jugde(a);//返回1为小端，返回0为大端
	if (i)
	{
		printf("小端\n");
	}
	else
		printf("大端\n");

	return 0;
}

#else
//法2：联合体法
int jugde()
{
	union test
	{
		int a;
		char b;
	}u;
	u.a = 1;
	return u.b;
}
int main()
{
	if (jugde() == 1)
	{
		printf("小端\n");
	}
	else
		printf("大端\n");
	return 0;
}
#endif
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
void swap(char* pa, char* pb)
{
	assert(pa && pb);
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}
void reverse1(char* arr, int len)
{
	assert(arr);
	char* pa = arr;
	char* pb = arr + len - 1;
	while (pa < pb)
	{
		swap(pa, pb);
		++pa;
		--pb;
	}
}
void reverse2(char* arr)
{
	int n = -1;
	while (arr[++n])
	{
		int len = 0;
		while(arr[n] != ' ' && arr[n])
		{
			++n;
			++len;
		}
		reverse1(&arr[n - len], len);
	}
}
int main()
{
	int len = 0;
	char arr[101] = { 0 };
	gets(arr);
	len = strlen(arr);
	reverse1(arr, len);
	reverse2(arr);
	printf("%s\n", arr);
	system("pause");
	return 0;
}
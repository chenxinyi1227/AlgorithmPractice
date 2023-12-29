/* 输入一个英文句子，翻转句子中单词的顺序，要求单词内字符的顺序不变，
句子中单词以空格隔开，为简单起见，标点符号和普通字母一样处理。
例如:输入“l am a student.”则输出:“student. a am l\"”。
解题步骤：
（1） 翻转整个字符串。 ​​​​​​​即：I am a student.   ------>    .tneduts a ma I
（2） 逐个翻转单词。即： .tneduts a ma I  ------>    student. a am l
*/
 
#include <stdio.h>
#include<string.h>
 
int main(void)
{
	int i = 0, j, k, m, n, t;
	int len;
	char a[] = "l am from nanjing";//初始化数组a
 
	len = strlen(a);   //计算a的长度
	n = len;
 
	while(i<n)       //翻转整个字符串
	{
		m = a[i];
		a[i] = a[n - 1];
		a[n - 1] = m;
		i++;
		n--;
	}
 
	n = len;
	k = 0;
	
	for (j = 0; j < n; j++)
	{
		if ((a[j] == ' ') )   //判断单词
		{
			t = j;
			while (k < j)   //单词内部进行翻转
			{
				m = a[k];
				a[k] = a[j - 1];
				a[j - 1] = m;
				k++;
				j--;
			}
			k = t + 1;
			j = k;
		}

 		if (j == (n-1) )   //进行第一个单词的翻转
		{
			t = j;
			while (k < j)   //单词内部进行翻转
			{
				m = a[k];
				a[k] = a[j];
				a[j] = m;
				k++;
				j--;
			}
			k = t + 1;
			j = k;
		}
	}
 
printf("str3:%s\n", a);    //输出字符串
 
	return 0;
}
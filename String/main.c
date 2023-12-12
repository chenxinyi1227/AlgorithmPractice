#include "MyString.h"
#include <stdio.h>
#define BUFFER_SIZE 16

int main()
{
    char str1[BUFFER_SIZE] = "hello world";
    int len = MyStrlen(str1);
    printf("len:%d\n",len);
    char str2[BUFFER_SIZE] = "";
    MyStrcpy(str2,str1);
    printf("str2:%s\n",str2);
    MyStrcat(str2,str1);
    puts(str1);
    puts(str2);
    MyStrcmp(str1,str2);
    printf("MyStrcmp:%d\n", MyStrcmp(str1,str2));
    return 0;
}


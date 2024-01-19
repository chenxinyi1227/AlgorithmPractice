#include "myString.h"
#include <stdio.h>
#define BUFFER_SIZE 16

int main()
{

   // char *p = NULL;
    char str1[BUFFER_SIZE] = "";

    int len = myStrlen(str1);
    printf("len:%d\n", len);

    char str2[BUFFER_SIZE] = "";

    myStrcpy(str2,str1);
    printf("str2:%s\n",str2);

    myStrcat(str2,str1);
    printf("str1:%s\n", str1);
    printf("str1:%s\n", str2);

    myStrcmp(str1, str2);
    printf("myStrcmp:%d\n", myStrcmp(str1, str2));
    return 0;
}


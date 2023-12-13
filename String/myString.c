#include "myString.h"
#include <stdio.h>

//获取字符串长度
int myStrlen(const char *str)
{
    int count = 0;
    if (str == NULL)
    {
        return count;
    }
    while (*str != '\0')
	{
		str++;
        count++;
	}
    return count;
}
void  myStrcpy(char *dest, const char *src)
{
#if 0  
     int len = MyStrlen(src);
    // for(int index = 0; index < len; index++ )
    // {
    //     dest[index] = src[index];
    // }
    // dest[len] = '\0';
#endif
    while (*src != '\0')
    {
        // *dest=*src;
        // dest++;
        // src++;  
        *dest++ = *src++;          
    }
    *dest = '\0';  
}

void myStrcat(char *dest, const char *src)
{
    while(*dest != '\0')
    {
        dest++;
    }
    myStrcpy(dest,src);
}

int myStrcmp(const char *s1, const char *s2)
{
    while(*s1 != '\0' && *s2 != '\0')
    {
        if(*s1 != *s2)
        {
            return *s1 - *s2;
        }
        s1++;
        s2++;  
    }
    return *s1 - *s2;
}

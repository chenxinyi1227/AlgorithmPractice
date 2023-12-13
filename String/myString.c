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
char  *myStrcpy(char *dest, const char *src)
{
#if 0  
     int len = MyStrlen(src);
    // for(int index = 0; index < len; index++ )
    // {
    //     dest[index] = src[index];
    // }
    // dest[len] = '\0';
#endif
    if (dest == NULL || src == NULL)
    {
        return 0;
    }

    while (*src != '\0')
    {
        // *dest = *src;
        // dest++;
        // src++;  
        *dest++ = *src++;          
    }
    *dest = '\0';  
    return dest;
}

char *myStrcat(char *dest, const char *src)
{
    if (dest == NULL || src == NULL)
    {
        return 0;
    }
    
    while(*dest != '\0')
    {
        dest++;
    }
    myStrcpy(dest,src);
    return dest;
}

int myStrcmp(const char *s1, const char *s2)
{
     if (s1 == NULL || s2 == NULL)
    {
        return 0;
    }

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

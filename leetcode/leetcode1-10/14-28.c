#include <stdio.h>
#include <string.h>
/* 找出字符串中第一个匹配项的下标
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。
如果 needle 不是 haystack 的一部分，则返回  -1 。
 */
#if 0
#include <stdio.h>

char* my_strstr(const char* haystack, const char* needle)
{
    if (*needle == '\0') 
    {
        return (char*)haystack; // 如果子字符串为空，则返回原始字符串
    }
    while (*haystack != '\0') 
    {
        const char* h = haystack;
        const char* n = needle;

        while (*n != '\0' && *h == *n) 
        {
            h++;
            n++;
        }

        if (*n == '\0') 
        {
            return (char*)haystack; // 子字符串匹配成功，返回匹配位置
        }
        haystack++;
    }
    return NULL; // 没有找到子字符串，返回NULL
}

int main() {
    char str[] = "Hello, world!";
    char sub_str[] = "world";

    char* result = my_strstr(str, sub_str);

    if (result == NULL) {
        printf("'%s' not found in '%s'.\n", sub_str, str);
    } else {
        printf("'%s' found at position %ld in '%s'.\n", sub_str, result - str, str);
    }

    return 0;
}
#elif 1

int strStr(char* haystack, char* needle) 
{
    if(haystack == NULL || needle == NULL)
    {
        return 0;
    }
    int idx = 0;
    while(haystack[idx] != '\0')
    { 
        int idx1 = idx;
        int idx2 = 0;
        while(needle[idx2] != '\0' && haystack[idx1] == needle[idx2])
        {
            idx1++;
            idx2++;
        }

        if(needle[idx2] == '\0')
        {
            return idx; 
        }
        idx++;
    }
    return -1;
}
int main() 
{
    char str[] = "sadbutsad";
    char sub_str[] = "sad";

    int ret = strStr(str, sub_str) ;
    printf("ret = %d\n", ret);

    return 0;
}
#else 

class Solution {
public:
    int strStr(string haystack, string needle)
    {
         int len = strlen(needle);
    int index = 0;
    int pos = 0;
    strStr()
    while(haystack != NULL)
    {
        if(*haystack == *needle)
        {
            pos
        }
    }
    }
};
#endif
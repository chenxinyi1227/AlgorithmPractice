// #include <iostream>
// using namespace std;
// #include <vector>
// #include <string>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/* 有效的字母异位词 
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。*/
/*  输入：s = "anagram", t = "nagaram"
    输出：true
    输出：s = "rat", t = "car"
    输出：false  
    s 和 t 仅包含小写字母
*/
bool isAnagram(char* s, char* t) 
{
    char *pStrs = s;
    char *pStrt = t;
    int buffer1[26];
    memset(buffer1, 0, sizeof(int) * 26);
    int buffer2[26];
    memset(buffer2, 0, sizeof(int) * 26);
    int idx1 = 0;
    int idx2 = 0;
    while(*pStrs != '\0')
    {
        int index = *pStrs - 'a';
        buffer1[index]++;
        pStrs++;
    }

    while(*pStrt != '\0')
    {
        int index = *pStrt - 'a';
        buffer2[index]++;
        pStrt++;
    }

    int idx = 0;
    while(idx < 26)
    {
        if(buffer1[idx] == buffer2[idx])
        {
           idx++;
        }
        else
        {
            return false;
        }
    }
    return true;
}

int main()
{
    char *s = "rat";
    char *t  ="car";
    int val = isAnagram(s, t);

    if(val)
    {
        printf("true!\n");
    }
    else
    {
        printf("false!\n");
    }
}
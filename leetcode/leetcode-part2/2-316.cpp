#include <iostream>
using namespace std;
#include <set>
#include <stdio.h>

/* 去除重复字母 与1081x相同*/
/* 给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。
需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
示例 1：
输入：s = "bcabc"
输出："abc"
示例 2：

输入：s = "cbacdcbc"
输出："acdb" */
#if 1
char* removeDuplicateLetters(char* s) 
{
    int start = 0;
    
}
#else

string removeDuplicateLetters(string s) 
    {
        
    }

#endif
int main()
{   
    string s = "bcabc";
    const char *str = s.c_str();
    set<char> myset;
    while(*str != '\0')
    {
        myset.insert(*str);
        str++;
    }
    int cnt = myset.size();
    printf("ret: %d\n", cnt);
     printf("%d\n", myset.begin());
    return 0;
}
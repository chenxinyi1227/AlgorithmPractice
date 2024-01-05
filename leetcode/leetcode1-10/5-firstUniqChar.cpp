#include <iostream>
using namespace std;
#include <string.h>
 #define BUFFER_SIZE 10
 /* 字符串中的第一个唯一字符
 给定一个字符串 s ，找到 它的第一个不重复的字符，并返回它的索引 。如果不存在，则返回 -1  */
 /* 1、扫描一遍字符串，记录每个字符出现的次数O(n)
    2、在扫描一遍字符串，每扫到一个字符，我就查一下出现的次数
  */

 class Solution {
public:
    int firstUniqChar(string s) {
        const char *ptr = s.c_str();
        const char *bakPtr = ptr;

        int bufferrequency[26];
        memset(bufferrequency, 0, sizeof(int) * 26);

        int index = 0;
        while(*ptr != '\0')
        {
            index = *ptr - 97;//数组的对应的索引
            bufferrequency[index]++;//出现的次数增加
            ptr++;
        }
        ptr = bakPtr;//指针回到开头的位置
        int pos = 0;
        while(*ptr != '\0')
        {
            if(bufferrequency[*ptr - 97] == 1)
            {
                return pos;
            }
            pos++;
            ptr++;
        }
        return -1;
    }
};

int main()
{
    char *s = "zazzang";
    // int index = firstUniqChar(s);
    // printf("index:%d\n", index);
    // printf("s[%d]:%c\n", index, s[index]);
    return 0;
}
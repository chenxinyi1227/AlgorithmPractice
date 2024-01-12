#include <iostream>
using namespace std;
#include <string.h>
/* 重复的子字符串
abab  ab 
输出：true */
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        const char *ptr = s.c_str();
        /* 字符串的长度 */
        int length = s.size();

        int flag = 0;

         int cmp = 0;;
        /* window是窗口的长度 */
        for(int window = 1; window <= length >> 1; window++)
        {
            flag = 1;
            /* 如果窗口不满足被整除，那么换一个窗口 */
            if(length % window != 0)
            {
                continue;
            }

            /* +1 的目的是：放字符串的结束符 */
            char buffer[window + 1];
            memset(buffer, 0, sizeof(buffer));

            /* 填充窗口的字符串 */
            for(int idx = 0; idx < window; idx++)
            {
                buffer[idx] = s[idx];
            }
            /* 按照窗口的大小去比较 */
            for(int idx = window; idx < length; idx += window)
            {
                cmp = strncmp(buffer, ptr + idx, window);
                if(cmp == 0)
                {
                    /* 相等 */
                    continue;
                }
                else
                {
                    flag = 0;
                    /* 不等 */
                    break;
                }
            }
            if(flag == 1)
            {
                return true;
            }
        }
        return false;
    }
};
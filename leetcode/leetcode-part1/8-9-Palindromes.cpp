//判断回文数  ABCDCBA 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <iostream>
using namespace std;
#include <stack>
#include <string>
#include <string.h>
#include <vector>

#if 0
void delete(char *str, int len)
{
    int i, j = 0;  
    char ch;
    for (i = 0; str[i] != '\0'; i++) 
    {  
        ch = str[i];  
        if (ch != ' ') 
        {  
            str[j] = ch;  
            j++;
        }  
    }  
    str[j] = '\0';  
}

bool Palindromes(char *str, int len)
{
    for(int i = 0; i < len; i++)
    {
        if(str[i] >= 'a')
        str[i] = str[i] - ' ';
    }
   
    int left, right;    
    left = 0;
    right = len - 1;        

    while(left < right)
    {
        if(left < right && (str[left] == ' '))
        {
            left++;
        }
        if(left < right && str[left] >= '0' && str[left] <= '9')
        {
            left++;
        }
        if(left < right && (str[right] == ' '))
        {
            right--;
        }
        if(left < right &&  str[right] >= '0' && str[right] <= '9')
        {
            right--;
        }

        if(str[left] != str[right])
        {
            return false;
        }
        left++;
        right--;
     }
    return true;
}
#else
class Solution {
public:
    bool isPalindrome(int x) 
    {
        vector<int> myvec;
        if (x < 0)
        {
            return false;
        }

        int tmp = x;
        while (tmp)
        {
            myvec.push_back(tmp % 10);
            tmp /= 10;
        }

        int begin = 0;
        int end = myvec.size() - 1;

        while (begin < end)
        {
            if (myvec[begin++] != myvec[end--])
            {
                return false;
            }
        }
        return true;
    }
};
#endif
int main()
{
    char str[] = "aB3c1 ba";
    int len = strlen(str);
   #if 0 
    if(isPalindrome(str, len))
    {
        printf("是回文数!\n");
    }
    else
    {
        printf("不是回文数!\n");
    }
    #endif
    return 0;
}
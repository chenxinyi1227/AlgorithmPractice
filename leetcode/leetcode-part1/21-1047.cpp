#include <iostream>
using namespace std;
#include <stack>
#include <string>
/* 删除字符串中的所有相邻重复项
输入：abbaca
输出：ca */
class Solution {
public:
    string removeDuplicates(string s) 
    {
        const char *ptr = s.c_str();
        stack<char> mystack;
        mystack.push(*ptr);
        ptr++;
        while(*ptr != '\0')
        {
            if(mystack.empty())
            {
                mystack.push(*ptr);
            }
            else
            {
                if(*ptr == mystack.top())
                {
                    mystack.pop();
                }
                else
                {
                    mystack.push(*ptr);
                }
            }
            ptr++;
        }
        /* 存放返回的字符串 */
        string mystring;
        mystring = "";
        while(!mystack.empty())
        {
            mystring += mystack.top();
            mystring.push_back(mystack.top());
            mystack.pop();
        }
        int start = 0;
        int end = mystring.size() - 1;
        while(start < end)
        {
            swap(mystring[start++], mystring[end--]);
        }
    return mystring;
    }
};
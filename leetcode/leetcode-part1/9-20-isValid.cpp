#include <iostream>
using namespace std;
#include <stack>
/* 有效的括号
左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。 */

/* 1、只要碰到左括号就压栈，指针后移，
2、碰到右括号就查看栈顶元素元素，是否与我是相同类型，如果不是，返回false 如果是：栈顶元素出栈，指针后移
3、遍历结束，说明有左边括号没匹配完成，返回false,如果栈为空，说明匹配完成， 返回true */
class Solution {
public:
    bool isValid(string s) {
        const char * ptr = s.c_str();
        char topVal = '0';
        stack<char> mystack;
        while(*ptr != '\0')
        {
            if(*ptr == '(' || *ptr == '[' || *ptr == '{')
            {
                mystack.push(*ptr);
            }
            else
            {
                /* 遍历到右括号，如果栈为空，直接返回 */
                if(mystack.empty())
                {
                    return false;
                }
                /* 栈顶元素 */
                topVal = mystack.top();
                mystack.pop();
                if(*ptr == ')' && topVal != '(')
                {
                    return false;
                }
                else if(*ptr == ']' && topVal != '[')
                {
                    return false;
                }
                else if(*ptr == '}' && topVal != '{')
                 {
                    return false;
                }
            }
            /* 指针后移 */
            ptr++;
        }///字符串遍历结束
        if(mystack.empty())
        {
            return true;
        }
            return false;
    }
};
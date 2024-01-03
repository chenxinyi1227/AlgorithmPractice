#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* 有效的括号 用栈写*/
bool isValid(char* s) {
    int len = strlen(s);
    if(len % 2 != 0)
    {
        return false;
    }
    else
    {
        for(int i = 0;i <= len - 1; i++)
        {
         if((s[i] == '(' && s[i+1] == ')') || (s[i] == '[' && s[i+1] == ']') || (s[i] == '{' &&s[i+1] == '}'))
           return true;
           else
           return false;
        }
     return 0;
    }
}

int main()
{
    
}
//判断回文数  ABCDCBA 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

int main()
{
    char str[] = "aB3c1 ba";
    int len = strlen(str);
    
    if(Palindromes(str, len))
    {
        printf("是回文数!\n");
    }
    else
    {
        printf("不是回文数!\n");
    }

    return 0;
}
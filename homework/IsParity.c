#include <stdio.h>
#include <stdbool.h>
/* 判断奇偶数 */
bool IsJshu(int num)
{
   if(num % 2 == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
int main()
{
    int num;
    int n = IsJshu(num);
    if(n)
    {
        printf("%d为奇数\n", num);
    }
    else
    {
        printf("%d为偶数\n", num);
    }
}
#include <stdio.h>
int strToInt(char *string)
{
    int number = 0;
    while(*string != '\0')
    {
        number = number * 10 + *string - '0';
        string++;
    }
    return number;
}
int main()
{
    char *str = "12";
    int number = strToInt(str);
    printf("number:%d\n", number);
}
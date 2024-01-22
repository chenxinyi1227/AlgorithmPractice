
#include <stdio.h>
double strToDouble(const char *str) 
{
    double num = 0.0;
    int sign = 1;
    int dot = 0;
    int i = 0;
    if (str[0] == '-') 
    {
        sign = -1;
        i++;
    }
    for (; str[i] != '\0'; i++) 
    {
        if (str[i] == '.') 
        {
            dot = 1;
            continue;
        }
        int digit = str[i] - '0';
        num = num * 10 + digit;
        if(dot)
        {
            dot *= 10;
        }
    }
    num = num / dot * sign;
    return num;
}

int main()
{
    char *str = "12.767";
    double number = strToDouble(str);
    printf("number:%f\n", number);
}

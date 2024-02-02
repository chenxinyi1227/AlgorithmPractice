#include <stdio.h>

int main()
{
    char buffer[10][10] = {"cvfd"};
    printf("buffer:%s\n", buffer[0]);

    char *str = buffer[0];
    printf("str %s\n", str);
    return 0;
}
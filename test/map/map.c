#include <stdio.h>
#include "map.h"
#include <nc

void InitMap(char*(*map)[MAPSIZE])
{
    // for(int i = 0; i < 5; i++)
    // {
    //     for(int j = 0; j < MAPSIZE; j++)
    //     {
    //         map[i][j] = "\033[1;47m                \033[0;m";
    //     }
    // }      
    map[0][0] ="\033[1;47m 请输入要进行的功能:           \033[0m";
    map[1][0] = "\033[1;47m a.登录                        \033[0m";
    map[2][0] = "\033[1;47m b.注册                        \033[0m";
    map[3][0] = "\033[1;47m 其他.退出聊天室               \033[0m";
    map[4][0] = "\033[1;47m 等待                          \033[0m";

}

void PrintMap(char*(*map)[MAPSIZE])
{
    printf("     ");
    for(int i = 0; i < 1; i++)
    {
        printf("***请选择功能*** ");
    }
    printf("\n");
    for(int i = 0 ;i < 5; i++)//y
    {
        printf("%4d ",i + 1);
        for(int j = 0; j < MAPSIZE; j++)
        {
            printf("%4s" ,map[i][j]);
        }
        printf("\n");
    }
printf("\n");
}

#include <stdio.h>
#include <string.h>
#include "map.h"

#define MAPSIZE 1

int main() 
{
    //初始化场景
    char *map[5][MAPSIZE] = {0};
    InitMap(map);
   
    PrintMap(map);
     printf("\033[1;45m \033map:%s\033[0m\n",map[2][0]);

    return 0;
}

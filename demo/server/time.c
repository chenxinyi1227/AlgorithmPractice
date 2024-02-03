#include <stdio.h>
#include <time.h>

int main()
{
    time_t current_time;
    time(&current_time);//更新于文件的元数据发生变化时
    char *str = ctime(&current_time);
    printf("curtimr:%s\n", str);
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* 宏函数在预处理阶段被替换 */
#define BUFFER_SIZE 10

/* 宏函数->无法调试 */
//#define

/* 数组做函数参数会自动弱化成指针 */
int printArray(int *array, int length)
{
    for(int idx = 0; idx < length; idx++)
    {
        printf("%d\t", array[idx]);
    }
}
/* 顺序查找 */
int findAppointValPos(int *array, int length, int val)
{
    if(array == NULL)
    {
        return 0;
    }
    for(int idx = 0; idx < length; idx++)
    {
        if(array[idx] == val)
        {
            return idx;
        }
    }
    return -1; //没找到
}

int main()
{
    /* 随机数种子 */
    // srand(time(NULL));
    
    int buffer[BUFFER_SIZE];
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        buffer[idx] = rand() % 100 + 1;//生成1-100的随机数
    }
    int length = sizeof(buffer) / sizeof(buffer[0]);
    printArray(buffer, length);
    int val = 0;
    printf("\n请输入要查询的元素\n");
    scanf("%d", &val);
    int index = findAppointValPos(buffer, length, val);
    printf("index:%d\n", index);
}
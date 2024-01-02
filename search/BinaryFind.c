#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* 宏函数在预处理阶段被替换 */
#define BUFFER_SIZE 10


/* 数组做函数参数会自动弱化成指针 */
int printArray(int *array, int length)
{
    for(int idx = 0; idx < length; idx++)
    {
        printf("%d\t", array[idx]);
    }
}

void BubbleSort(int *arr,int len)
{
    if(arr == NULL)
    {
        return;
    }
    //冒泡冒n-1次
    for(int i = 0;i < len - 1; i++)
    {
        int flag = 0;
        for(int j = 0; j < len - 1 - i; j++)//将剩下的（length-i）个记录进行比较
        {
            if(arr[j] > arr[j+1])
            {
                flag = 1;
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        //序列已经有序
        if(flag==0)
        {
            break;
        }
    }
}
/* 二分查找:已经排好序的 */
int BinaryFind(int *array, int length, int val)
{
    if(array == NULL)
    {
        return 0;
    }
    int start = 0;
    int end = length;
 
    while(start <= end)
    {
        int mid = start + (end - start) / 2;
        if(array[mid] == val)
        {
            return mid;
        }
        if(array[mid] > val)//往左找,更新end
        {
            end = mid - 1;
        }
        if(array[mid] < val)//往右找,更新start
        {
            start = mid + 1;
        }  
    }    
    return -1;
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
    BubbleSort(buffer, length);
    printArray(buffer, length);
    int val = 0;
    printf("\n请输入要查询的元素\n");
    scanf("%d", &val);
    int index = BinaryFind(buffer, length, val);
    printf("index:%d\n", index);
}
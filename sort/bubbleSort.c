#include <stdio.h>
#define BUFFER_SIZE 5
/* 冒泡排序：将最大值排到最后 */

/* 交换两个整数 */
void swap(int *val1, int *val2)
{
    int temp = *val1;
    *val1 = *val2;
    *val2  = temp;
}

/* 时间复杂度：O(n^2) */
void bubbleSort01(int *array, int length)
{
    for(int end = length; end > 0; end--)
    {
        for(int begin = 1; begin < end; begin++)
        {
            /* 后面的数 比 前面的小 就交换 */
            if(array[begin] < array[begin - 1])
            {
                swap(&array[begin], &array[begin - 1]);
            }
        }
    }
}

/* 优化1:当剩余数列已经有序时，则不需要在对后面的循环进行判断 */
void bubbleSort02(int *array, int length)
{
    int sorted = 1; //已经排好序
    for(int end = length; end > 0; end--)
    {
        for(int begin = 1; begin < end; begin++)
        {
            /* 后面的数 比 前面的小 就交换 */
            if(array[begin] < array[begin - 1])
            {
                sorted = 0;//没有排好序：只要有一次数据交换，则sorted为0
                swap(&array[begin], &array[begin - 1]);
            }
        }
        //sorted为1则退出循环
        //表明在剩余的序列中未进行元素位置的交换
        if(sorted)
        {
            break;
        }
    } 
}

/* 优化2*/
void bubbleSort03(int *array, int length)
{
    int sortedIndex = 0;
    for(int end = length; end > 0; end--)
    {
        /* 已经排好序的索引 */
        sortedIndex = 1;
        for(int begin = 1; begin < end; begin++)
        {
            /* 后面的数 比 前面的小 就交换 */
            if(array[begin] < array[begin - 1])
            {
                swap(&array[begin], &array[begin - 1]);
                /* 更新排好的索引 */
                sortedIndex = begin;
            }
        }
        /* 更新 */
        end = sortedIndex;
    } 
}

/* 数组做函数参数会自动弱化成指针 */
int printArray(int *array, int length)
{
    for(int idx = 0; idx < length; idx++)
    {
        printf("array[%d] = %d\n", idx, array[idx]);
    }
}

int main()
{
    int array[BUFFER_SIZE] = {11, 34, 21, 78, 24};
    int length = sizeof(array) / sizeof(array[0]);
    // bubbleSort01(array, length);
    // bubbleSort02(array, length);
    bubbleSort03(array, length);
    printArray(array, length);
}
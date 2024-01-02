#include <stdio.h>
#define BUFFER_SIZE 6

/* 交换两个整数 */
void swap(int *val1, int *val2)
{
    int temp = *val1;
    *val1 = *val2;
    *val2  = temp;
}

void printArray(int *array, int length)
{
    for(int idx = 0; idx < length; idx++)
    {
        printf("array[%d] = %d\n", idx, array[idx]);
    }
}
#if 1
/* 选择排序O(n^2):相较于冒泡排序，减少了排序次数
对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。 */
int selectSort(int *array, int length)
{
    int ret = 0;
    int minValue = 0;
    int minIndex = 0;
    for(int pos = 0; pos < length; pos++)
    {
        int min = array[pos];//定义最小值: 最小值在数组里，否则找不到
        for(int begin = pos + 1; begin < length; begin++)
        {
            /* 遍历到比最小值还小的值，就更新元素 */
            if(minValue > array[begin])
            {
                minValue = array[begin];
                minIndex = begin;//更新最小值下标
            }
        }
        if(array[pos] > minValue)
        {
            int temp = array[pos];
            array[pos] = minValue;
            array[minIndex] = temp;
        }
    }
    return 0;
}
#else
void selectSort(int *nums, int numsSize)
{
    int flag = 1;
    for(int idx = 0; idx <  numsSize - 1; idx++)
    {
        int min = idx;
        for(int jdx= idx + 1; jdx < numsSize; jdx++)
        {
            if(nums[jdx] < nums[min])
            {
                min = jdx;
            }
        }
        if(idx != min)//2
        {
            flag = 0;
            int temp = nums[idx];
            nums[idx] = nums[min];
            nums[min] = temp;
        }
    }
    if(flag)//flag = 1;idx = min 没有进行到2
    {
        printf("数据已经有序\n");
    }
}
#endif

int main()
{
    int nums[BUFFER_SIZE] = {-1, 5, 1, 8, 5};
    int size = sizeof(nums)/sizeof(nums[0]);
    selectSort(nums, size);
    printArray(nums, size);
    return 0;
}
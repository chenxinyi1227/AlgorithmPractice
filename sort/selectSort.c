#include <stdio.h>
#define BUFFER_SIZE 6
/* 选择排序：对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。 */
void selectSort(int *nums, int numsSize)
{
    int flag = 0;
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
            flag = 1;
            int temp = nums[idx];
            nums[idx] = nums[min];
            nums[min] = temp;
        }
    }
    if(!flag)//flag = 0;idx = min 没有进行到2
    {
        printf("数据已经有序\n");
    }
}


int main()
{
    int nums[BUFFER_SIZE] = {-1, 5, 1, 8, 5};
    int size = sizeof(nums)/sizeof(nums[0]);
    selectSort(nums, size);
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        printf("%d ", nums[idx]);
    }
    return 0;
}
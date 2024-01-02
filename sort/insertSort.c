#include <stdio.h>
#define BUFFER_SIZE 6
/* 插入，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
因而在从后向前扫描过程中，需要反复把已排序元素逐步向后 */
/* 交换两个整数 */
void swap(int *val1, int *val2)
{
    int temp = *val1;
    *val1 = *val2;
    *val2  = temp;
}
void insertSort(int *nums, int numsSize)
{
    for(int idx = 1; idx < numsSize; idx++)
    {
        int temp = nums[idx];//复制
        int jdx = idx;
        for(; jdx > 0; jdx--)
        {
            if(nums[jdx - 1] > temp)
            {
                nums[jdx] = nums[jdx - 1];//大的数往后移
            }
            else
            {
                nums[jdx] = temp;
                break;
            }
        }
    }
}


int main()
{
    int nums[BUFFER_SIZE] = {-1, 5, 3, 8, 1};
    int size = sizeof(nums)/sizeof(nums[0]);
    insertSort(nums, size);
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        printf("%d ", nums[idx]);
    }
    printf("\n");
    return 0;
}
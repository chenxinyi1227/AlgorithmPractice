#include <stdio.h>
#define BUFFER_SIZE 6
/* 插入，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
因而在从后向前扫描过程中，需要反复把已排序元素逐步向后 */

void printArray(int *nums, int length)
{
     for(int idx = 0; idx < length; idx++)
    {
        printf("%d ", nums[idx]);
    }
}

void insertSort(int *nums, int numsSize)
{
    if(nums == NULL)
    {
        return;
    }
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
            else// nums[jdx - 1] <= temp jdx== 0
            {
                nums[jdx] = temp;
                break;//找到比temp小的值中的最大值的位置插入就跳出，不继续循环
            }
        } 
    }
}

void insertion_sort(int arr[], int len)
{
    int i, j, temp;
    for (i = 1;i < len; i++)
    {
        temp = arr[i];
        for (j = i; j > 0 && arr[j-1] > temp; j--)
        {
            arr[j] = arr[j-1];
        }
        arr[j] = temp;
    }
}

int main()
{
    int nums[] = {0, 6, 5, 8, 1};
    int length = sizeof(nums)/sizeof(nums[0]);
    insertSort(nums, length);
    printArray(nums, length);
    printf("\n");
    return 0;
}
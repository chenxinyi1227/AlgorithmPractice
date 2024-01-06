#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 4
/* 丢失的数字
给定一个包含 [0, n] 中 n 个数的数组 nums ，找出 [0, n] 这个范围内没有出现在数组中的那个数。 */
/* 0《= nums[i] <= n
nums中的所有数字都独一无二 */

int cmp(const void *a, const void *b) 
{
    return *(int *)a - *(int *)b;
}

int missingNumber(int* nums, int numsSize) 
{
    // bubbleSort(nums, numsSize);
    qsort(nums, numsSize, sizeof(int), cmp);

    int newSize = numsSize + 1;
#if 0
    int newSize = numsSize + 1;
    int *array = (int *)malloc(sizeof(int) * newSize);
    for(int idx = 0; idx < newSize; idx++)
    {
        array[idx] = idx;
    }
    
    int *ptr1= array;
    int *ptr2= nums;
    while(ptr1 != NULL && ptr2 != NULL)
    {
        if(*ptr1 == *ptr2)
        {
            ptr1++;
            ptr2++;    
        }
        else
        {
            break;
        }
    }
    ret = *ptr1;
    free(array);
#endif
    for(int idx = 0; idx < newSize; idx++)
    {
        if(nums[idx] != idx)
        {
            return idx;
        }
    }
    return newSize;
}


int main()
{
    int nums[BUFFER_SIZE] = {2, 3, 1, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int ret = missingNumber(nums, numsSize);
    printf("ret:%d\n", ret);

}
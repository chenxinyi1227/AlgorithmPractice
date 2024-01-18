#include <stdio.h>
/* 搜索插入位置 */
int searchInsert(int* nums, int numsSize, int target) 
{
     int left = 0;
    int right = numsSize -1;
    int a=numsSize;
    while(left <= right)
    {
        int mid = left+(right-left)/2;
        if (target <= nums[mid])
        {
            a = mid;
            right = mid - 1;
        } 
        else 
        {
            left = mid + 1;
        }
    }
    return a;
}
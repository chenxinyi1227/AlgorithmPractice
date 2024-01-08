#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <set>

#define BUFFER_SIZE 4
/* 丢失的数字
给定一个包含 [0, n] 中 n 个数的数组 nums ，找出 [0, n] 这个范围内没有出现在数组中的那个数。 */
/* 0《= nums[i] <= n
nums中的所有数字都独一无二 */
#if 0
int cmp(const void *a, const void *b) 
{
    return *(int *)a - *(int *)b;
}

int missingNumber(int* nums, int numsSize) 
{
    // bubbleSort(nums, numsSize);
    qsort(nums, numsSize, sizeof(int), cmp);

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
    for(int idx = 0; idx < numsSize; idx++)
    {
        if(nums[idx] != idx)
        {
            return idx;
        }
    }
    return numsSize;
}
#else
class Solution {
public:
    int missingNumber(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end()); //排序
        int size = nums.size();
        for (int idx = 0; idx < size; idx++) 
        {
            if (nums[idx] != idx) //第一种情况
            return idx;
        }
        return size;  //第二种情况
    }
};
#endif

/* 集合 */
class Solution {
public:
    int missingNumber(vector<int>& nums) 
    {
        set<int> myset;
        for(int idx = 0;idx < nums.size(); idx++)
        {
            myset.insert(nums.at(idx));
        }

        int idx = 0;
        for(idx; idx < nums.size(); idx++)
        {
            if(myset.count(idx) == 0)
            {
                break;
            }
        }
        return idx;
    }
};

int main()
{
    int nums[BUFFER_SIZE] = {2, 3, 1, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    // int ret = missingNumber(nums, numsSize);
    // printf("ret:%d\n", ret);

}
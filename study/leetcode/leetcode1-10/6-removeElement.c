/*原地算法  随机 数组[2,3,1,7,5,2]  删掉2  [3,1,7,5] 不开辟新空间
27. 移除元素
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 6

int removeElement(int *nums, int numsSize, int val)
{
    if(numsSize == 0)
    {
        return 0;
    }
    int pos = 0;
    for(int index = 0; index < numsSize; index++)
    {
        if(nums[index] != val)
        {
            nums[pos] = nums[index];
            // printf("%d ",nums[pos]);
            pos++;
            
        }
    }
    // printf("\n");
    return pos;
}

int main()
{
    // int nums[] = { 2,3,1,7,5,2 };
    int nums[BUFFER_SIZE] = {0}; 

    srand(time(NULL));

    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        nums[idx] = rand() % 10 + 1; 
        printf("%d ", nums[idx]);
    }

    int val = 0;
    printf("\n请输入要删除的数字:");
    scanf("%d", &val);

    int size = sizeof(nums) / sizeof(nums[0]);

    int len = removeElement(nums, size, val);

    for(int i = 0; i < len; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\nlen = %d\n", len);

    return 0;
}
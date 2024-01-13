/*数组   去重：非连续递增 1 2 2 5 5 6 8     得到1 2 5 6 8*/
#include <stdio.h>

//删除有序数组中的重复项
int removeDuplicates(int *nums, int numsSize)
{
    int pos = 1;
    for(int idx = 1; idx < numsSize; idx++)
    {
      if(nums[idx] != nums[idx-1])                                                                                      
      {
        nums[pos] = nums[idx];
        pos++;
      }
    }
    return pos;
}    

int main()
{
    int nums[] = {1,1,2,3,7,9,9,11};
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    printf("原始数组:\n");

    for ( int idx = 0; idx < numsSize; idx++)
    {
      printf("%d ", nums[idx]);
    }
    printf("\n数组长度:%d\n",numsSize);

    int len = removeDuplicates(nums, numsSize);
    printf("删除重复项后:\n");
    for(int idx = 0; idx < len; idx++)
    {
      printf("%d ", nums[idx]);
    }
    printf("\n数组长度:%d\n", len);
    return 0;
}
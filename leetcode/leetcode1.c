//[ 2 7 1 3 15 ]  和为target的值的下标 target = 22  返回形式：[1 12]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE 5
int twoSum(int *nums, int numsSize,int target)
{
    for(int i = 0;i < numsSize; i++)
    {
        for(int j = i + 1;j <numsSize; j++)
        {
            if(nums[i] + nums[j] == target)
            {
               printf("[%d,%d]\n",i,j);
            } 
        }
    }
    //return NULL;
    //printf("not found!\n");
}

int main()
{
    int nums[SIZE] = {0};
    //memset(nums,0,sizeof(int) * SIZE);
    srand(time(NULL));
    for(int idx =0;idx < SIZE;idx++)
    {
        int Val = rand()%10 + 1;
        nums[idx] = Val; 
    }
    for(int idx = 0;idx < SIZE; idx++)
    {
       printf("%d ",nums[idx]);
    }

    int numsSize = sizeof(nums)/sizeof(nums[0]);

    int target;
    printf("\n请输入target:");
    scanf("%d",&target);

    twoSum(nums,numsSize,target);
}
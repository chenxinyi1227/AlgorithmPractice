//快速排序
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 10

void FastSort(int *a,int start,int end)
{
    //终止条件
    if(start >= end)
    {
        return;
    }
    
    int left = start;
    int right = end;
    int temp = a[left];

    while(left < right)
    {
        while(left < right && a[right] > temp)
        {
            right--;
        }
        if(left < right)
        {
            a[left] = a[right];
            left++;
        }
        while(left < right && a[left] < temp)
        {
            left++;
        }
        if(left < right)
        {
            a[right] = a[left];
            right--;

        }
    }
    a[left] = temp;
    //递归排序
    FastSort(a, start, left-1);
    FastSort(a, right+1, end); 
}

int main()
{
    int nums[BUFFER_SIZE] = {0};
    srand(time(NULL));
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        int Val = rand()%10 + 1;
        nums[idx] = Val; 
    }
    printf("排序前:");
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
       printf("%d ", nums[idx]);
    }
    
    FastSort(nums, 0, BUFFER_SIZE-1);

    printf("\n排序后:");
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
       printf("%d ", nums[idx]);
    }
     printf("\n");
}
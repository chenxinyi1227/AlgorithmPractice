//快速排序
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void Swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;

}
#define BUFFER_SIZE 10
//快速排序
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

//冒泡排序
void BubbleSort(int *nums, int len)
{
    for(int i = 0; i < len - 1; i++)
    {
        int flag = 0;
        for(int j= 0;j < len - 1 - i; j++)
        {
            if(nums[j] > nums[j + 1])
            {
                int flag = 1;
                int temp = nums[j];
                nums [j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
        if(flag == 0)
        {
            return;
        }
    }
}

//选择排序
void InsertSort(int *nums, int len)
{
    for(int i = 0; i< len - 1 ; i++)
    {
        int min = i;
        for(int j = i + 1; j < len; j++)
        {
            if(nums[j] < nums[min])
            {
                min = j;
            }
        }
        if(min != i)
        {
            int temp = nums[min];
            nums[i] = nums[min];
            nums[i] = temp;
        }
    }
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
 
return 0;
}
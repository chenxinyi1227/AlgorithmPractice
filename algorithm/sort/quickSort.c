#include <stdio.h>
#define BUFFER_SIZE 6
/* 快速排序：时间复杂度O(NlogN) */

void printArray(int *array, int length)
{
    for(int idx = 0; idx < length; idx++)
    {
        printf("array[%d] = %d\n", idx, array[idx]);
    }
}
/* 递归排序 */
void quickSort01(int *array, int start, int end)
{
    if(array == NULL)
    {
        return;
    }

    /* 终止条件 */
    if(start >= end)
    {
        return;
    }
    int left = start;
    int right = end;
    int temp = array[left];//基准值temp
    
    while(left < right && array[right] > temp)//比基准值大，指针向前移动
    {
        right--;
    }
    if(left < right)
    {
        array[left] = array[right];//交换比基准值大的记录到左端
        left++;
    }

    while(left < right && array[left] < temp)
    {
        left++;
    }
    if(left < right)
    {
        array[right] = array[left];//交换比基准值大的记录到右端
        right--;

    }
    /* 扫描完成，基准到位 */
    array[left] = temp;
    /* 递归排序左子数组 */
    quickSort01(array, start, left - 1);
    /* 递归排序右子数组 */
    quickSort01(array, right + 1, end); 
}

/* 静态函数1 */
/* 找到基准值的位置 */
static int getIndex(int *arr, int low, int high)
{
    //基准temp
    int temp = arr[low];
    while (low < high) 
    {
        while (low < high && arr[high] >= temp) 
        {
            high--;
        }
        //交换比基准大的记录到左端
        arr[low] = arr[high];
        while (low < high && arr[low] <= temp) 
        {
            low++;
        }
        //交换比基准小的记录到右端
        arr[high] = arr[low];
    }
    //扫描完成，基准到位
    arr[low] = temp;
    // 返回基准的位置
    return low;
}
void quickSort02(int *arr, int low, int high) 
{
    if(arr == NULL)
    {
        return;
    }

    if (low < high) 
    {
        //将数组分为两部分
        int index = getIndex(arr, low, high);
        //递归排序左子数组
        quickSort02(arr, low, index - 1);
        //递归排序右子数组
        quickSort02(arr, index + 1, high);
    }
}

/* 静态函数2 */
/* 找到基准值的位置 */
static int findBaseValPos(int *array, int start, int end)
{
    end--;
    /* 基准值 */
    int baseValPos = array[start];
    while(start < end)
    {
        while(start < end)
        {
            if(array[end] < baseValPos)
            {
                array[start++] = array[end];
                break;
            }
            else
            {
                end--;
            }
        }
        while(start < end)
        {
            if(array[start] < baseValPos)
            {
                array[end--] = array[start];
                break;
            }
            else
            {
                start++;
            }
        }
    }//推出条件是：start = end
    array[start] = baseValPos;
    return start;
}
int quickSort03(int *array, int start, int end)
{
    int ret = 0;
    if (array == NULL)
    {
        return ret;
    }
    /* 如果start == end 说明数组只有一个元素. 直接返回. */
    if (start >= end)
    {
        return ret;
    }
    int baseValPos = findBaseValPos(array, start, end);

    /* 对基准值左侧排序 */
    quickSort03(array, start, baseValPos);
    /* 对基准值右侧排序 */
    quickSort03(array, baseValPos + 1, end);

    return ret;
}

int main()
{
    int nums[] = {0, 6, 5, 8, 1};
    int length = sizeof(nums)/sizeof(nums[0]);
    quickSort02(nums, 0, length - 1);
    printArray(nums, length);
    return 0;
}
//非连续有序 [1,1,2,3,3,5,7,19]   [2,7,9,12,17]  
//合并两个有序数组
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 5
//malloc 返回新数 

int *mergeOrderNum(int *nums1, int nums1Size, int *nums2, int nums2Size, int * newSize)
{
   // *newSize = nums1Size + nums2Size;
    int arrLen = nums1Size + nums2Size;
    int *newArray = (int *)malloc(sizeof(int) * arrLen);

    if(newArray == NULL)
    {
        printf("malloc error!\n");
        return NULL;
    }
   
    int idx1 = 0;
    int idx2 = 0;
    int pos = 0;
    while(idx1 < nums1Size && idx2 < nums2Size)
    {
        if(nums1[idx1] < nums2[idx2])
        {
            newArray[pos] = nums1[idx1++];
        }
        else
        {
            newArray[pos] = nums2[idx2++];
        }
        pos++;
    }/* idx1 == num1Size || idx2 = num2Size 就跳出循环 */

    if(idx1 == nums1Size)
    {
        /* 这个是num1循环结束了 */
        for(int idx = idx2; idx <nums2Size; idx++)
        {
            newArray[pos++] = nums2[idx2++];
        }
    }
    else if(idx2 == nums2Size)
    {
        /* 这个是num2循环结束了 */
        for(int idx = idx1; idx < nums1Size; idx++)
        {
            newArray[pos++] = nums1[idx1++];
        }
    }
    *newSize = arrLen;
    return newArray;
    //return 0;
  //  free(newArray);

    
}

#if 0
int compare(const void *a,const void *b)
{
    return *(int*)a -*(int *)b;
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
    for(int i=0; i !=n ;i++)
        {
            nums1[m+i] = nums2[i];
        }
		qsort(nums1,nums1Size,sizeof(int),compare);
    // int sorted[m+n]={0};
	// int p1,p2;

	// for(int i=0;i<m;i++)
	// {

	// }
}
#endif
int compare(const void *a,const void *b)
{
    return *(int*)a -*(int *)b;
}

int main()
{
#if 1
    int nums1[] = {1,1,2,3,3,5,7,19};
    int nums1Size = sizeof(nums1) / sizeof(nums1[0]);
   
    int nums2[] = {2,7,9,12,17};
    int nums2Size = sizeof(nums2) / sizeof(nums2[0]);

    int newSize = 0; 
    int *array = mergeOrderNum(nums1, nums1Size, nums2, nums2Size, &newSize);
    for(int index = 0; index < newSize; index++)
    {
        printf(" %d", array[index]);
    }
    printf("\n");


#endif
    return 0;
}
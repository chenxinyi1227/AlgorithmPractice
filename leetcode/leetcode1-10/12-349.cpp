#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <algorithm>//排序
#include <set>
/*  两个数组的交集
给定两个数组 nums1 和 nums2 ，返回 它们的交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
*///1、暴力 2、排序
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#if 0

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) 
    {
        // set<int> myset;
         vector<int> res;
        if(nums1 == NULL || nums1.length == 0 || nums2 == null || arr2.nums2 == 0) {
            return res;
        }
        sert
        for(int i = 0;i < arr.length;i ++) {
            int temp = arr[i];
            for(int j = 0;j < arr.length;j ++) {
                if(arr2[j] == temp && !res.contains(temp)) {
                    res.add(temp);
                    break;
                }
            }
        }
        return res;
        
    }
};
#else
int cmp(const void *a, const void *b) 
{
    return *(int *)a - *(int *)b;
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) 
{
    #if 0
    // qsort(nums1, nums1Size, sizeof(int), cmp); 
    // qsort(nums2, nums2Size, sizeof(int), cmp);
    int pos = 0;
    vector<int> myvec;
    for(int idx1 = 0; idx1 < nums1Size; idx1++)
    {
        if(nums1[idx1] == nums1[idx1 + 1])
        {
            idx1++;
        }
        for(int idx2= 0; idx2 < nums2Size; idx2++)
        {
            if(nums2[idx2] == nums2[idx2 + 1])
            {
                idx2++;
            }
            if(nums1[idx1] == nums2[idx2] )
            { 
                myvec.push_back(nums1[idx1]);
            }
        }
    }   
    *returnSize = myvec.size();
    int *array = (int *)malloc(sizeof(int) * myvec.size());
    for(int index = 0; index < myvec.size(); index++)
    {
        array[index] = myvec[index];
    }
    return array;
#else
    
#endif
}



#endif


int main()
{
#if 1
    int nums1[] = {1,3,3,45,7,9,9};
    int nums1Size = sizeof(nums1) / sizeof(nums1[0]);
   
    int nums2[] = {1,7,7,9};
    int nums2Size = sizeof(nums2) / sizeof(nums2[0]);

    int newSize = 0; 
    #if 0
    int *array = intersection(nums1, nums1Size, nums2, nums2Size, &newSize);
    for(int index = 0; index < newSize; index++)
    {
        printf(" %d",array[index]);
    }
    printf("\n");
    #endif

#endif
    return 0;
}
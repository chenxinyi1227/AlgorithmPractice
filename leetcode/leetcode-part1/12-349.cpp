#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <algorithm>//排序
#include <set>
#include <stdio.h>
#include <stdlib.h>
/*  两个数组的交集
给定两个数组 nums1 和 nums2 ，返回 它们的交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
*///1、暴力 2、排序
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#if 0
/* 两个集合 */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) 
    {
        set<int> set1, set2;
        for (auto& num : nums1) 
        {
            set1.insert(num);
        }
        for (auto& num : nums2) 
        {
            set2.insert(num);
        }
        return getIntersection(set1, set2);
    }

    vector<int> getIntersection(set<int>& set1, set<int>& set2) 
    {
        if (set1.size() > set2.size()) 
        {
            return getIntersection(set2, set1);
        }
        vector<int> intersection;
        for (auto& num : set1) 
        {
            if (set2.count(num)) 
            {
                intersection.push_back(num);
            }
        }
        return intersection;
    }
};
#elif 1
/* 排序 + 双指针 */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) 
    {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int length1 = nums1.size(), length2 = nums2.size();
        int index1 = 0, index2 = 0;
        vector<int> intersection;
        while (index1 < length1 && index2 < length2) 
        {
            int num1 = nums1[index1], num2 = nums2[index2];
            if (num1 == num2) 
            {
                // 保证加入元素的唯一性
                if (!intersection.size() || num1 != intersection.back()) 
                {
                    intersection.push_back(num1);
                }
                index1++;
                index2++;
            } else if (num1 < num2) 
            {
                index1++;
            } else 
            {
                index2++;
            }
        }
        return intersection;
    }
};

#else
int cmp(const void *a, const void *b) 
{
    return *(int *)a - *(int *)b;
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) 
{
    qsort(nums1, nums1Size, sizeof(int), cmp);
    qsort(nums2, nums2Size, sizeof(int), cmp);

    *returnSize = 0;
    int index1 = 0, index2 = 0;
    int* intersection = (int*)malloc(sizeof(int) * (nums1Size + nums2Size));

    while (index1 < nums1Size && index2 < nums2Size) 
    {
        int num1 = nums1[index1], num2 = nums2[index2];
        if (num1 == num2) 
        {
            // 保证加入元素的唯一性
            if (!(*returnSize) || num1 != intersection[(*returnSize) - 1]) 
            {
                intersection[(*returnSize)++] = num1;
            }
            index1++;
            index2++;
        } 
        else if (num1 < num2) 
        {
            index1++;
        } 
        else 
        {
            index2++;
        }
    }
    return intersection;
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
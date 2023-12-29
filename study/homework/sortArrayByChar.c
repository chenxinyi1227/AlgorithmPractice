//作业：将字符数组array3排序
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 5

void SortByChar(char **nums, int numsSize)
{
    for(int i = 0; i < BUFFER_SIZE - 1; i++)
    {
        for(int j = 0; j < BUFFER_SIZE - 1 - i; j++)
        {
            int compare = strcmp(nums[j], nums[j+1]);
            if(compare > 0)
            {
                char *temp = NULL;
                temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }     
    }
}

int main()
{
#if 0
    int array1[BUFFER_SIZE] = {1, 2, 3, 4, 5};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        printf("array1[%d] = %d\n", idx, array1[idx]);
    }
    printf("\n");

    char array2[BUFFER_SIZE] = {'a', 'b', 'c', 'd', 'e'};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        printf("array2[%d] = %c\n", idx, array2[idx]);
    }
    printf("\n");
#endif
    char *array3[BUFFER_SIZE] = {"hello", "world", "nihao", "zhangsan", "china"};
#if 0
    for(int idx = 0; idx < BUFFER_SIZE -1; idx++)
    {
        printf("array3[%d+1] = %s\n", idx, array3[idx+1] );
    }
    char p = *array3[0];
    printf("p[0] = %c\n",p);

    char *p1 = array3[0];
    printf("p1[0] = %s\n",p1);
#else
    SortByChar(array3, BUFFER_SIZE);

    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        printf("array3[%d] = %s\n", idx, array3[idx]);
    }
#endif
    return 0;
}
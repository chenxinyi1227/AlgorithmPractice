#include "dynamicArray.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SZIE 10
#define DEFAULT_NUM 4

int compare(const void * p1, const void * p2)
{
 return (*( int *)p1 - *(int *) p2);
}

int main()
{
    dyArray pArray;
    dyInit(&pArray, BUFFER_SZIE);

   {
     int size = 0;
    int capacity = 0;
    dyGetSize(&pArray, &size);
    printf("size:%d\n", size);
    dyGetCapacity(&pArray, &capacity);
    printf("capacity:%d\n", capacity);
   }

    char *str = "chang tring";
    char **val = pArray.space[0];

    // int num1 = 1;
    // int *pval = pArray.dp[0];

    int pos = 0;
    dyInsert(&pArray, (void *)&str);
    
    dyGetElementypeByPos(&pArray, pos, (void *)&val);
    printf("val:%s\n", *val);

    {
        int size = 0;
        int capacity = 0;
        dyGetSize(&pArray, &size);
        printf("size:%d\n", size);
        dyGetCapacity(&pArray, &capacity);
        printf("capacity:%d\n", capacity);
    }
    return 0;
}
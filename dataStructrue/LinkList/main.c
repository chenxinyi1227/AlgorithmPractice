#include "LinkList.h"
#include <stdio.h>
#define BUFFER_SIZE 3

int printBasicData(void *arg)
{
    int data = *(int *)arg;
    printf("data:%d\n", data);
}

int compare(const void *pvData1, const void *pvData2)
{
    return strcmp((ELEMENTTYPE)pvData1, (ELEMENTTYPE)pvData2);
}

int main()
{
    linkList *list = NULL;
    linkListInit(&list);//链表初始化
    
    int buffer[BUFFER_SIZE] = {1, 2, 3};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        linkListInsertHead(list, (void *)&buffer[idx]);
    }

    {
        linkListGetData(list, printBasicData);
        printf("\n");

        int val = 44;
        linkListInsertTail(list, &val);

        int pos = 1;
        int val2 = 18;
        linkListInsertByPos(list, pos, &val2);
        linkListGetData(list, printBasicData);
        printf("\n");
    }
        

    return 0;
}
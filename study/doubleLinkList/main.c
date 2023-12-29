#include "doubleLinkList.h"
#include <stdio.h>  
#include <string.h>

#define BUFFER_SIZE 3

typedef struct stuInfo
{
    int age;
    char sex;
}stuInfo;

/* 自定义打印 */
int printStruct(void *arg)
{
    stuInfo *info= (stuInfo*)arg;
    printf("age:%d\tsex:%c\n", info->age, info->sex);
}

int printBasicData(void *arg)
{
    int data = *(int *)arg;
    printf("data:%d\n", data);
}

int compare(void *pvData1, void *pvData2)
{
    int num1 = *(int *)pvData1;
    int num2 = *(int *)pvData2;
    return num1 == num2 ? 0 : 1;
}

int main()
{

#if 1

    doubleLinkList *list = NULL;
    linkListInit(&list);    //初始化链表

#if 1
    int buffer[BUFFER_SIZE] = {1, 2, 3};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)//插入数据
    {
        linkListInsertHead(list, (void *)&buffer[idx]);
    }
    int size = 0;
    linkListGetLength(list,&size);//获取链表的长度
    printf("size:%d\n", size);
    linkListForeach(list, printBasicData);

    {
        printf("\n测试按指定位置插入\n");
        int val = 4;
        linkListInsertByPos(list, 1, &val);//按指定位置插入
        linkListForeach(list, printBasicData);
        printf("\n测试头插\n");
        int val1 = 0;
        linkListInsertHead(list, &val1);
        linkListForeach(list, printBasicData);
        printf("\n测试尾插\n");
        int val2 = 9;
        linkListInsertTail(list, &val2);
        linkListForeach(list, printBasicData);
    }

    {
        printf("\n测试头删\n");
        linkListDelHead(list);
        linkListForeach(list, printBasicData);
        printf("\n测试尾删\n");
        linkLisDelTail(list);
        linkListForeach(list, printBasicData);
        int pos = 2;
        printf("\n测试删除指定位置%d\n", pos);
        linkListDelByPos(list, pos);//指定位置删除
        linkListForeach(list, printBasicData);
    }
    
    {
        int val = 0;
        printf("\n测试删除指定元素:%d\n", val);
        linkListDelAppointData(list, &val, compare);
        linkListForeach(list, printBasicData);
    }

#else
    stuInfo stu1, stu2, stu3;
    memset(&stu1, 0, sizeof(stu1));
    memset(&stu2, 0, sizeof(stu2));
    memset(&stu3, 0, sizeof(stu3));
    

    stu1.age = 10;
    stu1.sex = 'm';

    stu2.age = 20;
    stu2.sex = 'f';

    stu3.age = 30;
    stu3.sex ='m';
    
    stuInfo buffer[BUFFER_SIZE] = {stu1, stu2, stu3};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        linkListHeadInsert(list, (void *)&buffer[idx]);
    }
 
     int size = 0;
    linkListGetLength(list,&size);//获取链表的长度
    printf("size:%d\n", size);

    linkListForeach(list, printStruct);      //遍历

//     stuInfo *info = NULL;  //二级指针 
//    // memset(&info, 0, sizeof(info));
//     for(int idx = 0; idx < BUFFER_SIZE; idx++)
//     {
//         dynamicArrayGetAppointPosVal(list, idx, (void *)&info);
//         printf("info.age:%d\tinfo.sex:%c\n", info->age, info->sex);
//     }
    #endif
#endif
    return 0;
}
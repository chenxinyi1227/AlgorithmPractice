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
    int data = *(int *)arg;//int / not void
    printf("data:%d\n", data);
}

int printBasicData1(void * args)
{
    printf("%d ", *(int *)args);
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
    doubleLinkListInit(&list);    //初始化链表

#if 1
    int buffer[BUFFER_SIZE] = {1, 2, 3};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)//插入数据
    {
        doubleLinkListInsertHead(list, (void *)&buffer[idx]);
    }
    int size = 0;
    doubleLinkListGetLength(list,&size);//获取链表的长度
    printf("size:%d\n", size);
    doubleLinkListForeach(list, printBasicData1);
    printf("\n");
#if 0       
    {
        doubleLinkListDelTail(list);
        // doubleLinkListDelByPos(list, pos);//指定位置删除
        doubleLinkListForeach(list, printBasicData1);
        printf("\n");
    }
   
    int val = 3;
    doubleLinkListDelAppointData(list, &val, compare);
    doubleLinkListForeach(list, printBasicData1);
    printf("\n");
#endif

    int *pVal1 = NULL;
    doubleLinkListGetAppointPosVal(list, 2, (void*)&pVal1);
    printf("pVal1:%d\n", *pVal1);
    int *pVal2 = NULL;
    doubleLinkListGetHeadVal(list, (void*)&pVal2);
    printf("pVal2:%d\n", *pVal2);
     int *pVal3 = NULL;
    doubleLinkListGetTailVal(list, (void*)&pVal3);
    printf("pVal2:%d\n", *pVal3);
    #if 0
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
    #endif
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
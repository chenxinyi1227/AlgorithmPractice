#include "linkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEAULIT_SIZE 10

#define ISNULL(pList)     if(pList == NULL)       return NULL_PTR
#define ISMALLOC(pList)   if(pList == NULL)       return MALLOC_ERROR
#define ISINVALID(pList,pos)   if(pos < 0 || pos > pList->len)  return INVALID_ACCESS

enum STATUS_CODE
{
    NOT_FOUND = -1,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
    ON_SUCCESS
};
/* 静态函数前置声明 */
static int linkListGetPosByApppointData(linkList *pList, ELEMENTTYPE nodeData, int *pPos, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2));

/* 链表初始化 */
int linkListInit(linkList **pList)
{
    linkList *list;     //定义一个链表
    list = (linkList *)malloc(sizeof(linkList));//为链表分配空间
    ISMALLOC(pList);
    memset(list, 0, sizeof(linkList));  //清除脏数据

    list->pHead = (linkNode *)malloc(sizeof(linkNode));//为链表的头指针分配空间
    if(list->pHead == NULL)
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
        return MALLOC_ERROR;
    }
    memset(list->pHead, 0, sizeof(linkNode));//清除脏数据

    list->pHead->data = 0;                  //将头节点数据域置空
    list->pHead->next = NULL;               //将头节点指针域置空
    list->len = 0;                          //将链表的长度置为0
    list->pTail = list->pHead;              //尾指针等于头指针

    *pList = list;                          //将新分配的内存和数据传给pList
    return ON_SUCCESS;
}

/* 头插 */
int linkListInsertHead(linkList *pList, ELEMENTTYPE nodeData)
{
    return linkListInsertByPos(pList, 0, nodeData);  //一定要return!否则有段错误
}
/* 尾插 */
int linkListInsertTail(linkList *pList, ELEMENTTYPE nodeData)
{
    return linkListInsertByPos(pList, pList->len, nodeData);
}
/* 指定位置插 */
int linkListInsertByPos(linkList *pList, int pos, ELEMENTTYPE nodeData)
{
    ISNULL(pList);
    ISINVALID(pList, pos);

    linkNode * newNode = (linkNode *)malloc(sizeof(linkNode));
    ISMALLOC(newNode);
    memset(newNode, 0, sizeof(linkNode));//新节点要清除脏数据
    newNode->data = nodeData;
    newNode->next = NULL;

    //linkNode * travelNode = (linkNode *)malloc(sizeof(linkNode));
    linkNode * travelNode = pList->pHead;//直接将头指针赋给遍历节点
    
    int flag = 0;
    if(pos == pList->len)//更改尾指针的位置
    {
        travelNode = pList->pTail;//当位置位于链表最后一个元素，遍历节点 = 尾指针
        flag = 1;
    }
    else//位置不在最后一个
    {
        while(pos--)
        {
            travelNode = travelNode->next;//开始遍历
        }
    }
    newNode->next = travelNode->next;
    travelNode->next = newNode;
    
    if(flag)
    {
        pList->pTail = newNode;//更新指针位置 travelnode = 头插
    }
    
    pList->len++;
    //free(travelNode);
    return ON_SUCCESS;

}

/* 链表删除 */
/* 头删 */
int linkListDelHead(linkList *pList)
{
    return linkListDelByPos(pList, 1);//从第一个元素开始删除
}

/* 尾删 */
int linkLisDelTail(linkList *pList)
{
    return linkListDelByPos(pList, pList->len);
}

/* 按位置删 */
int linkListDelByPos(linkList *pList, int pos)
{
    ISNULL(pList);
    ISINVALID(pList, pos);

#if 0
  //  linkNode * travelnode = (linkNode *)malloc(sizeof(linkNode));
    ISMALLOC(travelnode);
    travelnode = pList->pHead;
#endif
    linkNode * travelnode = pList->pHead;

    int flag = 0;
    if(pos == pList->len)//需要修改尾指针
    {
        flag = 1;
    }

    while(--pos)
    {
        travelnode = travelnode->next;
    }
    linkNode * tmpNode = travelnode->next;
    travelnode->next = tmpNode->next;

    if(flag)
    {
        pList->pTail = travelnode;//当删除最后
    }

    if(tmpNode != NULL)
    {
        free(tmpNode);
        tmpNode = NULL;
    }

    pList->len--;
    return ON_SUCCESS;
}

/* 根据指定的元素得到在链表中所在的位置（再思考） */
static int linkListGetPosByApppointData(linkList *pList, ELEMENTTYPE nodeData, int *pPos, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2))
{
    // int pos = 0;
    // int size = 0;
 //   linkNode * travelNode = (linkNode *)malloc(sizeof(linkNode));
   
    /* 从第一个数开始遍历 */
    int pos = 1;
    linkNode * travelNode = pList->pHead->next;

    int cmp = 0;
    while(travelNode != NULL)
    {
        cmp = compare(nodeData, travelNode->data);
        if(cmp == 0)
        {
            *pPos = pos;
           // return *pPos;
            return pos;//返回位置
        }
        /* 不相同继续遍历 */
        travelNode = travelNode->next;
        pos++;
    }
    *pPos = NOT_FOUND;
    return NOT_FOUND;
}

/* 删除指定数据 */
int linkListDelAppointData(linkList *pList, ELEMENTTYPE nodeData, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2))
{
 //   ISNULL(pList);
    int size = 0;
    int pos = 0;//数据在链表中的位置
    while(linkListGetLength(pList, &size) && pos != NOT_FOUND)
    {
        linkListGetPosByApppointData(pList, nodeData, &pos, compare);
        linkListDelByPos(pList, pos);
    }
    return ON_SUCCESS;
}

/* 获取链表大小 */
int linkListGetLength(linkList *pList, int *pLength)
{
    ISNULL(pList);
    // while(pList->pHead != NULL)
    // {
    //     *pLength = pList->len;
    // }
    if(pLength)
    {
       *pLength = pList->len; 
    }
    return pList->len;
}

/* 释放链表 */
int linkListDestory(linkList *pList)
{
    int length = 0;
    while(linkListGetLength(pList, &length))
    {
        linkListDelHead(pList);
    }

    if(pList->pHead != NULL)
    {
        free(pList->pHead);
        pList->pHead =NULL;
        pList->pTail = NULL;
    }
    return ON_SUCCESS;
}

/* 链表遍历 */
int linkListForeach(linkList *pList, int(*visit)(ELEMENTTYPE))
{
    ISNULL(pList);
    int length = 0;
   // linkNode * travelNode = (linkNode*)malloc(sizeof(linkNode));
   // travelNode = pList->pHead->next;
    linkNode * travelNode = pList->pHead->next;//从第一个元素开始遍历
    while(travelNode != NULL)
    {
        visit(travelNode->data);
        travelNode = travelNode->next;
    }
    
    return ON_SUCCESS;
}

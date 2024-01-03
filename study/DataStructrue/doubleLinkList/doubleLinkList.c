#include "doubleLinkList.h"
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
static int doubleLinkListGetPosByApppointData(doubleLinkList *pList, ELEMENTTYPE nodeData, int *pPos, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2));
/* 封装函数结点 */
static doubleLinkNode *createDoubleNewNode(ELEMENTTYPE val);
/* 链表初始化 */
int doubleLinkListInit(doubleLinkList **pList)
{
    doubleLinkList *list;     //定义一个链表
    list = (doubleLinkList *)malloc(sizeof(doubleLinkList));//为链表分配空间
    ISMALLOC(pList);
    memset(list, 0, sizeof(doubleLinkList));  //清除脏数据

    list->pHead = (doubleLinkNode *)malloc(sizeof(doubleLinkNode));//为链表的头指针分配空间
    if(list->pHead == NULL)
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
        return MALLOC_ERROR;
    }
    memset(list->pHead, 0, sizeof(doubleLinkNode));//清除脏数据

    list->pHead->data = 0;                  //将头节点数据域置空
    list->pHead->next = NULL;               //将头节点指针域置空
    list->pHead->prev = NULL;
    list->len = 0;                          //将链表的长度置为0
    list->pTail = list->pHead;              //尾指针等于头指针
  
    *pList = list;                          //将新分配的内存和数据传给pList
    return ON_SUCCESS;
}

/* 头插 */
int doubleLinkListInsertHead(doubleLinkList *pList, ELEMENTTYPE nodeData)
{
    return doubleLinkListInsertByPos(pList, 0, nodeData);  //一定要return!否则有段错误
}
/* 尾插 */
int doubleLinkListInsertTail(doubleLinkList *pList, ELEMENTTYPE nodeData)
{
    return doubleLinkListInsertByPos(pList, pList->len, nodeData);
}

/* 根据数值新建节点并封装成函数 返回的是node型的指针 */
static doubleLinkNode *createDoubleNewNode(ELEMENTTYPE val)
{
    doubleLinkNode * newNode = (doubleLinkNode *)malloc(sizeof(doubleLinkNode));
    ISMALLOC(newNode);
    memset(newNode ,0 ,sizeof(doubleLinkNode));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;//返回新结点
}

/* 指定位置插 */
int doubleLinkListInsertByPos(doubleLinkList *pList, int pos, ELEMENTTYPE nodeData)
{
    ISNULL(pList);
    ISINVALID(pList, pos);

    doubleLinkNode *newNode = createDoubleNewNode(nodeData);

    //doubleLinkNode * travelNode = (doubleLinkNode *)malloc(sizeof(doubleLinkNode));
    doubleLinkNode * travelNode = pList->pHead->data;//直接将头指针赋给遍历节点 头节点不能动
    
    int flag = 0;
    if(pos == pList->len)//更改尾指针的位置
    { 
       travelNode = pList->pTail;
       flag = 1;
    }
    else//位置不在最后一个
    {
        while(pos--)
        {
            travelNode = travelNode->next;//开始遍历
        }
        travelNode->next->prev = newNode;//3 空链表 
    }
    newNode->next = travelNode->next;//1
    newNode->prev = travelNode;      //2
    travelNode->next = newNode;      //4          

    if(flag)
    {
        pList->pTail = newNode;  //尾指针更新为位置
    }               
    
    pList->len++;
    //free(travelNode);
    return ON_SUCCESS;

}

/* 链表删除 */
/* 头删 */
int doubleLinkListDelHead(doubleLinkList *pList)
{
    return doubleLinkListDelByPos(pList, 1);//从第一个元素开始删除
}

/* 尾删 */
int linkLisDelTail(doubleLinkList *pList)
{
    return doubleLinkListDelByPos(pList, pList->len);
}

/* 按位置删 */
int doubleLinkListDelByPos(doubleLinkList *pList, int pos)
{
    ISNULL(pList);
    ISINVALID(pList, pos);

#if 0
  //  doubleLinkNode * travelnode = (doubleLinkNode *)malloc(sizeof(doubleLinkNode));
    ISMALLOC(travelnode);
    travelnode = pList->pHead;
#endif
    doubleLinkNode * travelnode = pList->pHead;
    doubleLinkNode * needDelNode = NULL;//需要删除的节点
    if(pos == pList->len)//需要修改尾指针
    {
        doubleLinkNode * tmpNode = pList->pTail;//备份尾指针
        pList->pTail = pList->pTail->prev;//更改为指针的位置
        #if 0
        pList->pTail->next = tmpNode->next;
        #else
        pList->pTail->next = NULL;//断掉原尾指针的连接
        #endif
        needDelNode = tmpNode;//把尾指针的值清理

    }
    else
    {
        while(--pos)
        {
            travelnode = travelnode->next;//向后移动
        }
        needDelNode = travelnode->next;
        travelnode->next = needDelNode->next;
        needDelNode->next->prev = travelnode;
    }

    if(needDelNode != NULL)
    {
        free(needDelNode);
        needDelNode = NULL;
    }

    pList->len--;
    return ON_SUCCESS;
}

/* 根据指定的元素得到在链表中所在的位置（再思考） */
static int doubleLinkListGetPosByApppointData(doubleLinkList *pList, ELEMENTTYPE nodeData, int *pPos, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2))
{
    // int pos = 0;
    // int size = 0;
 //   doubleLinkNode * travelNode = (doubleLinkNode *)malloc(sizeof(doubleLinkNode));
   
    /* 从第一个数开始遍历 */
    int pos = 1;
    doubleLinkNode * travelNode = pList->pHead->next;

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
int doubleLinkListDelAppointData(doubleLinkList *pList, ELEMENTTYPE nodeData, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2))
{
 //   ISNULL(pList);
    int size = 0;
    int pos = 0;//数据在链表中的位置
    while(doubleLinkListGetLength(pList, &size) && pos != NOT_FOUND)
    {
        doubleLinkListGetPosByApppointData(pList, nodeData, &pos, compare);
        doubleLinkListDelByPos(pList, pos);
    }
    return ON_SUCCESS;
}

/* 获取链表大小 */
int doubleLinkListGetLength(doubleLinkList *pList, int *pLength)
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
int doubleLinkListDestory(doubleLinkList *pList)
{
    int length = 0;
    while(doubleLinkListGetLength(pList, &length))
    {
        doubleLinkListDelHead(pList);
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
int doubleLinkListForeach(doubleLinkList *pList, int(*visit)(ELEMENTTYPE))
{
    ISNULL(pList);
    int length = 0;
   // doubleLinkNode * travelNode = (doubleLinkNode*)malloc(sizeof(doubleLinkNode));
   // travelNode = pList->pHead->next;
    doubleLinkNode * travelNode = pList->pHead->next;//从第一个元素开始遍历
    while(travelNode != NULL)
    {
        visit(travelNode->data);
        travelNode = travelNode->next;
    }
    return ON_SUCCESS;
}

/* 链表逆序遍历 */
int doubleLinkListForeach(doubleLinkList *pList, int(*visit)(ELEMENTTYPE))
{
    ISNULL(pList);
    int length = 0;
   // doubleLinkNode * travelNode = (doubleLinkNode*)malloc(sizeof(doubleLinkNode));
   // travelNode = pList->pHead->next;
    doubleLinkNode * travelNode = pList->pTail;//从第一个元素开始遍历
    while(travelNode != pList->pHead)
    {
        visit(travelNode->data);
        travelNode = travelNode->prev;
    }
    return ON_SUCCESS;
}

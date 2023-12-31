#include "doubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum  STATUS_CODE
{
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
    NOT_FIND
};

/* 宏函数 */
#define ISNULL(pList)       \
do{                         \
    if(pList == NULL)       \
    {                       \
        return NULL_PTR;    \
    }                       \
   }while(0);

#define ISVALID(pList, pos)         \
do{                                 \
    if(pos < 0 || pos > pList->len) \
    {                               \
        return INVALID_ACCESS;      \
    }                               \
}while(0);

#define ISVALID2(pList, pos)         \
do{                                 \
    if(pos <= 0 || pos > pList->len) \
    {                               \
        return INVALID_ACCESS;      \
    }                               \
}while(0);

#define ISMALLOC(pList)             \
do {                               \
    if(pList == NULL)               \
    {                               \
        printf("内存分配失败!\n");   \
        return MALLOC_ERROR;        \
    }                               \
 }while(0);

/* 链表初始化 */
int doubleLinkListInit(doubleLinkList **pList)
{
    int ret = 0;
    ISNULL(pList);

    doubleLinkList * list = (doubleLinkList *)malloc(sizeof(doubleLinkList));
    ISMALLOC(list);
    memset(list, 0, sizeof(doubleLinkList));

    /* 为头指针分配空间 */
    list->pHead = (doubleLinkNode *)malloc(sizeof(doubleLinkNode));
    ISMALLOC(list->pHead);
    memset( list->pHead, 0, sizeof(doubleLinkNode));

    list->pHead->data = 0;
    list->pHead->next = NULL;
    list->pHead->prev = NULL;
    list->pTail = list->pHead;//?首尾相连 注意顺序
    list->len = 0;

    *pList = list;
    return ret;
}

/* 头插 */
int doubleLinkListInsertHead(doubleLinkList *pList, ELEMENTTYPE nodeData)
{
    doubleLinkListInsertByPos(pList, 0, nodeData);
}
/* 尾插 */
int doubleLinkListInsertTail(doubleLinkList *pList, ELEMENTTYPE nodeData)
{
    doubleLinkListInsertByPos(pList, pList->len, nodeData);
}
/* 指定位置插 */
int doubleLinkListInsertByPos(doubleLinkList *pList, int pos, ELEMENTTYPE nodeData)
{
    int ret = 0;
    ISNULL(pList);
    ISVALID(pList, pos);   

    /* 创建节点 */
    doubleLinkNode * newNode = (doubleLinkNode *)malloc(sizeof(doubleLinkNode));
    if( newNode == NULL) 
    {
        printf("内存分配失败!\n"); 
        return MALLOC_ERROR;
    }
    ISMALLOC(newNode);
    memset(newNode, 0, sizeof(doubleLinkNode));
    newNode->data = nodeData;
    newNode->next = NULL;
    newNode->prev = NULL;
    /* 遍历节点 */
    doubleLinkNode * travelNode = pList->pHead;
    
    int flag = 0;
    if(pos == pList->len)//链表为空 或 尾插
    {
        flag = 1;//更改尾指针
        travelNode = pList->pTail;//从尾部遍历
    }
    else
    {
        while (pos--)
        {
            travelNode = travelNode->next;
        }
        travelNode->next->prev = newNode;
    }
    newNode->next = travelNode->next;
    newNode->prev = travelNode;
    travelNode->next = newNode; 

    if(flag)
    {
        pList->pTail = newNode;//更新尾指针位置
    }

    pList->len++;
    return ret;
    
}

/* 链表删除 */
/* 头删 */
int doubleLinkListDelHead(doubleLinkList *pList)
{
    doubleLinkListDelByPos(pList, 1);
}
/* 尾删 */
int doubleLinkListDelTail(doubleLinkList *pList)
{
    doubleLinkListDelByPos(pList, pList->len);
}
/* 按位置删 */
int doubleLinkListDelByPos(doubleLinkList *pList, int pos)
{   
    int ret = 0;
    ISNULL(pList);
    ISVALID2(pList, pos);

    /* 遍历节点 */
    doubleLinkNode * travelNode = pList->pHead;
    doubleLinkNode * nedDelNode = NULL;//赋值NULL,否则野指针
    if(pos == pList->len)//链表无数据或尾删
    {
        travelNode = pList->pTail->prev;
        nedDelNode = pList->pTail;
        travelNode->next = nedDelNode->next;
    }
    else
    {
        while (--pos)
        {
            travelNode = travelNode->next;
        }
        nedDelNode = travelNode->next;    
        travelNode->next = nedDelNode->next;
        nedDelNode->next->prev = travelNode; 
    }
  
    pList->pTail = pList->pTail->prev;
    pList->len--;

    /* 释放内存 */
    if(nedDelNode != NULL)
    {
        free(nedDelNode);
        nedDelNode = NULL;
    }

    return ret;
}
/* 根据元素获取下标 */
static int getIndexByVal(doubleLinkList *pList, ELEMENTTYPE nodeData,int *pos, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2))
{

    int ret = 0;
    int Pos = 1;
    doubleLinkNode * travelNode = pList->pHead->next;
    int cmp = 0;
    while(travelNode != NULL)
    {
        cmp = compare(travelNode->data, nodeData);
        if(cmp == 0)
        {
            *pos = Pos;
            return Pos;
        }
        travelNode = travelNode->next;
        Pos++;//错误1:pos/Pos变量命名不能与函数参数相同
    }
    /* travelNode = NULL 或 没找到 */
    *pos = NOT_FIND;
    return NOT_FIND;
}
/* 删除指定数据 */
int doubleLinkListDelAppointData(doubleLinkList *pList, ELEMENTTYPE nodeData, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2))
{
    int ret = 0;
    int pos = 0;
    int length = 0;
    while(doubleLinkListGetLength(pList, &length) && pos != NOT_FIND)//条件需要再思考:链表长度不为0并且pos能找到
    {
        getIndexByVal(pList, nodeData, &pos, compare);
        doubleLinkListDelByPos(pList, pos);
    }
    return ret;
}

/* 获取链表大小 */
int doubleLinkListGetLength(doubleLinkList *pList, int *pLength)
{
    int ret = 0;
    ISNULL(pList);
    int length = 0;
    if(pLength)
    {
        length = pList->len;
    }
    *pLength = length;
    return pList->len;//返回链表长度
}

/* 销毁链表 */
int doubleLinkListDestory(doubleLinkList *pList)
{
    int ret = 0;
    int length = 0;
    while(length)
    { 
        doubleLinkListGetLength(pList, &length);
        doubleLinkListDelTail(pList);
    }

    if(pList->pHead != NULL)
    {
        free(pList->pHead);//初始化为头指针开辟了空间
        pList->pHead = NULL;
        pList->pTail = NULL;
    }
    return ret;
}   

/* 链表遍历 */
int doubleLinkListForeach(doubleLinkList *pList, int(*visit)(ELEMENTTYPE))
{
    int ret = 0;
    ISNULL(pList);
    doubleLinkNode *travelNode = pList->pHead->next;//不能从头指针开始，头指针为空
    #if 0
    for(int idx = 0; idx < length; idx++)
    {
        travelNode = travelNode->next;
        visit(travelNode->data);//虚拟头指针为空指针
    }
    #endif
    while(travelNode != NULL)
    {
        visit(travelNode->data);
        travelNode = travelNode->next;
    }
    return ret;
}

/* 获取链表头位置的值 */
int doubleLinkListGetHeadVal(doubleLinkList *pList, ELEMENTTYPE *pVal)
{
    doubleLinkListGetAppointPosVal(pList, 1, pVal);//0->1
}

/* 获取链表尾位置的值 */
int doubleLinkListGetTailVal(doubleLinkList *pList, ELEMENTTYPE *pVal)
{
    doubleLinkListGetAppointPosVal(pList, pList->len, pVal);
}

/* 获取链表指定的值 */
int doubleLinkListGetAppointPosVal(doubleLinkList *pList, int pos, ELEMENTTYPE *pVal)
{
    ISNULL(pList);
    ISVALID(pList, pos);
    int ret = 0;
    doubleLinkNode * travelNode = pList->pHead;
    if(pos == pList->len)
    {
        *pVal = pList->pTail->data;
    }
    else
    {
        while(pos--)
        {
            travelNode = travelNode->next;
        }
        *pVal = travelNode->data;//pos = -1 
    }
    return ret;
}
#include "LinkList.h"
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
static int linkListGetPosByApppointData(linkList *pList, ELEMENTTYPE nodeData, int *pPos);

/* 链表初始化 */
int linkListInit(linkList **pList)
{
    linkList *list;     //定义一个链表
    list = (linkList *)malloc(sizeof(linkList));//为链表分配空间
    ISMALLOC(pList);
    memset(list, 0, sizeof(linkList) * 1);  //清除脏数据

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
    ISMALLOC(pList);
    ISINVALID(pList, pos);

    linkNode *newNode;      //建立一个新节点
    newNode = (linkNode *)malloc(sizeof(linkNode));//为新节点申请空间
    ISMALLOC(newNode);
    memset(newNode, 0, sizeof(linkNode *));//清除脏数据
    newNode->data = nodeData;                   //将nodeData保存到新节点的数据域中
    newNode->next = NULL;//

    linkNode *travelNode = pList->pHead;   //设置遍历节点
    
    int flag = 0;//标志位
    if(pos == pList->len)//这时需要更改尾指针
    {
        travelNode = pList->pTail;//
        flag = 1;
    }
    else
    {
        while(pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
    }
    newNode->next = travelNode->next;   //新节点指向插入位置的下一个节点
    travelNode->next = newNode;         //插入位置的前一节点指向新节点   
    if(flag)
    {
        pList->pTail = newNode;
    }

    pList->len++;//更新链表长度
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

    linkNode *travelNode = pList->pHead;
    int flag = 0;
    if(pos == pList->len)
    {
        flag = 1;
    }
    while(--pos)
    {
        travelNode = travelNode->next;  // 指定位置的前一节点  
    }
    
    linkNode *posNode = travelNode->next;//需要删除的节点posNode
    travelNode->next = posNode->next;    

    if(flag)
    {
        pList->pTail = travelNode;
    }
    
    if(posNode != NULL)//释放内存
    {
        free(posNode);
        posNode = NULL;
    }
    pList->len--;//更新链表长度
    return ON_SUCCESS;
}

/* 根据指定的元素得到在链表中所在的位置 */
static int linkListGetPosByApppointData(linkList *pList, ELEMENTTYPE nodeData, int *pPos)
{
    int pos = 1;
    linkNode *travelNode = pList->pHead->next;
    while(travelNode != NULL)
    {
        if(travelNode->data == nodeData)
        {
            *pPos = pos;//解引用
            return pos;
        }
        travelNode = travelNode->next;
        pos++;
    }
    *pPos = NOT_FOUND;//解引用
    return NOT_FOUND;
}

/* 删除指定数据 */
int linkListDelAppointData(linkList *pList, ELEMENTTYPE nodeData, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2))
{
    int ret = 0;
    int pos = 0;
    int size = 0;
    while(LinkListGetLength(pList, &size) && pos != NOT_FOUND)
    {
        linkListGetPosByApppointData(pList, nodeData, &pos);
        linkListDelByPos(pList, pos);
    }
    return ret;
}

/* 获取链表大小 */
int LinkListGetLength(linkList *pList, int *pLength)
{
    ISNULL(pList);
    if(pLength)//地址不为空
    {
        *pLength = pList->len;
    }
    return pList->len;//返回链表长度
}

/* 释放链表 */
int LinkListDestory(linkList *pList)
{
    int ret = 0;
    /* 头删删除节点 */
    int size = 0;
    while(LinkListGetLength(pList, &size))
    {
        linkListDelHead(pList);
    }
    /* 释放空间 */
    if(pList->pHead != NULL)
    {
        free(pList->pHead);
        pList->pHead = NULL;//指针置空
        pList->pTail = NULL;
    }
    return ret;
}

/* 获取链表数据 */
int linkListGetData(linkList *pList, int(*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    ISNULL(pList);
    
    linkNode *travelNode = pList->pHead->next;//从第一个元素开始遍历
    while(travelNode != NULL)
    {
        printFunc(travelNode->data);//钩子函数输出数据域
        travelNode = travelNode->next;//移动遍历节点
    }
    return ret;
}

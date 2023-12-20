#include "LinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum STATUS_CODE
{
    NOT_FOUND = -1,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS
};

/* 链表初始化 */
int linkListInit(linkList **pList)
{
    int ret  = 0;
    linkList *list;     //定义一个链表
    list = (linkList *)malloc(sizeof(linkList));//为链表分配空间
    if(list == NULL)
    {
        return MALLOC_ERROR;
    }
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
    return ret;
}


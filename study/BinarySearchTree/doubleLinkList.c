#include "common.h"
#include "doubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,    //非法访问
};

/* 静态函数只给本源文件（.c)的函数使用 */
/* 静态前置声明 */
static int doubleLinkListAccordApppointValGetPos(doubleLinkList *pList, ELEMENTTYPE val, int *pPos, int(*compareFunc)(ELEMENTTYPE,ELEMENTTYPE));
/* 新建新节点封装成函数 */
static doubleLinkNode *createdoubleLinkList(ELEMENTTYPE val);

/* 链表初始化 */
int doubleLinkListInit(doubleLinkList **pList)
{
    int ret = 0;
    doubleLinkList *list = (doubleLinkList *)malloc(sizeof(doubleLinkList) * 1);
    if(list == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list, 0, sizeof(doubleLinkList) * 1);      //清空脏数据

    list->head = (doubleLinkNode *)malloc(sizeof(doubleLinkNode) * 1); //为head分配空间
    if(list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list->head, 0, sizeof(doubleLinkNode *));  //清空脏数据
    list->head->data = 0;
    list->head->next = NULL;
    list->head->prev = NULL;  //虚拟头节点的prev指针指向NULL
    list->tail = list->head;  //尾指针初始化时,尾指针 = 头指针
   
    list->len = 0;                  //链表的长度为0

    *pList = list;                  // 二级指针 
    return ret;
}

/* 链表头插 */
int doubleLinkListHeadInsert(doubleLinkList *pList, ELEMENTTYPE val)
{
    return doubleLinkListAppointPosInsert(pList, 0, val);
}

/* 链表尾插 */
int doubleLinkListTailInsert(doubleLinkList *pList, ELEMENTTYPE val)
{
    /* todo... */
    return doubleLinkListAppointPosInsert(pList, pList->len, val);
}

/* 新建新节点封装成函数 */
static doubleLinkNode *createdoubleLinkList(ELEMENTTYPE val)
{
    /* 封装节点 */
    doubleLinkNode * newNode = (doubleLinkNode *)malloc(sizeof(doubleLinkNode *) * 1);
    if(newNode == NULL)
    {
        return NULL;
    }
    memset(newNode, 0 , sizeof(doubleLinkNode *) * 1);//清除脏数据
#if 1
    /* 维护新节点 */
    newNode->data = 0;
    newNode->next = NULL;
    newNode->prev = NULL;//新建的prev节点
#endif
    newNode->data = val;                        //赋值
    return newNode;//返回新节点
}

/* 链表指定位置插入 */
int doubleLinkListAppointPosInsert(doubleLinkList *pList, int pos, ELEMENTTYPE val)
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }
    if(pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    /* 新建新节点封装成函数 */
    doubleLinkNode * newNode = createdoubleLinkList(val);
    if(newNode == NULL)
    {
        return NULL_PTR;
    }
#if 0
    /* 封装结点 */
    doubleLinkNode * newNode = (doubleLinkNode *)malloc(sizeof(doubleLinkNode *) * 1);
    if(newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newNode, 0 , sizeof(doubleLinkNode *) * 1);//清除脏数据
#if 1
    newNode->data = 0;
    newNode->next = NULL;
#endif
    newNode->data = val;                        //赋值
#endif

#if 1
    doubleLinkNode * travelNode = pList->head;        //从虚拟头结点开始遍历
#else
    doubleLinkNode * travelNode = pList->head->next;
#endif
    int flag = 0;
    if(pos == pList->len)                       //这种情况下需要更改尾指针
    {
        travelNode = pList->tail;               // 修改节点指向
#if 0
        // newNode->next == travelNode->next;  
        // travelNode->next = newNode;
#endif
        flag = 1;
    }
    else
    {
        while(pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
        travelNode->next->prev = newNode;  //没有节点的情况下
    }
    newNode->next = travelNode->next;  //1
    newNode->prev = travelNode;        //2
    travelNode->next = newNode;        //4 //?

    if(flag)
    {
        pList->tail = newNode;  //尾指针更新为位置
    }

    (pList->len)++;             //更新链表长度
    return ret;
}

/* 链表头删 */
int doubleLinkListHeadDel(doubleLinkList *pList)
{
    return doubleLinkListDelAppointPos(pList, 1);
}

/* 链表尾删 */
int doubleLinkListTailDel(doubleLinkList *pList)
{
    return doubleLinkListDelAppointPos(pList, pList->len);
}

/* 链表指定位置删除 */
int doubleLinkListDelAppointPos(doubleLinkList *pList, int pos)
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }
    /* todo...          */
    if(pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

#if 1
    doubleLinkNode * travelNode = pList->head;
#else
doubleLinkNode * travelNode = pList->head->next;
#endif
    doubleLinkNode * needDelNode = NULL;
    /* 需要修改尾指针 */
    if(pos == pList->len)
    {
        /* 备份尾指针 */
        doubleLinkNode * tmpNode = pList->tail;
        pList->tail = pList->tail->prev;
        needDelNode = tmpNode;
        pList->tail->next = NULL;//尾指针置空，否则段错误
    }
   else
   {
        while(--pos)
        {
            travelNode = travelNode->next;//向后移动位置
        }
        /* 跳出循环的是哪一个节点 */
        needDelNode = travelNode->next;         //1
        travelNode->next = needDelNode->next;   //2
        needDelNode->next->prev = travelNode;   //3
   }
    
    /* 释放内存 */
    if(needDelNode != NULL)
    {
        free(needDelNode);
        needDelNode = NULL;
    }

    pList->len--;      //链表长度减一
    return ret;
}

/* 根据指定的元素得到在链表中所在的位置 */
static int doubleLinkListAccordApppointValGetPos(doubleLinkList *pList, ELEMENTTYPE val, int *pPos, int(*compareFunc)(ELEMENTTYPE,ELEMENTTYPE))
{
    /* 静态函数只给本源文件的函数使用，不需要判断合法性 */
    int ret;
#if 0
    doubleLinkNode * travelNode = pList->head;
#else
    int pos = 1;
    doubleLinkNode *travelNode = pList->head->next;
#endif
    int cmp = 0;
    while(travelNode != NULL)
    {
        #if 0
        if(travelNode->data == val)
        {
            *pPos = pos;//解引用
            return pos;
        }
        #else
       cmp = compareFunc(val, travelNode->data);
       if(cmp == 0)
       {
            *pPos = pos;//解引用
            return pos;
       }
       #endif
        travelNode = travelNode->next;
        pos++;
    }
    /* 解除解引用 */
    *pPos = NOT_FIND;
    return NOT_FIND;
}

/* 链表删除指定数据 */ 
int doubleLinkListDelAppointData(doubleLinkList *pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE,ELEMENTTYPE))//??
{
    int ret = 0;
    int pos = 0;        //元素在链表中的位置
    int size = 0;       //链表的长度
    while(doubleLinkListGetLength(pList, &size) && pos != NOT_FIND)
    {
        /* 根据指定的元素得到在链表中所在的位置 */    
        doubleLinkListAccordApppointValGetPos(pList, val, &pos, compareFunc);
        doubleLinkListDelAppointPos(pList, pos);
    }
    return ret;
}

/* 获取链表的长度 */
int doubleLinkListGetLength(doubleLinkList *pList, int *pSize)
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pSize)
    {
        *pSize = pList->len;
    }
    return pList->len; //返回链表长度
}

/* 链表的销毁 */
int doubleLinkListDestory(doubleLinkList *pList)
{
    int ret = 0;
    /* 头删释放链表 */
    int size = 0;
    while(doubleLinkListGetLength(pList, &size))
    {
        doubleLinkListHeadDel(pList);
    }
    /* 释放头节点 */
    if(pList->head != NULL)
    {
        free(pList->head);
        /* 指针置为NULL */
        pList->head = NULL;
        pList->tail = NULL;
    }

    /* 释放链表  */
    if (pList)
    {
        free(pList);
        pList = NULL;
    }
    return ret;
}

/* 链表遍历接口 */
int doubleLinkListForeach(doubleLinkList *pList, int(*printFunc)(ELEMENTTYPE))
{

    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }
#if 0
    doubleLinkNode * travelNode = pList->head;        // travelNode指向虚拟头节点 
    while(travelNode->next != NULL)
    {
        travelNode = travelNode->next;
        printf("travelNode->data:%d\n", travelNode->data);
    }
#else
    doubleLinkNode * travelNode = pList->head->next;  //travelNde 指向链表第一个元素 
    while(travelNode != NULL)
    {
        #if 0
        printf("travelNode->data:%d\n", travelNode->data);//travelNode->data放的是地址
        #else
        /* 包装器（C++) 钩子函数-回调函数（C) */
        printFunc(travelNode->data);
        #endif
        travelNode = travelNode->next;
    }
#endif    
    return ret;
}

/* 链表逆序遍历接口 */
int doubleLinkListReverseForeach(doubleLinkList *pList, int(*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }
    /* 标记到尾指针 */
    doubleLinkNode * travelNode = pList->tail;  //travelNde 指向链表最后一个元素 
    #if 1
    while(travelNode != pList->head)
    {    
        /* 包装器（C++) 钩子函数-回调函数（C) */
        printFunc(travelNode->data);
        /* 移动前指针 */
        travelNode = travelNode->prev;
    } 

    #else
    int size = 0;
    doubleLinkListGetLength(pList, &size);
    for(int idx = 0; idx < size; idx++)
    {    
        /* 包装器（C++) 钩子函数-回调函数（C) */
        printFunc(travelNode->data);
        /* 移动前指针 */
        travelNode = travelNode->prev;
    } 
    #endif
    return ret;
}

/* 获取链表头位置的值 */
int doubleLinkListGetHeadVal(doubleLinkList *pList, ELEMENTTYPE *pVal)
{
    #if 0
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }
    if(pVal)
    {
        *pVal = pList->head->next->data;
    }
    return ret = 0;
    #else
    return doubleLinkListGetAppointPosVal(pList, 1, pVal);
    #endif
} 

/* 获取链表尾位置的值 */
int doubleLinkListGetTailVal(doubleLinkList *pList, ELEMENTTYPE *pVal)
{
    return doubleLinkListGetAppointPosVal(pList, pList->len, pVal);
}

/* 获取链表指定位置的值 */
int doubleLinkListGetAppointPosVal(doubleLinkList *pList,int pos, ELEMENTTYPE *pVal)
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }
    if(pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    doubleLinkNode * travelNode = pList->head;
#if 0
    if(pos == pList->len)
    { 
        *pVal = pList->tail->data;       
    }
    else
    {   
        while(pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
        *pVal = travelNode->data;
    }
#endif
    while(pos)
    {
        travelNode = travelNode->next;
        pos--;
    }
    if(pVal)
    {
        *pVal = travelNode->data;
    }
    return ON_SUCCESS;
}
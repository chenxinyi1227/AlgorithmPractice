#include "doubleLinkList.h"
#include <stdio.h>
/* 链表初始化 */
int doubleLinkListInit(doubleLinkList **pList)
{

}

/* 头插 */
int doubleLinkListInsertHead(doubleLinkList *pList, ELEMENTTYPE nodeData)
{

}
/* 尾插 */
int doubleLinkListInsertTail(doubleLinkList *pList, ELEMENTTYPE nodeData)
{

}
/* 指定位置插 */
int doubleLinkListInsertByPos(doubleLinkList *pList, int pos, ELEMENTTYPE nodeData)
{

}

/* 链表删除 */
/* 头删 */
int doubleLinkListDelHead(doubleLinkList *pList)
{

}
/* 尾删 */
int linkLisDelTail(doubleLinkList *pList)
{

}
/* 按位置删 */
int doubleLinkListDelByPos(doubleLinkList *pList, int pos)
{

}

/* 删除指定数据 */
int doubleLinkListDelAppointData(doubleLinkList *pList, ELEMENTTYPE nodeData, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2))
{
    
}

/* 获取链表大小 */
int doubleLinkListGetLength(doubleLinkList *pList, int *pLength)
{

}

/* 销毁链表 */
int doubleLinkListDestory(doubleLinkList *pList)
{

}

/* 链表遍历 */
int doubleLinkListForeach(doubleLinkList *pList, int(*visit)(ELEMENTTYPE))
{

}
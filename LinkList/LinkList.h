#ifndef _LINKLIST_H_
#define _LINKLIST_H_
  
#define ELEMENTTYPE void *

/* 链表节点数据类型定义 */
typedef struct linkNode
{
    ELEMENTTYPE data;       //数据域
    struct linkNode *next;  //指针域，下一个节点的地址
}linkNode;

/* 链表 */
typedef struct  linkList
{
    struct linkNode * pHead;  //虚拟头指针
    struct linkNode * pTail;  //尾指针
    int len;                 //链表长度
}linkList;

/* 链表初始化 */
int linkListInit(linkList **pList);

/* 头插 */
int linkListInsertHead(linkList *pList, ELEMENTTYPE nodeData);
/* 尾插 */
int linkListInsertTail(linkList *pList, ELEMENTTYPE nodeData);
/* 指定位置插 */
int linkListInsertByPos(linkList *pList, int pos, ELEMENTTYPE nodeData);

/* 链表删除 */
/* 头删 */
int linkListDelHead(linkList *pList);
/* 尾删 */
int linkLisDelTail(linkList *pList);
/* 按位置删 */
int linkListDelByPos(linkList *pList, int pos);

/* 删除指定数据 */
int linkListDelAppointData(linkList *pList, ELEMENTTYPE nodeData, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2));

/* 获取链表大小 */
int LinkListGetLength(linkList *pList, int *pLength);

/* 销毁链表 */
int LinkListDestory(linkList *pList);

/* 获取链表数据 */
int linkListGetData(linkList *pList, int(*printFunc)(ELEMENTTYPE));

#endif
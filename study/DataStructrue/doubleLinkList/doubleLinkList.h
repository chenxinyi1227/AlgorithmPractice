#ifndef _DOUBLELINKLIST_H_
#define _DOUBLELINKLIST_H_
  
#define ELEMENTTYPE void *

/* 链表节点数据类型定义 */
typedef struct doubleLinkNode
{
    ELEMENTTYPE data;       //数据域
    struct doubleLinkNode *next;  //指针域，下一个节点的地址
    struct doubleLinkNode *prev;  //指针域，前一个节点的地址
}doubleLinkNode;

/* 链表 */
typedef struct  doubleLinkList
{
    struct doubleLinkNode * pHead;  //虚拟头指针
    struct doubleLinkNode * pTail;  //尾指针
    int len;                 //链表长度
}doubleLinkList;

/* 链表初始化 */
int doubleLinkListInit(doubleLinkList **pList);

/* 头插 */
int doubleLinkListInsertHead(doubleLinkList *pList, ELEMENTTYPE nodeData);
/* 尾插 */
int doubleLinkListInsertTail(doubleLinkList *pList, ELEMENTTYPE nodeData);
/* 指定位置插 */
int doubleLinkListInsertByPos(doubleLinkList *pList, int pos, ELEMENTTYPE nodeData);

/* 链表删除 */
/* 头删 */
int doubleLinkListDelHead(doubleLinkList *pList);
/* 尾删 */
int doubleLinkListDelTail(doubleLinkList *pList);
/* 按位置删 */
int doubleLinkListDelByPos(doubleLinkList *pList, int pos);

/* 删除指定数据 */
int doubleLinkListDelAppointData(doubleLinkList *pList, ELEMENTTYPE nodeData, int(*compare)(ELEMENTTYPE pvData1, ELEMENTTYPE pvData2));

/* 获取链表大小 */
int doubleLinkListGetLength(doubleLinkList *pList, int *pLength);

/* 销毁链表 */
int doubleLinkListDestory(doubleLinkList *pList);

/* 链表遍历 */
int doubleLinkListForeach(doubleLinkList *pList, int(*visit)(ELEMENTTYPE));

#endif
#ifndef COMMON_H_
#define COMMON_H_
#define ELEMENTTYPE void*

/* 链表节点取别名 */
typedef struct doubleLinkNode
{
    ELEMENTTYPE data;                //数据域：存储节点数据信息
    struct doubleLinkNode *prev;    //指向前一节点
    struct doubleLinkNode *next;    //指针域：存储直接后继节点的地址 （指向下一个结点的指针  指针的类型为什么是节点？)
}doubleLinkNode;

typedef struct doubleLinkList
{
    doubleLinkNode * head;            //链表的虚拟头节点：1、数据域无意义 2、只使用指针域
    doubleLinkNode * tail;            //为什么尾指针不需要分配空间？
    int len;                    //链表的长度
}doubleLinkList;
#endif
/* 相交链表  
相交指的是：元素在内存中指向相同的位置*/
#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode 
{
    int val;
    struct ListNode *next;
 };

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) 
{
    if(headA == NULL || headB == NULL)
    {
        return NULL;
    }
    ListNode *ptrA = headA;
    ListNode *ptrB = headB;
    #if 1
    while(ptrA != ptrB)//内存中指向相同的位置
    {
        /* 指针PA一开始在链表A上遍历当走到wweib */
        ptrA = (ptrA == NULL ? headB : ptrA->next);
        ptrB = (ptrB == NULL ? headA : ptrB->next);
    }
    return ptrA;

    #else
    // 指针 pointA 和 指针 pointB 不断向后遍历，直到找到相交点
    // 不用担心会跳不出这个循环，实际上在链表 headA 长度和链表 headB 长度的之和减一
    // pointA 和 pointB 都会同时指向 null
    // 比如 headA 的长度是 7，headB 的长度是 11，这两个链表不相交
    // 那么 pointA 移动了 7 + 11 - 1 次之后，会指向 null
    // pointB 移动了 7 + 11 - 1  次之后，也指向 null
    // 这个时候就跳出了循环
    while (ptrA != ptrB) 
    {
        // 指针 pointA 一开始在链表 A 上遍历，当走到链表 A 的尾部即 null 时，跳转到链表 B 上 
        if( ptrA == NULL)
        {
            // 指针 pointA 跳转到链表 B 上  
            ptrA = headB;
        }
        else
        {
            // 否则的话 pointA 不断的向后移动
            ptrA = ptrA->next;
        }
        // 指针 pointB 一开始在链表 B 上遍历，当走到链表 B 的尾部即 null 时，跳转到链表 A 上 
        if( ptrB == NULL)
        {
            // 指针 pointA 跳转到链表 B 上  
            ptrB = headA;
        }
        else
        {
            // 否则的话 pointB 不断的向后移动
            ptrB = ptrB->next;
        }
    }
    // 1、此时，pointA 和 pointB 指向那个相交的节点，返回任意一个均可
    // 2、此时，headA 和 headB 不相交，那么 pointA 和 pointB 均为 null，也返回任意一个均可
    return ptrA;
    #endif
}
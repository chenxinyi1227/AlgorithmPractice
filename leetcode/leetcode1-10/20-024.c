#include <stdio.h>
/* 反转链表 */
//Definition for singly-linked list.
struct ListNode 
{
   int val;
   struct ListNode *next;
 };

struct ListNode* reverseList(struct ListNode* head){
    struct ListNode *pre = NULL;
    struct ListNode *cur = head;
    struct ListNode *nextNode =  NULL;

    while(cur != NULL)
    {
        nextNode = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nextNode;
    }
    return pre;
}
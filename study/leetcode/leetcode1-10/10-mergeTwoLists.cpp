#include <iostream>
using namespace std;
#include <list>
/* 合并两个有序链表 
将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有结点组成的*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
 };

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
{
    ListNode * newNode = NULL;
    newNode->val = 0;
    newNode->next = NULL;
    // ListNode * newNode = new ListNode(0);
    ListNode * pre = newNode;
    while(list1 != NULL && list2 != NULL)
    {
        if(list1->val <= list2->val)
        {
            pre->next = list1;
            list1 = list1->next;
        }
        else
        {
            pre->next = list2;
            list2 = list2->next;
        }
    pre = pre->next;
    }
    if(list1)
    {
        pre->next = list1;
    }
    if(list2)
    {
        pre->next = list2;
    }
    return newNode->next;
}
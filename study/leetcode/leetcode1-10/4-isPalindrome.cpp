#include <iostream>
using namespace std;
#include <vector>

/* 回文链表
给你一个单链表的头节点 head ，
请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。 */

#if 0
class Solution {
public:
    bool isPalindrome(ListNode* head) 
    {
        if (head == NULL)
        {
            return true;
        }

        /* 备份 */
        ListNode* travelNode = head;
        vector<int> myvec;
        while(travelNode != NULL)
        {
            myvec.emplace_back(travelNode->val);
            travelNode = travelNode->next;
        }
        #if 0
        for (int idx = 0; idx < myvec.size() / 2; idx++)
        {
            if (myvec[idx] != myvec[myvec.size() -1 -idx])
            {
                return false;
            }
        }
        #elif 0
        int begin = 0;
        int end = myvec.size() - 1;
        while (begin < end)
        {
            if (myvec.at(begin) != myvec.at(end))
            {
                return false;
            }
            begin++;
            end--;
        }
        #else
        int begin = 0;
        int end = myvec.size() - 1;
        while (begin < end)
        {
            if (myvec[begin++] != myvec[end--])
            {
                return false;
            }
        }
        #endif
        return true;
    }
};

#endif
#if 0
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        stack<ListNode*> mystack;

        ListNode *travelNode = head;

        while(travelNode != NULL)
        {
            mystack.push(travelNode);
            travelNode = travelNode->next;
        }

        travelNode = head;

        ListNode * topVal = NULL;
        while(!mystack.empty())
        {
            topVal = mystack.top();
            mystack.pop();

            if(travelNode->val != topVal->val)
            {
                return false;
            }
            travelNode = travelNode->next;
        }
    return true;
    }
};
#endif

struct ListNode 
{
    int val;
    ListNode *next;
 };

bool isPalindrome(struct ListNode* head) {
    struct ListNode* fast = head->next;
    struct ListNode* slow = head->next;
    int pos = 0;
    vector<int> myvec;
    myvec.emplace_back(head->val);
    int begin = 0;
    int end = myvec.size() - 1;
    while (begin < end)
    {
        if (myvec[begin++] != myvec[end--])
        {
            return false;
        }
    } 
}


#include <istream>
using namespace std;
#include <vector>
/**删除排序链表中的重复元素 单链表
 * Definition for singly-linked list.*/
struct ListNode 
 {
    int val;
    ListNode *next;
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) 
    {
        ListNode *cur = head;
        while(cur != NULL && cur->val != NULL)
        /* while(cur->next) */
        {
            if(cur->val == cur->next->val)
            {
                cur->next = cur->next->next;//去重
            }
            else
            {
                cur = cur->next;
            }
        }
        return head;
    }
};
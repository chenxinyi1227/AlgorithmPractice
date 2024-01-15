/* 二叉树的层序遍历 */
#include <iostream>
using namespace std;
#include <stack>
#include <string>
#include <string.h>
#include <queue>


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) 
    {
        vector<vector<int>> res;
        if(!root)
        {
            return res;
        }
        /* 程序执行到这个地方 就不是空树 */
        queue<TreeNode *> myqueue;
        /* 1.根结点入队 */
        myqueue.push(root);
        
        TreeNode *frontNode = NULL;
        /* 每一层结点的数量 */
        int levelSize = 0;
        while(!myqueue.empty())
        {
            /* 每一层的结点的数组 */
            vector<int> levelVector;

            /* 每一层结点的数量 */
            levelSize = myqueue.size();

            for (int idx = 0; idx < levelSize; idx++)
            {
                frontNode = myqueue.front();
                levelVector.push_back(frontNode->val);
                myqueue.pop();
                
                /* 左子树不为空 */
                if(frontNode->left != NULL)
                {
                    myqueue.push(frontNode->left);
                }

                /* 右子树不为空 */
                if(frontNode->right != NULL)
                {
                    myqueue.push(frontNode->right);
                }
            }
            res.push_back(levelVector);
        }
        return res;
    }
};
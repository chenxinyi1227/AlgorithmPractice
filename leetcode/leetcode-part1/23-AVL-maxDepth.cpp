#include <iostream>
using namespace std;
/* 最大深度 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};

class Solution {
public:
    int maxDepth(TreeNode* root) {

        // 如果 root 为空，直接返回 0
        if(root == NULL) return 0;

        // 递归调用 maxDepth，求出当前节点的左子树的最大深度
        int left = maxDepth(root->left);

        // 递归调用 maxDepth，求出当前节点的右子树的最大深度
        int right = maxDepth(root->right);

        // 求出当前节点的左右子树中较大的值
        int childMaxDepth = max(left,right);

        // 二叉树的最大深度就是它的左右子树中较大的值加上 1
        return childMaxDepth + 1;
    }
};


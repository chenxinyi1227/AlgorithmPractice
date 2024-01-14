#include "balanceBinarySearchTree.h"
#include "doubleLinkListQueue.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* 状态码 */
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS  //非法访问
};

/* 宏函数 */
#define ISNULL(pList)       \
do{                         \
    if(pList == NULL)       \
    {                       \
        return NULL_PTR;    \
    }                       \
   }while(0);

#define ISVALID(pList, pos)         \
do{                                 \
    if(pos < 0 || pos > pList->len) \
    {                               \
        return INVALID_ACCESS;      \
    }                               \
}while(0);

#define ISVALID2(pList, pos)         \
do{                                 \
    if(pos <= 0 || pos > pList->len) \
    {                               \
        return INVALID_ACCESS;      \
    }                               \
}while(0);

#define ISMALLOC(pList)             \
do {                               \
    if(pList == NULL)               \
    {                               \
        printf("内存分配失败!\n");   \
        return MALLOC_ERROR;        \
    }                               \
 }while(0);

#define true 1
#define false 0

/* 创建节点 */
static AVLTreeNode *createAVLTreeNewNode(ELEMENTTYPE val, AVLTreeNode *parentNode);
/* 根据指定的值获取二叉搜索树的结点  */
static AVLTreeNode * baseAppointValGetBSTreeNode(balanceBinarySearchTree *pAvltree, ELEMENTTYPE val);
/* 二叉搜索树删除指定的结点 */
static int balanceBinarySearchTreeDeleteNode(balanceBinarySearchTree *pAvltree, AVLTreeNode *node);
/* 判断二叉搜索树度为2 */
static int balanceBinarySearchTreeNodeHasTwochilds(AVLTreeNode *node);
/* 判断二叉搜索树度为1 */
static int balanceBinarySearchTreeNodeHasOnechilds(AVLTreeNode *node);
/* 判断二叉搜索树度为0 */
static int balanceBinarySearchTreeNodeIsLeft(AVLTreeNode *node);
/* 前序遍历 */
static int preOrderTraverse(balanceBinarySearchTree *pAvltree, AVLTreeNode *node);
/* 中序遍历 */
static int midOrderTraverse(balanceBinarySearchTree *pAvltree, AVLTreeNode *node);
/* 后序遍历*/
static int posOrderTree(balanceBinarySearchTree *pAvltree, AVLTreeNode *node);
/* 获取当前结点的的前驱结点 */
static AVLTreeNode *bstreeNodePreDecessor(AVLTreeNode *node);
/* 获取当前结点的的后驱结点 */
static AVLTreeNode *bstreeNodeSucDecessor(AVLTreeNode *node);
/* 添加结点之后的操作 */
static int insertNodeAfter(balanceBinarySearchTree *pAvltree, AVLTreeNode *node);
/* 更新结点高度 */
static int AVLTreeNodeUpdateHeight(AVLTreeNode *node);
/* 添加结点之后的操作 */
static int insertNodeAfter(balanceBinarySearchTree *pAvltree, AVLTreeNode *node);
/* 删除结点之后要做的事 */
static int removeNodeAfter(balanceBinarySearchTree *pAvltree, AVLTreeNode *node);
/* 计算结点的平衡因子 */
static int AVLTreeNodeIsBalanceFactor(AVLTreeNode *node);
/* 判断结果是否平衡 */
static int AVLTreeNodeIsBalanced(AVLTreeNode *node);
/* AVL树调整结点平衡 */
static int AVLTreeNodeAdjustBalance(balanceBinarySearchTree *pAvltree, AVLTreeNode *node);
/* 获取AVL结点较高的子结点 */
static AVLTreeNode *AVLTreeNodeGetChildTaller(AVLTreeNode *node);
/* 当前结点是父节点的左子树 */
static int AVLTreeCurrentNodeIsLeft(AVLTreeNode *node);
/* 当前结点是父节点的左子树 */
static int AVLTreeCurrentNodeIsRight(AVLTreeNode *node);
/* LL 左旋 */
static int AVLTreeCurrentNodeRotateLeft(balanceBinarySearchTree *pAvltree, AVLTreeNode *grand);
/* LL 右旋 */
static int AVLTreeCurrentNodeRotateRight(balanceBinarySearchTree *pAvltree, AVLTreeNode *grand);
/* 维护父结点 */
static int AVLTreeNodeRotate(balanceBinarySearchTree *pAvltree,AVLTreeNode *grand, AVLTreeNode *parent,AVLTreeNode *child);

/* 创建节点 */
static AVLTreeNode *createAVLTreeNewNode(ELEMENTTYPE val, AVLTreeNode *parentNode)
{
    AVLTreeNode * newAVLNode = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));
    ISMALLOC(newAVLNode);
    memset(newAVLNode, 0, sizeof(AVLTreeNode));
    /* 初始化结点 */
    newAVLNode->data = val;
    newAVLNode->height = 1;//结点的高度
    newAVLNode->left = NULL;
    newAVLNode->right = NULL;
    newAVLNode->parent = parentNode;

    return newAVLNode;
}

/* 二叉搜索树的初始化 */
int balanceBinarySearchTreeInit(balanceBinarySearchTree **pAvltree, int(*cpmpareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*visit)(ELEMENTTYPE val))
{
    int ret = 0;
    ISNULL(pAvltree);
    balanceBinarySearchTree *Avltree;
    ISMALLOC(Avltree);
    memset(Avltree, 0, sizeof(balanceBinarySearchTree));

    /* 初始化树 */
    {
        Avltree->root = NULL;
        Avltree->size = 0;//？？？
        Avltree->cpmpareFunc = cpmpareFunc;
        Avltree->visit = visit;
    }
    
#if 0
    Avltree->root = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
    ISMALLOC(Avltree->root);

    Avltree->root->data = 0;
    Avltree->root->height = 1;
    Avltree->root->left = NULL;
    Avltree->root->right = NULL;
    Avltree->root->parent = NULL;
#endif
    Avltree->root = createAVLTreeNewNode(0, NULL);//根结点的父节点为NULL

    *pAvltree = Avltree;
    return ret;
}

/* 计算结点的平衡因子 */
static int AVLTreeNodeIsBalanceFactor(AVLTreeNode *node)
{
    /* 左子树高度 */
    int leftHeight = node->left == NULL ? 0 : node->left->height;
    /* 右子树高度 */
    int rightHeight = node->right == NULL ? 0 : node->right->height;
    return leftHeight - rightHeight;
}
/* 判断是否平衡 
平衡条件：左右子树高度相差的绝对值不超过1*/
static int AVLTreeNodeIsBalanced(AVLTreeNode *node)
{
    int cmp = abs(AVLTreeNodeIsBalanceFactor(node));
    if(cmp <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/* 两数的最大值 ：高度沿最长的分支增加*/
static int tmpMax(int val1, int val2)
{
    return val1 - val2 >= 0 ? val1 : val2;
}
/* 更新高度 */
static int AVLTreeNodeUpdateHeight(AVLTreeNode *node)
{
    int ret = 0;
    /* 左子树高度 */
    int leftHeight = node->left == NULL ? 0 : node->left->height;
    /* 右子树高度 */
    int rightHeight = node->right == NULL ? 0 : node->right->height;

    /* 高度沿最长的分支增加 */
    node->height = 1 + tmpMax(leftHeight, rightHeight);
    return ret;
}

/* 调整平衡 */
static int AVLTreeNodeAdjustBalance(balanceBinarySearchTree *pAvltree, AVLTreeNode *node)
{
    
}

/* 添加结点之后的操作
    *新添加的结点一定是叶子结点
    1、树的高度
    2、调整平衡 **/
static int insertNodeAfter(balanceBinarySearchTree *pAvltree, AVLTreeNode *node)
{
    int ret = 0;
    while((node = node->parent) != NULL)//
    {
        if(AVLTreeNodeIsBalanced(node))//节点平衡
        {
            AVLTreeNodeUpdateHeight(node);//1:更新高度
        }
        else
        {
            AVLTreeNodeAdjustBalance(pAvltree, node);//2、调整平衡
        }
    }
    return ret;
}

/* 二叉搜索树的插入 */
int balanceBinarySearchTreeInsert(balanceBinarySearchTree *pAvltree, ELEMENTTYPE val)
{
    int ret = 0;
    /* 空树情况 */
    if(pAvltree->size == 0)
    {
        pAvltree->root->data = val;
        pAvltree->size++;//更新结点数量
        insertNodeAfter(pAvltree, pAvltree->root);//添加结点之后的操作
    }

    /* 1、程序运行到这里根结点已经赋值，结点数量为1
    2、接下来考虑新节点挂到根结点的左右哪个子树上 */
    AVLTreeNode * travelNode  = pAvltree->root;//遍历节点
    AVLTreeNode * parentNode  = pAvltree->root;//父结点
    
    int cmp = pAvltree->cpmpareFunc(val, pAvltree->root->data);
    if(travelNode != NULL)
    {
        /* 标记父结点 */
        parentNode = travelNode;//在循环中更新父结点
        cmp = pAvltree->cpmpareFunc(val, travelNode->data);//?parentNode : 挂子树时使用
        
        if(cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if(cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            return ret;
        }
    }
    AVLTreeNode * newAVLNode  = createAVLTreeNewNode(val, parentNode);
    if(newAVLNode = travelNode->left)
    {
        parentNode->left = newAVLNode;
    }
    else if(newAVLNode = travelNode->right)
    {
        parentNode->right = newAVLNode;
    }
    /* 添加之后的调整：
    1、树的高度
    2、调整平衡
    3、节点数量 */
    insertNodeAfter(pAvltree, newAVLNode);

    pAvltree->size++;//更新结点数量
    return ret;
}

/* 二叉搜索树是否包含指定元素 */
int balanceBinarySearchTreeIsContainAppointVal(balanceBinarySearchTree *pAvltree, ELEMENTTYPE val)
{

}

/* 前序遍历：根结点->左子树->右子树 */

static int preOrderTraverse(balanceBinarySearchTree *pAvltree, AVLTreeNode *node)
{
    int ret = 0;
    ISNULL(pAvltree);
    pAvltree->visit(node->data);
    preOrderTraverse(pAvltree,node->left);
    preOrderTraverse(pAvltree,node->right);
    return ret;
}

/* 二叉树先序遍历 */
int balanceBinarySearchTreePreOrderTraverse(balanceBinarySearchTree *pAvltree)
{
    int ret = 0;
    return preOrderTraverse(pAvltree,  pAvltree->root);
    return ret;

}

/* 二叉树中序遍历 */
int balanceBinarySearchTreeMidOrderTraverse(balanceBinarySearchTree *pAvltree)
{

}

/* 二叉树后序遍历 */
int balanceBinarySearchTreePosOrderTraverse(balanceBinarySearchTree *pAvltree)
{

}

/* 二叉树层序遍历 */
int balanceBinarySearchTreeLevelOrderTraverse(balanceBinarySearchTree *pAvltree)
{
    int ret = 0;
    ISNULL(pAvltree);
    doubleLinkListQueue * AVLqueue = NULL;
    doubleLinkListQueueInit(&AVLqueue);//取地址&

    doubleLinkListQueuePush(AVLqueue, pAvltree->root);

    //nodeVal接队头元素
    AVLTreeNode * nodeVal = NULL;
    /* 当队列不为空 */
    while(!doubleLinkListQueueIsEmpty(AVLqueue))
    {
        /* (void**)val 结点入队 */
        doubleLinkListQueueTop(AVLqueue, (void**)&nodeVal);//travelNode->data 
        pAvltree->visit(nodeVal->data);
        doubleLinkListQueuePop(AVLqueue);
        if(nodeVal->left)//左子树入队
        {
            doubleLinkListQueuePush(AVLqueue, nodeVal->left);//nodeVal->right->data
        }
        if(nodeVal->right)
        {
            doubleLinkListQueuePush(AVLqueue, nodeVal->right);//结点入队
        }
    }
    doubleLinkListQueueDestroy(AVLqueue);
    return ret;
}

/* 获取二叉搜索树的节点个数 */
int balanceBinarySearchTreeGetNodeSize(balanceBinarySearchTree *pAvltree, int *pSize)
{
    ISNULL(pAvltree);
    if(pSize)
    {
        *pSize = pAvltree->size;
    }
    return pAvltree->size;
}

/* 获取二叉树的高度:需要记录每一层的结点树->每一层的节点数技术完成，就是树的高度加1 */
int balanceBinarySearchTreeGetHeight(balanceBinarySearchTree *pAvltree, int *pHeight)
{
    
}

/* 二叉树的删除 */
int balanceBinarySearchTreeDelete(balanceBinarySearchTree *pAvltree, ELEMENTTYPE val);

/* 二叉树的销毁 */
int balanceBinarySearchTreeDestroy(balanceBinarySearchTree *pAvltree);

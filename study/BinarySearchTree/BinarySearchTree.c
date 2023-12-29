#include "BinarySearchTree.h"
#include "doubleLinkListQueue.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS  //非法访问
};
/* 静态函数前置声明 */
#if 0
static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2);
static int visit(BSTreeNode *parentNode);
#endif
static BSTreeNode *createBSTreeNewNode(ELEMENTTYPE val, BSTreeNode *parentNode);
static BSTreeNode * baseAppointValGetBSTreeNode(binarySearchTree *pBstree, ELEMENTTYPE val);
static int binarySearchTreeDeleteNode(binarySearchTree *pBstree, BSTreeNode *node);
/* 判断二叉搜索树度为2 */
static int binarySearchTreeNodeHasTwochilds(BSTreeNode *node);
/* 判断二叉搜索树度为1 */
static int binarySearchTreeNodeHasOnechilds(BSTreeNode *node);
/* 判断二叉搜索树度为0 */
static int binarySearchTreeNodeIsLeft(BSTreeNode *node);
/* 前序遍历 */
static int preOrderTraverse(binarySearchTree *pAvltree, BSTreeNode *node);
/* 中序遍历 */
static int midOrderTraverse(binarySearchTree *pAvltree, BSTreeNode *node);
/* 后序遍历*/
static int posOrderTree(binarySearchTree *pAvltree, BSTreeNode *node);
/* 获取当前结点的的前驱结点 */
static BSTreeNode *bstreeNodePreDecessor(BSTreeNode *node);
/* 获取当前结点的的后驱结点 */
static BSTreeNode *bstreeNodeSucDecessor(BSTreeNode *node);

/* 二叉搜索树的初始化 */
int binarysearchTreeInit(binarySearchTree **pBstree, int(*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*visit)(ELEMENTTYPE val))
{
    int ret = 0;
    binarySearchTree * bstree = (binarySearchTree *)malloc(sizeof(binarySearchTree));
    if(bstree == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(bstree, 0, sizeof(bstree));//清除脏数据
    /* 初始化树 */
    {
        bstree->root = NULL;
        bstree->size = 0;
        /* 钩子函数在这边赋值 */
        bstree->cpmpareFunc = compareFunc;
        bstree->visit = visit;
    }
    #if 0
    /* 分配根结点 */
    bstree->root = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    if(bstree->root = NULL)
    {
        return MALLOC_ERROR;
    }
    memset(bstree->root, 0, sizeof(BSTreeNode));
 
    /* 初始化根结点 */
    {
        bstree->root->data = 0;
        bstree->root->left = NULL;
        bstree->root->right = NULL;
        bstree->root->parent = NULL;
    }
       #endif
    #if 0
    doubleLinkListQueueInit(&(bstree->pQueue));
    #endif
    bstree->root = createBSTreeNewNode(0, NULL);//根结点的父节点为NULL
    *pBstree = bstree;
}
#if 0
static compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2)
{
    return val1 - val2;
}
#endif

/* 判断二叉搜索树度为2 */
static int binarySearchTreeNodeHasTwochilds(BSTreeNode *node)
{
    return node->left != NULL && node->right != NULL;
}
/* 判断二叉搜索树度为1 */
static int binarySearchTreeNodeHasOnechilds(BSTreeNode *node)
{
    return ((node->left != NULL) && (node->right != NULL)) || ((node->left != NULL) && (node->right == NULL));
}
/* 判断二叉搜索树度为0 */
static int binarySearchTreeNodeIsLeft(BSTreeNode *node)
{
    return (node->left == NULL) && (node->right == NULL);
}

/* 获取当前结点的的前驱结点 */
/* 中序遍历到节点的前一个结点 */
static BSTreeNode *bstreeNodePreDecessor(BSTreeNode *node)
{
    if(node->left != NULL)
    {
        /* 前驱节点是在左子树的右子树上... */
        BSTreeNode * travelNode = node->left;
        while(travelNode->right != NULL)
        {
            travelNode = travelNode->right;
        }
        return travelNode;
    }
    /* 程序到这个地方 说明一定没有左子树，那就需要向父结点找 */
    while(node->parent != NULL && node == node->parent->left)
    {
        node = node->parent;
    }
    /* node->parent == NULL
       node == node->parent->right */
    return node->parent;
}
/* 获取当前结点的的后继结点 */
static BSTreeNode *bstreeNodeSucDecessor(BSTreeNode *node)
{
    if(node->right != NULL)
    {
        /* 前驱节点是在右子树的左子树的左子树的左子树上... */
        BSTreeNode * travelNode = node->right;
        while(travelNode->left != NULL)
        {
            travelNode = travelNode->left;
        }
        return travelNode;
    }
    /* 程序到这个地方 说明一定没有右子树，那就需要向父结点找 */
    while(node->parent != NULL && node == node->parent->right)
    {
        node = node->parent;
    }
    /* node->parent == NULL
       node == node->parent->left */
    return node->parent;
}

static BSTreeNode *createBSTreeNewNode(ELEMENTTYPE val, BSTreeNode *parentNode)//在上一个父节点后添加节点
{
    BSTreeNode *newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    if(newBstNode == NULL)
    {
        return NULL;//no malloc error!
    }
    memset(newBstNode, 0, sizeof(BSTreeNode));

    /* 初始化根结点 */
    {
        newBstNode->data = 0;
        newBstNode->left = NULL;
        newBstNode->right = NULL;
        newBstNode->parent = NULL;
    }
    newBstNode->data = val;
    newBstNode->parent = parentNode;
    return newBstNode;
}

/* 二叉搜索树的插入 */
int binarysearchTreeInsert(binarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    if(pBstree->size == 0)//空树
    {
        pBstree->size++;//更新树的结点
        pBstree->root->data = val;
        return ret;
    }
    /* travelNode 指向根结点 */
    BSTreeNode * travelNode = pBstree->root;
    BSTreeNode * parentNode = pBstree->root;

    int cmp = 0;/* 确定符号：到底放在在左边还是右边 */
    while(travelNode != NULL)
    {
        parentNode = travelNode;/* 标记父结点 */
        cmp = pBstree->cpmpareFunc(val, travelNode->data);//结构体内的比较函数

        if(cmp < 0) /* 插入元素 < 遍历到的节点  左子树 */
        {
            travelNode = travelNode->left;
        }
        else if(cmp > 0)/* 插入元素 > 遍历到的节点 右子树 */ 
        {
            travelNode = travelNode->right;
        }
        else    /* 插入元素 = 遍历到的节点 右子树 */ 
        {   
            return ret;
        }
    }

 #if 0
    /* 分配根结点 */
    BSTreeNode * newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    if(newBstNode = NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newBstNode, 0, sizeof(BSTreeNode));
    /* 初始化根结点 */
    {
        newBstNode->data = 0;
        newBstNode->left = NULL;
        newBstNode->right = NULL;
        newBstNode->parent = NULL;
    }
#endif
    BSTreeNode * newBstNode = createBSTreeNewNode(val, parentNode);
    /* 挂在左子树 */
    if(cmp < 0)
    {
        parentNode->left = newBstNode;
    }
    else/* 挂在右子树 */
    {
        parentNode->right = newBstNode;
    }
#if 0
    /* 新节点的parent指针赋值 */
    newBstNode->parent = parentNode;
#endif
    pBstree->size++;
    return ret;
}
/* 根据指定的值获取二叉搜索树的节点 */
static BSTreeNode * baseAppointValGetBSTreeNode(binarySearchTree *pBstree,ELEMENTTYPE val)
{
    BSTreeNode *travelNode = pBstree->root;
    int cmp = 0;
    while(travelNode != NULL)
    {
        cmp = pBstree->cpmpareFunc(val, travelNode->data);
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
            return travelNode;//找到了
        }
    }
    return NULL;
}

/* 二叉搜索树是否包含指定元素 */
int binarySearchTreeIsContainAppointVal(binarySearchTree *pBstree, ELEMENTTYPE val)
{
    return baseAppointValGetBSTreeNode(pBstree, val) == NULL ? 0 : 1;
}

/* 前序遍历：根结点->左子树->右子树 */
static int preOrderTraverse(binarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if(node == NULL)
    {
        return ret;
    }
    /* 根结点 */
    pBstree->visit(node->data);
    /* 左子树 */
    preOrderTraverse(pBstree, node->left);
    /* 右子树 */
    preOrderTraverse(pBstree, node->right);
}

/* 二叉树前序遍历 */
int binarySearchTreePreOrderTraverse(binarySearchTree *pBstree)
{
    int ret = 0;
    preOrderTraverse(pBstree, pBstree->root);
    return ret;
}

/* 中序遍历:左子树->根结点->右子树 */
static int midOrderTraverse(binarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if(node == NULL)
    {
        return ret;
    }
    /* 左子树 */
    midOrderTraverse(pBstree, node->left);
    /* 根结点 */
    pBstree->visit(node->data);
    /* 右子树 */
    midOrderTraverse(pBstree, node->right);
}

/* 二叉树中序遍历 */
int binarySearchTreeMidOrderTraverse(binarySearchTree *pBstree)
{
    int ret = 0;
    midOrderTraverse(pBstree, pBstree->root);
    return ret;
}

/* 后序遍历 :左子树->右子树->根结点*/
static int posOrderTree(binarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if(node == NULL)
    {
        return ret;
    }
    /* 左子树 */
    posOrderTree(pBstree, node->left);
    /* 右子树 */
    posOrderTree(pBstree, node->right);
    /* 根结点 */
    pBstree->visit(node->data);
}

/* 二叉树后序遍历 */
int binarySearchTreePosOrderTraverse(binarySearchTree *pBstree)
{
    int ret = 0;
    posOrderTree(pBstree, pBstree->root);
    return ret;
}

/* 二叉树层序遍历*/
int binarySearchTreeLevelOrderTraverse(binarySearchTree *pBstree)
{
    int ret = 0;
    /*算法: 使用队列 
        1. 将根结点入队
        2. 循环执行以下操作, 直到队列为空
            2.1 将队头结点(A)出队,并访问
            2.2 将(A)的左子节点入队
            2.3 将(A)的右子节点入队
    */
   doubleLinkListQueue *pQueue = NULL;
   doubleLinkListQueueInit(&pQueue);
   doubleLinkListQueuePush(pQueue, pBstree->root);
   BSTreeNode *valNode = NULL;//树节点

   while(!doubleLinkListQueueIsEmpty(pQueue))
   {
        doubleLinkListQueueTop(pQueue, (void **)valNode);
        pBstree->visit(valNode->data);
        doubleLinkListQueuePop(valNode);

        if(valNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, valNode->left);
        }
        if(valNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, valNode->right);
        }
   }
   doubleLinkListQueueDestroy(pQueue);

    return ret;
}

/* 获取二叉搜索树的节点个数 */
int binarySearchTreeGetNodeSize(binarySearchTree *pBstree, int *pSize)
{
    if(pBstree == NULL)
    {
        return 0;
    }
    
    if(pSize)
    {
        *pSize = pBstree->size;
    }
    return pBstree->size;
}

/* 获取二叉树的高度 */
int binarySearchTreeGetHeight(binarySearchTree *pBstree, int *pHeight)
{
    int ret = 0;
    if(pBstree == NULL)
    {
        return NULL_PTR;//应该返回0
    }
    
    if(pBstree->size == 0)//空树
    {
        return 0;
    }
    doubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);
    doubleLinkListQueuePush(pQueue, pBstree->root);//入队 节点
    int height= 0;//树的高度 （根结点入队高度为）
    int levelSize = 1; //树每一层的节点数量
    BSTreeNode *travelNode = NULL;
    while(!doubleLinkListQueueIsEmpty(pQueue))//
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);
        doubleLinkListQueuePop(pQueue);
        levelSize--;

        /* 左子树不为空 */
        if(travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }
        /* 右子树不为空 */
        if(travelNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue,travelNode->right);
        }
        /* 树的当前节点遍历结束 */
        if(levelSize == 0)
        {
            height++;
            doubleLinkListQueueGetSize(pQueue, &levelSize);
        }
    }
    *pHeight = height;//解引用
    /* 释放队列 */
    doubleLinkListQueueDestroy(pQueue);
    return ret;
}

/* 删除节点 */
static int binarySearchTreeDeleteNode(binarySearchTree *pBstree, BSTreeNode *node)
{
/* 算法
 * 删除度为0的结点: 要么是叶子结点,要么是只有唯一一个结点的树。这种情况下直接释放free结点即可
 * 删除度为1的结点: 
 *      当要删除的结点有父结点的时候,修改要删除结点的父结点和子结点的指向关系,再释放free结点.
 *      当要删除的结点没有父结点的时候, 直接改变根结点的指向即可。
 * 删除度为2的结点:
 *      找到前驱结点和后继结点,前驱结点或者后继结点的值替换掉当前要删除结点的值
 *      再删除前驱结点或者后继结点。(度为2结点的前驱结点或者后继结点的度一定是1或者0)
 *      再按照上面删除度为0还是度为1的逻辑操作即可.
 * */ 
    int ret = 0;
    if(node == NULL)
    {
        return ret;
    }

    /* 树的结点减一 */
    pBstree->size--;

    if(binarySearchTreeNodeHasTwochilds(node))
    {
        BSTreeNode * preNode = bstreeNodePreDecessor(node);//找到前驱结点
        node->data = preNode->data;
        node = preNode;//node是要删除的结点
    }
    /* 程序执行到这里，要么是度为1要么是度为0 */
    #if 0
    if(binarySearchTreeNodeHasOnechilds(node))
    {
        BSTreeNode * preNode = bstreeNodePreDecessor(node);
        node->data = preNode->data;
        node = preNode;
    }
    if(binarySearchTreeNodeIsLeft(node))
    {
        if(node->data == node->parent->left)
        {
            node->parent->left = NULL;
        }
        else
        {
            node->parent->right = NULL;
        }   
    }
#endif
    /* 假设nod结点是度为1，他的child 要没事是左要么是右 */
    /* 假设node的结点是度为0的 */
    BSTreeNode * child =node->left != NULL ? node->left : node->right;

    BSTreeNode * delNode = NULL;
    if(child)
    {
        /* 度为1 */
        child->parent = node->parent; 
        if(node->parent == NULL)
        {
            /* 它是根结点 */
            pBstree->root = child;
            delNode = node;
        }
        else
        {
            if(node == node->parent->left)
            {
                node->parent->left = child;
            }
            else if(node == node->parent->right)
            {
                node->parent->right = child;
            }
            /* 释放节点 */
            delNode = node;
            #if 0
            if(node)
            {
                free(node);
                node= NULL;
            }
            #endif
        }   
    }
    else
    {
        /* 度为0 */
        if(node->parent == NULL)
        {
            delNode = node;
            #if 0
            if(node)
            {
                free(node);
                node = NULL;
            } 
            #endif
        }
        else
        {
            if(node == node->parent->left)
            {
                node->parent->left = NULL;
            }
            else
            {
                node->parent->right = NULL;
            }
            delNode = node;
            #if 0
            if(node)
            {
                free(node);
                node = NULL;
            }  
            #endif
        }   
    }
    if(delNode)
    {
        free(delNode);
        delNode = NULL;
    }
    return ret;
}

/* 二叉树的删除 */
int binarySearchTreeDelete(binarySearchTree *pBstree, ELEMENTTYPE val)
{
    /* 算法：
    度为2 结点的前驱/后继 结点的度一定为1和0
    删除度为2的结点
    1、找到前驱/后继结点的值
    2、复制前驱结点的value 到 要删除的节点
    3、删除前驱/后继结点*/  
    /*
    删除度为2的结点
    1、找到前驱结点的值
    2、复制前驱结点的value 到 要删除的结点
    3、删除前驱结点
    删除度为0的结点：
    直接删除结点，并且将父节点的指针（left/right)置为NULL
    删除度为1的结点：
    说明一定有孩子(要么是left要么是right)
    1、让孩子的parent指针指向delNode->parent
    2、然delNode->parent(left/right)指向delNode的孩子
    */
    int ret= 0;
    #if 0
    BSTreeNode *delNode = baseAppointValGetBSTreeNode(pBstree,val);
    binarySearchTreeDeleteNode(pBstree, delNode);
    #else
    return binarySearchTreeDeleteNode(pBstree, baseAppointValGetBSTreeNode(pBstree,val));
    #endif
    return ret;
}

/* 二叉树的销毁 */
int binarySearchTreeDestroy(binarySearchTree *pBstree)
{
    int ret = 0;
    if(pBstree == NULL)
    {
        return NULL_PTR;
    }
    doubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);
    /* 将根结点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);
    BSTreeNode * travelNode = NULL;
    while(!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);
        doubleLinkListQueuePop(pQueue);

        if(travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }

        if(travelNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->right);
        }
        /* 最后释放 */
         if(travelNode)
        {
            free(travelNode);
            travelNode = NULL;
        }
    }  
    /* 释放队列 */
    doubleLinkListQueueDestroy(pQueue);
    /* 释放树 */
    if(pBstree)
    {
        free(pBstree);
        pBstree = NULL;
    }
    return ret;
}
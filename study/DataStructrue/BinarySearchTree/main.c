#include "BinarySearchTree.h"
#include <stdio.h>
#define BUFFER_SIZE 5

/* 测试二叉搜索树 */
int compareBasicFunc(void * arg1, void * arg2)
{
    int val1 = *(int *)arg1;
    int val2 = *(int *)arg2;
    return val1 - val2;
}

/* 打印基础数据 */
int printBasicData(void *arg)
{
    int ret = 0;
    int val = *(int *)arg;
    printf("val:%d\t", val);
    return ret;
}
int main()
{
    binarySearchTree * BST;
    binarysearchTreeInit(&BST, compareBasicFunc, printBasicData);
    int buffer[BUFFER_SIZE] = {56, 28, 75, 73, 77};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        binarysearchTreeInsert(BST, (void *)&buffer[idx]);
    }
    /* 获取二叉搜索树的节点个数 */
    int size = 0;
    binarySearchTreeGetNodeSize(BST, &size);
    printf("size:%d\n", size);

    /* 获取二叉搜索树的高度 */
    int height = 0;
    binarySearchTreeGetHeight(BST,&height);
    printf("height:%d\n", height);
    
    /* 中序遍历 */
    printf("中序遍历\n");
    binarySearchTreeMidOrderTraverse(BST);
    printf("\n");
    /* 层序遍历 */
    printf("层序遍历\n");
    binarySearchTreeLevelOrderTraverse(BST);
    printf("\n");

{
    /* 删除度为2 */
    int delVal = 56;
    binarySearchTreeDelete(BST, &delVal);
    printf("\n");

    /* 获取二叉搜索树的节点个数 */
    int size = 0;
    binarySearchTreeGetNodeSize(BST, &size);
    printf("size:%d\n", size);

    /* 获取二叉搜索树的高度 */
    int height = 0;
    binarySearchTreeGetHeight(BST,&height);
    printf("height:%d\n", height);

     /* 层序遍历 */
    printf("层序遍历\n");
    binarySearchTreeLevelOrderTraverse(BST);
    printf("\n");
}


    
    return 0;
}
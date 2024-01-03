#include "balanceBinarySearchTree.h"
#include <stdio.h>
#define BUFFER_SIZE 3

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
    balanceBinarySearchTree * AVL;
    balanceBinarySearchTreeInit(&AVL, compareBasicFunc, printBasicData);
    int buffer[BUFFER_SIZE] = {11, 22, 33};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        balanceBinarySearchTreeInsert(AVL, (void *)&buffer[idx]);
    }
    /* 获取二叉搜索树的节点个数 */
    int size = 0;
    balanceBinarySearchTreeGetNodeSize(AVL, &size);
    printf("size:%d\n", size);

    /* 获取二叉搜索树的高度 */
    int height = 0;
    balanceBinarySearchTreeGetHeight(AVL,&height);
    printf("height:%d\n", height);

 /* 层序遍历 */
    printf("层序遍历\n");
    balanceBinarySearchTreeLevelOrderTraverse(AVL);
    printf("\n");
    int val = 21;
    int fd= balanceBinarySearchTreeIsContainAppointVal(AVL, (void *)&val);
    if(fd)
    {
        printf("true\n");
    }
    else
    {
         printf("true\n");
    }
#if 0
    /* 中序遍历 */
    printf("中序遍历\n");
    balanceBinarySearchTreeMidOrderTraverse(AVL);
    printf("\n");

{
    /* 删除度为2 */
    int delVal = 56;
    balanceBinarySearchTreeDelete(AVL, &delVal);
    printf("\n");

    /* 获取二叉搜索树的节点个数 */
    int size = 0;
    balanceBinarySearchTreeGetNodeSize(AVL, &size);
    printf("size:%d\n", size);

    /* 获取二叉搜索树的高度 */
    int height = 0;
    balanceBinarySearchTreeGetHeight(AVL,&height);
    printf("height:%d\n", height);

     /* 层序遍历 */
    printf("层序遍历\n");
    balanceBinarySearchTreeLevelOrderTraverse(AVL);
    printf("\n");
}
#endif

    
    return 0;
}
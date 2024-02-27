#include <stdio.h>
#include <myAVLTree.h>
#include <string.h>
#include <stdlib.h>
#include <myBSTree.h>

typedef struct STUDENT
{
    char id[10];
    char name[10];
}stu;

int printfData(void *args)
{
    int ret = 0;
    stu *val = (stu *)args;
    printf("id:%s\tname:%s\n", val->id, val->name);
    return ret;
}
int compareFunc(void *arg1, void *arg2)
{
  #if 0
    int num1 = *(int *)arg1;
    int num2 = *(int *)arg2;

    return num1 - num2;
    #endif
    char *str1 = (char *)arg1;
    char *str2 = (char *)arg2;

    return strcmp(str1, str2);
}

int main()
{
    #if 1
    AVLTree *myAvl;
    AVLTreeInit(&myAvl, compareFunc, printfData);

    stu myStu1, myStu2, myStu3;//结构体变量
    // stu *myStu1, *myStu2, *myStu3;//结构体指针

    memset(&myStu1, 0,sizeof(myStu1));
    memset(&myStu2, 0,sizeof(myStu2));

    strncpy(myStu1.id, "52", strlen("11"));
    strncpy(myStu1.name, "zhangsan", strlen("zhangsan"));

    strncpy(myStu2.id, "22", strlen("22"));
    strncpy(myStu2.name, "lisi", strlen("lisi"));

    strncpy(myStu3.id, "33", strlen("33"));
    strncpy(myStu3.name, "wangwu", strlen("wangwu"));
    
    printf("id:%s\t姓名:%s\n", myStu1.id, myStu1.name);
    printf("id:%s\t姓名:%s\n", myStu2.id, myStu2.name);
    printf("id:%s\t姓名:%s\n", myStu3.id, myStu3.name);

    AVLTreeInsert(myAvl, (void*)&myStu1);
    AVLTreeInsert(myAvl, (void*)&myStu2);
    AVLTreeInsert(myAvl, (void*)&myStu3);

    AVLTreeMidOrderTraverse(myAvl);
    printf("\n");
    AVLTreeDestroy(myAvl);
    #endif

    doubleLinkList *list = NULL;
    doubleLinkListInit(&list);
    
    
}
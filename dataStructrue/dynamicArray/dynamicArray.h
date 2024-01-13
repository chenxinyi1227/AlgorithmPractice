#ifndef _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_

#define ELEMENTTYPE void *

typedef struct dynamicArray
{
    ELEMENTTYPE *space;
    int len;
    int capacity;
}dyArray;

/* 初始化 */
int dynamicArrayInit(dyArray *pArray, int capacity);

/* 插入 */
int dynamicArrayInsert(dyArray *pArray, ELEMENTTYPE val);

/* 指定位置插入 */
int dynamicArrayInsertByPos(dyArray *pArray, int pos, ELEMENTTYPE val);

/* 更改指定位置数据 */
int ModifydynamicArrayByPos(dyArray *pArray, int pos, ELEMENTTYPE val);

/* 删除数据 */
int dynamicArrayDelElementype(dyArray *pArray);

/* 删除指定位置数据 */
int dynamicArrayDelByPos(dyArray *pArray, int pos);

/* 删除指定元素 */
int dynamicArrayDelByElementype(dyArray *pArray, ELEMENTTYPE val);

/* 销毁 */
int dynamicArrayDestory(dyArray *pArray);

/* 获取大小 */
int dynamicArrayGetSize(dyArray *pArray, int *pSize);

/* 获取容量 */
int dynamicArrayGetCapacity(dyArray *pArray, int *pCapacity);

/* 指定位置的元素数据*/ 
int dynamicArrayGetElementypeByPos(dyArray *pArray, int pos, ELEMENTTYPE *val);

#endif
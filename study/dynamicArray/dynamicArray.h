#ifndef _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_
/* 避免文件重复包含 */

#if 1
#define ELEMENTTYPE void * 
#else
typedef int ELEMENTTYPE;
#endif

typedef struct dynamicArray
{
    ELEMENTTYPE *data;  /* 数组的空间 | 动态数组指针 */
    int len;            /* 数组的大小 | 长度*/
    int capacity;       /* 数组的容量*/
}dynamicArray;

/* API:application program interface */

/* 动态数组的初始化 */
int dynamicArrayInit(dynamicArray *pArray, int capacity);

/* 动态数组插入数据(默认插到数组的末尾) */
int dynamicArrayInsertData(dynamicArray *pArray, ELEMENTTYPE val);

/* 动态数组插入数据，在指定位置插入 */
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, int pos, ELEMENTTYPE val);

/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray *pArray, int pos, ELEMENTTYPE val);

/* 动态数组删除数据 （默认情况下删除最后末尾的数据*/
int dynamicArrayDeleteData(dynamicArray *pArray);

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData(dynamicArray *pArray, int pos);

/* 动态数组删除指定的元素 */
int dynamicArrayDeleteAppointData(dynamicArray *pArray, ELEMENTTYPE val, int(*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2));

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray *pArray);

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize);

/* 获取数组的容量*/
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity);

/* 获取指定位置的元素数据 */
int dynamicArrayGetAppointPosVal(dynamicArray *pArray, int pos, ELEMENTTYPE *pVal);

/* 数组排序 */
int dynamicArrayAppointWaySort(dynamicArray *pArray, int(*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2));

#endif //_DYNAMICARRAY_H_
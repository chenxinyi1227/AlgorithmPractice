#include "common.h"
#ifndef _DOUBLELISTLINK_QUEUE_H_
#define _DOUBLELISTLINK_QUEUE_H_

typedef doubleLinkList doubleLinkListQueue;

/* 队列初始化 */
int doubleLinkListQueueInit(doubleLinkListQueue **pQueue);

/* 队列入队 */
int doubleLinkListQueuePush(doubleLinkListQueue *pQueue, ELEMENTTYPE val);

/* 队头元素 */
int doubleLinkListQueueTop(doubleLinkListQueue *pQueue, ELEMENTTYPE *val);

/* 队尾元素 */
int doubleLinkListQueueRear(doubleLinkListQueue *pQueue, ELEMENTTYPE *val);

/* 队列出列 */
int doubleLinkListQueuePop(doubleLinkListQueue *pQueue);

/* 队列大小 */
int doubleLinkListQueueGetSize(doubleLinkListQueue *pQueue, int *pSize);

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty(doubleLinkListQueue *pQueue);

/* 队列销毁 */
int doubleLinkListQueueDestroy(doubleLinkListQueue *pQueue);
#endif
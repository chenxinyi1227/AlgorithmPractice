#include "threadPoll.h"
#include <stdio.h>
#include <unistd.h>

void * printData(void *arg)
{
    int val = *(int *)arg;
    printf("hello world, val:%d\n", val);
    return NULL;
}
void * printData2(void *arg)
{
    int val = *(int *)arg;
    printf("hello world, val:%d\n", val);
    return NULL;
}

int main()
{
    thread_poll_t poll;
    threadPollInit(&poll, 5, 10, 10);
    int num = 2, num2 = 4;
    threadPollAddTask(&poll, printData, (void*)&num);
    threadPollAddTask(&poll, printData2, (void*)&num2);

    sleep(2);
    threadPollDestroy(&poll);

    return 0;
}
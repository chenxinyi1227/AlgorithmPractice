#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

/* 将线程设置为可分离状态，并在主线程中调用 pthread_detach() 分离线程。
这样做是可以的，但是需要注意以下几点：
线程分离后，无需使用 pthread_join() 函数等待线程结束，也不需要调用 pthread_detach() 函数。
因此，可以将 pthread_join() 和 pthread_detach() 函数的调用去掉。
当主线程结束时，如果其他线程仍在运行，可能会导致这些线程被强制终止而无法正常释放资源。
所以建议在主线程结束前，让其他线程先退出，再进行资源释放。 */

/* 上锁 */
pthread_mutex_t g_mutex;

void *thread_fun_1(void *arg)
{
    int fd = *(int *)arg;
    while(1)
    {

        pthread_mutex_lock(&g_mutex);
        write(fd, "hello", 5);
        write(fd, "nihao", 5);
        write(fd, "\n", 1);
        pthread_mutex_unlock(&g_mutex);
    }
}

void *thread_fun_2(void *arg)
{
    pthread_detach(pthread_self());

    int fd = *(int *)arg;
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        write(fd, "yeliang", strlen("yeliang"));
        write(fd, "****", 4);
        write(fd, "\n", 1);
        pthread_mutex_unlock(&g_mutex);
    }
}

int main()
{
    pthread_mutex_init(&g_mutex, NULL);//初始化锁

    int fd = open("./1.txt", O_RDWR | O_CREAT, 0644);
    if(fd == -1)
    {
        perror("open error");
        exit(-1);
    }
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, thread_fun_1, (void *)&fd);
    pthread_create(&tid2, NULL, thread_fun_2, (void *)&fd);

    
    /* 等待一段时间，让线程运行 */
    sleep(10);


    close(fd);
    return 0;
}
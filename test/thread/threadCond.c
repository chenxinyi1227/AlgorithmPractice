#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>

/* 上锁 */
pthread_mutex_t g_mutex;
int val = 0;
/* 条件变量 */
pthread_cond_t cond;

void *thread_fun_1(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        val++;
        if(val == 5)
        {
            /* 通知thread2打印，并且清零 */
            //pthread_cond_signal(&cond);
            pthread_cond_broadcast(&cond);//广播唤醒所有因为该条件变量睡眠的锁
        }
        pthread_mutex_unlock(&g_mutex);
        sleep(1);
    }
}

void *thread_fun_2(void *arg)
{
    int fd = *(int *)arg;
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        while(val != 5)
        {
            //阻塞睡眠,并且释放已加锁
            pthread_cond_wait(&cond, &g_mutex);
        }
        printf("val = %d\n", val);
        val = 0;
        pthread_mutex_unlock(&g_mutex);
    }
}

int main(int arg, char argv[])
{
    pthread_mutex_init(&g_mutex, NULL);//初始化锁
    pthread_cond_init(&cond, NULL);
    

    int fd = open("./1.txt", O_RDWR | O_CREAT, 0644);
    if(fd == -1)
    {
        perror("open error");
        exit(-1);
    }
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, thread_fun_1, (void *)&fd);
    pthread_create(&tid2, NULL, thread_fun_2, (void *)&fd);

    pthread_detach(tid1);
    pthread_detach(tid2);

    /* 等待一段时间，让线程运行 */
    sleep(5);

    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&cond);
    close(fd);
    return 0;
}
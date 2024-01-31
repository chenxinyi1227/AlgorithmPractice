#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;
pthread_cond_t cond;

void* thread_func(void* arg) 
{
    printf("Thread %d waiting for signal...\n", *((int*)arg));

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex); // 等待条件变量的信号
    pthread_mutex_unlock(&mutex);
    
    printf("Thread %d received signal!\n", *((int*)arg));

    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_args[3] = {1, 2, 3};

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // 创建三个线程
    for (int i = 0; i < 3; i++) 
    {
        pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
    }

    sleep(2); // 等待一段时间，以确保所有线程都在等待信号

    printf("Broadcasting signal...\n");
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cond); // 广播条件变量的信号
    pthread_mutex_unlock(&mutex);

    // 等待所有线程结束
    for (int i = 0; i < 3; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#if 0
char *getTime()
{
    time_t currentTime;
    struct tm *timeinfo;
    /* char timeString[80];输出有错
    这是因为timeString字符数组是在showTime函数的内部定义的局部变量。
    当函数返回时，该数组将被销毁，指向它的指针将成为悬空指针。
    在main函数中，curTime指向timeString数组的地址已经成为悬空指针，所以输出操作会导致未定义行为。
    为了解决这个问题，可以将timeString数组声明为静态变量或者动态分配内存：（main里要释放） */
    #if 0
    char *timeString = (char *)malloc(sizeof(char) * 80);
     strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    #else
    /*将timeString数组声明为静态变量, 使其存储在静态存储区，在函数返回后仍然有效 */
    static char timeString[80];//将timeString改为静态变量
    #endif

    //获取当前时间
    time(&currentTime);
    timeinfo = localtime(&currentTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);
    return timeString;
}
#endif

char *getTime()
{
    time_t currentTime;
    struct tm *timeinfo;
    static char timeString[80] = {0};//将timeString改为静态变量
    time(&currentTime);  //获取当前时间
    timeinfo = localtime(&currentTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);
    return timeString;
}

int main()
{
    char *curTime = getTime();
    char name[6] = "nihao";
    printf("%s \033[1;47m %s \033[0m\n", curTime, name);//白色背景
    printf("%s \033[1;32m %s \033[0m\n", curTime, name);//红色文本

}
/* 在C语言中，可以使用ANSI控制字符来输出带有高亮效果的文本。常用的ANSI控制字符包括`\033[`、`m`和数字等。
 */
#include <stdio.h>
#include <unistd.h>

int main(){
    #if 1
    printf("\033[1;31m这是红色的文本。\033[0m\n"); // 红色字体
    printf("\033[1;32m这是绿色的文本。\033[0m\n"); // 绿色字体
    printf("\033[1;33m这是黄色的文本。\033[0m\n"); // 黄色字体
    printf("\033[1;34m这是蓝色的文本。\033[0m\n"); // 蓝色字体
    printf("\033[1;35m这是紫色的文本。\033[0m\n"); // 紫色字体
    printf("\033[1;36m这是青色的文本。\033[0m\n"); // 青色字体
    printf("\033[1;37m这是白色的文本。\033[0m\n"); // 白色字体

    printf("\033[1;41m这是红色背景的文本。\033[0m\n"); // 红色背景
    printf("\033[1;42m这是绿色背景的文本。\033[0m\n"); // 绿色背景
    printf("\033[1;43m这是黄色背景的文本。\033[0m\n"); // 黄色背景
    printf("\033[1;44m这是蓝色背景的文本。\033[0m\n"); // 蓝色背景
    printf("\033[1;45m这是紫色背景的文本。\033[0m\n"); // 紫色背景
    printf("\033[1;46m这是青色背景的文本。\033[0m\n"); // 青色背景
    printf("\033[1;47m这是白色背景的文本。\033[0m\n"); // 白色背景
    #else

    int i;
    for (i = 0; i < 20; i++) {
        // 移动光标位置到第一行第一列
        printf("\033[1;1H");
        // 输出高亮块
        printf("\033[1;7m");
        printf(" ");
        // 休眠一段时间
        usleep(1020);
    }
    // 重置高亮选项
    printf("\033[0m");
    #endif
    return 0;
}



/* 
在上述代码中，`\033[`是ANSI控制字符的起始符号，后面的数字表示不同的颜色和高亮选项，`m`是ANSI控制字符的结束符号。在每个文本输出结束后，需要使用`\033[0m`将高亮选项重置为默认值，以免影响后续的文本输出。

需要注意的是，ANSI控制字符只在支持ANSI控制序列的终端中起作用，如常见的Linux终端、macOS终端等。在Windows环境下，可能需要特定的库或工具才能实现类似的高亮效果。 */
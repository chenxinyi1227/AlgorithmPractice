#include <stdio.h>

int main() 
{
    FILE *file;
    char ch;

    // 打开文件
    file = fopen("col.txt", "a+");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return 1;
    }

    // 设置白色背景
    printf("\033[1;47m");
   

    // 逐字符读取并输出文件内容
    while ((ch = fgetc(file)) != EOF) 
    {
        putchar(ch);
    }

    // 恢复默认文本属性
    printf("\033[0m");
    printf("\n");
    // 关闭文件
    fclose(file);

    return 0;
}

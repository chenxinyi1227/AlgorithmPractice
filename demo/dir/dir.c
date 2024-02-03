#include <stdio.h>
#include <dirent.h>

int main() 
{
    DIR *dir;
    struct dirent *entry;

    // 打开当前目录
    #if 0
    dir = opendir("/home/AlgorithmPractice/AlgorithmPractice/demo/md5/socket");//绝对路径
    #else
    dir = opendir("../md5/socket");//相对路径
    #endif

    if (dir == NULL) 
    {
        printf("无法打开目录\n");
        return 1;
    }

    // 读取目录中的文件列表
    while ((entry = readdir(dir)) != NULL) 
    {
        printf("%s\n", entry->d_name);
    }

    // 关闭目录
    closedir(dir);

    return 0;
}

#include <stdio.h>
#include <string.h>

#define MAX_PATH 1024

//拼接路径
int JoinPath(char *path, const char *dir, const char *filename)
{
    int ret = 0;
    if (path == NULL || dir == NULL || filename == NULL)
    {
        return -1;
    }
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, filename);
    return 0;
}

int main()
{
    char src_path[MAX_PATH] = "/home/AlgorithmPractice/AlgorithmPractice/charRoom/md5/record"; // 源文件路径
    char dest_dir[MAX_PATH] = "server.c"; // 目标目录路径
    char dest_path[MAX_PATH * 2] = {0}; // 目标文件路径
   
    JoinPath(dest_path, src_path, dest_dir);
    printf("dest_path:%s\n", dest_path);

    return 0;
}
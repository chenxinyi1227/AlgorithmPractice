#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#if 0
typedef struct 
{
    const char** files;
    size_t count;
} FileList;

FileList getDirectoryFiles(const char* directory_path) 
{
    FileList fileList;
    fileList.files = NULL;
    fileList.count = 0;

    DIR* directory = opendir(directory_path);
    if (directory == NULL) 
    {
        printf("无法打开目录\n");
        return fileList;
    }

    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) 
    {
        fileList.count++;
        fileList.files = realloc(fileList.files, sizeof(const char*) * fileList.count);
        fileList.files[fileList.count - 1] = entry->d_name;
    }
    closedir(directory);
    return fileList;
}
#else
//获取文件目录下的文件
int getDirectoryFiles(const char* directory_path) 
{
    DIR* directory = opendir(directory_path);
    struct dirent* entry;

    if (directory == NULL) 
    {
        printf("无法打开目录\n");
        return EXIT_FAILURE;
    }
 
    while ((entry = readdir(directory)) != NULL) 
    {
        printf("%s\n", entry->d_name);
    }
    closedir(directory);
    return EXIT_SUCCESS;
}
#endif

int main() 
{
    #if 0
    const char* directory_path = "../md5";
    FileList fileList = getDirectoryFiles(directory_path);

    for (size_t i = 0; i < fileList.count; i++) 
    {
        printf("%s\n", fileList.files[i]);
    }

    free(fileList.files);
    #endif
    char buffer[1024] = {0};
    printf("请输入文件目录：");
    scanf("%s", buffer);
    const char* directory_path = buffer;
    getDirectoryFiles(directory_path);

    return EXIT_SUCCESS;
}


#include <stdio.h>
#include <stdlib.h>
//分页显示

#define PAGE_SIZE 10

void displayPage(int page) 
{
    // 根据页码计算起始索引和结束索引
    int start = (page - 1) * PAGE_SIZE + 1;
    int end = start + PAGE_SIZE - 1;

    // 显示当前页的数据
    printf("显示第 %d 页数据：\n", page);
    for (int i = start; i <= end; i++) 
    {
        printf("数据 %d\n", i);
    }
}

int main() {
    int totalPages = 0;
    int currentPage = 1;

    // 假设有100个数据
    int totalData = 100;

    // 计算总页数
    if (totalData % PAGE_SIZE == 0) 
    {
        totalPages = totalData / PAGE_SIZE;
    } else 
    {
        totalPages = totalData / PAGE_SIZE + 1;
    }

    while (1) 
    {
        printf("\n");

        // 显示当前页的数据
        displayPage(currentPage);

        printf("\n");
        printf("第 %d 页 / 共 %d 页\n", currentPage, totalPages);
        printf("输入 'n' 查看下一页，输入 'p' 查看上一页，输入 'q' 退出：");

        char input;
        scanf(" %c", &input);

        if (input == 'n') 
        {
            system("clear");
            // 显示下一页数据
            if (currentPage < totalPages) 
            {
                currentPage++;
            }
        } 
        else if (input == 'p') 
        {
            system("clear");
            // 显示上一页数据
            if (currentPage > 1) 
            {
                currentPage--;
            }
        } 
        else if (input == 'q') 
        {
            // 退出循环
            break;
        } 
        else 
        {
            printf("无效的输入！\n");
        }
    }

    return 0;
}

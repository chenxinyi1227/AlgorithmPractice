#include <stdio.h>
#include <string.h>
#define N 3
#define BUFFER_SIZE 10
/* 学生数组存储信息 */
typedef struct student
{
    char name[BUFFER_SIZE];
    int stunums;
    int sorce;
}student;

void BubbleSort(student *nums)
{
    for(int i = 0; i < N - 1; i++)
    {
        for(int j = 0; j < N - i - 1; j++)
        {
            int cmp = strcmp(nums[j].name, nums[j + 1].name);
            if(cmp > 0)
            {
                student tmp = nums[j];
                nums[j]= nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
    }
}
int main()
{
    student stu[N];
    char name[BUFFER_SIZE];
    int stunum;
    int score;
    for(int i = 0; i < N; i++)
    {
        printf("请输入学生信息\n");
        scanf("%s %d %d", name, &score, &stunum);
    
        strcpy(stu[i].name, name);
        stu[i].sorce = score;
        stu[i].stunums = stunum;
    }
#if 0
    for(int i = 0; i < N; i++)
    {
        printf("stu[%d].name:%-8s stu[%d].sorce:%-4d stu[%d].stunums:%-4d\n", i+1, stu[i].name, i+1, stu[i].sorce, i+1, stu[i].stunums);
    }
#endif
    BubbleSort(stu);

    for(int i = 0; i < N; i++)
    {
        printf("stu[%d].name:%-8s stu[%d].sorce:%-4d stu[%d].stunums:%-4d\n", i+1, stu[i].name, i+1, stu[i].sorce, i+1, stu[i].stunums);
    }

    return 0;
}
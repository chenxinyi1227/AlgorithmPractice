#include <stdio.h>
/* 将内容输出到字符串上面 */
#define BUFFER_SIZE 1024

typedef struct Student
{
	int age;
	float score;
	char name[20];
}studnt;

int main () 
{
	/* 格式化输入数据 */
	studnt stu1 = {20, 2.14f, "jack"};
    studnt stu2 = {0};
    char arr[BUFFER_SIZE]= {0};

    /* 把格式化的数据转换成字符存储在arr中 */
    sprintf(arr, "%d %f %s", stu1.age, stu1.score, stu1.name);
    // printf("arr:%s\n", arr); 

    //从arr中读取格式化的数据到stu2中
    sscanf(arr, "%d %f %s", &stu2.age, &stu2.score, stu2.name);
    printf("age:%d score:%f name:%s\n", stu2.age, stu2.score, stu2.name);

	return 0;
}

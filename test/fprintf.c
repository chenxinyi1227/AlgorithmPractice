#include <stdio.h>
/* 将文件输出到文件流上 */
typedef struct Student
{
	int age;
	float score;
	char name[20];
}studnt;

int main () 
{
	/* 格式化输入数据 */
#if 0
	studnt stu = {20, 2.14f, "jack"};
	FILE * pf = fopen("test.txt", "w");
	if(pf == NULL)
	{
		return 0;
	}
	fprintf(pf, "%d %f %s", stu.age, stu.score, stu.name);

	fclose(pf);
	pf = NULL;

#else
	/* 格式化输出数据 */
	studnt stu = {0};
	FILE * pf = fopen("test.txt", "r");
	if(pf == NULL)
	{
		return 0;
	}
	fscanf(pf, "%d %f %s", &(stu.age), &(stu.score), &(stu.name));
	printf("%d %f %s\n", stu.age, stu.score, stu.name);

	fclose(pf);
	pf = NULL;
#endif
	
	return 0;
}

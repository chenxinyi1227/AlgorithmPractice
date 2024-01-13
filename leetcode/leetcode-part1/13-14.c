#include <stdio.h>

/* 最长公共前缀 
编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串 ""*/
//%s  *names + i
// %c  *(*(names+i)+j));
char* longestCommonPrefix(char** strs, int strsSize) 
{
    //如果数组为空，直接返回空字符串
    if(strsSize == 0)
    {
        return "";
    }
    //第一个字符串作为初始公共前缀
    char * prefix = strs[0];
    //遍历数组中的每个字符串
    for(int i = 0; i < strsSize; i++)
    {
        //从第一个字符开始逐个比较
        int j = 0;
        while(prefix[j] && strs[i][j] && prefix[j] == strs[i][j])
        {
            j++;
        }
        //更新公共前缀
        prefix[j] = '\0';
    }
    return prefix;
}

int main() {
    char *names = {
        "flower",
        "flow",
        "flight"
    };
    int numSize = sizeof(names) /sizeof(names[0]);

    printf("numSize:%d\n", numSize);
    longestCommonPrefix(names,30);
    

#if 0
    printf("%c\n", *(*names + 1));//l
    printf("%s\n", *names + 1);//lower
    printf("%s\n", *(names+1));//flow
    printf("%c\n", *(*(names+2)+3));//g
#endif
    return 0;
}

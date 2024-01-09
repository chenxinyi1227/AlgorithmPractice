#include <stdio.h>
#include <string.h>

/* 最大重复子字符串 */
/* 给你一个字符串 sequence ，如果字符串 word 连续重复 k 次形成的字符串是 sequence 的一个子字符串，那么单词 word 的 重复值为 k 。单词 word 的 最大重复值 是单词 word 在 sequence 中最大的重复值。
如果 word 不是 sequence 的子串，那么重复值 k 为 0 。
给你一个字符串 sequence 和 word ，请你返回 最大重复值 k 。 */
/* 输入：sequence = "ababc", word = "ab"
输出：2
解释："abab" 是 "ababc" 的子字符串。 */
/* 简单枚举 */
int maxRepeating(char* sequence, char* word) 
{
    int num = 0;
    int slen = strlen(sequence);
    int wlen  = strlen(word);
    for(int idx = 0; idx < slen; idx++)
    {
        //找到第一个相同的字符
        if(sequence[idx] != word[0])
        {
            continue;
        }
        /* 开始比较 */
        int travel = idx;//遍历sequence
        int jdx = 0;//遍历word
        int sum = 0;//匹配个数
        while(travel < slen && sequence[travel] == word[jdx])
        {
            travel++;
            jdx++;
            /* 匹配个数 */
            if(jdx == wlen)//当遍历到word最后一个字符匹配个数增加
            {
                jdx = 0;
                sum++;
            }
        }
        if(num < sum)
        {
            num = sum;//更新最大匹配个数
        }
    }
    return num;
}

int main()
{
    char *s = "cabababd";
    char *t = "ab";
    int nums = maxRepeating(s, t);
    printf("nums:%d\n", nums);

}
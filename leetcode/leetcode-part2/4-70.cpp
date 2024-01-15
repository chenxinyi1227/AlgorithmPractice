#include <iostream>
using namespace std;
#include <vector>
/* 爬楼梯 */
/* 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
示例 1：
输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶 */
class Solution {
public:
    int climbStairs(int n) 
    {
         // 使用数组 dp 存储每一级台阶的爬法数量
        // 由于后面初始化 dp[1] 和 dp[2] 
        // 为了让当 n = 0 时不越界，保证 dp[1] 和 dp[2] 都有值
        // 所以 dp 的长度为 n + 2
        vector<int> dp( n + 2 , 0 );

        // 初始化 dp[1] 和 dp[2] 
        // 一级台阶只有一种爬法
        dp[1] = 1;

        // 二级台阶有两种爬法
        // 一种爬法是先爬 1 个台阶，再爬 1 个台阶
        // 一种爬法是爬 2 个台阶
        dp[2] = 2;

        // 从 3 开始循环至 n，计算 dp[3] 至 dp[n]
        for(int i = 3; i <= n; i++) {
            // 第 i 级台阶的结果 dp[i] 等于第 i-1 和 i-2 的结果之和
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        // 最后返回 n 级台阶的结果
        return dp[n];
    }
};
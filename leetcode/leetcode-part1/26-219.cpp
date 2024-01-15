/* 存在重复元素 */
#include <iostream>
using namespace std;
#include <vector>


class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) 
    {
        if (nums.size() <= 1)
        {
            return false;
        }
        int length = nums.size();
        for (int idx = 0; idx < length; idx++)
        {
            for (int jdx = idx + 1; jdx < idx + 1 + k && (jdx < length); jdx++)
            {
                if (nums[idx] == nums[jdx])
                {
                    return true;
                }
            }
        }
        return false;
    }
};



int main()
{


    return 0;
}
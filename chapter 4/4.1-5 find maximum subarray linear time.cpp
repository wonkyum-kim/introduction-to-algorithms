#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <utility>

size_t maximum_subarray(const std::vector<int>& nums, const size_t n)
{
    if (n == 1) {
        return nums[1];
    }
    std::vector<int> dp(n + 1);
    dp[1] = nums[1];
    auto max = dp[1];
    for (auto i = 2; i <= n; ++i) {
        dp[i] = std::max(0, dp[i - 1]) + nums[i];
        max = std::max(max, dp[i]);
    }
    return max;
}

int main()
{
	std::vector<int> v{ 0, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    std::cout << maximum_subarray(v, 16);
}

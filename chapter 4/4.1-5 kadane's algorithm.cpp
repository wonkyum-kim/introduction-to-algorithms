#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <utility>

int maximum_subarray(std::vector<int>& v)
{
    std::vector<int> dp(v.size());
    if (v.size() == 1) {
        return v[0];
    }
    dp[0] = v[0];
    int max = dp[0];
    for (auto i = 1; i < v.size(); ++i) {
        dp[i] = std::max(0, dp[i - 1]) + v[i];
        max = std::max(max, dp[i]);
    }
    return max;
}

int main()
{
    std::vector<int> v{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    std::cout << maximum_subarray(v);
}

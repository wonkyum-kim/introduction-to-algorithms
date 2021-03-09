#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <utility>

int maximum_subarray(const std::vector<int>& nums, const size_t n)
{
    int best = 0;
    int curr = 0;
    for (auto i = 1; i <= n; ++i) {
        curr = std::max(curr + nums[i], 0);
        best = std::max(best, curr);
    }
    return best;
}

int main()
{
    std::vector<int> v{ 0, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    std::cout << maximum_subarray(v, 16);
}

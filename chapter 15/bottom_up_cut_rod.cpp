#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// bottom up

int bottom_up_cut_rod(const std::vector<int>& p, int n)
{
	std::vector<int> dp(n + 1);
	for (auto i = 1; i <= n; ++i) {
		for (auto j = 1; j <= i; ++j) {
			dp[i] = std::max(dp[i], dp[i - j] + p[j]);
		}
	}
	return dp[n];
}

int main()
{
	int n = 0;
	std::cin >> n;
	std::vector<int> p{0,1,5,8,9,10,17,17,20,24,30 };
	std::cout << bottom_up_cut_rod(p, n);
}

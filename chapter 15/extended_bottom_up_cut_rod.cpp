#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <utility>

// bottom up

using pair = std::pair<std::vector<int>, std::vector<int>>;

pair extended_bottom_up_cut_rod(const std::vector<int>& p, int n)
{
	std::vector<int> dp(n + 1);
	std::vector<int> length(n + 1);
	for (auto i = 1; i <= n; ++i) {
		for (auto j = 1; j <= i; ++j) {
			if (dp[i] < dp[i - j] + p[j]) {
				dp[i] = dp[i - j] + p[j];
				length[i] = j;
			}
		}
	}
	return { dp, length };
}

void print_cur_rod_solution(std::vector<int>& p, int n)
{
	auto [dp, length] = extended_bottom_up_cut_rod(p, n);
	while (n > 0) {
		std::cout << length[n] << ' ';
		n -= length[n];
	}
}

int main()
{
	int n = 0;
	std::cin >> n;
	std::vector<int> p{0,1,5,8,9,10,17,17,20,24,30 };
	print_cur_rod_solution(p, n);
}

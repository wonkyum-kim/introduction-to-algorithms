#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include <numeric>

std::vector<std::vector<size_t>> LCS_length(const std::vector<char>& X, const std::vector<char>& Y)
{
	auto m = X.size() - 1;
	auto n = Y.size() - 1;
	std::vector<std::vector<size_t>> c(m + 1, std::vector<size_t>(n + 1));
	for (auto i = 1; i <= m; ++i) {
		for (auto j = 1; j <= n; ++j) {
			if (X[i] == Y[j]) {
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
			}
			else {
				c[i][j] = c[i][j - 1];
			}
		}
	}
	return c;
}

void print_LCS(const std::vector<std::vector<size_t>>& c, const std::vector<char>& X, const std::vector<char>& Y, size_t i, size_t j)
{
	if (c[i][j] == 0) {
		return;
	}
	if (X[i] == Y[j]) {
		print_LCS(c, X, Y, i - 1, j - 1);
		std::cout << X[i];
	}
	else if (c[i - 1][j] > c[i][j - 1]) {
		print_LCS(c, X, Y, i - 1, j);
	}
	else {
		print_LCS(c, X, Y, i, j - 1);
	}
}

int main()
{
	constexpr char dummy = '?';
	std::vector<char> X{ dummy,'1','0','0','1','0','1','0','1'};
	std::vector<char> Y{ dummy,'0','1','0','1','1','0','1','1','0' };
	auto c = LCS_length(X, Y);
	print_LCS(c, X, Y, X.size() - 1, Y.size() - 1);
}

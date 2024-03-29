#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include <numeric>

enum class Direction {
	upperleft,	// ↖
	up,		// ↑
	left		// ←
};

template<typename T>
std::pair<std::vector<std::vector<Direction>>, std::vector<std::vector<T>>> LCS_length(const std::vector<T>& X, const std::vector<T>& Y)
{
	auto m = X.size() - 1;
	auto n = Y.size() - 1;
	std::vector<std::vector<Direction>> b(m + 1, std::vector<Direction>(n + 1));
	std::vector<std::vector<T>> c(m + 1, std::vector<T>(n + 1));
	for (auto i = 1; i <= m; ++i) {
		for (auto j = 1; j <= n; ++j) {
			if (X[i] == Y[j]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = Direction::upperleft;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = Direction::up;
			}
			else {
				c[i][j] = c[i][j - 1];
				b[i][j] = Direction::left;
			}
		}
	}
	return { b, c };
}

template<typename T>
void print_LCS(const std::vector<std::vector<Direction>>& b, const std::vector<T>& X, size_t i, size_t j)
{
	if (i == 0 || j == 0) {
		return;
	}
	if (b[i][j] == Direction::upperleft) {
		print_LCS(b, X, i - 1, j - 1);
		std::cout << X[i] << ' ';
	}
	else if (b[i][j] == Direction::up) {
		print_LCS(b, X, i - 1, j);
	}
	else {
		print_LCS(b, X, i, j - 1);
	}
}

int main()
{
	constexpr char dummy = '?';
	std::vector<char> X{ dummy,'A','B','C','B','D','A','B' };
	std::vector<char> Y{ dummy,'B','D','C','A','B','A' };
	auto [b, c] = LCS_length(X, Y);
	print_LCS(b, X, X.size() - 1, Y.size() - 1);
}

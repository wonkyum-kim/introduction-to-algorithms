#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include <numeric>

template<typename T>
std::vector<std::vector<T>> matrix_multiply(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B)
{
	// row 0 & column 0 are empty.
	assert(A[1].size() != B.size() - 1);
	std::vector<std::vector<T>> C(A.size(), std::vector<T>(B[1].size()));
	for (auto i = 1; i < A.size(); ++i) {
		for (auto j = 1; j < B[1].size(); ++j) {
			for (auto k = 1; k < A[1].size(); ++k) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}

template<typename T>
std::pair<std::vector<std::vector<T>>, std::vector<std::vector<T>>> matrix_chain_order(const std::vector<T>& p)
{
	auto n = p.size() - 1;
	std::vector<std::vector<T>> m(n + 1, std::vector<T>(n + 1));
	std::vector<std::vector<T>> s(n, std::vector<T>(n + 1));
	for (auto l = 2; l <= n; ++l) {
		for (auto i = 1; i <= n - l + 1; ++i) {
			auto j = i + l - 1;
			m[i][j] = std::numeric_limits<int>::max();
			for (auto k = i; k <= j - 1; ++k) {
				auto q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	return { m,s };
}

template<typename T>
void print_optimal_parens(std::vector<std::vector<T>>& s, size_t i, size_t j)
{
	if (i == j) {
		std::cout << 'A' << i;
	}
	else {
		std::cout << '(';
		print_optimal_parens(s, i, s[i][j]);
		print_optimal_parens(s, s[i][j] + 1, j);
		std::cout << ')';
	}
}

template <typename T>
std::vector<std::vector<T>> matrix_chain_multiply(const std::vector<std::vector<std::vector<T>>>& A, const std::vector<std::vector<size_t>>& s, size_t i, size_t j) {
	if (i == j) {
		return A[i];
	}
	if (i + 1 == j) {
		return matrix_multiply(A[i], A[j]);
	}
	auto B = matrix_chain_multiply(A, s, i, s[i][j]);
	auto C = matrix_chain_multiply(A, s, s[i][j] + 1, j);
	return matrix_multiply(B, C);
}


int main()
{
	std::vector<size_t> p = { 2, 2, 2, 2 };
	auto [m, s] = matrix_chain_order(p);
	std::vector<std::vector<int>> dummy;
	std::vector<std::vector<int>> A1{ {0,0,0},{0,1,0},{0,0,1} };
	std::vector<std::vector<int>> A2{ {0,0,0},{0,2,0},{0,0,2} };
	std::vector<std::vector<int>> A3{ {0,0,0},{0,3,0},{0,0,3} };
	std::vector<std::vector<std::vector<int>>> A{ dummy,A1,A2,A3 };
	auto result = matrix_chain_multiply(A, s, 1, 3);
	for (auto i = 1; i <= p.front(); ++i) {
		for (auto j = 1; j <= p.back(); ++j) {
			std::cout << result[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template<typename T>
void counting_sort(std::vector<T>& A, std::vector<T>& B, T k)
{
	std::vector<int> C(k + 1);
	for (auto j = 1; j <= A.size() - 1; ++j) {
		C[A[j]] = C[A[j]] + 1;
	}
	for (auto i = 1; i <= k; ++i) {
		C[i] = C[i] + C[i - 1];
	}
	for (auto j = A.size() - 1; j >= 1; --j) {
		B[C[A[j]]] = A[j];
		C[A[j]] = C[A[j]] - 1;
	}
}

int main()
{
	constexpr int dummy = std::numeric_limits<int>::min();
	std::vector<int> A{ dummy,2,5,3,0,2,3,0,3 };
	auto k = std::max_element(A.begin(), A.end());
	std::vector<int> B(A.size());
	counting_sort(A, B, *k);
	for (auto i = 1; i < B.size(); ++i) {
		std::cout << B[i] << ' ';
	}
}

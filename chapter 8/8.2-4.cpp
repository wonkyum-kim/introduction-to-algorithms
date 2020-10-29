#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

template<typename T>
std::vector<T> counting_sort(std::vector<T>& A, std::vector<T>& B, T k)
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
	return C;
}

template<typename T>
T counting_range(const std::vector<T>& C, const int a, const int b)
{
	assert(b >= a, "b must have a same or bigger value than a");
	return C[b] - C[a];
}



int main()
{
	constexpr int dummy = std::numeric_limits<int>::min();
	std::vector<int> A{ dummy,2,5,3,0,2,3,0,3 };
	auto k = std::max_element(A.begin(), A.end());
	std::vector<int> B(A.size());
	std::vector<int> C = counting_sort(A, B, *k);
	int a = 1;
	int b = 4;
	std::cout << "the number of integer(s) in the range [1, 4] is " << counting_range(C, a, b);
	
}

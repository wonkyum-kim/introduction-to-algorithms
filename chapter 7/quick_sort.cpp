#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
size_t partition(std::vector<T>& A, size_t p, size_t r)
{
	T x = A[r];
	size_t i = p - 1;
	for (auto j = p; j <= r - 1; ++j) {
		if (A[j] <= x)
			std::swap(A[++i], A[j]);
	}
	std::swap(A[i + 1], A[r]);
	return ++i;
}

template<typename T>
void quick_sort(std::vector<T>& A, size_t p, size_t r)
{
	if (p < r) {
		size_t q = partition(A, p, r);
		quick_sort(A, p, q - 1);
		quick_sort(A, q + 1, r);
	}
}

int main()
{
	constexpr int dummy = 0;
	std::vector<int> A{ dummy, 5, 3, 2, 4, 1 };
	quick_sort(A, 1, A.size() - 1);
	for (auto i = 1; i < A.size(); ++i) {
		std::cout << A[i] << ' ';
	}
}

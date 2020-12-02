#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#include <random>
#include <numeric>

std::mt19937 gen(std::random_device{}());

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
    std::vector<int> v(101);
    std::iota(v.begin() + 1, v.end(), 1);
    std::shuffle(v.begin() + 1, v.end(), gen);
	quick_sort(v, 1, v.size() - 1);
    for (auto i = 1; i <= 100; ++i) {
        std::cout << v[i] << ' ';
    }
}

#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <numeric>
#include <utility>

std::mt19937 gen(std::random_device{}());

template<typename T>
void selection_sort(std::vector<T>& A)
{
	for (auto i = 1; i < A.size() - 1; ++i) {
		auto min_index = i;
		for (auto j = i + 1; j < A.size(); ++j) {
			if (A[min_index] > A[j]) {
				min_index = j;
			}
		}
		std::swap(A[i], A[min_index]);
	}
}

int main()
{
	constexpr int SIZE{ 100 };
	std::vector<int> v(SIZE + 1);
	std::iota(v.begin() + 1, v.end(), 1);
	std::shuffle(v.begin() + 1, v.end(), gen);
	selection_sort<int>(v);
	for (auto x : v) {
		std::cout << x << ' ';
	}
}

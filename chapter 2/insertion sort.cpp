#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <numeric>

std::mt19937 gen(std::random_device{}());

template<typename T>
void insertion_sort(std::vector<T>& A)
{
	for (auto j = 2; j < A.size(); ++j) {
		T key = A[j];
		auto i = j - 1;
		while (i > 0 && A[i] > key) {
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}

int main()
{
	constexpr int SIZE{ 100 };
	std::vector<int> v(SIZE + 1);
	std::iota(v.begin() + 1, v.end(), 1);
	std::shuffle(v.begin() + 1, v.end(), gen);
	std::cout << "before" << '\n';
	for (const auto& x : v) {
		std::cout << x << ' ';
	}
	std::cout << '\n' << "after" << '\n';
	insertion_sort<int>(v);
	for (const auto& x : v) {
		std::cout << x << ' ';
	}
}

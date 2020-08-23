#include <iostream>
#include <vector>
#include <limits>
#include <tuple>

using ans_type = std::tuple<size_t, size_t, int>;

template<typename T>
ans_type brute_force(const std::vector<T>& A)
{
	int max_sum = std::numeric_limits<int>::min();		// sentinel value;
	size_t max_left = 1;
	size_t max_right = 1;
	for (size_t i = 1; i < A.size(); i++) {
		int sum = 0;
		for (size_t j = i; j < A.size(); j++) {
			sum += A[j];
			if (max_sum < sum) {
				max_left = i;
				max_right = j;
				max_sum = sum;
			}
		}
	}
	return { max_left, max_right, max_sum };
}

int main()
{
	std::vector<int> A{ 0, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	auto arr = brute_force(A);
	std::cout << std::get<0>(arr) << ' ' << std::get<1>(arr) << ' ' << std::get<2>(arr);
}

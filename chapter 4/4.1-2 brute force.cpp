#include <iostream>
#include <vector>
#include <limits>
#include <tuple>

using tuple = std::tuple<int, int, int>;

template<typename T>
tuple brute_force(const std::vector<T>& A)
{
	int max_sum = std::numeric_limits<int>::min();		
	int max_left = 1;
	int max_right = 1;
	for (int i = 1; i < A.size(); i++) {
		int sum = 0;
		for (int j = i; j < A.size(); j++) {
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

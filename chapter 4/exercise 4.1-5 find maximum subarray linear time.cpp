#include <iostream>
#include <vector>
#include <limits>
#include <tuple>

using ans_type = std::tuple<size_t, size_t, int>;

template<typename T>
ans_type find_maximum_subarray_linear(const std::vector<T>& A)
{
	int max_sum = std::numeric_limits<int>::min();		// sentinel value
	int running_sum = 0;
	size_t max_left = 0;
	size_t max_right = 0;
	size_t curr_left = 0;
	size_t curr_right = 0;

	for (size_t i = 1; i < A.size(); i++) {
		if (running_sum <= 0) {
			curr_left = i;
			curr_right = i;
			running_sum = A[i];
		}
		else {
			running_sum += A[i];
			curr_right = i;
		}

		if (running_sum > max_sum) {
			max_sum = running_sum;
			max_left = curr_left;
			max_right = curr_right;
		}
	}
	return { max_left, max_right, max_sum };
}

int main()
{
	// A[0] is sentinel value.
	std::vector<int> A{ 0, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	auto arr = find_maximum_subarray_linear(A);
	std::cout << std::get<0>(arr) << ' ' << std::get<1>(arr) << ' ' << std::get<2>(arr);
}

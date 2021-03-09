#include <iostream>
#include <vector>
#include <limits>
#include <tuple>

using tuple = std::tuple<int, int, int>;

tuple find_max_crossing_subarray(const std::vector<int>& A, const int low, const int mid, const int high)
{
	int left_sum = std::numeric_limits<int>::min();		
	int sum = 0;
	int max_left = 0;

	for (int i = mid; i >= low; --i) {
		sum += A[i];
		if (sum > left_sum) {
			left_sum = sum;
			max_left = i;
		}
	}

	int right_sum = std::numeric_limits<int>::min();	
	sum = 0;
	int max_right = 0;

	for (int i = mid + 1; i <= high; ++i) {
		sum += A[i];
		if (sum > right_sum) {
			right_sum = sum;
			max_right = i;
		}
	}
	return { max_left, max_right, left_sum + right_sum };
}

tuple find_maximum_subarray(const std::vector<int>& A, const int low, const int high)
{
	if (high == low)	// base case: only one element
		return { low, high, A[low] };
	else {
		int mid = (low + high) / 2;
		auto [left_low, left_high, left_sum] = find_maximum_subarray(A, low, mid);
		auto [right_low, right_high, right_sum] = find_maximum_subarray(A, mid + 1, high);
		auto [cross_low, cross_high, cross_sum] = find_max_crossing_subarray(A, low, mid, high);

		if (left_sum >= right_sum && left_sum >= cross_sum) {
			return { left_low, left_high, left_sum };
		}
		else if (right_sum >= left_sum && right_sum >= cross_sum) {
			return { right_low, right_high, right_sum };
		}
		else {
			return { cross_low, cross_high, cross_sum };
		}
	}
}

int main()
{
	std::vector<int> A{ 0, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int low = 1;
	int high = 16;
	auto arr = find_maximum_subarray(A, low, high);
	std::cout << std::get<0>(arr) << ' ' << std::get<1>(arr) << ' ' << std::get<2>(arr);
}

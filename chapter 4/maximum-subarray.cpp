#include <iostream>
#include <vector>
#include <limits>
#include <tuple>

using ans_type = std::tuple<size_t, size_t, int>;

template<typename T>
ans_type find_max_crossing_subarray(const std::vector<T>& A, size_t low, size_t mid, size_t high)
{
	int left_sum = std::numeric_limits<int>::min();		// sentinel value
	int sum = 0;
	size_t max_left = 0;

	for (size_t i = mid; i >= low; --i)
	{
		sum += A[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}

	int right_sum = std::numeric_limits<int>::min();	// sentinel value
	int sum = 0;
	size_t max_right = 0;


	for (size_t i = mid + 1; i <= high; ++i)
	{
		sum += A[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = i;
		}
	}
	return { max_left, max_right, left_sum + right_sum };
}

template <typename T>
ans_type find_maximum_subarray(const std::vector<T>& A, size_t low, size_t high)
{
	if (high == low)	// only one element
		return { low, high, A[low] };
	else
	{
		size_t mid = (low + high) / 2;
		auto [l_low, l_high, l_sum] = find_maximum_subarray(A, low, mid);
		auto [r_low, r_high, r_sum] = find_maximum_subarray(A, mid + 1, high);
		auto [c_low, c_high, c_sum] = find_max_crossing_subarray(A, low, mid, high);

		if (l_sum >= r_sum && l_sum >= c_sum)
			return { l_low, l_high, l_sum };
		else if (r_sum >= l_sum && r_sum >= c_sum)
			return { r_low, r_high, r_sum };
		else
			return { c_low, c_high, c_sum };
	}
}

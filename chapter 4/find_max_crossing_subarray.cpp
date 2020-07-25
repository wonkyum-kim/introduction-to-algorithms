#include <iostream>
#include <vector>
#include <limits>
#include <tuple>

using ans_type = std::tuple<size_t, size_t, int>;

template<typename T>
ans_type find_max_crossing_subarray(std::vector<T>& A, size_t low, size_t mid, size_t high)
{
	// the smallest value(doesn't matter)
	int left_sum = std::numeric_limits<int>::min();
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

	// the smallest value(doesn't matter)
	int right_sum = std::numeric_limits<int>::min();
	int sum = 0;
	size_t max_right = 0;


	for (size_t i = mid+1; i <=high; ++i)
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

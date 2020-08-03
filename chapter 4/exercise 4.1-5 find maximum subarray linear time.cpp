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

	for (size_t i = 0; i < A.size(); i++)
	{
		if (running_sum <= 0)
		{
			curr_left = i;
			curr_right = i;
			running_sum = A[i];
		}
		else
		{
			running_sum += A[i];
			curr_right = i;
		}

		if (running_sum > max_sum)
		{
			max_sum = running_sum;
			max_left = curr_left;
			max_right = curr_right;
		}
	}
	return { max_left, max_right, max_sum };
}

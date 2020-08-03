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
	for (size_t i = 0; i < A.size(); i++)
	{
		int sum = 0;
		for (size_t j = i; j < A.size(); j++)
		{
			sum += A[j];
			if (max_sum < sum)
			{
				max_left = i;
				max_right = j;
				max_sum = sum;
			}
		}
	}
	return { max_left, max_right, max_sum };
}

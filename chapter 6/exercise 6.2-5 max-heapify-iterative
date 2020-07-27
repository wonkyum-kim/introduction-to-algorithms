#include <iostream>
#include <algorithm>
#include <vector>

size_t left(size_t& l)
{
	return 2*l;
}

size_t right(size_t& r)
{
	return 2*r + 1;
}

template <typename T>
void max_heapify(std::vector<T>& A)
{
	size_t i = 0;
	while (i <= A.size() / 2)
	{
		size_t l = left(i);
		size_t r = right(i);
		size_t largest;

		if (l <= A.size() && A[l] > A[i])
			largest = l;
		else
			largest = i;

		if (r <= A.size() && A[r] > A[i])
			largest = r;

		if (largest != i)
		{
			std::swap(A[i], A[largest]);
			i = largest;
		}
		else
			return;
	}
}

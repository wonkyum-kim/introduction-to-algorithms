#include <iostream>
#include <algorithm>
#include <vector>

size_t parent(const size_t& i)
{
	return i/2;
}

size_t left(const size_t& i)
{
	return 2*i;
}

size_t right(const size_t& i)
{
	return 2*i + 1;
}

template <typename T>
void max_heapify(std::vector<T>& A, size_t i)
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
	else
		largest = i;

	if (largest != i)
	{
		std::swap(A[i], A[largest]);
		max_heapify(A, largest);
	}
}

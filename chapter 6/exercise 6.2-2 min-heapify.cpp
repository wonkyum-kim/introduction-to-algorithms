#include <iostream>
#include <algorithm>
#include <vector>

size_t parent(const size_t& i)
{
	return i/2;
}

size_t left(size_t& i)
{
	return 2*i;
}

size_t right(size_t& i)
{
	return 2*i + 1;
}

template <typename T>
void max_heapify(std::vector<T>& A, size_t i)
{
	size_t l = left(i);
	size_t r = right(i);
	size_t smallest = i;

	if (l <= A.size() && A[l] < A[i])
		smallest = l;

	if (r <= A.size() && A[r] < A[i])
		smallest = r;

	if (largest != i)
	{
		std::swap(A[i], A[smallest]);
		max_heapify(A, smallest);
	}
}

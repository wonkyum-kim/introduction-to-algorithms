#include <iostream>
#include <algorithm>
#include <vector>


// index of root node is 0. 
size_t parent(const size_t& i)
{
	return i/2;
}

size_t left(const size_t& i)
{
	return 2*i + 1;
}

size_t right(const size_t& i)
{
	return 2*i + 2;
}

// heapsize argument?
template <typename T>
void max_heapify(std::vector<T>& A, size_t i)
{
	size_t l = left(i);
	size_t r = right(i);
	size_t largest;

	if (l < A.size() && A[l] > A[i])
		largest = l;
	else
		largest = i;

	if (r < A.size() && A[r] > A[i])
		largest = r;
	else
		largest = i;

	if (largest != i)
	{
		std::swap(A[i], A[largest]);
		max_heapify(A, largest);
	}
}

template<typename T>
void build_max_heap(std::vector<T>& A)
{
	auto A_heap_size = A.size();
	for (size_t i = A.size() / 2; i > 0; i--)
		max_heapify(A, i);
}

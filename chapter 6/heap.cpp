#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

// index of root node is 1. 
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

// heapsize argument?
template <typename T>
void max_heapify(std::pair<std::vector<T>&, size_t>& A, size_t i)
{
	size_t l = left(i);
	size_t r = right(i);
	size_t largest = i;

	if (l <= A.second && A.first[l] > A.first[i])
		largest = l;

	if (r <= A.second && A.first[r] > A.first[i])
		largest = r;

	if (largest != i)
	{
		std::swap(A.first[i], A.first[largest]);
		max_heapify(A, largest);
	}
}

template<typename T>
void build_max_heap(std::pair<std::vector<T>&, size_t>& A)
{
	A.second = A.size();
	for (size_t i = A.first.size() / 2; i >= 1; i--)
		max_heapify(A, i);
}

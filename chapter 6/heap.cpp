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

template <typename T>
void max_heapify(std::pair<std::vector<T>&, size_t>& B, size_t i)
{
	size_t l = left(i);
	size_t r = right(i);
	size_t largest = i;

	if (l <= B.second && B.first[l] > B.first[i])
		largest = l;

	if (r <= B.second && B.first[r] > B.first[i])
		largest = r;

	if (largest != i)
	{
		std::swap(B.first[i], B.first[largest]);
		max_heapify(B, largest);
	}
}

template<typename T>
void build_max_heap(std::vector<T>& A)
{
        size_t A_heap_size = A.size()-1;
        auto B = std::make_pair(A, A_heap_size);
        // terminal nodes are start at A_heap_size / 2
	for (size_t i = A_heap_size / 2; i >= 1; --i)
		max_heapify(B, i);
}

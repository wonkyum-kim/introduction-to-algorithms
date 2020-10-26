#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

// d - ary heap
constexpr int d = 3;

int d_parent(const int i)
{
	assert(i > 0, "the index of the root node is 1");
	if (i == 1) {
		return 1;
	}
	return (i - 2) / d + 1;
}

int d_child(const int i, const int j)
{
	assert(j >= 1 && j <= d, "the range of the indices of this node is 1 to d");
	return (i - 1) * d + j + 1;
}

template<typename T>
void max_heapify(std::vector<T>& A, int dh_size, int i)
{
	int largest = i;
	for (auto j = 1; j <= d; ++j) {
		int child = d_child(i, j);
		if (child <= dh_size && A[child] > A[largest]) {
			largest = child;
		}
	}
	if (largest != i) {
		std::swap(A[largest], A[i]);
		max_heapify(A, dh_size, largest);
	}
}

template<typename T>
void build_max_heap(std::vector<T>& A, int dh_size)
{
	for (auto i = dh_size / d; i > 0; --i) {
		max_heapify(A, dh_size, i);
	}
}

template<typename T>
T heap_extract_max(std::vector<T>& A, int dh_size)
{
	assert(dh_size >= 1, "heap underflow");
	T max = A[1];
	A[1] = A[dh_size];
	max_heapify(A, --dh_size, 1);
}

template <typename T>
void heap_increase_key(std::vector<T>& A, int i, T key) 
{
	assert(key >= A[i], "new key is smaller than current key");
	A[i] = key;
	while (i > 1 && A[d_parent(i)] < A[i])
	{
		std::swap(A[i], A[d_parent(i)]);
		i = d_parent(i);
	}
}

template<typename T>
void max_heap_insert(std::vector<T>& A, int dh_size, T key)
{
	dh_size++;
	A.push_back(std::numeric_limits<T>::min());
	heap_increase_key(A, dh_size, key);
}


int main()
{
	constexpr int dummy = 0;
	std::vector<int> d_heap{ dummy, 5,6,4,7,8,2,1 };
	build_max_heap(d_heap, d_heap.size());
	for (auto i = 1; i < d_heap.size(); ++i) {
		std::cout << d_heap[i] << ' ';
	}
}

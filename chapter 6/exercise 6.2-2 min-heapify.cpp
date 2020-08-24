#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
void min_heapify(std::vector<T>& A, const int h_size, const size_t i)
{
    size_t l = left(i);
    size_t r = right(i);
    size_t smallest = i;

    if (l <= h_size && A[l] < A[i])
        smallest = l;

    if (r <= h_size && A[r] < A[smallest])
        smallest = r;

    if (smallest != i)
    {
        std::swap(A[i], A[smallest]);
        max_heapify(A, h_size, smallest);
    }
}


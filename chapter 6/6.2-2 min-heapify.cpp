#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#include <random>
#include <numeric>

std::mt19937 gen(std::random_device{}());

// the index of the root node is 1.
size_t parent(size_t i)
{
    return i / 2;
}

size_t left(size_t i)
{
    return 2 * i;
}

size_t right(size_t i)
{
    return 2 * i + 1;
}

template<typename T>
void max_heapify(std::vector<T>& A, int h_size, size_t i)
{
    size_t l = left(i);
    size_t r = right(i);
    size_t largest = i;

    if (l <= h_size && A[l] > A[i])
        largest = l;

    if (r <= h_size && A[r] > A[largest])
        largest = r;

    if (largest != i)
    {
        std::swap(A[i], A[largest]);
        max_heapify(A, h_size, largest);
    }
}

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

template<typename T>
void build_max_heap(std::vector<T>& A, int h_size)
{
    for (size_t i = h_size / 2; i > 0; --i)
        max_heapify(A, h_size, i);
}

template<typename T>
void heap_sort(std::vector<T>& A)
{
    auto A_length = A.size() - 1;
    build_max_heap(A, A_length);
    for (auto i = A_length; i >= 2; --i)
    {
        std::swap(A[1], A[i]);
        max_heapify(A, --A_length, 1);
    }
}

int main()
{
    std::vector<int> v(101);
    std::iota(v.begin() + 1, v.end(), 1);
    std::shuffle(v.begin() + 1, v.end(), gen);
    heap_sort(v);
    for (auto x : v) {
        std::cout << x << ' ';
    }
}

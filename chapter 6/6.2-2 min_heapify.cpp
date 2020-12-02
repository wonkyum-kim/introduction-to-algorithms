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
void min_heapify(std::vector<T>& A, int h_size, size_t i)
{
    size_t l = left(i);
    size_t r = right(i);
    size_t smallest = 0;

    if (l <= h_size && A[l] < A[i]) {
        smallest = l;
    }
    else {
        smallest = i;
    }

    if (r <= h_size && A[r] < A[smallest]) {
        smallest = r;
    }

    if (smallest != i) {
        std::swap(A[i], A[smallest]);
        min_heapify(A, h_size, smallest);
    }
}

template<typename T>
void build_min_heap(std::vector<T>& A, int h_size)
{
    for (size_t i = h_size / 2; i > 0; --i)
        min_heapify(A, h_size, i);
}


int main()
{
    std::vector<int> v(11);
    std::iota(v.begin() + 1, v.end(), 1);
    std::shuffle(v.begin() + 1, v.end(), gen);
    build_min_heap(v, 10);
    for (auto i = 1; i <= 10; ++i) {
        std::cout << v[i] << ' ';
    }
}

#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#include<random>
#include<numeric>

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

template <typename T>
void max_heapify(std::vector<T>& A, size_t h_size, size_t i) {
    while (i <= h_size / 2) {
        size_t l = left(i);
        size_t r = right(i);
        size_t largest = i;
        if (l <= h_size && A[l] > A[i]) {
            largest = l;
        }
        if (r <= h_size && A[r] > A[largest]) {
            largest = r;
        }
        if (largest != i) {
            std::swap(A[i], A[largest]);
            i = largest;
        }
        else {
            return;
        }
    }
}

template<typename T>
void build_max_heap(std::vector<T>& A)
{
    size_t h_size = A.size() - 1;
    for (size_t i = h_size / 2; i > 0; --i)
        max_heapify(A, h_size, i);
}

int main()
{
    std::vector<int> v(11);
    std::iota(v.begin() + 1, v.end(), 1);
    std::shuffle(v.begin() + 1, v.end(), gen);
    build_max_heap(v);
    for (auto i = 1; i <= 10; ++i) {
        std::cout << v[i] << ' ';
    }
}

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

std::mt19937 gen(std::random_device {}());

std::vector<int> v;
int heap_size = 0;

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * (i + 1);
}

void min_heapify(std::vector<int>& A, int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l <= heap_size && A[l] < A[i]) {
        smallest = l;
    }

    if (r <= heap_size && A[r] < A[smallest]) {
        smallest = r;
    }

    if (smallest != i) {
        std::swap(A[i], A[smallest]);
        min_heapify(A, smallest);
    }
}

void build_min_heap(std::vector<int>& A)
{
    for (int i = heap_size / 2 - 1; i >= 0; --i) {
        min_heapify(A, i);
    }
}

int heap_extract_min(std::vector<int>& A)
{
    if (heap_size <= 0) {
        // error "heap underflow"
    }

    int min = A[0];
    A[0] = A[heap_size];
    heap_size--;
    min_heapify(A, 0);
    return min;
}

void heap_decrease_key(std::vector<int>& A, int i, int key)
{
    if (key > A[i]) {
        // error
    }

    A[i] = key;
    while (i > 0 && A[parent(i)] > A[i]) {
        std::swap(A[i], A[parent(i)]);
        i = parent(i);
    }
}

void min_heap_insert(std::vector<int>& A, int key)
{
    heap_size++;
    A.push_back(std::numeric_limits<int>::max());
    heap_decrease_key(A, heap_size, key);
}

int main()
{
    v = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
    heap_size = v.size() - 1;
    build_min_heap(v);
    min_heap_insert(v, -2);

    for (auto x : v) {
        std::cout << x << ' ';
    }
}

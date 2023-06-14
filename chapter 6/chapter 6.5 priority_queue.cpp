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

void max_heapify(std::vector<int>& A, int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l <= heap_size && A[l] > A[i]) {
        largest = l;
    }

    if (r <= heap_size && A[r] > A[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(A[i], A[largest]);
        max_heapify(A, largest);
    }
}

void build_max_heap(std::vector<int>& A)
{
    for (int i = heap_size / 2 - 1; i >= 0; --i) {
        max_heapify(A, i);
    }
}

void heap_sort(std::vector<int>& A)
{
    build_max_heap(A);
    for (int i = A.size() - 1; i >= 1; --i) {
        std::swap(A[0], A[i]);
        heap_size--;
        max_heapify(A, 0);
    }
}

int heap_maximum(std::vector<int>& A)
{
    return A[0];
}

int heap_extract_max(std::vector<int>& A)
{
    if (heap_size <= 0) {
        // error "heap underflow"
    }

    int max = A[0];
    A[0] = A[heap_size];
    heap_size--;
    max_heapify(A, 0);
    return max;
}

void heap_increase_key(std::vector<int>& A, int i, int key)
{
    if (key < A[i]) {
        // error
    }

    A[i] = key;
    while (i > 0 && A[parent(i)] < A[i]) {
        std::swap(A[i], A[parent(i)]);
        i = parent(i);
    }
}

void max_heap_insert(std::vector<int>& A, int key)
{
    heap_size++;
    A.push_back(std::numeric_limits<int>::min());
    heap_increase_key(A, heap_size, key);
}

int main()
{
    v = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
    heap_size = v.size() - 1;
    build_max_heap(v);
    max_heap_insert(v, 20);

    for (auto x : v) {
        std::cout << x << ' ';
    }
}

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

std::mt19937 gen(std::random_device {}());

std::vector<int> v(100);
int heap_size = v.size() - 1;

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

int main()
{
    std::iota(v.begin(), v.end(), 1);
    std::shuffle(v.begin(), v.end(), gen);

    heap_sort(v);

    for (auto x : v) {
        std::cout << x << ' ';
    }
}

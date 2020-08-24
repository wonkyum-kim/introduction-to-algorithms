#include<iostream>
#include<vector>
#include<algorithm>

// the index of root node is 1.
int parent(int i)
{
    return i / 2;
}

int left(int i)
{
    return 2 * i;
}

int right(int i)
{
    return 2 * i + 1;
}


template<typename T>
void max_heapify(std::vector<T>& A, const int h_size, const size_t i)
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
void build_max_heap(std::vector<T>& A, const int h_size)
{
    for (size_t i = h_size / 2; i > 0; --i)
        max_heapify(A, h_size, i);
}

template<typename T>
void heap_sort(std::vector<T>& A, int h_size)
{
    build_max_heap(A, h_size);
    for (size_t i = h_size; i > 1; --i)
    {
        std::swap(A[1], A[i]);
        max_heapify(A, --h_size, 1);
    }
}

int main()
{
    constexpr int dummy = 0;
    std::vector<int> A{ dummy,9,6,3,8,5,2,7,4,1,0 };
    heap_sort(A, A.size() - 1);     // A.size() - 1 is h_size
    for (int i = 1; i < A.size(); i++)
        std::cout << A[i] << " ";
    return 0;
}

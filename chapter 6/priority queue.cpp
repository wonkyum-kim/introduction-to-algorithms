#include<iostream>
#include<vector>
#include<algorithm>
#include<stdexcept>

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
void max_heapify(std::vector<T>& A, int h_size, size_t i)
{
    size_t l = left(i);
    size_t r = right(i);
    size_t largest = i;
    
    if(l <= h_size && A[l] > A[i])
        largest = l;
    
    if(r <= h_size && A[r] > A[largest])
        largest = r;
        
    if(largest != i)
    {
        std::swap(A[i], A[largest]);
        max_heapify(A,h_size,largest);
    }
}

template<typename T>
void build_max_heap(std::vector<T>& A, int h_size)
{
    for(size_t i = h_size / 2; i > 0; --i)
        max_heapify(A, h_size, i);
}

template<typename T>
void heap_sort(std::vector<T>& A, int h_size)
{
    build_max_heap(A, h_size);
    for(size_t i = h_size; i > 1; --i)
    {
        std::swap(A[1], A[i]);
        max_heapify(A,--h_size,1);
    }
}

template<typename T>
T heap_maximum(std::vector<T>& A)
{
    return A[1];
}

template<typename T>
T heap_extract_max(std::vector<T>& A, int h_size)
{
    if(h_size < 1)
        throw std::underflow_error("heap underflow");
    T max = A[1];
    A[1] = A[h_size - 1];
    max_heapify(A, h_size - 1, 1);
    return max;
}

template<typename T>
void heap_increase_key(std::vector<T>& A, size_t i, T key)
{
    if(key < A[i])
        throw std::runtime_error("new key is smaller than current key");
    A[i] = key;
    while(i > 1 && A[parent(i)] < A[i])
    {
        std::swap(A[i], A[parent(i)]);
        i = parent(i);
    }
}

template<typename T>
void max_heap_insert(std::vector<T>& A, int h_size, T key)
{
    h_size++;
    A.push_back(std::numeric_limits<T>::min());
    heap_increase_key(A, h_size, key);
}


int main()
{
    std::vector<int> A {0,9,6,3,8,5,2,7,4,1,0};
    std::make_heap(A.begin() + 1, A.end());
    max_heap_insert(A, A.size() - 1, 6);
    for(auto i = 1; i < A.size() - 1; ++i)
        std::cout << A[i] << ' ';
    return 0;
}


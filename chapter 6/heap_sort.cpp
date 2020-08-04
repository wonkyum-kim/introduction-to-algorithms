
// start !

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
        mx_hepify(A,h_size,largest);
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
    buld_max_heap(A, h_size);
    for(size_t i = h_size; i > 1; --i)
    {
        std::swap(A[1], A[i]);
        h_size -= 1;
        max_heapify(A,1);
    }
}


//*********************************************************************************************

#include<iostream>
#include<vector>

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
    return 2 * i + 2;
}

template<typename T>
void max_heapify(std::vector<T>& A, int n, int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l <= (n - 1) && A[l] > A[i])
        largest = l;
 
    if (r <= (n - 1) && A[r] > A[largest])
        largest = r;

    if (largest != i)
    {
        std::swap(A[i], A[largest]);
        max_heapify(A, n, largest);
    }
}

template<typename T>
void build_max_Heap(std::vector<T>& A, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        max_heapify(A, n, i);

}

template<typename T>
void heap_sort(std::vector<T>& A, int n)
{
    build_max_Heap(A, n);
    for (int i = n - 1; i > 0; i--)
    {
        std::swap(A[0], A[i]);
        max_heapify(A, --n, 0);
    }
}


int main()
{
    std::vector<int> A {9,6,3,8,5,2,7,4,1,0};
    heap_sort(A, A.size());
    for (int i = 0; i < A.size(); i++)
        std::cout << A[i] << " ";
    return 0;
}

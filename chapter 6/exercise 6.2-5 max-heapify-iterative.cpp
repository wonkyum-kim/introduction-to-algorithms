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
void max_heapify_iterative(std::vector<T>& A, int h_size)
{
    size_t i = 1;
    size_t l, r;
    size_t largest = i;
    while(i <= h_size / 2)
    {
        l = left(i);
        r = right(i);
        if(l <= h_size && A[l] > A[i])
            largest = l;
        if(r <= h_size && A[r] > A[largest])
            largest = r;
    }
    
    if(largest != i)
    {
        std::swap(A[largest], A[i]);
        i = largest;
    }
    else
        return;
}

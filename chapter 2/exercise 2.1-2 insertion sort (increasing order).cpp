#include <vector>
#include <iostream>

template <typename T>
void insertion-sort(std::vector<T>& A) 
{
    for (size_t j = 1; j < A.size(); ++j) 
    {
        T key = A[j];
        size_t i = j - 1;
        while (A[i] > key) 
        {
            A[i + 1] = A[i];
            if (i > 0)
                i--;
            else
                break;
        }
        if (i = 0)
            A[i] = key;
        else
            A[i + 1] = key;
    }
}

int main() 
{
    std::vector<int> v{ 5, 2, 3, 1, 4 };
    insertion_sort(v);
    for (auto n : v) 
        std::cout << n << ' ';
}

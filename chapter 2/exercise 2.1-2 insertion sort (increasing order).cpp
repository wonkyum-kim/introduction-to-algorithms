#include <vector>
#include <iostream>

template <typename T>
void insertion_sort(std::vector<T>& A)
{
    for (auto j = 1; j < A.size(); ++j)
    {
        T key = A[j];
        auto i = j - 1;
        while (i>=0 && A[i] > key)
        {
            A[i + 1] = A[i];
            i--;
        }
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

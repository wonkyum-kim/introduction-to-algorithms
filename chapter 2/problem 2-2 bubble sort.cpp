#include <algorithm>
#include <iostream>
#include <vector>

void bubble_sort(std::vector<int>& A)
{
    for (int i = 0; i < A.size() - 1; ++i) {
        for (int j = A.size() - 1; j > i; --j) {
            if (A[j] < A[j - 1]) {
                std::swap(A[j], A[j - 1]);
            }
        }
    }
}

int main()
{
    std::vector<int> A { 5, 2, 4, 1, 3 };
    bubble_sort(A);
    for (auto& x : A)
        std::cout << x << ' ';
}

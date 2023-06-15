#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

std::mt19937 gen(std::random_device {}());

int partition(std::vector<int>& A, int p, int r)
{
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; ++j) {
        if (A[j] <= x) {
            std::swap(A[++i], A[j]);
        }
    }
    std::swap(A[i + 1], A[r]);
    return ++i;
}

void quick_sort(std::vector<int>& A, int p, int r)
{
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

int main()
{
    std::vector<int> v(100);
    std::iota(v.begin(), v.end(), 1);
    std::shuffle(v.begin() + 1, v.end(), gen);
    quick_sort(v, 0, v.size() - 1);
    for (auto i = 0; i < 100; ++i) {
        std::cout << v[i] << ' ';
    }
}

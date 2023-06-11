#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

std::mt19937 gen(std::random_device {}());

void merge(std::vector<int>& A, const int p, const int q, const int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    std::vector<int> L;
    std::vector<int> R;

    for (auto i = 0; i < n1; ++i) {
        L.push_back(A[p + i]);
    }
    for (auto j = 0; j < n2; ++j) {
        R.push_back(A[q + j + 1]);
    }

    L.push_back(std::numeric_limits<int>::max());
    R.push_back(std::numeric_limits<int>::max());

    int i = 0;
    int j = 0;

    for (int k = p; k <= r; ++k) {
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        } else {
            A[k] = R[j++];
        }
    }
}

void merge_sort(std::vector<int>& A, const int p, const int r)
{
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main()
{
    // Generate a random input.
    std::vector<int> v(100);
    std::iota(v.begin(), v.end(), 1);
    std::shuffle(v.begin(), v.end(), gen);

    // Sort
    merge_sort(v, 0, v.size() - 1);

    for (auto x : v) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

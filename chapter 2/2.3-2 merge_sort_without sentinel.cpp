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

    for (int i = 0; i < n1; ++i) {
        L.push_back(A[p + i]);
    }
    for (int j = 0; j < n2; ++j) {
        R.push_back(A[q + j + 1]);
    }

    int i = 0;
    int j = 0;
    int k = p;

    while (i != n1 && j != n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        } else {
            A[k] = R[j++];
        }
        k++;
    }

    while (i == n1 && k <= r) {
        A[k++] = R[j];
        j++;
    }

    while (j == n2 && k <= r) {
        A[k++] = L[i];
        i++;
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

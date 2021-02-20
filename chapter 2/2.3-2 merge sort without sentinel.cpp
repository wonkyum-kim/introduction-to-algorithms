#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <numeric>
#include <utility>

std::mt19937 gen(std::random_device{}());

template<typename T>
void merge(std::vector<T>& A, const size_t p, const size_t q, const size_t r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    std::vector<T> L;
    std::vector<T> R;
    L.push_back(0);
    R.push_back(0);

    for (auto i = 1; i <= n1; ++i) {
        L.push_back(A[p + i - 1]);
    }
    for (auto j = 1; j <= n2; ++j) {
        R.push_back(A[q + j]);
    }

    size_t i = 1;
    size_t j = 1;
    size_t k = p;

    while (i != n1 + 1 && j != n2 + 1) {
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        }
        else {
            A[k] = R[j++];
        }
        k++;
    }

    if (i == n1 + 1) {
        for (auto m = j; m <= n2; ++m) {
            A[k++] = R[m];
        }
    }

    if (j == n2 + 1) {
        for (auto m = i; m <= n1; ++m) {
            A[k++] = L[m];
        }
    }
}

template<typename T>
void merge_sort(std::vector<T>& A, const size_t p, const size_t r)
{
    if (p < r) {
        size_t q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main()
{
	constexpr int SIZE{ 100 };
	std::vector<int> v(SIZE + 1);
	std::iota(v.begin() + 1, v.end(), 1);
	std::shuffle(v.begin() + 1, v.end(), gen);
    	merge_sort<int>(v, 1, v.size() - 1);
	for (auto x : v) {
		std::cout << x << ' ';
	}
}

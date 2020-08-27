#include <vector>
#include <iostream>
#include <limits>

// combine
template<typename T>
void merge(std::vector<T>& A, const size_t p, const size_t q, const size_t r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    std::vector<T> L;
    std::vector<T> R;
    L.push_back(0);
    R.push_back(0);

    for (auto i = 1; i <= n1; ++i) 
        L.push_back(A[p + i - 1]);
    for (auto j = 1; j <= n2; ++j)
        R.push_back(A[q + j]);

    L.push_back(std::numeric_limits<int>::max());
    R.push_back(std::numeric_limits<int>::max());
    
    size_t i = 1;
    size_t j = 1;

    for (auto k = p; k <= r; ++k) {
        if (L[i] <= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }

}

// devide and conquer
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
    std::vector<int> A{ 2, 1, 3, 5, 4 };
    merge_sort(A, 0, A.size() - 1);
    for (auto& x : A)
        std::cout << x << ' ';
}
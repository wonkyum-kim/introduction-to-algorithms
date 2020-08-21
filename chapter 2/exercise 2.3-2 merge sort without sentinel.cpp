/* first version */

#include <vector>
#include <iostream>

// combine
template<typename T>
void merge(std::vector<T>& A, const size_t p, const size_t q, const size_t r)
{
    size_t n1 = q - p + 1;  // L.size() 
    size_t n2 = r - q;      // R.size() 
    std::vector<T> L;
    std::vector<T> R;

    for(auto i = 0; i < n1; ++i)
        L.push_back(A[p + i]);
    for(auto j = 0; j < n2; ++j)
        R.push_back(A[q + j + 1]);
    
    size_t i = 0;
    size_t j = 0;
    
    for(auto k = p; k <= r; ++k) {
        if(L[i] <= R[j]) {
            A[k] = L[i++];
            if(i == n1) {
                A.erase(A.begin() + k + 1, A.end());
                A.insert(A.end(), R.begin() + j, R.end());
                break;
            }
        } else {
            A[k] = R[j++];
            if(j == n2) {
                A.erase(A.begin() + k + 1, A.end());
                A.insert(A.end(), L.begin() + i, L.end());
                break;
            }
        }
    }
}

// devide and conquer
template<typename T>
void merge_sort(std::vector<T>& A, const size_t p, const size_t r)
{
    if(p < r) {
        size_t q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main()
{
    std::vector<int> A{ 5,2,4,1,3 };
	merge_sort(A, 0, A.size() - 1);
	for (auto& x : A)
		std::cout << x << ' ';
}

/****************************************************************/

/* second version */

#include <vector>
#include <iostream>

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
    
    size_t i = 1;
    size_t j = 1;
    size_t k = p;

    while (i != n1 + 1 && j != n2 + 1) {
        if (L[i] <= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
        k++;
    }

    if (i == n1 + 1) {
        for (auto m = j; m <= n2; ++m) 
            A[k++] = R[m];
    }

    if (j == n2 + 1) {
        for (auto m = i; m <= n1; ++m)
            A[k++] = L[m];
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

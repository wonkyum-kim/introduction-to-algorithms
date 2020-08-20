#include <vector>
#include <iostream>
#include <limits>

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
        
    L.push_back(std::numeric_limits<T>::max());     // sentinel
    R.push_back(std::numeric_limits<T>::max());     // sentinel
    
    size_t i = 0;
    size_t j = 0;
    
    for(auto k = p; k <= r; ++k) {
        if(L[i] <= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
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

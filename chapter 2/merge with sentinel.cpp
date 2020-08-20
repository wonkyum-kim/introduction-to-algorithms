#include <vector>
#include <iostream>
#include <limits>

// combine
template<typename T>
void merge(std::vector<T>& A, size_t p, size_t q, size_t r)
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

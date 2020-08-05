#include<iostream>
#include<algorithm>
#include<vector>

template<typename T>
T minimum(const std::vector<T>& A)
{
    T min = A[0];
    for(auto i = 0; i < A.size(); ++i)
        min = std::min(min, A[i]);
    return min;
}

template<typename T>
T maximum(const std::vector<T>& A)
{
    T max = A[0];
    for(auto i = 0; i < A.size(); ++i)
        max = std::max(max, A[i]);
    return max;
}

int main()
{
    std::vector<int> A {5,3,2,1,4};
    std::cout << minimum(A) << ' ' << maximum(A);
}
